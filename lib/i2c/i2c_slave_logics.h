/**************************************************\
 * I2C Slave side Library for RoboCup
 *
 * Device   : dsPIC33FJ32GP202,dsPIC33FJ12MC202
 *
 * Author   : Shota Aoki
 *
 * Compiler : XC16 (v1.20)
 *
 * Reference Page :
 * h ttp://www.ys-labo.com/pic/pic%20chips/pic%20chips%20contets/2009/0911%20I2C.html
 *
\**************************************************/

/**************************************************\
 *
 * 導入方法
 * 1. "i2c_slave_logics.c"をコンパイル対象のファイルに入れる
 * 2. "i2c_slave_logics.h"のI2C_DATA_SIZEとi2cDataTypeを任意に変更する
 *
 * 使用方法
 * 1. 初期化
 *  1.1 使用関数
 *      i2cSlaveInitialize(unsigned char address)
 *          i2cSlave初期設定関数
 *          address: 設定アドレス 0x08 ~ 0x77 のみ使用可能
 *
 *  1.2 返り値
 *      i2cSlaveInitialize(unsigned char address)
 *          1: addressが規格外の値
 *          2: 設定後のアイドル時間が長い
 *          0: 正常終了
 *
 *  1.3 使用例
 *      i2cSlaveInitialize(0x08);
 *
 * 2. データ取得
 *  2.1 使用関数
 *      i2cPullData(unsigned char num, i2cDataType *data)
 *          データ取り出し関数
 *          num: 受信ストレージから取り出すデータ数 1以上　上限はfifoのデータ保存数に依存
 *          *data: データ格納ポインタ　配列を使うと捗る
 *          データを取り出すと、そのデータはストレージから無くなる
 *
 *      i2cClearReceivedStorage(void)
 *          受信ストレージクリア関数
 *
 *      i2cGetState(void)
 *          割り込み状態取得関数
 *
 *  2.2 返り値
 *      i2cPullData(unsigned char num, i2cDataType *data)
 *          1~: FIFOが空　何個目のデータが取れなかったのかを返す
 *          0 : データ取得完了
 *
 *      i2cClearReceivedStorage(void)
 *          0 : 正常終了
 *
 *      i2cGetState(void)
 *          MISSED_RECEIVING_DATA   : アドレス・データ受信ミス
 *          CONTINUE_IDLE           : アドレス・データ受信後のアイドルから復帰しない
 *          RECEIVED_ADD            : アドレス受信完了
 *          R_STORAGE_OVERFLOWED    : 受信オーバーフロー　受信ストレージがいっぱい
 *          RECEIVED_DATA           : データ受信完了
 *          BEFORE_INTERRUPT        : 初期値 割り込みに入る前

 *  2.3 仕様例
 *      i2cDataType data[4];
 *
 *      i2cPullData(2,data);
 *
 *
 * 3. データ送信
 *  3.1 使用関数
 *      i2cPushData(i2cDataType data)
 *          データ押し出し関数
 *          data: 送信ストレージに格納するデータ
 *
 *      i2cClearTransmissionStorage(void)
 *          送信ストレージクリア関数
 *
 *      i2cGetState(void)
 *          割り込み状態取得関数
 *
 *  3.2 返り値
 *      i2cPushData(i2cDataType data)
 *          1: FIFOがオーバーフロー 送信ストレージがいっぱい
 *          0: 正常終了
 *
 *      i2cClearTransmissionStorage(void)
 *          0: 正常終了
 *
 *      i2cGetState(void)
 *          T_STORAGE_IS_EMPTY      : 送信ストレージが空
 *          COMPLETE_TRANSMISSION   : バッファに書き込み完了
 *          RECEIVED_NACK           : マスターからNACKを受信
 *          BEFORE_INTERRUPT        : 初期値 割り込みに入る前
 *
 *  3.3 使用例
 *      i2cDataType data = 10;
 *
 *      i2cPushData(data);
 *
 * 4. その他の関数
 *  4.1 ストレージに入っているデータ数を取得
 *      i2cGetStorageDataNum(unsigned char choices)
 *      引数:
 *          choices :0 送信ストレージをチェック
 *                  :1 受信ストレージをチェック
 *      返り値:
 *          0~: ストレージに入っているデータ数
 *          99: 引数が0or1でない
 *
 *  4.2 送信ストレージが空のときに送信するエラー値を設定
 *      i2cSetErrValue(i2cDataType errValue)
 *      引数:
 *          errValue    送信するエラー値
 *      返り値: 0
 *
 *
\**************************************************/


#ifndef	__I2C_SLAVE_LOGICS_H
#define	__I2C_SLAVE_LOGICS_H

/* デバイス分類 */
#if	defined	__dsPIC33FJ32GP202__
#define	PORT_SDA	_TRISB9
#define	PORT_SCL	_TRISB8

#elif	defined	__dsPIC33FJ128MC802__
#define	PORT_SDA	_TRISB9
#define	PORT_SCL	_TRISB8

#else
#error	This device is NOT supported in "I2C for RoboCup" library.

#endif

/* I2C_DATA_SIZE
 * 送信ストレージと、受信ストレージのおおきさ
 * 必ず2のべき乗にすること(2,4,8,16...)
 */
#define	I2C_DATA_SIZE   32
typedef	signed char     i2cDataType; /* ストレージに格納するデータ型 */

//typedef enum I2CSTATE{/*I2C割り込みの状態*/
//    BEFORE_INTERRUPT,       //初期値 割り込みに入る前
//    MISSED_RECEIVING_DATA,  //アドレス・データ受信ミス
//    CONTINUE_IDLE,          //アドレス・データ受信後のアイドルから復帰しない
//    RECEIVED_ADD,           //アドレス受信完了
//    R_STORAGE_OVERFLOWED,   //受信オーバーフロー　受信ストレージがいっぱい
//    RECEIVED_DATA,          //データ受信完了
//    T_STORAGE_IS_EMPTY,     //送信ストレージが空 エラー値をセット
//    SET_DATA,               //送信データをバッファにセット
//    RECEIVED_NACK           //マスターからNACKを受信
//}I2CSTATE;


extern unsigned char i2cSlaveInitialize(unsigned char address);

extern unsigned char i2cPullData(unsigned char num, i2cDataType *data);

extern unsigned char i2cPushData(i2cDataType data);

extern unsigned char i2cClearTransmissionStorage(void);

extern unsigned char i2cClearReceivedStorage(void);

//extern I2CSTATE i2cGetState(void);

extern unsigned char i2cGetStorageDataNum(unsigned char choices);

extern unsigned char i2cSetErrValue(i2cDataType errValue);

#endif

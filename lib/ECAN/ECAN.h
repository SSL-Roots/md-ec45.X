/* 
 * File:   ECAN.h
 * Author: Tomoaki YOSHIDA
 *
 * Created on 2015/05/16, 17:30
 */

#ifndef ECAN_H
#define	ECAN_H


//#ifndef defined(NUM_OF_ECAN_BUFS)
//#define NUM_OF_ECAN_BUFS    4
////任意で決めたい場合はヘッダーのincludeの前に定義付けすること
//#endif
//
//#ifndef defined(ECAN_SID_F0)
//#define ECAN_SID_F0 0x1AA
//#endif

#define NUM_OF_ECAN_BUFS    4
#define ECAN_SID_F0 0x1AA
//#define ECAN_SID_F0 0x1cB

typedef unsigned int ECAN1MSGBUF[NUM_OF_ECAN_BUFS][8];
extern  ECAN1MSGBUF ecan1msgBuf __attribute__( (space(dma), aligned(NUM_OF_ECAN_BUFS*32))); //DMA領域に，NUM_OF_ECAN_BUFS*16バイトを配置
//ECAN1MSGBUF ecan1msgBuf __attribute__( (space(dma), aligned(NUM_OF_ECAN_BUFS*16)));
/****************ECAN message buffers*****************/
typedef union EcanMsgBuf0{
    unsigned int ecanmsg0;
    struct {
        unsigned IDE    :1;
        unsigned SRR    :1;
        unsigned SID    :11;
        unsigned        :3;
    };
}EcanMsgBuf0;
typedef union EcanMsgBuf1{
    unsigned int ecanmsg1;
    struct {
        unsigned EID_6_17   : 11;
        unsigned        :5;
    };
}EcanMsgBuf1;
typedef union EcanMsgBuf2{
    unsigned int ecanmsg2;
    struct {
        unsigned DLC    :4;
        unsigned RB0    :1;
        unsigned        :3;
        unsigned RB1    :1;
        unsigned RTR    :1;
        unsigned EID_0_5    :6;
    };
}EcanMsgBuf2;
typedef union EcanMsgBuf36{
    unsigned int ecanmsg36[4];
    char ecandata[8];
}EcanMsgBuf36;

typedef union EcanMessageBuffers{
    struct{
        EcanMsgBuf0     m_msg0;
        EcanMsgBuf1     m_msg1;
        EcanMsgBuf2     m_msg2;
        EcanMsgBuf36    m_msg36;
    };
    unsigned int ecanmsg[7];
}EcanMessageBuffers;

#define	CAN_DATA_SIZE   48
typedef	signed char     CANDataType; /* ストレージに格納するデータ型 */

typedef enum CANSTATE{/*I2C割り込みの状態*/
    BEFORE_INTERRUPT,       //初期値 割り込みに入る前
    MISSED_RECEIVING_DATA,  //アドレス・データ受信ミス
    CONTINUE_IDLE,          //アドレス・データ受信後のアイドルから復帰しない
    RECEIVED_ADD,           //アドレス受信完了
    R_STORAGE_OVERFLOWED,   //受信オーバーフロー　受信ストレージがいっぱい
    RECEIVED_DATA,          //データ受信完了
    T_STORAGE_IS_EMPTY,     //送信ストレージが空 エラー値をセット
    SET_DATA,               //送信データをバッファにセット
    RECEIVED_NACK           //マスターからNACKを受信
}CANSTATE;

void setEcanMessage(EcanMessageBuffers *buffer, int sid, long eid, unsigned int is_eid, unsigned int is_remote, unsigned int data_length, unsigned char *send_data);

unsigned char CANPullData(unsigned char num, CANDataType *data);

Order getOrder(void);

void configEcanFilter(unsigned int filter_num, unsigned int buffer, unsigned int is_eid_enable, unsigned int sid, unsigned long eid);

void initilizeCanConfiguration(void);
void initilizeCanDmaConfiguration(unsigned int buf_add);
/*******************CANxのボーレート，時間関係の初期設定********************
 * CANxInitialize(unsigned int config1, unsigned int config2)
 * CANモジュールの初期設定（x=1,2)
 *
 * config1:CiCFG1の設定(ボーレートのせってい）
 *      TQ（Time Quanta)の何倍がSynchronization Jump Widthかを設定
 *          CAN_SYNC_JUMP_WIDTH1    0x003F
 *          CAN_SYNC_JUMP_WIDTH2    0x007F
 *          CAN_SYNC_JUMP_WIDTH3    0x00BF
 *          CAN_SYNC_JUMP_WIDTH4    0x00FF
 *      ボーレートの設定(TQの設定)
 *          CAN_BAUD_PRE_SCALE(x)   x=1～64
 *
 * config2:CiCFG2の設定
 *      スリープからの復帰用フィルタについて
 *          CAN_WAKEUP_BY_FILTER_EN     0x47FF
 *          CAN_WAKEUP_BY_FILTER_DIS    0x07FF
 *      Propagation Segment長の設定
 *          CAN_PROPAGATIONTIME_SEG_TQ(x)
 *      Phase Segment 1長の設定
 *          CAN_PHASE_SEG1_TQ(x)
 *      Phase Segment 2長の設定
 *          CAN_PHASE_SEG2_TQ(x)
 *      Phase Segment 2のモード設定
 *          CAN_SEG2_FREE_PROG          0x47FF
 *          CAN_SEG2_TIME_LIMIT_SET     0x477F
 *      バスのサンプリング
 *          CAN_SAMPLE3TIMES            0x47FF
 *          CAN_SAMPLE1TIME             0x47BF
 * example
    CAN1Initialize(CAN_SYNC_JUMP_WIDTH2 & CAN_BAUD_PRE_SCALE(2),
                    CAN_WAKEUP_BY_FILTER_DIS & CAN_PHASE_SEG2_TQ(5) & CAN_PHASE_SEG1_TQ(4) & CAN_PROPAGATIONTIME_SEG_TQ(4) & CAN_SEG2_FREE_PROG & CAN_SAMPLE1TIME);
 ***************************************************/

/*******************CANxのバッファ設定********************
 * CANxFIFOCon(unsigned int fifo_val)
 * CANのバッファ設定
 * 
 * fifo_val:CxFCTRLの設定
 *      バッファの数
 *          CAN_DMA_BUF_SIZE_32
 *          CAN_DMA_BUF_SIZE_24
 *          CAN_DMA_BUF_SIZE_16
 *          CAN_DMA_BUF_SIZE_12
 *          CAN_DMA_BUF_SIZE_8
 *          CAN_DMA_BUF_SIZE_6
 *          CAN_DMA_BUF_SIZE_4
 *      FIFOのスタート
 *          CAN_FIFO_AREA_RB31
 *          CAN_FIFO_AREA_RB30
 *          ....
 *          ....
 *          CAN_FIFO_AREA_RB8
 *          CAN_FIFO_AREA_TRB7
 *          ....
 *          ....
 *          CAN_FIFO_AREA_TRB0
 * example
    CAN1FIFOCon (CAN_DMA_BUF_SIZE_32 & CAN_FIFO_AREA_RB9);
 ***************************************************/

/*******************CANxモジュールの初期設定********************
 * CANxSetOperationMode(unsigned int config1, unsigned int config2)
 * CANモジュールの初期設定（x=1,2)
 *
 * config1:CiCTRL1の設定
 *      アイドル時の動作の継続
 *          CAN_IDLE_CON                0xEFFF
 *          CAN_IDLE_STOP               0xCFFF
 *      CANモジュールのモード設定
 *          CAN_REQ_OPERMODE_NOR        0xE8FF  ノーマルモード
 *          CAN_REQ_OPERMODE_DIS        0xE9FF  disable
 *          CAN_REQ_OPERMODE_LOOPBK     0xEAFF  loopback
 *          CAN_REQ_OPERMODE_LISTENONLY 0xEBFF
 *          CAN_REQ_OPERMODE_CONFIG     0xECFF
 *          CAN_REQ_OPERMODE_LISTENALL  0xEFFF
 *      キャプチャの設定
 *          CAN_CAPTURE_ENABLE
 *          CAN_CAPTURE_DISABLE
 *      SFRの設定
 *          CAN_SFR_FILTER_WIN
 *          CAN_SFR_BUFFER_WIN
 * config2:CiCTRL2の設定
 *      比較する部分について
 *          CAN_DO_NOT_CMP_DATABYTES
 *          CAN_CMP_DATABYTE1_BIT7_EID0
 *          CAN_CMP_DATABYTE1_BIT6_EID1
 *          CAN_CMP_DATABYTE1_BIT5_EID2
 *          CAN_CMP_DATABYTE1_BIT4_EID3
 *          CAN_CMP_DATABYTE1_BIT3_EID4
 *          CAN_CMP_DATABYTE1_BIT2_EID5
 *          CAN_CMP_DATABYTE1_BIT1_EID6
 *          CAN_CMP_DATABYTE1_BIT0_EID7
 *          CAN_CMP_DATABYTE2_BIT7_EID8
 *          CAN_CMP_DATABYTE2_BIT6_EID9
 *          CAN_CMP_DATABYTE2_BIT5_EID10
 *          CAN_CMP_DATABYTE2_BIT4_EID11
 *          CAN_CMP_DATABYTE2_BIT3_EID12
 *          CAN_CMP_DATABYTE2_BIT2_EID13
 *          CAN_CMP_DATABYTE2_BIT1_EID14
 *          CAN_CMP_DATABYTE2_BIT0_EID15
 *          CAN_CMP_DATABYTE3_BIT7_EID16
 *          CAN_CMP_DATABYTE3_BIT6_EID17
 * example
    CAN1SetOperationMode(CAN_IDLE_STOP & CAN_REQ_OPERMODE_DIS &CAN_CAPTURE_DISABLE & CAN_SFR_FILTER_WIN, CAN_DO_NOT_CMP_DATABYTES);
 *
 * CANxSetOperationModeNoWaitは通信を速攻で中断してモード変更などをする
 ***************************************************/

/*******************CANxのID設定********************
 * CAN1SetFilter(char filter_no, unsigned int sid, unsigned long eid)
 * sID(standard)とeID(enhanced)の設定
 *
 * filter_no:設定するフィルターの番号
 *      フィルターの番号を0-14で渡す
 * sid:IDを設定
 *      SIDの設定
 *          CAN_FILTER_SID(x)       x:16bit
 *      EIDを使うか
 *          CAN_RX_EID_EN
 *          CAN_RX_EID_DIS
 * eid:EIDの設定
 *      EIDの値
 *          CAN_FILTER_EID(x)       x:32bit
 *
 * example
    CAN1SetFilter(1, CAN_FILTER_SID(7) & CAN_RX_EID_EN, CAN_FILTER_EID(3));
 ***************************************************/

/*******************フィルタの許可********************
 * CANxEnableFilter(char filter_number)
 * 使用するフィルタの設定
 *
 * filter_number:使うフィルターの番号
 *      フィルターの番号を0-14で渡す
 * example
    CAN1EnableFilter(10);
 ***************************************************/

/*******************CANxのマスク設定********************
 * CANxSetMask(char mask_no, unsigned int sid, unsigned long eid)
 * マスクの設定
 *
 * mask_no:使うマスクの番号
 *      マスクの番号を0-2で設定
 * sid:CiRXMnSIDに渡す値を決める
 *      SIDの設定
 *          CAN_MASK_SID(x)         x:16bit
 *     フィルタで特定されたメッセージ
 *          CAN_MATCH_FILTER_TYPE
 *          CAN_IGNORE_FILTER_TYPE
 * eid:CiRXMnSID<1:0> bits and the CiRXMnEID
 *      EIDの値
 *          CAN_MASK_EID(x)         x:32bit
 *
 * example
    CAN1SetMask(1, CAN_MASK_SID(7) & CAN_MATCH_FILTER_TYPE, CAN_MASK_EID(3));
 ***************************************************/

/*******************CANxでフィルターが使うマスクの設定********************
 * CAN1SetMaskSource(unsigned int mask_val1, unsigned int mask_val2)
 * 各フィルタで使用するマスクを決定
 *
 * mask_val1:フィルタ0-7の設定
 *      フィルタ0で使用するマスクの番号を0-2で設定
 *          CAN_MASK_FILTER0_NO_MASK
 *          CAN_MASK_FILTER0_MASK2
 *          CAN_MASK_FILTER0_MASK1
 *          CAN_MASK_FILTER0_MASK0
 *      フィルタ1で使用するマスクの番号を0-2で設定
 *          CAN_MASK_FILTER1_NO_MASK
 *          CAN_MASK_FILTER1_MASK2
 *          CAN_MASK_FILTER1_MASK1
 *          CAN_MASK_FILTER1_MASK0
 *      ...
 *      フィルタ7で使用するマスクの番号を0-2で設定
 *          CAN_MASK_FILTER7_NO_MASK
 *          CAN_MASK_FILTER7_MASK2
 *          CAN_MASK_FILTER7_MASK1
 *          CAN_MASK_FILTER7_MASK0
 * mask_val2:フィルタ8-15の設定
 *      フィルタ8で使用するマスクの番号を0-2で設定
 *          CAN_MASK_FILTER8_NO_MASK
 *          CAN_MASK_FILTER8_MASK2
 *          CAN_MASK_FILTER8_MASK1
 *          CAN_MASK_FILTER8_MASK0
 *      フィルタ9で使用するマスクの番号を0-2で設定
 *          CAN_MASK_FILTER9_NO_MASK
 *          CAN_MASK_FILTER9_MASK2
 *          CAN_MASK_FILTER9_MASK1
 *          CAN_MASK_FILTER1_MASK0
 *      ...
 *      フィルタ15で使用するマスクの番号を0-2で設定
 *          CAN_MASK_FILTER15_NO_MASK
 *          CAN_MASK_FILTER15_MASK2
 *          CAN_MASK_FILTER15_MASK1
 *          CAN_MASK_FILTER15_MASK0
 *
 ***************************************************/

/*******************CANxでフィルターに引っかかったデータの格納先********************
 * CANxSetBUFPNT1 (unsigned int pointer_value)  Filter0-3
 * CANxSetBUFPNT2 (unsigned int pointer_value)  Filter4-7
 * CANxSetBUFPNT3 (unsigned int pointer_value)  Filter8-11
 * CANxSetBUFPNT4 (unsigned int pointer_value)  Filter12-15
 * 
 * pointer_velue:格納するバッファの指定
 *      指定するバッファ i=0-15
 *          CAN_FILTERi_RX_BUFFER0
 *          CAN_FILTERi_RX_BUFFER1
 *          CAN_FILTERi_RX_BUFFER2
 *          CAN_FILTERi_RX_BUFFER3
 *          CAN_FILTERi_RX_BUFFER4
 *          CAN_FILTERi_RX_BUFFER5
 *          CAN_FILTERi_RX_BUFFER6
 *          CAN_FILTERi_RX_BUFFER7
 *          CAN_FILTERi_RX_BUFFER8
 *          CAN_FILTERi_RX_BUFFER9
 *          CAN_FILTERi_RX_BUFFER10
 *          CAN_FILTERi_RX_BUFFER11
 *          CAN_FILTERi_RX_BUFFER12
 *          CAN_FILTERi_RX_BUFFER13
 *          CAN_FILTERi_RX_BUFFER14
 *          CAN_FILTERi_RX_BUFFER_FIFO
 ***************************************************/

/*******************CANxのバッファのTX/RXの設定********************
 * CANxSetTXRXMode(char buffno, unsigned int config)
 * 
 * buffno:設定するバッファの番号（0－7）
 * config:CxTRmnCONの設定
 *      バッファm,nのTX/RXの設定(i=m,n)
 *          CAN_BUFFERi_IS_TX
 *          CAN_BUFFERi_IS_RX
 *      送信リクエストのセット，クリア
 *          CAN_SEND_REQUEST_BUFFERi    セット
 *          CAN_ABORT_REQUEST_BUFFERi   クリア
 *      RTR（リモート送信）の自動処理許可
 *          CAN_AUTOREMOTE_ENABLE_BUFFERi
 *          CAN_AUTOREMOTE_DISABLE_BUFFERi
 *      送信優先度
 *          CAN_TX_HIGH_PRI_BUFFERi
 *          CAN_TX_HIGHINTM_PRI_BUFFERi
 *          CAN_TX_LOWINTM_PRI_BUFFERi
 *          CAN_TX_LOW_PRI_BUFFERi
 ***************************************************/    
#endif	/* ECAN_H */


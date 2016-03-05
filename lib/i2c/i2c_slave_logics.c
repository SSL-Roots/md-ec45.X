///**************************************************\
// * I2C Slave side Library for RoboCup
// *
// * Device   : dsPIC33FJ32GP202,dsPIC33FJ12MC202
// *
// * Author   : Shota Aoki
// *
// * Compiler : XC16 (v1.20)
// *
// * Reference Page :
// * http://www.ys-labo.com/pic/pic%20chips/pic%20chips%20contets/2009/0911%20I2C.html
// *
//\**************************************************/
//
//#include <xc.h>
//#include <i2c.h>
//#include <timer.h>
////#include <stdbool.h>
//#include "i2c_slave_logics.h"
//
//
///*************************fifo.hから抜粋*************************/
//typedef struct {
//    i2cDataType	data[I2C_DATA_SIZE];
//    unsigned char head_write, head_read;
//}I2CFIFO;
//
//
//typedef enum I2CErrAddFIFO {  /* addFIFO()の戻り値 */
//    I2C_ADD_SUCCESS,
//    I2C_FIFO_OVERFLOWED
//} I2CErrAddFIFO;
//
//
//typedef enum I2CErrGetFIFO { /* getFIFO()の戻り値 */
//    I2C_GET_SUCCESS,
//    I2C_FIFO_EMPTY
//} I2CErrGetFIFO;
//
//
//typedef	enum I2CErrGetAllFIFO{ /*getAllFIFO()の戻り値 */
//    I2C_SUCCESS_GET_ALL_FIFO,
//    I2C_BUFFER_SIZE_IS_NOT_ENOUGH
//} I2CErrGetAllFIFO;
//
//static void initializeFIFO( I2CFIFO *p_fifo );
//static I2CErrAddFIFO addFIFO( I2CFIFO *p_fifo, i2cDataType data );
//static I2CErrGetFIFO getFIFO( I2CFIFO *p_fifo, i2cDataType *buf );
//static void clearFIFO( I2CFIFO *p_fifo );
//static unsigned char getFillFIFO(I2CFIFO *p_fifo);
////static bool isEmptyFIFO(I2CFIFO *p_fifo);
///*************************fifo.hから抜粋*************************/
//
//
//
//
//static I2CFIFO receiveStorage;
//static I2CFIFO transmitStorage;
//
//static I2CSTATE state = BEFORE_INTERRUPT;
//static unsigned char waitIdleTime(void);
//static unsigned char waitRBF(void);
//
//static i2cDataType I2C_errValue = 0;   //送信ストレージにデータが無いときの送信値
//
//unsigned char i2cSlaveInitialize(unsigned char address){
//
//    unsigned int I2Cconfig1 = (I2C1_ON & I2C1_IDLE_CON & I2C1_CLK_HLD & I2C1_IPMI_DIS & I2C1_7BIT_ADD & I2C1_SLW_EN & I2C1_SM_DIS &I2C1_GCALL_DIS & I2C1_STR_EN & I2C1_NACK & I2C1_ACK_DIS & I2C1_RCV_DIS & I2C1_STOP_DIS & I2C1_RESTART_DIS);
//    unsigned int baudrate;
//
//    /*FIFOの初期化*/
//    initializeFIFO(&receiveStorage);
//    initializeFIFO(&transmitStorage);
//
//    PORT_SDA	= 1;
//    PORT_SCL	= 1;
//
//    if(address < 0x08 || address > 0x77){
//        return 1;
//    }
//
//    baudrate = 63;//random value
//    OpenI2C1(I2Cconfig1,baudrate);
//
//    I2C1ADD = address;
//
//    ConfigIntI2C1(MI2C1_INT_OFF & SI2C1_INT_ON & SI2C1_INT_PRI_7);
//    EnableIntSI2C1;
//
//    if(waitIdleTime()){
//        /*アイドル時間が長過ぎ*/
//        return 2;
//    }
//
//    return 0;
//
//}
//
//unsigned char i2cPullData(unsigned char num, i2cDataType *data){
//    int i;
//
//    for(i=0;i<num;i++){
//        if(getFIFO(&receiveStorage, &data[i]) == I2C_FIFO_EMPTY){
//            /*FIFOが空*/
//            return i+1; //何個目のデータが取れなかったのかを返す
//        }
//    }
//
//    return 0;
//}
//
//unsigned char i2cPushData(i2cDataType data){
//    if(addFIFO(&transmitStorage, data) == I2C_FIFO_OVERFLOWED){
//        /*FIFOオーバーフロー*/
//        return 1;
//    }
//    return 0;
//}
//
//unsigned char i2cClearTransmissionStorage(void){
//    /*送信ストレージを初期化*/
//    clearFIFO(&transmitStorage);
//    return 0;
//}
//
//unsigned char i2cClearReceivedStorage(void){
//    /*受信ストレージを初期化*/
//    clearFIFO(&receiveStorage);
//    return 0;
//}
//
//
//I2CSTATE i2cGetState(void){
//    return state;
//}
//
//unsigned char i2cGetStorageDataNum(unsigned char choices){
//    if(choices == 0){
//        /*送信ストレージ*/
//        return getFillFIFO(&transmitStorage);
//    }else if(choices == 1){
//        /*受信ストレージ*/
//        return getFillFIFO(&receiveStorage);
//    }
//    return 99;
//}
//
//unsigned char i2cSetErrValue(i2cDataType errValue){
//    I2C_errValue = errValue;
//    return 0;
//}
//
//void _ISR _SI2C1Interrupt(void){
//    i2cDataType buffer;
//
//    _SI2C1IF = 0;   //割り込みフラグ解除
//    if(!_R_W){
//        /*マスター送信モード*/
//
//        /*データ受信*/
//        if(waitRBF()){
//            /*データ受信ミス*/
//            _SCLREL = 1;    //クロック解放
//            state = MISSED_RECEIVING_DATA;
//            return;
//        }
//        _I2COV = 0; //エラークリア
//        buffer = I2C1RCV;
//
//        _SCLREL = 1;    //クロック解放
//
//        if(waitIdleTime()){
//            /*アイドル時間が長過ぎ*/
//            state = CONTINUE_IDLE;
//            return;
//        }
//
//        if(!_D_A){
//            /*アドレス受信*/
//            state = RECEIVED_ADD;
//            return;
//        }else{
//            /*データ受信*/
//            if(addFIFO(&receiveStorage, buffer) == I2C_FIFO_OVERFLOWED){
//                /*受信データオーバーフロー*/
//                state = R_STORAGE_OVERFLOWED;
//                return;
//            }
//            /*データ受信完了*/
//            state = RECEIVED_DATA;
//            return;
//        }
//    }else{
//        /*マスター受信モード*/
//        if(!_D_A || !_ACKSTAT){
//            /*アドレス受信 or ACK受信*/
//            if(getFIFO(&transmitStorage, &buffer) == I2C_FIFO_EMPTY){
//                /*送信データが空*/
//                state = T_STORAGE_IS_EMPTY;
//                I2C1TRN = I2C_errValue; //エラー値を返す
//                _SCLREL = 1;    //クロック解放
//                return;
//            }
//            I2C1TRN = buffer;   //データ送信
//            _SCLREL = 1;    //クロック解放
//            
//            state = SET_DATA;
//            return;
//        }else{
//            state = RECEIVED_NACK;
//            return;
//        }
//        
//    }
//}
//
//
//static unsigned char waitIdleTime(void){
//    /*アイドル待ち*/
//    const unsigned int TIMEOUT = 10000;
//    unsigned int i;
//
//    for(i=0; i<TIMEOUT; i++){
//        if(!_SEN && !_PEN && !_RCEN && !_RSEN && !_ACKEN && !_TRSTAT){
//            break;
//        }
//    }
//    if(i == TIMEOUT){
//        return 1;
//    }
//    return 0;
//}
//
//static unsigned char waitRBF(void){
//    /*受信待ち*/
//    const unsigned int TIMEOUT = 10000;
//    unsigned int i;
//
//    for(i=0; i<TIMEOUT; i++){
//        if(_RBF == 1){
//            break;
//        }
//    }
//    if(i == TIMEOUT){
//        return 1;
//    }
//
//    return 0;
//}
//
//
///*************************fifo.hから抜粋*************************/
//static void initializeFIFO( I2CFIFO *p_fifo ){
//    p_fifo -> head_read	 = 0;
//    p_fifo -> head_write = 0;
//}
//
//
//static I2CErrAddFIFO addFIFO( I2CFIFO *p_fifo, i2cDataType data )
//{
//    unsigned char next = (p_fifo -> head_write+ 1) & (I2C_DATA_SIZE - 1);
//
//    if( next == p_fifo->head_read ){
//        return	I2C_FIFO_OVERFLOWED;
//    }
//
//    p_fifo->data[p_fifo->head_write] = data;
//    p_fifo->head_write = next;
//
//    return I2C_ADD_SUCCESS;
//
//}
//
//static I2CErrGetFIFO getFIFO( I2CFIFO *p_fifo, i2cDataType *buf )
//{
//    if( p_fifo->head_read == p_fifo->head_write ){
//        return I2C_FIFO_EMPTY;
//    }
//
//    *buf = p_fifo->data[p_fifo->head_read];
//    p_fifo->head_read = (p_fifo->head_read + 1) & (I2C_DATA_SIZE - 1 );
//
//    return I2C_GET_SUCCESS;
//}
//
//static void clearFIFO( I2CFIFO *p_fifo )
//{
//    p_fifo->head_read = p_fifo->head_write;
//}
//
//static unsigned char getFillFIFO(I2CFIFO *p_fifo)
//{
//	return	(I2C_DATA_SIZE + p_fifo->head_write - p_fifo->head_read) % I2C_DATA_SIZE;
//}
//
////static bool isEmptyFIFO(I2CFIFO *p_fifo)
////{
////	return	(p_fifo->head_write == p_fifo->head_read) ? true : false;
////}
//
///*************************fifo.hから抜粋*************************/

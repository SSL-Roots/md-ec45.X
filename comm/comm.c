/****************************************/
/*comm.c*/
/*Author    : Makito Ishikura*/
/****************************************/

#include <xc.h>
#include <stdbool.h>
#include <uart_dsPIC33F/uart_dsPIC33F.h>
#include <i2c/i2c_slave_logics.h>
#include <xprintf/xprintf.h>
#include <msgpack/src/msgpack.h>
#include "comm.h"
#include <pps.h>
#include <ecan.h>
#include "ECAN/ECAN.h"

#define	FCY 39613750
#include <libpic30.h>

/**************************************/
#define	NUM_OF_BUF_SEND	50
/**************************************/


/**************************************/
/*グローバル変数宣言*/
static msgpack_unpacker	G_upkr;
static msgpack_unpacked	G_upkd;
ECAN1MSGBUF ecan1msgBuf __attribute__( (space(dma), aligned(NUM_OF_ECAN_BUFS*32))); //DMA領域に，NUM_OF_ECAN_BUFS*16バイトを配置
/**************************************/



/**************************************/
static bool fetchByteData(unsigned char* buf);
/**************************************/

void initializeComm(void)
{
#ifdef  COMM_MODE_UART
    initializeUart( 9, 8, FCY*2, UART_BAUDRATE);
#elif   defined(COMM_MODE_I2C)
    i2cSlaveInitialize(I2C_ID);
#elif   defined(COMM_MODE_CAN)
    initilizeCanConfiguration();
    initilizeCanDmaConfiguration(__builtin_dmaoffset(ecan1msgBuf));
    PPSInput(IN_FN_PPS_C1RX, IN_PIN_PPS_RP6);       //RX pin
    PPSOutput(OUT_FN_PPS_C1TX, OUT_PIN_PPS_RP7);    //TX pin
    TRISBbits.TRISB6 = 1;
    //Filter
    configEcanFilter(0, CAN_FILTER0_RX_BUFFER1, 0, 0x1AA, 0);
#else
#error  "COMM_MODE IS NOT DEFINED"
#endif
    initUnpackerMsgpack(&G_upkr);
    initUnpackedMsgpack(&G_upkd);
}
/**************************************/


/**************************************/
Order fetchOrder(void)
{
    static Order    order;
    unsigned char   buf;
    unsigned char   send_data[8] = {11,12,13,14,15,16,17,18};
    unsigned char   i = 0;
    
    Err_unpackerNextMsgpack err;
    
    /* 受信バッファからアンパッカーへデータを移動 */
    while(fetchByteData(&buf) == true){
        pushByteUnpackerMsgpack(buf, &G_upkr);
    }
  

    while(1){
        err = unpackerNextMsgpack(&G_upkr, &G_upkd);

        if(err == UNPACKING_UNPACKER_NEXT_MSGPACK_){ break;}	//アンパッカーのバッファが空
        if(err == SUCCEEDED_UNPACKER_NEXT_MSGPACK_){
            if (G_upkd.data->type != MSGPACK_OBJECT_ARRAY){ continue; }
            if (G_upkd.data->via.array.size != 2){ continue; }

            /* Order 更新 */
            msgpack_object* obj_order   = G_upkd.data->via.array.ptr;
            msgpack_object* obj_data    = obj_order[1].via.array.ptr;
            order.command = (unsigned char)obj_order[0].via.u64;
            order.data[0] = (signed int)obj_data->via.i64;
            send_data[0] = order.command;
            send_data[1] = (unsigned char)(order.data[0] & 0x00FF);
            send_data[2] = (unsigned char)((order.data[0] & 0xFF00) >> 4);
            CAN1SendMessage(&send_data, 3, 1337, 0, 0, ecan1msgBuf, 0);
            while(C1TR01CONbits.TXREQ0==1){
                if(C1TR01CONbits.TXERR0 == 1)LATAbits.LATA1  = 0;
            }
            LATAbits.LATA1  = 1;
        }
    }
    
    return order;
}
/**************************************/

static bool fetchByteData(unsigned char* buf)
{
#if defined(COMM_MODE_UART)
    ErrGetcUart	err;
    err	= getcUart(buf);
    return (err == SUCCESS_GETC) ? true : false;

#elif defined(COMM_MODE_I2C)
    return (i2cPullData(1, buf) == 0) ? true : false;

#elif defined(COMM_MODE_CAN)
    return (CANPullData(1, buf) == 0) ? true : false;
    
#endif
    return 0;
}

/**************************************/
short sendLogs(unsigned short num_data, signed char* ref, signed char* mes)
{
#if defined(COMM_MODE_I2C)
    const size_t        num_buffer = 12;
    static signed char  buf_ref[12], buf_mes[12];
    static size_t       num_buffered_data;
    unsigned short      i;
    msgpack_packed      pk;

    //i2cの送信バッファが空になるまで、バッファにデータをため続ける
    for (i=0; i<num_data; i++) {
        if (i >= (12 - num_buffered_data)) {break;}
        buf_ref[num_buffered_data + i]  = ref[i];
        buf_mes[num_buffered_data + i]  = mes[i];
    }
    num_buffered_data += i;
//    if (i2cIsEmptyTransmissionStorage() == false) { return -1; }
    if (i2cGetStorageDataNum(0) != 0) {return -1;}

    /* pack */
    initPackedMsgpack(&pk);
    packArrayMsgpack(&pk, 2);

    packArrayMsgpack(&pk, num_buffered_data);
    for (i=0; i<num_buffered_data; i++) {
        packSignedCharMsgpack(&pk, *(buf_ref + i));
    }
    packArrayMsgpack(&pk, num_buffered_data);
    for (i=0; i<num_buffered_data; i++) {
        packSignedCharMsgpack(&pk, *(buf_mes + i));
    }

    /* send */
    i2cPushData((i2cDataType)pk.size);	//全体のデータ数を先に送信

    for (i=0; i<pk.size; i++) {
        i2cPushData(*(pk.data + i));
    }

    num_buffered_data = 0;

    if (i2cGetState() == 6) {
        return -100;
    }

    return 0;
#endif
    return 0;
}
#include <xc.h>
#include <ecan.h>
#include <dma.h>
#include "ECAN.h"
#include "ECAN_config.h"

#define CAN_MODE_IS_CONFIG 0x4
#define CAN_FILTER_WIN     0x1
#define CAN_BUFFER_WIN     0x0
#define CAN_CLK_FCY        0x1
#define CAN_CLK_FOSC       0x0

#define CAN_SJW_2TQ        0x1

#define CAN_BRP_2          0x1

#define CAN_NOWAKEUPFIL    0x0

#define CAN_SEG_1TQ        0x0
#define CAN_SEG_2TQ        0x1
#define CAN_SEG_3TQ        0x2
#define CAN_SEG_4TQ        0x3
#define CAN_SEG_5TQ        0x4
#define CAN_SEG_6TQ        0x5
#define CAN_SEG_7TQ        0x6
#define CAN_SEG_8TQ        0x7

#define CAN_SAM_1          0x0
#define CAN_SAM_3          0x1

/*************************fifo.hから抜粋*************************/
typedef struct {
    CANDataType	data[CAN_DATA_SIZE];
    unsigned char head_write, head_read;
}CANFIFO;


typedef enum CANErrAddFIFO {  /* addFIFO()の戻り値 */
    CAN_ADD_SUCCESS,
    CAN_FIFO_OVERFLOWED
} CANErrAddFIFO;


typedef enum CANErrGetFIFO { /* getFIFO()の戻り値 */
    CAN_GET_SUCCESS,
    CAN_FIFO_EMPTY
} CANErrGetFIFO;


typedef	enum CANErrGetAllFIFO{ /*getAllFIFO()の戻り値 */
    CAN_SUCCESS_GET_ALL_FIFO,
    CAN_BUFFER_SIZE_IS_NOT_ENOUGH
} CANErrGetAllFIFO;

static void initializeFIFO( CANFIFO *p_fifo );
static CANErrAddFIFO addFIFO( CANFIFO *p_fifo, CANDataType data );
static CANErrGetFIFO getFIFO( CANFIFO *p_fifo, CANDataType *buf );
static void clearFIFO( CANFIFO *p_fifo );
static unsigned char getFillFIFO(CANFIFO *p_fifo);


static CANFIFO receiveStorage;
static CANFIFO transmitStorage;
static CANSTATE state = BEFORE_INTERRUPT;
unsigned int G_ecanbuf[4][8];

void initilizeCanConfiguration(void){
    
    initializeFIFO(&receiveStorage);
    initializeFIFO(&transmitStorage);
    
    C1CTRL1bits.REQOP   = 4;
    while(C1CTRL1bits.OPMODE != 4);
    
    C1CTRL1bits.WIN = 0;        //フィルター以外を設定する
    C1CTRL1bits.CANCKS  = 1;
    
//    CAN1Initialize(baud_conf, baud_conf);
    C1CFG1bits.SJW      = CAN_SJW_2TQ;
    C1CFG1bits.BRP      = CAN_BRP_2;
    C1CFG2bits.WAKFIL   = CAN_NOWAKEUPFIL;
    C1CFG2bits.SEG2PHTS = 1;
    C1CFG2bits.SEG2PH   = CAN_SEG_6TQ;
    C1CFG2bits.SAM      = CAN_SAM_1;
    C1CFG2bits.SEG1PH   = CAN_SEG_8TQ;
    C1CFG2bits.PRSEG    = CAN_SEG_5TQ;
    CAN1FIFOCon(fifo_conf);
    
    //Filter
    C1CTRL1bits.WIN = 1;
    
    CAN1SetMaskSource(mask_val1, mask_val2);
    CAN1SetMask(0, set_mask_sid[0], set_mask_eid[0]);
    CAN1SetMask(1, set_mask_sid[1], set_mask_eid[1]);
    CAN1SetMask(2, set_mask_sid[2], set_mask_eid[2]);
    
    CAN1SetFilter(0, CAN_FILTER_SID(ECAN_SID_F0) & CAN_RX_EID_DIS, 0);  //デフォルトのフィルタを設定
    CAN1SetBUFPNT1(CAN_FILTER0_RX_BUFFER1);
    CAN1EnableFilter(0);
    
    C1CTRL1bits.WIN = 0;
    
    CAN1SetTXRXMode(0, txrx_mode_config[0]);
    CAN1SetTXRXMode(2, txrx_mode_config[1]);
    CAN1SetTXRXMode(4, txrx_mode_config[2]);
    CAN1SetTXRXMode(6, txrx_mode_config[3]);
    
    ConfigIntCAN1(ecan_int_enble_event, ecan_int_pri_en);

    
    C1CTRL1bits.REQOP   = 0;
    while(C1CTRL1bits.OPMODE != 0);
    
}

void initilizeCanDmaConfiguration(unsigned int buf_add){
    DMA0CONbits.SIZE    = 0;
    DMA0CONbits.DIR     = 1;
    DMA0CONbits.AMODE   = 0b11;
    DMA0CONbits.MODE    = 0b00;
    DMA0REQbits.IRQSEL  = 0b1000110;
    DMA0PAD =   0x0442;
    DMA0STA = buf_add;
    DMA0CNT = 7;
    DMA0CONbits.CHEN    = 1;
    
    DMA2CONbits.SIZE    = 0;
    DMA2CONbits.DIR     = 0;
    DMA2CONbits.AMODE   = 0b11;
    DMA2CONbits.MODE    = 0b00;
    DMA2REQbits.IRQSEL  = 0b0100010;
    DMA2PAD =   0x0440;
    DMA2STA = buf_add;
    DMA2CNT = 7;
    DMA2CONbits.CHEN    = 1;
}

void configEcanFilter(unsigned int filter_num, unsigned int buffer, unsigned int is_eid_enable, unsigned int sid, unsigned long eid){
    unsigned temp_sid;
    
    //Config Mode
    C1CTRL1bits.REQOP   = 4;
    while(C1CTRL1bits.OPMODE != 4);
    
    //Filter Config
    C1CTRL1bits.WIN = 1;
    
    //
    if(is_eid_enable==0){
        temp_sid    = CAN_FILTER_SID(sid) & CAN_RX_EID_DIS;
    }else if(is_eid_enable==1){
        temp_sid    = CAN_FILTER_SID(sid) & CAN_RX_EID_EN;
    }
    CAN1SetFilter(filter_num, temp_sid, eid);
    switch(filter_num){
        case 0:
        case 1:
        case 2:
        case 3:
            CAN1SetBUFPNT1(buffer&C1BUFPNT1);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
            CAN1SetBUFPNT2(buffer&C1BUFPNT2);
            break;
        case 8:
        case 9:
        case 10:
        case 11:
            CAN1SetBUFPNT3(buffer&C1BUFPNT3);
            break;
        case 12:
        case 13:
        case 14:
        case 15:
            CAN1SetBUFPNT3(buffer&C1BUFPNT4);
            break;   
    }
    
    CAN1EnableFilter(filter_num);
    
    C1CTRL1bits.WIN = 0;
    
    //Config Mode
    C1CTRL1bits.REQOP   = 0;
    while(C1CTRL1bits.OPMODE != 0);
}

void setEcanMessage(EcanMessageBuffers* buffer, int sid, long eid, unsigned int is_eid, unsigned int is_remote, unsigned int data_length, unsigned char* send_data){
    unsigned int i;
    buffer->m_msg0.SID  = sid;
    buffer->m_msg0.IDE  = is_eid;
    if(is_eid==1){
        buffer->m_msg0.SRR  = 1;
    }else{
        buffer->m_msg0.SRR  = is_remote;
    }
    
    buffer->m_msg1.EID_6_17 = (unsigned int)eid>>6;   //上位11bit
    
    buffer->m_msg2.EID_0_5  = eid&0x000003FF;   //下位6bit
    buffer->m_msg2.RTR  = is_remote;
    buffer->m_msg2.RB0  = 0;
    buffer->m_msg2.RB1  = 0;
    buffer->m_msg2.DLC  = data_length;
    
    for(i=0;i<data_length;i++){
        buffer->m_msg36.ecandata[i] = *(send_data+i);
    }
}

unsigned char CANPullData(unsigned char num, CANDataType *data){
    int i;

    for(i=0;i<num;i++){
        if(getFIFO(&receiveStorage, &data[i]) == CAN_FIFO_EMPTY){
            /*FIFOが空*/
            return i+1; //何個目のデータが取れなかったのかを返す
        }
    }

    return 0;
}
/*************************fifo.hから抜粋*************************/
static void initializeFIFO( CANFIFO *p_fifo ){
    p_fifo -> head_read	 = 0;
    p_fifo -> head_write = 0;
}


static CANErrAddFIFO addFIFO( CANFIFO *p_fifo, CANDataType data )
{
    unsigned char next = (p_fifo -> head_write+ 1) & (CAN_DATA_SIZE - 1);
    

    if( next == p_fifo->head_read ){
        return	CAN_FIFO_OVERFLOWED;
    }
   
    p_fifo->data[p_fifo->head_write]= data;
    
    p_fifo->head_write = next;

    return CAN_ADD_SUCCESS;

}

static CANErrGetFIFO getFIFO( CANFIFO *p_fifo, CANDataType *buf )
{
    if( p_fifo->head_read == p_fifo->head_write ){
        return CAN_FIFO_EMPTY;
    }

    *buf = p_fifo->data[p_fifo->head_read];
    p_fifo->head_read = (p_fifo->head_read + 1) & (CAN_DATA_SIZE - 1 );

    return CAN_GET_SUCCESS;
}

static void clearFIFO( CANFIFO *p_fifo )
{
    p_fifo->head_read = p_fifo->head_write;
}

static unsigned char getFillFIFO(CANFIFO *p_fifo)
{
	return	(CAN_DATA_SIZE + p_fifo->head_write - p_fifo->head_read) % CAN_DATA_SIZE;
}

void __attribute__((  interrupt, auto_psv)) _C1Interrupt(void)
{
    int i;
    char buffer[8];
   
    if(C1INTFbits.RBIF==1){
        //Buffer 1に入ったとき
        if(C1RXFUL1bits.RXFUL1){
            LATAbits.LATA2  = 1;
            for(i=0;i<8;i++){
                G_ecanbuf[1][i] = ecan1msgBuf[1][i];
                C1RXFUL1bits.RXFUL1 = 0;
            }
            i = 0;
            for(i=0;i<2;i++){
                buffer[2*i] = (unsigned char)(G_ecanbuf[1][i+3] & 0x00FF);
                if(addFIFO(&receiveStorage, buffer[2*i]) == CAN_FIFO_OVERFLOWED){
                    /*受信データオーバーフロー*/
                    state = R_STORAGE_OVERFLOWED;
                    return;
                }
                buffer[2*i+1] = (unsigned char)((G_ecanbuf[1][i+3] & 0xFF00) >>8);
                if(addFIFO(&receiveStorage, buffer[2*i+1]) == CAN_FIFO_OVERFLOWED){
                    /*受信データオーバーフロー*/
                    state = R_STORAGE_OVERFLOWED;
                    return;
                }
            }
            if(addFIFO(&receiveStorage, buffer[i]) == CAN_FIFO_OVERFLOWED){
                /*受信データオーバーフロー*/
                state = R_STORAGE_OVERFLOWED;
                return;
            }
            /*データ受信完了*/
            state = RECEIVED_DATA;
            return;
        }
        //Buffer 2に入ったとき
        else if(C1RXFUL1bits.RXFUL2){
            for(i=0;i<8;i++){
                G_ecanbuf[2][i] = ecan1msgBuf[2][i];
                C1RXFUL1bits.RXFUL2 = 0;
            }
        }
        //Buffer 3に入ったとき
        else{
            for(i=0;i<8;i++){
                G_ecanbuf[3][i] = ecan1msgBuf[3][i];
                C1RXFUL1bits.RXFUL3 = 0;
            }
        }

        C1INTFbits.RBIF = 0;
    }

    IFS2bits.C1IF   = 0;
}
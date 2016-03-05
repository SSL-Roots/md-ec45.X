/* 
 * File:   ECAN_config.h
 * Author: 12-85
 *
 * Created on 2015/06/16, 10:47
 */

#ifndef ECAN_CONFIG_H
#define	ECAN_CONFIG_H

//CANxinitilize
int baud_conf   = CAN_SYNC_JUMP_WIDTH2 & CAN_BAUD_PRE_SCALE(3);
int phase_conf  = CAN_WAKEUP_BY_FILTER_DIS & CAN_PROPAGATIONTIME_SEG_TQ(3) & CAN_PHASE_SEG1_TQ(3) & CAN_PHASE_SEG2_TQ(3) & CAN_SEG2_FREE_PROG & CAN_SAMPLE3TIMES;
/****************************************************************************** 
 * baud_conf:CiCFG1の設定(ボーレートのせってい）
 *      TQ（Time Quanta)の何倍がSynchronization Jump Widthかを設定
 *          CAN_SYNC_JUMP_WIDTH1    0x003F
 *          CAN_SYNC_JUMP_WIDTH2    0x007F
 *          CAN_SYNC_JUMP_WIDTH3    0x00BF
 *          CAN_SYNC_JUMP_WIDTH4    0x00FF
 *      ボーレートの設定(TQの設定)
 *          CAN_BAUD_PRE_SCALE(x)   x=1～64
 * phase_conf:CiCFG2の設定
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
*******************************************************************************/

//CANxFIFOCon
int fifo_conf   = CAN_DMA_BUF_SIZE_4 & CAN_FIFO_AREA_TRB1;
/****************************************************************************** 
 * fifo_conf:CxFCTRLの設定
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
*******************************************************************************/

//CANxSetMaskSource
int mask_val1   = CAN_MASK_FILTER0_MASK0 & CAN_MASK_FILTER1_MASK0;
int mask_val2   = 0;
/****************************************************************************** 
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
*******************************************************************************/

//CANxSetMask
int mask_no = 0;
int set_mask_sid[3]    = {CAN_MASK_SID(0xFFFF) & CAN_MATCH_FILTER_TYPE, CAN_MASK_SID(0xFFFF) & CAN_MATCH_FILTER_TYPE, CAN_MASK_SID(0xFFFF) & CAN_MATCH_FILTER_TYPE};
int set_mask_eid[3]    = {CAN_MASK_EID(0xFFFF), CAN_MASK_EID(0xFFFF), CAN_MASK_EID(0xFFFF)};
/****************************************************************************** 
 * mask_no:設定するマスクの番号
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
*******************************************************************************/

//CAN1SetTXRXMode
int txrx_mode_config[4] = {CAN_BUFFER0_IS_TX & CAN_ABORT_REQUEST_BUFFER0 & CAN_AUTOREMOTE_DISABLE_BUFFER0 & CAN_TX_HIGH_PRI_BUFFER0         //buffer0
                                &CAN_BUFFER1_IS_RX & CAN_ABORT_REQUEST_BUFFER1 & CAN_AUTOREMOTE_DISABLE_BUFFER1 & CAN_TX_LOW_PRI_BUFFER1,   //buffer1
                           CAN_BUFFER2_IS_TX & CAN_ABORT_REQUEST_BUFFER2 & CAN_AUTOREMOTE_ENABLE_BUFFER2 & CAN_TX_HIGH_PRI_BUFFER2         //buffer2    TX,auto remote is enable
                                &CAN_BUFFER3_IS_RX & CAN_ABORT_REQUEST_BUFFER3 & CAN_AUTOREMOTE_DISABLE_BUFFER3 & CAN_TX_LOW_PRI_BUFFER3,   //buffer3
                           CAN_BUFFER4_IS_RX & CAN_ABORT_REQUEST_BUFFER4 & CAN_AUTOREMOTE_DISABLE_BUFFER4 & CAN_TX_HIGH_PRI_BUFFER4         //buffer4
                                &CAN_BUFFER5_IS_RX & CAN_ABORT_REQUEST_BUFFER5 & CAN_AUTOREMOTE_DISABLE_BUFFER5 & CAN_TX_LOW_PRI_BUFFER5,   //buffer5
                           CAN_BUFFER6_IS_RX & CAN_ABORT_REQUEST_BUFFER6 & CAN_AUTOREMOTE_DISABLE_BUFFER6 & CAN_TX_HIGH_PRI_BUFFER6         //buffer6
                                &CAN_BUFFER7_IS_RX & CAN_ABORT_REQUEST_BUFFER7 & CAN_AUTOREMOTE_DISABLE_BUFFER7 & CAN_TX_LOW_PRI_BUFFER7};  //buffer7
/****************************************************************************** 
 * txrx_mode_config:CxTRmnCONの設定
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
*******************************************************************************/

// ConfigIntCAN1
int ecan_int_enble_event    = CAN_INVALID_MESSAGE_INT_DIS & CAN_WAKEUP_INT_DIS & CAN_ERR_INT_DIS & CAN_FIFO_INT_DIS & CAN_RXBUF_OVERFLOW_INT_DIS & CAN_RXBUF_INT_EN & CAN_TXBUF_INT_DIS;
int ecan_int_pri_en         = CAN_INT_ENABLE & CAN_INT_PRI_7;
#endif	/* ECAN_CONFIG_H */


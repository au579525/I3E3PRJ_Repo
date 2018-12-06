/*******************************************************************************
* File Name: SPI_1.h
* Version 2.70
*
* Description:
*  Contains the function prototypes, constants and register definition
*  of the SPI Slave Component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SPIS_SPI_1_H)
#define CY_SPIS_SPI_1_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define SPI_1_DATA_WIDTH                  (8u)
#define SPI_1_INTERNAL_TX_INT_ENABLED     (0u)
#define SPI_1_INTERNAL_RX_INT_ENABLED     (1u)
#define SPI_1_MODE_USE_ZERO               (1u)
#define SPI_1_BIDIRECTIONAL_MODE          (0u)
#define SPI_1_MODE                        (0u)

#define SPI_1_FIFO_SIZE                  (4u)
/* Internal interrupt handling */
#define SPI_1_TX_BUFFER_SIZE             (4u)
#define SPI_1_RX_BUFFER_SIZE             (4u)
#define SPI_1_INTERNAL_TX_INT_ENABLED    (0u)
#define SPI_1_INTERNAL_RX_INT_ENABLED    (1u)

#define SPI_1_TX_SOFTWARE_BUF_ENABLED    ((0u != SPI_1_INTERNAL_TX_INT_ENABLED) && \
                                                     (SPI_1_TX_BUFFER_SIZE > SPI_1_FIFO_SIZE))

#define SPI_1_RX_SOFTWARE_BUF_ENABLED    ((0u != SPI_1_INTERNAL_RX_INT_ENABLED) && \
                                                     (SPI_1_RX_BUFFER_SIZE > SPI_1_FIFO_SIZE))


/***************************************
*        Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
    uint8 cntrPeriod;
} SPI_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  SPI_1_Init(void) ;
void  SPI_1_Enable(void) ;
void  SPI_1_Start(void) ;
void  SPI_1_Stop(void) ;
void  SPI_1_EnableTxInt(void) ;
void  SPI_1_EnableRxInt(void) ;
void  SPI_1_DisableTxInt(void) ;
void  SPI_1_DisableRxInt(void) ;
void  SPI_1_SetTxInterruptMode(uint8 intSrc) ;
void  SPI_1_SetRxInterruptMode(uint8 intSrc) ;
uint8 SPI_1_ReadTxStatus(void) ;
uint8 SPI_1_ReadRxStatus(void) ;
void  SPI_1_WriteTxData(uint8 txData);

#if(SPI_1_MODE_USE_ZERO != 0u)
    void  SPI_1_WriteTxDataZero(uint8 txDataByte) \
                                              ;
#endif /* (SPI_1_MODE_USE_ZERO != 0u) */

uint8 SPI_1_ReadRxData(void) ;
uint8 SPI_1_GetRxBufferSize(void) ;
uint8 SPI_1_GetTxBufferSize(void) ;
void  SPI_1_ClearRxBuffer(void) ;
void  SPI_1_ClearTxBuffer(void) ;

#if (SPI_1_BIDIRECTIONAL_MODE != 0u)
    void  SPI_1_TxEnable(void) ;
    void  SPI_1_TxDisable(void) ;
#endif /* SPI_1_BIDIRECTIONAL_MODE != 0u */

void  SPI_1_PutArray(const uint8 buffer[], uint8 byteCount) ;
void  SPI_1_ClearFIFO(void) ;
void  SPI_1_Sleep(void) ;
void  SPI_1_Wakeup(void) ;
void  SPI_1_SaveConfig(void) ;
void  SPI_1_RestoreConfig(void) ;

/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_1) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    SPI_1_CyBtldrCommStart(void) CYSMALL ;
    void    SPI_1_CyBtldrCommStop(void) CYSMALL ;
    void    SPI_1_CyBtldrCommReset(void) CYSMALL ;
    cystatus SPI_1_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus SPI_1_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_1)
        #define CyBtldrCommStart    SPI_1_CyBtldrCommStart
        #define CyBtldrCommStop     SPI_1_CyBtldrCommStop
        #define CyBtldrCommReset    SPI_1_CyBtldrCommReset
        #define CyBtldrCommWrite    SPI_1_CyBtldrCommWrite
        #define CyBtldrCommRead     SPI_1_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_1) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define SPI_1_BYTE2BYTE_TIME_OUT (1u)

#endif /* (CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SPI_1) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


CY_ISR_PROTO(SPI_1_TX_ISR);
CY_ISR_PROTO(SPI_1_RX_ISR);

/* Macros for getting software status of SPIS Statusi Register */
#define SPI_1_GET_STATUS_TX(swTxSts) ( (uint8)(SPI_1_TX_STATUS_REG | \
                                                       ((swTxSts) & SPI_1_STS_CLR_ON_RD_BYTES_MASK)) )
#define SPI_1_GET_STATUS_RX(swRxSts) ( (uint8)(SPI_1_RX_STATUS_REG | \
                                                       ((swRxSts) & SPI_1_STS_CLR_ON_RD_BYTES_MASK)) )


/***************************************
*   Variable with external linkage
***************************************/

extern uint8 SPI_1_initVar;


/***************************************
*           API Constants
***************************************/

#define SPI_1_TX_ISR_NUMBER     ((uint8)SPI_1_TxInternalInterrupt__INTC_NUMBER)
#define SPI_1_RX_ISR_NUMBER     ((uint8)SPI_1_RxInternalInterrupt__INTC_NUMBER)
#define SPI_1_TX_ISR_PRIORITY   ((uint8)SPI_1_TxInternalInterrupt__INTC_PRIOR_NUM)
#define SPI_1_RX_ISR_PRIORITY   ((uint8)SPI_1_RxInternalInterrupt__INTC_PRIOR_NUM)


/***************************************
*    Initial Parameter Constants
***************************************/

#define SPI_1_INT_ON_SPI_DONE    (uint8)(0u << SPI_1_STS_SPI_DONE_SHIFT)
#define SPI_1_INT_ON_TX_EMPTY    (uint8)(0u << SPI_1_STS_TX_FIFO_EMPTY_SHIFT)
#define SPI_1_INT_ON_TX_NOT_FULL (uint8)(0u << SPI_1_STS_TX_FIFO_NOT_FULL_SHIFT)
#define SPI_1_INT_ON_BYTE_COMP   (uint8)(0u << SPI_1_STS_BYTE_COMPLETE_SHIFT)

#define SPI_1_TX_INIT_INTERRUPTS_MASK  (SPI_1_INT_ON_SPI_DONE | \
                                            SPI_1_INT_ON_TX_EMPTY | SPI_1_INT_ON_TX_NOT_FULL | \
                                            SPI_1_INT_ON_BYTE_COMP)

#define SPI_1_INT_ON_RX_EMPTY     (uint8)(0u << SPI_1_STS_RX_FIFO_EMPTY_SHIFT)
#define SPI_1_INT_ON_RX_NOT_EMPTY (uint8)(1u << SPI_1_STS_RX_FIFO_NOT_EMPTY_SHIFT)
#define SPI_1_INT_ON_RX_OVER      (uint8)(1u << SPI_1_STS_RX_FIFO_OVERRUN_SHIFT)
#define SPI_1_INT_ON_RX_FULL      (uint8)(0u << SPI_1_STS_RX_FIFO_FULL_SHIFT)

#define SPI_1_RX_INIT_INTERRUPTS_MASK (SPI_1_INT_ON_RX_EMPTY | \
                                            SPI_1_INT_ON_RX_NOT_EMPTY | SPI_1_INT_ON_RX_OVER | \
                                            SPI_1_INT_ON_RX_FULL)

#define SPI_1_BITCTR_INIT           (SPI_1_DATA_WIDTH - 1u)

#define SPI_1__MODE_00 0
#define SPI_1__MODE_01 1
#define SPI_1__MODE_10 2
#define SPI_1__MODE_11 3


#define SPI_1_TX_BUFFER_SIZE         (4u)
#define SPI_1_RX_BUFFER_SIZE         (4u)

/* Following definitions are for version Compatibility, they are obsolete.
*  Please do not use it in new projects
*/
#define SPI_1_INIT_INTERRUPTS_MASK  (SPI_1_INT_ON_SPI_DONE | SPI_1_INT_ON_TX_EMPTY | \
                                            SPI_1_INT_ON_TX_NOT_FULL | SPI_1_INT_ON_RX_EMPTY | \
                                            SPI_1_INT_ON_RX_NOT_EMPTY | SPI_1_INT_ON_RX_OVER | \
                                            SPI_1_INT_ON_BYTE_COMP)


/***************************************
*             Registers
***************************************/
#if(CY_PSOC3 || CY_PSOC5)
    #define SPI_1_TXDATA_ZERO_REG          (* (reg8  *) \
            SPI_1_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_1_TXDATA_ZERO_PTR           (  (reg8  *) \
            SPI_1_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_1_RXDATA_ZERO_REG           (* (reg8  *) \
            SPI_1_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_1_RXDATA_ZERO_PTR           (  (reg8  *) \
            SPI_1_BSPIS_sR8_Dp_u0__A0_REG)

    #define SPI_1_TXDATA_REG                (* (reg8  *) \
            SPI_1_BSPIS_sR8_Dp_u0__F0_REG)

    #define SPI_1_TXDATA_PTR                (  (reg8  *) \
            SPI_1_BSPIS_sR8_Dp_u0__F0_REG)

    #define SPI_1_RXDATA_REG                (* (reg8  *) \
            SPI_1_BSPIS_sR8_Dp_u0__F1_REG)

    #define SPI_1_RXDATA_PTR                (  (reg8  *) \
            SPI_1_BSPIS_sR8_Dp_u0__F1_REG)
#else
    #if(SPI_1_DATA_WIDTH <= 8u) /* 8bit - SPIS */
        #define SPI_1_TXDATA_ZERO_REG           (* (reg8 *) \
                SPI_1_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_1_TXDATA_ZERO_PTR           (  (reg8  *) \
                SPI_1_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_1_RXDATA_ZERO_REG           (* (reg8  *) \
                SPI_1_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_1_RXDATA_ZERO_PTR           (  (reg8 *) \
                SPI_1_BSPIS_sR8_Dp_u0__A0_REG)

        #define SPI_1_TXDATA_REG                (* (reg8  *) \
                SPI_1_BSPIS_sR8_Dp_u0__F0_REG)

        #define SPI_1_TXDATA_PTR                (  (reg8  *) \
                SPI_1_BSPIS_sR8_Dp_u0__F0_REG)

        #define SPI_1_RXDATA_REG                (* (reg8  *) \
                SPI_1_BSPIS_sR8_Dp_u0__F1_REG)

        #define SPI_1_RXDATA_PTR                (  (reg8  *) \
                SPI_1_BSPIS_sR8_Dp_u0__F1_REG)
    #else /* 16bit - SPIS */
        #define SPI_1_TXDATA_ZERO_REG           (* (reg16  *) \
                SPI_1_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_1_TXDATA_ZERO_PTR           (  (reg16  *) \
                SPI_1_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_1_RXDATA_ZERO_REG           (* (reg16  *) \
                SPI_1_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_1_RXDATA_ZERO_PTR           (  (reg16  *) \
                SPI_1_BSPIS_sR8_Dp_u0__16BIT_A0_REG)

        #define SPI_1_TXDATA_REG                (* (reg16  *) \
                SPI_1_BSPIS_sR8_Dp_u0__16BIT_F0_REG)

        #define SPI_1_TXDATA_PTR                (  (reg16  *) \
                SPI_1_BSPIS_sR8_Dp_u0__16BIT_F0_REG)

        #define SPI_1_RXDATA_REG                (* (reg16  *) \
                SPI_1_BSPIS_sR8_Dp_u0__16BIT_F1_REG)

        #define SPI_1_RXDATA_PTR                (  (reg16 *) \
                SPI_1_BSPIS_sR8_Dp_u0__16BIT_F1_REG)
    #endif /* (SPI_1_DATA_WIDTH <= 8u) */
#endif     /* (CY_PSOC3 || CY_PSOC5) */

#define SPI_1_TX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
        SPI_1_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)
#define SPI_1_TX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
        SPI_1_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)

#define SPI_1_RX_AUX_CONTROL_DP0_REG       (* (reg8 *) \
        SPI_1_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)
#define SPI_1_RX_AUX_CONTROL_DP0_PTR       (  (reg8 *) \
        SPI_1_BSPIS_sR8_Dp_u0__DP_AUX_CTL_REG)

#if(SPI_1_DATA_WIDTH > 8u)

    #define SPI_1_TX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
            SPI_1_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define SPI_1_TX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
            SPI_1_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)

    #define SPI_1_RX_AUX_CONTROL_DP1_REG   (* (reg8 *) \
            SPI_1_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)
    #define SPI_1_RX_AUX_CONTROL_DP1_PTR   (  (reg8 *) \
            SPI_1_BSPIS_sR8_Dp_u1__DP_AUX_CTL_REG)

#endif /* SPI_1_DATA_WIDTH > 8u */


#define SPI_1_COUNTER_PERIOD_REG    (* (reg8 *) \
        SPI_1_BSPIS_BitCounter__PERIOD_REG)
#define SPI_1_COUNTER_PERIOD_PTR    (  (reg8 *) \
        SPI_1_BSPIS_BitCounter__PERIOD_REG)

#define SPI_1_TX_STATUS_MASK_REG    (* (reg8 *) \
        SPI_1_BSPIS_TxStsReg__MASK_REG)
#define SPI_1_TX_STATUS_MASK_PTR    (  (reg8 *) \
        SPI_1_BSPIS_TxStsReg__MASK_REG)

#define SPI_1_RX_STATUS_MASK_REG    (* (reg8 *) \
        SPI_1_BSPIS_RxStsReg__MASK_REG)
#define SPI_1_RX_STATUS_MASK_PTR    (  (reg8 *) \
        SPI_1_BSPIS_RxStsReg__MASK_REG)

#define SPI_1_ONE_REG               (* (reg8 *) \
        SPI_1_BSPIS_SPISlave_dpCounter_u0__D1_REG)
#define SPI_1_ONE_PTR               (  (reg8 *) \
        SPI_1_BSPIS_dpCounter_u0__D1_REG)

#define SPI_1_TX_STATUS_REG         (* (reg8 *) \
        SPI_1_BSPIS_TxStsReg__STATUS_REG)
#define SPI_1_TX_STATUS_PTR         (  (reg8 *) \
        SPI_1_BSPIS__TxStsReg__STATUS_REG)

#define SPI_1_RX_STATUS_REG         (* (reg8 *) \
        SPI_1_BSPIS_RxStsReg__STATUS_REG)
#define SPI_1_RX_STATUS_PTR         (  (reg8 *) \
        SPI_1_BSPIS_RxStsReg__STATUS_REG)

#define SPI_1_COUNTER_CONTROL_REG   (* (reg8 *) \
        SPI_1_BSPIS_BitCounter__CONTROL_AUX_CTL_REG)
#define SPI_1_COUNTER_CONTROL_PTR   (  (reg8 *) \
        SPI_1_BSPIS_BitCounter__CONTROL_AUX_CTL_REG)

#define SPI_1_TX_STATUS_ACTL_REG    (* (reg8 *) \
        SPI_1_BSPIS_TxStsReg__STATUS_AUX_CTL_REG)
#define SPI_1_TX_STATUS_ACTL_PTR    (  (reg8 *) \
        SPI_1_TX_BSPIS_TxStsReg__STATUS_AUX_CTL_REG)

#define SPI_1_RX_STATUS_ACTL_REG    (* (reg8 *) \
        SPI_1_BSPIS_RxStsReg__STATUS_AUX_CTL_REG)
#define SPI_1_RX_STATUS_ACTL_PTR    (  (reg8 *) \
        SPI_1_RX_BSPIS_RxStsReg__STATUS_AUX_CTL_REG)

#if(SPI_1_BIDIRECTIONAL_MODE)

    #define SPI_1_CONTROL_REG       (* (reg8 *) \
   SPI_1_BSPIS_SyncCtl_CtrlReg__CONTROL_REG)
    #define SPI_1_CONTROL_PTR       (  (reg8 *) \
   SPI_1_BSPIS_SyncCtl_CtrlReg__CONTROL_REG)

#endif /* SPI_1_BIDIRECTIONAL_MODE */


/***************************************
*       Register Constants
***************************************/

/* Status Register Definitions */
#define SPI_1_STS_SPI_DONE_SHIFT             (0x00u)
#define SPI_1_STS_TX_FIFO_NOT_FULL_SHIFT     (0x01u)
#define SPI_1_STS_TX_FIFO_EMPTY_SHIFT        (0x02u)
#define SPI_1_STS_RX_FIFO_NOT_EMPTY_SHIFT    (0x03u)
#define SPI_1_STS_RX_FIFO_EMPTY_SHIFT        (0x04u)
#define SPI_1_STS_RX_FIFO_OVERRUN_SHIFT      (0x05u)
#define SPI_1_STS_RX_FIFO_FULL_SHIFT         (0x06u)
#define SPI_1_STS_BYTE_COMPLETE_SHIFT        (0x06u)

#define SPI_1_STS_SPI_DONE                   ((uint8)(0x01u << SPI_1_STS_SPI_DONE_SHIFT))
#define SPI_1_STS_TX_FIFO_EMPTY              ((uint8)(0x01u << SPI_1_STS_TX_FIFO_EMPTY_SHIFT))
#define SPI_1_STS_TX_FIFO_NOT_FULL           ((uint8)(0x01u << SPI_1_STS_TX_FIFO_NOT_FULL_SHIFT))
#define SPI_1_STS_RX_FIFO_EMPTY              ((uint8)(0x01u << SPI_1_STS_RX_FIFO_EMPTY_SHIFT))
#define SPI_1_STS_RX_FIFO_NOT_EMPTY          ((uint8)(0x01u << SPI_1_STS_RX_FIFO_NOT_EMPTY_SHIFT))
#define SPI_1_STS_RX_FIFO_OVERRUN            ((uint8)(0x01u << SPI_1_STS_RX_FIFO_OVERRUN_SHIFT))
#define SPI_1_STS_RX_FIFO_FULL               ((uint8)(0x01u << SPI_1_STS_RX_FIFO_FULL_SHIFT))
#define SPI_1_STS_BYTE_COMPLETE              ((uint8)(0x01u << SPI_1_STS_BYTE_COMPLETE_SHIFT))

#define SPI_1_STS_CLR_ON_RD_BYTES_MASK       (0x61u)

/* StatusI Register Interrupt Enable Control Bits */
/* As defined by the Register map for the AUX Control Register */
#define SPI_1_INT_ENABLE                     (0x10u)
#define SPI_1_TX_FIFO_CLR    (0x01u) /* F0 - TX FIFO */
#define SPI_1_RX_FIFO_CLR    (0x02u) /* F1 - RX FIFO */
#define SPI_1_FIFO_CLR       (SPI_1_TX_FIFO_CLR | SPI_1_RX_FIFO_CLR)

/* Bit Counter (7-bit) Control Register Bit Definitions */
/* As defined by the Register map for the AUX Control Register */
#define SPI_1_CNTR_ENABLE                    (0x20u)

/* Bi-Directional mode control bit */
#define SPI_1_CTRL_TX_SIGNAL_EN              (0x01u)

/* Datapath Auxillary Control Register definitions */
#define SPI_1_AUX_CTRL_FIFO0_CLR             (0x00u)
#define SPI_1_AUX_CTRL_FIFO1_CLR             (0x00u)
#define SPI_1_AUX_CTRL_FIFO0_LVL             (0x00u)
#define SPI_1_AUX_CTRL_FIFO1_LVL             (0x00u)
#define SPI_1_STATUS_ACTL_INT_EN_MASK        (0x10u)

/* Component disabled */
#define SPI_1_DISABLED   (0u)

/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define SPI_1_TXDATA_ZERO               (SPI_1_TXDATA_ZERO_REG)
#define SPI_1_TXDATA                    (SPI_1_TXDATA_REG)
#define SPI_1_RXDATA                    (SPI_1_RXDATA_REG)
#define SPI_1_MISO_AUX_CONTROLDP0       (SPI_1_MISO_AUX_CTRL_DP0_REG)
#define SPI_1_MOSI_AUX_CONTROLDP0       (SPI_1_MOSI_AUX_CTRL_DP0_REG)
#define SPI_1_TXBUFFERREAD              (SPI_1_txBufferRead)
#define SPI_1_TXBUFFERWRITE             (SPI_1_txBufferWrite)
#define SPI_1_RXBUFFERREAD              (SPI_1_rxBufferRead)
#define SPI_1_RXBUFFERWRITE             (SPI_1_rxBufferWrite)

#if(SPI_1_DATA_WIDTH > 8u)

    #define SPI_1_MISO_AUX_CONTROLDP1   (SPI_1_MISO_AUX_CTRL_DP1_REG)
    #define SPI_1_MOSI_AUX_CONTROLDP1   (SPI_1_MOSI_AUX_CTRL_DP0_REG)

#endif /* SPI_1_DATA_WIDTH > 8u */

#define SPI_1_COUNTER_PERIOD            (SPI_1_COUNTER_PERIOD_REG)
#define SPI_1_COUNTER_CONTROL           (SPI_1_COUNTER_CONTROL_REG)
#define SPI_1_ONE                       (SPI_1_ONE_REG)
#define SPI_1_STATUS                    (SPI_1_TX_STATUS_REG)
#define SPI_1_STATUS_MASK               (SPI_1_TX_STATUS_MASK_REG)
#define SPI_1_STATUS_ACTL               (SPI_1_TX_STATUS_ACTL_REG)

#define SPI_1_WriteByte      (SPI_1_WriteTxData)
#define SPI_1_ReadByte       (SPI_1_ReadRxData)
#define SPI_1_WriteByteZero  (SPI_1_WriteTxDataZero)
void  SPI_1_SetInterruptMode(uint8 intSrc) ;
uint8 SPI_1_ReadStatus(void) ;
void  SPI_1_EnableInt(void) ;
void  SPI_1_DisableInt(void) ;

#define SPI_1_STS_TX_BUF_NOT_FULL_SHIFT      (0x01u)
#define SPI_1_STS_TX_BUF_FULL_SHIFT          (0x02u)
#define SPI_1_STS_RX_BUF_NOT_EMPTY_SHIFT     (0x03u)
#define SPI_1_STS_RX_BUF_EMPTY_SHIFT         (0x04u)
#define SPI_1_STS_RX_BUF_OVERRUN_SHIFT       (0x05u)

#define SPI_1_STS_TX_BUF_NOT_FULL            ((uint8)(0x01u << SPI_1_STS_TX_BUF_NOT_FULL_SHIFT))
#define SPI_1_STS_TX_BUF_FULL                ((uint8)(0x01u << SPI_1_STS_TX_BUF_FULL_SHIFT))
#define SPI_1_STS_RX_BUF_NOT_EMPTY           ((uint8)(0x01u << SPI_1_STS_RX_BUF_NOT_EMPTY_SHIFT))
#define SPI_1_STS_RX_BUF_EMPTY               ((uint8)(0x01u << SPI_1_STS_RX_BUF_EMPTY_SHIFT))
#define SPI_1_STS_RX_BUF_OVERRUN             ((uint8)(0x01u << SPI_1_STS_RX_BUF_OVERRUN_SHIFT))

#define SPI_1_DataWidth                  (SPI_1_DATA_WIDTH)
#define SPI_1_InternalClockUsed          (SPI_1_INTERNAL_CLOCK)
#define SPI_1_InternalTxInterruptEnabled (SPI_1_INTERNAL_TX_INT_ENABLED)
#define SPI_1_InternalRxInterruptEnabled (SPI_1_INTERNAL_RX_INT_ENABLED)
#define SPI_1_ModeUseZero                (SPI_1_MODE_USE_ZERO)
#define SPI_1_BidirectionalMode          (SPI_1_BIDIRECTIONAL_MODE)
#define SPI_1_Mode                       (SPI_1_MODE)
#define SPI_1_DATAWIDHT                  (SPI_1_DATA_WIDTH)
#define SPI_1_InternalInterruptEnabled   (0u)

#define SPI_1_TXBUFFERSIZE   (SPI_1_TX_BUFFER_SIZE)
#define SPI_1_RXBUFFERSIZE   (SPI_1_RX_BUFFER_SIZE)

#define SPI_1_TXBUFFER       SPI_1_txBuffer
#define SPI_1_RXBUFFER       SPI_1_rxBuffer

#endif  /* CY_SPIS_SPI_1_H */

/* [] END OF FILE */

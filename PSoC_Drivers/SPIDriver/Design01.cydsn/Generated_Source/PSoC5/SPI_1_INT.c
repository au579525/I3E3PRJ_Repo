/*******************************************************************************
* File Name: SPI_1_INT.c
* Version 2.70
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Slave
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SPI_1_PVT.h"
#include "cyapicallbacks.h"

/* User code required at start of ISR */
/* `#START SPI_1_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: SPI_1_TX_ISR
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPI_1_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  SPI_1_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  SPI_1_txBuffer[SPI_1_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPI_1_TX_ISR)
{

    #if(SPI_1_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (SPI_1_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPI_1_TX_ISR_ENTRY_CALLBACK
        SPI_1_TX_ISR_EntryCallback();
    #endif /* SPI_1_TX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPI_1_ISR_TX_START` */

    /* `#END` */

    #if(SPI_1_TX_SOFTWARE_BUF_ENABLED)
        /* Component interrupt service code */

        /* See if TX data buffer is not empty and there is space in TX FIFO */
        while(SPI_1_txBufferRead != SPI_1_txBufferWrite)
        {
            tmpStatus = SPI_1_GET_STATUS_TX(SPI_1_swStatusTx);
            SPI_1_swStatusTx = tmpStatus;

            if ((SPI_1_swStatusTx & SPI_1_STS_TX_FIFO_NOT_FULL) != 0u)
            {
                if(SPI_1_txBufferFull == 0u)
                {
                   SPI_1_txBufferRead++;

                    if(SPI_1_txBufferRead >= SPI_1_TX_BUFFER_SIZE)
                    {
                        SPI_1_txBufferRead = 0u;
                    }
                }
                else
                {
                    SPI_1_txBufferFull = 0u;
                }

                /* Put data element into the TX FIFO */
                CY_SET_REG8(SPI_1_TXDATA_PTR, 
                                             SPI_1_txBuffer[SPI_1_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        /* If Buffer is empty then disable TX FIFO status interrupt until there is data in the buffer */
        if(SPI_1_txBufferRead == SPI_1_txBufferWrite)
        {
            SPI_1_TX_STATUS_MASK_REG &= ((uint8)~SPI_1_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* SPI_1_TX_SOFTWARE_BUF_ENABLED */

    /* User code required at end of ISR (Optional) */
    /* `#START SPI_1_ISR_TX_END` */

    /* `#END` */
    
    #ifdef SPI_1_TX_ISR_EXIT_CALLBACK
        SPI_1_TX_ISR_ExitCallback();
    #endif /* SPI_1_TX_ISR_EXIT_CALLBACK */
   }


/*******************************************************************************
* Function Name: SPI_1_RX_ISR
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Slave.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SPI_1_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  SPI_1_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  SPI_1_rxBuffer[SPI_1_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SPI_1_RX_ISR)
{
    #if(SPI_1_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (SPI_1_TX_SOFTWARE_BUF_ENABLED) */

    #ifdef SPI_1_RX_ISR_ENTRY_CALLBACK
        SPI_1_RX_ISR_EntryCallback();
    #endif /* SPI_1_RX_ISR_ENTRY_CALLBACK */

    /* User code required at start of ISR */
    /* `#START SPI_1_RX_ISR_START` */

    /* `#END` */
    
    #if(SPI_1_RX_SOFTWARE_BUF_ENABLED)
        tmpStatus = SPI_1_GET_STATUS_RX(SPI_1_swStatusRx);
        SPI_1_swStatusRx = tmpStatus;
        /* See if RX data FIFO has some data and if it can be moved to the RX Buffer */
        while((SPI_1_swStatusRx & SPI_1_STS_RX_FIFO_NOT_EMPTY) != 0u)
        {
            rxData = CY_GET_REG8(SPI_1_RXDATA_PTR);

            /* Set next pointer. */
            SPI_1_rxBufferWrite++;
            if(SPI_1_rxBufferWrite >= SPI_1_RX_BUFFER_SIZE)
            {
                SPI_1_rxBufferWrite = 0u;
            }

            if(SPI_1_rxBufferWrite == SPI_1_rxBufferRead)
            {
                SPI_1_rxBufferRead++;
                if(SPI_1_rxBufferRead >= SPI_1_RX_BUFFER_SIZE)
                {
                    SPI_1_rxBufferRead = 0u;
                }
                SPI_1_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            SPI_1_rxBuffer[SPI_1_rxBufferWrite] = rxData;

            tmpStatus = SPI_1_GET_STATUS_RX(SPI_1_swStatusRx);
            SPI_1_swStatusRx = tmpStatus;
        }
    #endif /* SPI_1_RX_SOFTWARE_BUF_ENABLED */

    /* User code required at end of ISR (Optional) */
    /* `#START SPI_1_RX_ISR_END` */

    /* `#END` */

    #ifdef SPI_1_RX_ISR_EXIT_CALLBACK
        SPI_1_RX_ISR_ExitCallback();
    #endif /* SPI_1_RX_ISR_EXIT_CALLBACK */
}

/* [] END OF FILE */

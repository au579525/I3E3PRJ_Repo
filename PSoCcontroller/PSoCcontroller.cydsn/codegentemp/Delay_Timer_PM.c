/*******************************************************************************
* File Name: Delay_Timer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Delay_Timer.h"

static Delay_Timer_backupStruct Delay_Timer_backup;


/*******************************************************************************
* Function Name: Delay_Timer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Delay_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Delay_Timer_SaveConfig(void) 
{
    #if (!Delay_Timer_UsingFixedFunction)
        Delay_Timer_backup.TimerUdb = Delay_Timer_ReadCounter();
        Delay_Timer_backup.InterruptMaskValue = Delay_Timer_STATUS_MASK;
        #if (Delay_Timer_UsingHWCaptureCounter)
            Delay_Timer_backup.TimerCaptureCounter = Delay_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Delay_Timer_UDB_CONTROL_REG_REMOVED)
            Delay_Timer_backup.TimerControlRegister = Delay_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Delay_Timer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Delay_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Delay_Timer_RestoreConfig(void) 
{   
    #if (!Delay_Timer_UsingFixedFunction)

        Delay_Timer_WriteCounter(Delay_Timer_backup.TimerUdb);
        Delay_Timer_STATUS_MASK =Delay_Timer_backup.InterruptMaskValue;
        #if (Delay_Timer_UsingHWCaptureCounter)
            Delay_Timer_SetCaptureCount(Delay_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Delay_Timer_UDB_CONTROL_REG_REMOVED)
            Delay_Timer_WriteControlRegister(Delay_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Delay_Timer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Delay_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Delay_Timer_Sleep(void) 
{
    #if(!Delay_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Delay_Timer_CTRL_ENABLE == (Delay_Timer_CONTROL & Delay_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Delay_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Delay_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Delay_Timer_Stop();
    Delay_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: Delay_Timer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Delay_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Delay_Timer_Wakeup(void) 
{
    Delay_Timer_RestoreConfig();
    #if(!Delay_Timer_UDB_CONTROL_REG_REMOVED)
        if(Delay_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Delay_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

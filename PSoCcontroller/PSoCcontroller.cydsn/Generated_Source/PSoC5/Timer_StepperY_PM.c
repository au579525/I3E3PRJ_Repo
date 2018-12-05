/*******************************************************************************
* File Name: Timer_StepperY_PM.c
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

#include "Timer_StepperY.h"

static Timer_StepperY_backupStruct Timer_StepperY_backup;


/*******************************************************************************
* Function Name: Timer_StepperY_SaveConfig
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
*  Timer_StepperY_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_StepperY_SaveConfig(void) 
{
    #if (!Timer_StepperY_UsingFixedFunction)
        Timer_StepperY_backup.TimerUdb = Timer_StepperY_ReadCounter();
        Timer_StepperY_backup.InterruptMaskValue = Timer_StepperY_STATUS_MASK;
        #if (Timer_StepperY_UsingHWCaptureCounter)
            Timer_StepperY_backup.TimerCaptureCounter = Timer_StepperY_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_StepperY_UDB_CONTROL_REG_REMOVED)
            Timer_StepperY_backup.TimerControlRegister = Timer_StepperY_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_StepperY_RestoreConfig
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
*  Timer_StepperY_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_StepperY_RestoreConfig(void) 
{   
    #if (!Timer_StepperY_UsingFixedFunction)

        Timer_StepperY_WriteCounter(Timer_StepperY_backup.TimerUdb);
        Timer_StepperY_STATUS_MASK =Timer_StepperY_backup.InterruptMaskValue;
        #if (Timer_StepperY_UsingHWCaptureCounter)
            Timer_StepperY_SetCaptureCount(Timer_StepperY_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_StepperY_UDB_CONTROL_REG_REMOVED)
            Timer_StepperY_WriteControlRegister(Timer_StepperY_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_StepperY_Sleep
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
*  Timer_StepperY_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_StepperY_Sleep(void) 
{
    #if(!Timer_StepperY_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_StepperY_CTRL_ENABLE == (Timer_StepperY_CONTROL & Timer_StepperY_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_StepperY_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_StepperY_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_StepperY_Stop();
    Timer_StepperY_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_StepperY_Wakeup
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
*  Timer_StepperY_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_StepperY_Wakeup(void) 
{
    Timer_StepperY_RestoreConfig();
    #if(!Timer_StepperY_UDB_CONTROL_REG_REMOVED)
        if(Timer_StepperY_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_StepperY_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */

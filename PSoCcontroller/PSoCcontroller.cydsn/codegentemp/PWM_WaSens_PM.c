/*******************************************************************************
* File Name: PWM_WaSens_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_WaSens.h"

static PWM_WaSens_backupStruct PWM_WaSens_backup;


/*******************************************************************************
* Function Name: PWM_WaSens_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_WaSens_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_WaSens_SaveConfig(void) 
{

    #if(!PWM_WaSens_UsingFixedFunction)
        #if(!PWM_WaSens_PWMModeIsCenterAligned)
            PWM_WaSens_backup.PWMPeriod = PWM_WaSens_ReadPeriod();
        #endif /* (!PWM_WaSens_PWMModeIsCenterAligned) */
        PWM_WaSens_backup.PWMUdb = PWM_WaSens_ReadCounter();
        #if (PWM_WaSens_UseStatus)
            PWM_WaSens_backup.InterruptMaskValue = PWM_WaSens_STATUS_MASK;
        #endif /* (PWM_WaSens_UseStatus) */

        #if(PWM_WaSens_DeadBandMode == PWM_WaSens__B_PWM__DBM_256_CLOCKS || \
            PWM_WaSens_DeadBandMode == PWM_WaSens__B_PWM__DBM_2_4_CLOCKS)
            PWM_WaSens_backup.PWMdeadBandValue = PWM_WaSens_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_WaSens_KillModeMinTime)
             PWM_WaSens_backup.PWMKillCounterPeriod = PWM_WaSens_ReadKillTime();
        #endif /* (PWM_WaSens_KillModeMinTime) */

        #if(PWM_WaSens_UseControl)
            PWM_WaSens_backup.PWMControlRegister = PWM_WaSens_ReadControlRegister();
        #endif /* (PWM_WaSens_UseControl) */
    #endif  /* (!PWM_WaSens_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_WaSens_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_WaSens_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_WaSens_RestoreConfig(void) 
{
        #if(!PWM_WaSens_UsingFixedFunction)
            #if(!PWM_WaSens_PWMModeIsCenterAligned)
                PWM_WaSens_WritePeriod(PWM_WaSens_backup.PWMPeriod);
            #endif /* (!PWM_WaSens_PWMModeIsCenterAligned) */

            PWM_WaSens_WriteCounter(PWM_WaSens_backup.PWMUdb);

            #if (PWM_WaSens_UseStatus)
                PWM_WaSens_STATUS_MASK = PWM_WaSens_backup.InterruptMaskValue;
            #endif /* (PWM_WaSens_UseStatus) */

            #if(PWM_WaSens_DeadBandMode == PWM_WaSens__B_PWM__DBM_256_CLOCKS || \
                PWM_WaSens_DeadBandMode == PWM_WaSens__B_PWM__DBM_2_4_CLOCKS)
                PWM_WaSens_WriteDeadTime(PWM_WaSens_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_WaSens_KillModeMinTime)
                PWM_WaSens_WriteKillTime(PWM_WaSens_backup.PWMKillCounterPeriod);
            #endif /* (PWM_WaSens_KillModeMinTime) */

            #if(PWM_WaSens_UseControl)
                PWM_WaSens_WriteControlRegister(PWM_WaSens_backup.PWMControlRegister);
            #endif /* (PWM_WaSens_UseControl) */
        #endif  /* (!PWM_WaSens_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_WaSens_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_WaSens_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_WaSens_Sleep(void) 
{
    #if(PWM_WaSens_UseControl)
        if(PWM_WaSens_CTRL_ENABLE == (PWM_WaSens_CONTROL & PWM_WaSens_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_WaSens_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_WaSens_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_WaSens_UseControl) */

    /* Stop component */
    PWM_WaSens_Stop();

    /* Save registers configuration */
    PWM_WaSens_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_WaSens_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_WaSens_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_WaSens_Wakeup(void) 
{
     /* Restore registers values */
    PWM_WaSens_RestoreConfig();

    if(PWM_WaSens_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_WaSens_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */

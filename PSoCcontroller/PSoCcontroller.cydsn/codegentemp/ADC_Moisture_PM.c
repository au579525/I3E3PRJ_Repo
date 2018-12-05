/*******************************************************************************
* File Name: ADC_Moisture_PM.c
* Version 3.10
*
* Description:
*  This file provides Sleep/WakeUp APIs functionality.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ADC_Moisture.h"


/***************************************
* Local data allocation
***************************************/

static ADC_Moisture_BACKUP_STRUCT  ADC_Moisture_backup =
{
    ADC_Moisture_DISABLED
};


/*******************************************************************************
* Function Name: ADC_Moisture_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_Moisture_SaveConfig(void)
{
    /* All configuration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_Moisture_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ADC_Moisture_RestoreConfig(void)
{
    /* All congiguration registers are marked as [reset_all_retention] */
}


/*******************************************************************************
* Function Name: ADC_Moisture_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred routine to prepare the component for sleep.
*  The ADC_Moisture_Sleep() routine saves the current component state,
*  then it calls the ADC_Stop() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_Moisture_backup - The structure field 'enableState' is modified
*  depending on the enable state of the block before entering to sleep mode.
*
*******************************************************************************/
void ADC_Moisture_Sleep(void)
{
    if((ADC_Moisture_PWRMGR_SAR_REG  & ADC_Moisture_ACT_PWR_SAR_EN) != 0u)
    {
        if((ADC_Moisture_SAR_CSR0_REG & ADC_Moisture_SAR_SOF_START_CONV) != 0u)
        {
            ADC_Moisture_backup.enableState = ADC_Moisture_ENABLED | ADC_Moisture_STARTED;
        }
        else
        {
            ADC_Moisture_backup.enableState = ADC_Moisture_ENABLED;
        }
        ADC_Moisture_Stop();
    }
    else
    {
        ADC_Moisture_backup.enableState = ADC_Moisture_DISABLED;
    }
}


/*******************************************************************************
* Function Name: ADC_Moisture_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred routine to restore the component to the state when
*  ADC_Moisture_Sleep() was called. If the component was enabled before the
*  ADC_Moisture_Sleep() function was called, the
*  ADC_Moisture_Wakeup() function also re-enables the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ADC_Moisture_backup - The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void ADC_Moisture_Wakeup(void)
{
    if(ADC_Moisture_backup.enableState != ADC_Moisture_DISABLED)
    {
        ADC_Moisture_Enable();
        #if(ADC_Moisture_DEFAULT_CONV_MODE != ADC_Moisture__HARDWARE_TRIGGER)
            if((ADC_Moisture_backup.enableState & ADC_Moisture_STARTED) != 0u)
            {
                ADC_Moisture_StartConvert();
            }
        #endif /* End ADC_Moisture_DEFAULT_CONV_MODE != ADC_Moisture__HARDWARE_TRIGGER */
    }
}


/* [] END OF FILE */

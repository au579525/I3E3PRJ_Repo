/*******************************************************************************
* File Name: SPI_read_req.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_SPI_read_req_H) /* Pins SPI_read_req_H */
#define CY_PINS_SPI_read_req_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SPI_read_req_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SPI_read_req__PORT == 15 && ((SPI_read_req__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SPI_read_req_Write(uint8 value);
void    SPI_read_req_SetDriveMode(uint8 mode);
uint8   SPI_read_req_ReadDataReg(void);
uint8   SPI_read_req_Read(void);
void    SPI_read_req_SetInterruptMode(uint16 position, uint16 mode);
uint8   SPI_read_req_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SPI_read_req_SetDriveMode() function.
     *  @{
     */
        #define SPI_read_req_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SPI_read_req_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SPI_read_req_DM_RES_UP          PIN_DM_RES_UP
        #define SPI_read_req_DM_RES_DWN         PIN_DM_RES_DWN
        #define SPI_read_req_DM_OD_LO           PIN_DM_OD_LO
        #define SPI_read_req_DM_OD_HI           PIN_DM_OD_HI
        #define SPI_read_req_DM_STRONG          PIN_DM_STRONG
        #define SPI_read_req_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SPI_read_req_MASK               SPI_read_req__MASK
#define SPI_read_req_SHIFT              SPI_read_req__SHIFT
#define SPI_read_req_WIDTH              1u

/* Interrupt constants */
#if defined(SPI_read_req__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SPI_read_req_SetInterruptMode() function.
     *  @{
     */
        #define SPI_read_req_INTR_NONE      (uint16)(0x0000u)
        #define SPI_read_req_INTR_RISING    (uint16)(0x0001u)
        #define SPI_read_req_INTR_FALLING   (uint16)(0x0002u)
        #define SPI_read_req_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SPI_read_req_INTR_MASK      (0x01u) 
#endif /* (SPI_read_req__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SPI_read_req_PS                     (* (reg8 *) SPI_read_req__PS)
/* Data Register */
#define SPI_read_req_DR                     (* (reg8 *) SPI_read_req__DR)
/* Port Number */
#define SPI_read_req_PRT_NUM                (* (reg8 *) SPI_read_req__PRT) 
/* Connect to Analog Globals */                                                  
#define SPI_read_req_AG                     (* (reg8 *) SPI_read_req__AG)                       
/* Analog MUX bux enable */
#define SPI_read_req_AMUX                   (* (reg8 *) SPI_read_req__AMUX) 
/* Bidirectional Enable */                                                        
#define SPI_read_req_BIE                    (* (reg8 *) SPI_read_req__BIE)
/* Bit-mask for Aliased Register Access */
#define SPI_read_req_BIT_MASK               (* (reg8 *) SPI_read_req__BIT_MASK)
/* Bypass Enable */
#define SPI_read_req_BYP                    (* (reg8 *) SPI_read_req__BYP)
/* Port wide control signals */                                                   
#define SPI_read_req_CTL                    (* (reg8 *) SPI_read_req__CTL)
/* Drive Modes */
#define SPI_read_req_DM0                    (* (reg8 *) SPI_read_req__DM0) 
#define SPI_read_req_DM1                    (* (reg8 *) SPI_read_req__DM1)
#define SPI_read_req_DM2                    (* (reg8 *) SPI_read_req__DM2) 
/* Input Buffer Disable Override */
#define SPI_read_req_INP_DIS                (* (reg8 *) SPI_read_req__INP_DIS)
/* LCD Common or Segment Drive */
#define SPI_read_req_LCD_COM_SEG            (* (reg8 *) SPI_read_req__LCD_COM_SEG)
/* Enable Segment LCD */
#define SPI_read_req_LCD_EN                 (* (reg8 *) SPI_read_req__LCD_EN)
/* Slew Rate Control */
#define SPI_read_req_SLW                    (* (reg8 *) SPI_read_req__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SPI_read_req_PRTDSI__CAPS_SEL       (* (reg8 *) SPI_read_req__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SPI_read_req_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SPI_read_req__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SPI_read_req_PRTDSI__OE_SEL0        (* (reg8 *) SPI_read_req__PRTDSI__OE_SEL0) 
#define SPI_read_req_PRTDSI__OE_SEL1        (* (reg8 *) SPI_read_req__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SPI_read_req_PRTDSI__OUT_SEL0       (* (reg8 *) SPI_read_req__PRTDSI__OUT_SEL0) 
#define SPI_read_req_PRTDSI__OUT_SEL1       (* (reg8 *) SPI_read_req__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SPI_read_req_PRTDSI__SYNC_OUT       (* (reg8 *) SPI_read_req__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SPI_read_req__SIO_CFG)
    #define SPI_read_req_SIO_HYST_EN        (* (reg8 *) SPI_read_req__SIO_HYST_EN)
    #define SPI_read_req_SIO_REG_HIFREQ     (* (reg8 *) SPI_read_req__SIO_REG_HIFREQ)
    #define SPI_read_req_SIO_CFG            (* (reg8 *) SPI_read_req__SIO_CFG)
    #define SPI_read_req_SIO_DIFF           (* (reg8 *) SPI_read_req__SIO_DIFF)
#endif /* (SPI_read_req__SIO_CFG) */

/* Interrupt Registers */
#if defined(SPI_read_req__INTSTAT)
    #define SPI_read_req_INTSTAT            (* (reg8 *) SPI_read_req__INTSTAT)
    #define SPI_read_req_SNAP               (* (reg8 *) SPI_read_req__SNAP)
    
	#define SPI_read_req_0_INTTYPE_REG 		(* (reg8 *) SPI_read_req__0__INTTYPE)
#endif /* (SPI_read_req__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SPI_read_req_H */


/* [] END OF FILE */

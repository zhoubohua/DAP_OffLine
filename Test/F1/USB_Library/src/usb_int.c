/******************** (C) COPYRIGHT ********************************************
* File Name          : usb_int.c
* Author             : zhaoqunzhang
* Version            : V1.0
* Date               : 12/16/2014
* Description        : Endpoint CTR (Low and High) interrupt's service routines
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"

u16 SaveRState;
u16 SaveTState;

/* Extern variables ----------------------------------------------------------*/
extern void (*pEpInt_IN[7])(void);    /*  Handles IN  interrupts   */
extern void (*pEpInt_OUT[7])(void);   /*  Handles OUT interrupts   */

/*******************************************************************************
* Function Name  : CTR_LP.
* Description    : Low priority Endpoint Correct Transfer interrupt's service
*                  routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CTR_LP(void)  
{
  u32 wEPVal = 0;
  /* stay in loop while pending ints */
  while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
  {
    _SetISTR((u16)CLR_CTR); /* clear CTR flag */
    EPindex = (u8)(wIstr & ISTR_EP_ID);/* extract highest priority endpoint number */
    if (EPindex == 0)
    {
      SaveRState = _GetEPRxStatus(ENDP0);
      SaveTState = _GetEPTxStatus(ENDP0);
      _SetEPRxStatus(ENDP0, EP_RX_NAK);
      _SetEPTxStatus(ENDP0, EP_TX_NAK);

      if ((wIstr & ISTR_DIR) == 0)
      {
        _ClearEP_CTR_TX(ENDP0);
        In0_Process();  
        _SetEPRxStatus(ENDP0, SaveRState);/* before terminate set Tx & Rx status */
        _SetEPTxStatus(ENDP0, SaveTState);
        return;
      }
      else
      {
        wEPVal = _GetENDPOINT(ENDP0);
        if ((wEPVal & EP_CTR_TX) != 0)
        {
          _ClearEP_CTR_TX(ENDP0);
          In0_Process();
          _SetEPRxStatus(ENDP0, SaveRState);
          _SetEPTxStatus(ENDP0, SaveTState);
          return;
        }
        else if ((wEPVal &EP_SETUP) != 0)
        {
          _ClearEP_CTR_RX(ENDP0); /* SETUP bit kept frozen while CTR_RX = 1 */
          Setup0_Process();
          _SetEPRxStatus(ENDP0, SaveRState);
          _SetEPTxStatus(ENDP0, SaveTState);
          return;
        }

        else if ((wEPVal & EP_CTR_RX) != 0)
        {
          _ClearEP_CTR_RX(ENDP0);
          Out0_Process();
          _SetEPRxStatus(ENDP0, SaveRState);
          _SetEPTxStatus(ENDP0, SaveTState);
          return;
        }
      }
    }
    else
    {
      wEPVal = _GetENDPOINT(EPindex);
      if ((wEPVal & EP_CTR_RX) != 0)
      {
        _ClearEP_CTR_RX(EPindex);/* clear int flag */
        (*pEpInt_OUT[EPindex-1])();/* call OUT service function */
      }

      if ((wEPVal & EP_CTR_TX) != 0)
      {
        _ClearEP_CTR_TX(EPindex);
        (*pEpInt_IN[EPindex-1])();
      }
    }
  }
}

/*******************************************************************************
* Function Name  : CTR_HP.
* Description    : High Priority Endpoint Correct Transfer interrupt's service 
*                  routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void CTR_HP(void)
{
  u32 wEPVal = 0;

  while (((wIstr = _GetISTR()) & ISTR_CTR) != 0)
  {
    _SetISTR((u16)CLR_CTR); /* clear CTR flag */   
    EPindex = (u8)(wIstr & ISTR_EP_ID);/* extract highest priority endpoint number */ 
    wEPVal = _GetENDPOINT(EPindex);/* process related endpoint register */
    if ((wEPVal & EP_CTR_RX) != 0)
    {      
      _ClearEP_CTR_RX(EPindex);/* clear int flag */     
      (*pEpInt_OUT[EPindex-1])();/* call OUT service function */

    }
    else if ((wEPVal & EP_CTR_TX) != 0)
    {
      _ClearEP_CTR_TX(EPindex); 
      (*pEpInt_IN[EPindex-1])();/* call IN service function */
    }
  }
}

/******************* (C) COPYRIGHT 2008 STMicroelectronics *****END OF FILE****/

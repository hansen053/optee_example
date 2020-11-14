/****************************************************************************************/
/*               COPYRIGHT INFORMATION                                                  */
/*    	All rights reserved:hansen@autobio.com.cn                                       */
/****************************************************************************************/
/*
 ****************************************************************************************
 *
 *
 * Filename      : AutoTaFsHandle.h
 * Mail          : hansen@autobio.com.cn  
 * Create Time   : 25 August 2020 
 ****************************************************************************************
 */


#ifndef AUTOTACRYPTOHANDLE_H_
#define AUTOTACRYPTOHANDLE_H_




/*
 *******************************************************************************
 *                                INCLUDE FILES
 *******************************************************************************
*/
#include "AutoTaType.h"





/*
 *******************************************************************************
 *                  MACRO DEFINITION USED ONLY BY THIS MODULE
 *******************************************************************************
*/
/* Define the UUID of this TA */


    



/*
 *******************************************************************************
 *                STRUCTRUE DEFINITION USED ONLY BY THIS MODULE
 *******************************************************************************
*/













/*
 *******************************************************************************
 *                      VARIABLES SUPPLIED BY THIS MODULE
 *******************************************************************************
*/





/*
 *******************************************************************************
 *                      FUNCTIONS SUPPLIED BY THIS MODULE
 *******************************************************************************
*/
extern int g_CryptoTaHandle_Random(uint32_t paramTypes, TEE_Param params[4]);
extern int g_CryptoTaHandle_Sha(uint32_t paramTypes, TEE_Param params[4]);
extern int g_CryptoTaHandle_Aes(uint32_t paramTypes, TEE_Param params[4]);
extern int g_CryptoTaHandle_Rsa(uint32_t paramTypes, TEE_Param params[4], UINT32 opMode, UINT32 padding);
extern int g_CryptoTaHandle_Pbkdf(uint32_t paramTypes, TEE_Param params[4]);
extern int g_CryptoTaHandle_hmac(uint32_t paramTypes, TEE_Param params[4]);
extern int g_CryptoTaHandle_base64(uint32_t paramTypes, TEE_Param params[4]);










#endif  /* MOUDLE_NAME_H*/

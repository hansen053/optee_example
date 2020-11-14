/****************************************************************************************/
/*               COPYRIGHT INFORMATION                                                  */
/*    	All rights reserved:hansen@autobio.com.cn                                       */
/****************************************************************************************/
/*
 ****************************************************************************************
 *
 *
 * Filename      : AutoTaEntry.c
 * Mail          : hansen@autobio.com.cn  
 * Create Time   : 25 August 2020 
 ****************************************************************************************
 */


#define AUTOTAENTYR_C_

/** @defgroup MODULE_NAME_INFOR
* @{
*/

/*
 *******************************************************************************
 *                                INCLUDE FILES
 *******************************************************************************
*/
#include "AutoTaHandle.h"
#include "AutoTaCryptoHandle.h"
#include "AutoTaRsa.h"






/*
 *******************************************************************************
 *                         FUNCTIONS SUPPLIED BY THIS MODULE
 *******************************************************************************
*/





/*
 *******************************************************************************
 *                          VARIABLES SUPPLIED BY THIS MODULE
 *******************************************************************************
*/





/*
 *******************************************************************************
 *                          FUNCTIONS USED ONLY BY THIS MODULE
 *******************************************************************************
*/





/*
 *******************************************************************************
 *                          VARIABLES USED ONLY BY THIS MODULE
 *******************************************************************************
*/





/*
 *******************************************************************************
 *                               FUNCTIONS IMPLEMENT
 *******************************************************************************
*/
/** @ingroup MOUDLE_NAME_C_
 *- #Description  This function creating the entry point of crypto verify task.
 * @param   void
 *
 * @return     TEE_Result
 * @retval     TEE_SUCCESS
 *
 *
 */
TEE_Result TA_CreateEntryPoint(void)
{
    TF("Sec storage task test TA_CreateEntryPoint \n");
    
    return TEE_SUCCESS;
}







/** @ingroup MOUDLE_NAME_C_
 *- #Description  This function openning the session of crypto verify task.
 * @param   void
 *
 * @return     TEE_Result
 * @retval     TEE_SUCCESS
 *
 *
 */
TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes, TEE_Param __maybe_unused params[4], 
                void __maybe_unused **sessionContext)
{
    TEE_Result ret=TEE_SUCCESS;
    TF("Sec storage task test TA_OpenSessionEntryPoint\n");

    UNUSED(paramTypes);
    UNUSED(params);
    UNUSED(sessionContext);

    return ret;
}



/** @ingroup MOUDLE_NAME_C_
 *- #Description  This function closing the seccsion of crypto verify task.
 * @param   void
 *
 * @return     TEE_Result
 * @retval     TEE_SUCCESS
 *
 *
 */
void TA_CloseSessionEntryPoint(void __maybe_unused *session_context)
{
    TF("Sec storage task test TA_CloseSessionEntryPoint\n");
    UNUSED(session_context);
}



/** @ingroup MOUDLE_NAME_C_
 *- #Description  This function for destroying the task of crypto verify.
 * @param   void
 *
 * @return     TEE_Result
 * @retval     TEE_SUCCESS
 *
 *
 */

void TA_DestroyEntryPoint(void)
{
    TF("Sec storage task test TA_DestroyEntryPoint\n");
}







/** @ingroup MOUDLE_NAME_C_
 *- #Description  This function for handling the command in crypto verify task.
 * @param   void
 *
 * @return     TEE_Result
 * @retval     TEE_SUCCESS
 *
 *
 */
TEE_Result TA_InvokeCommandEntryPoint(void __maybe_unused *session_context,
                uint32_t cmd_id, 
                uint32_t paramTypes, TEE_Param params[4])
{
    TEE_Result l_ret = TEE_SUCCESS;
    UNUSED(paramTypes);

    TF("CMD_ID = %d\n", cmd_id);

    /** 1) Handle the CA request message according to command index
    *      - EN_CMD_AES_KEY_GET: Get the aes boot key;
    *      - Default:            discard the message */
    switch(cmd_id)
    {
       /*********Value dec or inc*************/
    	case CMD_DEC_VALUE:
            l_ret =  g_Dec_Value(paramTypes,params);
            break;
    	case CMD_INC_VALUE:
            l_ret =  g_Inc_Value(paramTypes,params);
            break;	
		
		/*********data or dir  test and opertion *************/
        case CMD_TEST:
            l_ret = store_data_sample();
            break;
        case CMD_CREATE_OPER:
            l_ret = g_SecStorTa_CreateFile(paramTypes, params);
            break;
        case CMD_READ_OPER:
            l_ret = g_SecStorTa_Read(paramTypes, params);
            break;
        case CMD_WRITE_OPER:
            l_ret = g_SecStorTa_Write(paramTypes, params);
            break;
        case CMD_TRUNCATE_OPER:
            l_ret = g_SecStorTa_Truncate(paramTypes, params);
            break;
        case CMD_RENAME_OPER:
            l_ret = g_SecStorTa_Rename(paramTypes, params);
            break;
        case CMD_DEL_OPER:
            l_ret = g_SecStorTa_Dle(paramTypes, params);
            break;  
		/******crypto*********/
		case CMD_GEN_RANDOM_OPER: 
            TF("Start to generate random data!!!!\n");
            l_ret= g_CryptoTaHandle_Random(paramTypes, params);
            break;
        case CMD_SHA_OPER:
            TF("Entry the sha oper\n");
            l_ret = g_CryptoTaHandle_Sha(paramTypes, params);
            break;
        case CMD_AES_OPER:
            TF("Entry the aes operation!!!\n");
            l_ret = g_CryptoTaHandle_Aes(paramTypes, params);
            break;
        case CMD_PBKDF_OPER:
            TF("Entry pbkdf operation!!\n");
            l_ret = g_CryptoTaHandle_Pbkdf(paramTypes, params);
            break;
        case CMD_RSA_ENC_PKCS1_OPER:
            TF("Entry RSA1024_ENC_PKCS1!\n");
            l_ret = g_CryptoTaHandle_Rsa(paramTypes, params, EM_OP_ENC, PADDING_PKCS1);
            break;
        case CMD_RSA_DEC_PKCS1_OPER:
            TF("Entry RSA1024_DEC_PKCS1!\n");
            l_ret = g_CryptoTaHandle_Rsa(paramTypes, params, EM_OP_DEC, PADDING_PKCS1);
            break;
        case CMD_RSA_SIGN_PKCS1_OPER:
            TF("Entry RSA1024_SIGN_PKCS1!\n");
            l_ret = g_CryptoTaHandle_Rsa(paramTypes, params, EM_OP_SIGN, PADDING_PKCS1);
            break;
        case CMD_RSA_VERIFY_PKCS1_OPER:
            TF("Entry RSA1024_VERIFY_PKCS1!\n");
            l_ret = g_CryptoTaHandle_Rsa(paramTypes, params, EM_OP_VERIFY, PADDING_PKCS1);
            break;
        case CMD_HMAC_OPER:
            TF("Entry HMAC!\n");
            l_ret = g_CryptoTaHandle_hmac(paramTypes, params);
            break;
        case CMD_BASE64_OPER:
            TF("Entry BASE64!\n");
            l_ret = g_CryptoTaHandle_base64(paramTypes, params);
            break;
		/******  *********/
        default:
            l_ret = TEE_EXEC_FAIL;
            break;
    }

    /**3) Return the result */
    return  l_ret;
}


























/**
 * @}
 */

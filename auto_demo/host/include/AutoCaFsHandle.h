/****************************************************************************************/
/*               COPYRIGHT INFORMATION                                                  */
/*    	All rights reserved:hansen@autobio.com.cn                                       */
/****************************************************************************************/
/*
 ****************************************************************************************
 *
 *
 * Filename      : AutoCaCaFsHandle.h
 * Mail          : hansen@autobio.com.cn  
 * Create Time   : 25 August 2020 
 ****************************************************************************************
 */

#ifndef AUTOCADEBUG_H_
#define AUTOCADEBUG_H_




/*
 *******************************************************************************
 *                                INCLUDE FILES
 *******************************************************************************
*/





/*
 *******************************************************************************
 *                  MACRO DEFINITION USED ONLY BY THIS MODULE
 *******************************************************************************
*/





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




#ifndef AUTOCADEBUG_C_

/*
 *******************************************************************************
 *                      FUNCTIONS SUPPLIED BY THIS MODULE
 *******************************************************************************
*/
extern int g_SecStorCa_CreateFile(UINT32 len, CHAR* fileName);
extern int g_SecStorCa_ReadFile(UINT32 fLen, CHAR* fName , UINT32 len, CHAR* output);
extern int g_SecStorCa_WiteFile(UINT32 fLen, CHAR* fName , UINT32 len, CHAR* input);
extern int g_SecStorCa_TrunCatFile(UINT32 fLen, CHAR* fName, UINT32 size);
extern int g_SecStorCa_RenameFile(UINT32 oldLen, CHAR* oldName, UINT32 newLen, CHAR* newName);
extern int g_SecStorCa_DeleteFile(UINT32 oldLen, CHAR* oldName);
extern void g_SecStorCa_test();


extern int g_ValueCa_Dec(UINT32 val);
extern int g_ValueCa_Inc(UINT32 val);



extern int g_CryptoVerifyCa_Random(UINT32 len, CHAR* output);
extern int g_CryptoVerifyCa_Sha(CHAR* pData, UINT32 len, EN_SHA_MODE shaMode, CHAR* output, UINT32 outLen);
extern int g_CryptoVerifyCa_Pbkdf(UINT32 len, CHAR* output);
extern int g_CryptoVerifyCa_Rsa(RsaCaPara rsaPara);
extern int g_CryptoVerifyCa_Aes(CHAR* pData, UINT32 len, EN_AES_MODE aesMode, EN_AES_OPERATION_ACTION operAction, CHAR* output);
extern int g_CryptoVerifyCa_hmac(UINT32 len, CHAR* output, UINT32 count);
extern int g_CryptoVerifyCa_base64(CHAR* input, UINT32 lenIn, CHAR* output, UINT32 lenOut, UINT32 oper);

















#endif  


#endif  /* MOUDLE_NAME_H*/

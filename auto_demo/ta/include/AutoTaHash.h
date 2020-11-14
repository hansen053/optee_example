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


#ifndef AUTOTAHASH_H_
#define AUTOTAHASH_H_




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
/* SHA operation type */
typedef enum
{
    EN_OP_SHA1 = 1,
    EN_OP_SHA224,
    EN_OP_SHA256,
    EN_OP_SHA384,
    EN_OP_SHA512,
    EN_OP_SHA_INVALID
}EN_SHA_MODE;














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



extern void test_hash(void);

extern int g_CryptoTaHash_sha(EN_SHA_MODE shaMode, CHAR* input, UINT32 inLen, CHAR* output, UINT32* pOutLen);
extern int g_CryptoTaHash_hmac(CHAR* output, UINT32 OutLen, CHAR* passWd, UINT32 passLen, CHAR* salt, UINT32 saltLen, UINT32 count);








#endif  /* MOUDLE_NAME_H*/

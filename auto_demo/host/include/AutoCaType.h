/****************************************************************************************/
/*               COPYRIGHT INFORMATION                                                  */
/*    	All rights reserved:hansen@autobio.com.cn                                       */
/****************************************************************************************/
/*
 ****************************************************************************************
 *
 *
 * Filename      : AutoCaTupe.h
 * Mail          : hansen@autobio.com.cn  
 * Create Time   : 25 August 2020 
 ****************************************************************************************
 */


#ifndef AUTOCATYPE_H_ 
#define AUTOCATYPE_H_




/*
 *******************************************************************************
 *                                INCLUDE FILES
 *******************************************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "tee_client_api.h"




/*
 *******************************************************************************
 *                  MACRO DEFINITION USED ONLY BY THIS MODULE
 *******************************************************************************
*/
    /* Define the return status of each function */
#define   FAIL     -1            /* Return value when operation fail */
#define   OK        0            /* Return value when operation OK */

/* RSA key bit elect */
#define RSA_1024        1U        /* Do RSA signa operation */
#define RSA_2048        2U       /* Do RSA authentic operation */



/*
 *******************************************************************************
 *                STRUCTRUE DEFINITION USED ONLY BY THIS MODULE
 *******************************************************************************
*/
/* Define the type of variable */
typedef unsigned char  UINT8;    /**< Typedef for 8bits unsigned integer  */
typedef unsigned short UINT16;   /**< Typedef for 16bits unsigned integer */
typedef unsigned int   UINT32;   /**< Typedef for 32bits unsigned integer */
typedef signed char    INT8;     /**< Typedef for 8bits signed integer    */
typedef signed short   INT16;    /**< Typedef for 16bits signed integer   */
typedef signed int     INT32;    /**< Typedef for 32bits signed integer   */
typedef char           CHAR;     /**< Typedef for char                    */


/* RSA key type(1024,2048) */
typedef enum
{
    EN_KEY_1024 = 1,
    EN_KEY_2048,
    EN_KEY_INVALID
}EN_RSA_KEY_TYPE;


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



/* AES operation type */
typedef enum
{
    EN_OP_AES_ENCRYPT = 1,
    EN_OP_AES_DECRYPT,
    EN_OP_AES_INVALID
}EN_AES_OPERATION_ACTION;

/* AES mode type */
typedef enum
{
    EN_MODE_CBC = 1,
    EN_MODE_ECB,
    EN_MODE_CTR,
    EN_MODE_CBC_CTS,
    EN_MODE_INVALIE
}EN_AES_MODE;


typedef struct _AesOperModeInfo
{
    EN_AES_OPERATION_ACTION active;
    EN_AES_MODE mode;
}AesOperModeInfo;


typedef struct RsaCaPara_s
{
    CHAR* m_pInput;
    CHAR* m_pOutput;
    UINT32 m_InputLen;
    UINT32 m_OutputLen;
    UINT32 cmdId;
    EN_RSA_KEY_TYPE Rsa_Elect;
}RsaCaPara;



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






















#endif  /* MOUDLE_NAME_H*/

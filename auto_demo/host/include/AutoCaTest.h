/****************************************************************************************/
/*               COPYRIGHT INFORMATION                                                  */
/*    	All rights reserved:hansen@autobio.com.cn                                       */
/****************************************************************************************/
/*
 ****************************************************************************************
 *
 *
 * Filename      : AutoCaTest.h
 * Mail          : hansen@autobio.com.cn  
 * Create Time   : 25 August 2020 
 ****************************************************************************************
 */


#ifndef AUTOCATEST_H_
#define AUTOCATEST_H_




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

/* Define the command index in this TA(Get Aes boot key) */
#define CMD_PRINT                  11U     /**< Command ID of communicat CA with TA */


#define	CMD_INC_VALUE			   22U     /**< Command ID of inc value  */
#define	CMD_DEC_VALUE			   23U     /**< Command ID of dec value */						
#define CMD_GEN_RANDOM_OPER        24U     /**< Command ID of using RSA algorithm to signa data */


#define CMD_SHA_OPER               31U     /**< Command ID of using RSA algorithm to signa data */
#define CMD_AES_OPER               32U
#define CMD_RSA_ENC_PKCS1_OPER     33U     /**< Command ID of using RSA algorithm to signa data */
#define CMD_RSA_DEC_PKCS1_OPER     34U
#define CMD_RSA_SIGN_PKCS1_OPER    35U
#define CMD_RSA_VERIFY_PKCS1_OPER  36U          
#define CMD_HMAC_OPER              37U 
#define CMD_BASE64_OPER            38U
#define CMD_PBKDF_OPER             39U
#define CMD_BN_OPER                40U 


														
#define CMD_CREATE_OPER            41U     /**< Command ID of cread operation in rpmb */
#define CMD_READ_OPER              42U     /**< Command ID of read operation in rpmb */
#define CMD_WRITE_OPER             43U     /**< Command ID of write operation in rpmb */
#define CMD_TRUNCATE_OPER          44U     /**< Command ID of truncate operation in secure storage */
#define CMD_RENAME_OPER            45U     /**< Command ID of rename operation in secure storage */
#define CMD_DEL_OPER               46U     /**< Command ID of close and delete operation in secure storage */
#define CMD_TEST                   47U     /**< Command ID of test operation in secure storage */

#define CMD_MAX_NUMBER             66U     /**< The max command number in this TA           */ 

/* Define the comman ID */







/* Define the UUID of this TA */
#define TA_DEMO_UUID    {0x53e4d3d3, 0x0199, 0x4f74, \
                                                { \
                                                    0xb9, 0x4d, 0x53, 0xd3, 0xda, 0xa5, 0x7d, 0x73 \
                                                } \
                                            }




/*
 *******************************************************************************
 *                      FUNCTIONS SUPPLIED BY THIS MODULE
 *******************************************************************************
*/
























#endif  /* MOUDLE_NAME_H*/

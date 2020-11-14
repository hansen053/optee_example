/****************************************************************************************/
/*                  COPYRIGHT INFORMATION                                               */
/*    	All rights reserved:hansen@autobio.com.cn                                       */
/****************************************************************************************/
/*
 ****************************************************************************************
 *
 *
 * Filename      : AutoCaDebug.c
 * Mail          : hansen@autobio.com.cn  
 * Create Time   : 25 August 2020 
 *****************************************************************************************/
#define AUTOCADEBUG_C_

/** @defgroup MODULE_NAME_INFOR
* @{
*/

/*
 *******************************************************************************
 *                                INCLUDE FILES
 *******************************************************************************
*/
#include "AutoCaType.h"
#include "AutoCaDebug.h"
#include "AutoCaFsHandle.h"
#include "AutoCaTest.h"




/*
 *******************************************************************************
 *                         FUNCTIONS SUPPLIED BY THIS MODULE
 *******************************************************************************
*/
int g_SecStorCa_CreateFile(UINT32 len, CHAR* fileName);
int g_SecStorCa_ReadFile(UINT32 fLen, CHAR* fName , UINT32 len, CHAR* output);
int g_SecStorCa_WiteFile(UINT32 fLen, CHAR* fName , UINT32 len, CHAR* input);
int g_SecStorCa_TrunCatFile(UINT32 fLen, CHAR* fName, UINT32 size);
int g_SecStorCa_RenameFile(UINT32 oldLen, CHAR* oldName, UINT32 newLen, CHAR* newName);
int g_SecStorCa_DeleteFile(UINT32 oldLen, CHAR* oldName);
void g_SecStorCa_test();
int g_ValueCa_Dec(UINT32 val);
int g_ValueCa_Inc(UINT32 val);




/*
 *******************************************************************************
 *                          VARIABLES SUPPLIED BY THIS MODULE
 *******************************************************************************
*/
static int g_TaskInitFlag = -1;    /* Flag if the task done initialize operation */

TEEC_UUID svc_id = TA_DEMO_UUID;
TEEC_Context g_TaskContext;





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

static int l_CryptoVerifyCa_TaskInit(void)
{
    TEEC_Result result;
    int l_RetVal = OK;
    
    /**1) Check if need to do task initialization operation */
    if(-1 == g_TaskInitFlag)
    {
        result = TEEC_InitializeContext(NULL, &g_TaskContext);
        if(result != TEEC_SUCCESS) 
        {
            TF("InitializeContext failed, ReturnCode=0x%x\n", result);
            l_RetVal= FAIL;
        } 
        else 
        {
            g_TaskInitFlag = 1;
            TF("InitializeContext success\n");
            l_RetVal = OK;
        }
    }
    
    return l_RetVal;
}


static int l_CryptoVerifyCa_OpenSession(TEEC_Session* session)
{
    TEEC_Result result;
    int l_RetVal = FAIL;
    uint32_t origin;

    result = TEEC_OpenSession(&g_TaskContext, session, &svc_id, 
                                TEEC_LOGIN_PUBLIC, NULL, NULL, &origin);
    if(result != TEEC_SUCCESS) 
    {
        TF("OpenSession failed, ReturnCode=0x%x, ReturnOrigin=0x%x\n", result, origin);
        g_TaskInitFlag = -1;
        l_RetVal = FAIL;
    } 
    else 
    {

        TF("OpenSession success\n");
        l_RetVal = OK;
    }

    return l_RetVal;
}


static int l_CryptoVerifyCa_SendCommand(TEEC_Operation* operation, TEEC_Session* session, uint32_t commandID)
{
    TEEC_Result result;
    int l_RetVal = FAIL;
    uint32_t origin;

    result = TEEC_InvokeCommand(session, commandID, operation, &origin);
    if (result != TEEC_SUCCESS) 
    {
        TF("InvokeCommand failed, ReturnCode=0x%x, ReturnOrigin=0x%x\n", result, origin);
        l_RetVal = FAIL;
    } 
    else 
    {
        TF("InvokeCommand success\n");
        l_RetVal = OK;
    }


    return l_RetVal;
}

/** @ingroup MOUDLE_NAME_C_
 *- #Description  This function for handle command.
 * @param   pMsg           [IN] The received request message
 *                               - Type: MBX_Msg *
 *                               - Range: N/A.
 *
 * @return     void
 * @retval     void
 *
 *
 */

int g_SecStorCa_CreateFile(UINT32 len, CHAR* fileName)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */
    

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,TEEC_NONE, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].tmpref.size = len;
    l_operation.params[0].tmpref.buffer = fileName;

    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_CREATE_OPER);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }
    else
    {
        goto cleanup_1;
    }


    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}



int g_SecStorCa_ReadFile(UINT32 fLen, CHAR* fName , UINT32 len, CHAR* output)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */
    

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_OUTPUT,TEEC_MEMREF_TEMP_INPUT, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].tmpref.size = len;
    l_operation.params[0].tmpref.buffer = output;
    l_operation.params[1].tmpref.size = fLen;
    l_operation.params[1].tmpref.buffer = fName;



    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_READ_OPER);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }
    else
    {
        goto cleanup_1;
    }


    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}






int g_SecStorCa_WiteFile(UINT32 fLen, CHAR* fName , UINT32 len, CHAR* input)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */
    

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,TEEC_MEMREF_TEMP_INPUT, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].tmpref.size = len;
    l_operation.params[0].tmpref.buffer = input;
    l_operation.params[1].tmpref.size = fLen;
    l_operation.params[1].tmpref.buffer = fName;


    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_WRITE_OPER);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }
    else
    {
        goto cleanup_1;
    }


    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}




int g_SecStorCa_TrunCatFile(UINT32 fLen, CHAR* fName, UINT32 size)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */
    

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT,TEEC_MEMREF_TEMP_INPUT, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].value.a = size;
    l_operation.params[1].tmpref.buffer = fName;
    l_operation.params[1].tmpref.size = fLen;


    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_TRUNCATE_OPER);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }
    else
    {
        goto cleanup_1;
    }


    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}

int g_SecStorCa_RenameFile(UINT32 oldLen, CHAR* oldName, UINT32 newLen, CHAR* newName)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */
    

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,TEEC_MEMREF_TEMP_INPUT, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].tmpref.size = oldLen;
    l_operation.params[0].tmpref.buffer = oldName;
    l_operation.params[1].tmpref.size = newLen;
    l_operation.params[1].tmpref.buffer = newName;



    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_RENAME_OPER);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }
    else
    {
        goto cleanup_1;
    }


    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}





int g_SecStorCa_DeleteFile(UINT32 oldLen, CHAR* oldName)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */
    

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,TEEC_NONE, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].tmpref.size = oldLen;
    l_operation.params[0].tmpref.buffer = oldName;




    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_DEL_OPER);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }
    else
    {
        goto cleanup_1;
    }

    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}




void g_SecStorCa_test()
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE,TEEC_NONE, 
                                              TEEC_NONE, TEEC_NONE);

    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_TEST);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }
    else
    {
        goto cleanup_1;
    }

    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        TF("The successful\n");
}

int g_ValueCa_Dec(UINT32 val)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */
    

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT,TEEC_NONE, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].value.a = val;


    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_DEC_VALUE);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }
    else
    {
        goto cleanup_1;
    }


    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}

int g_ValueCa_Inc(UINT32 val)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */
    

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT,TEEC_NONE, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].value.a = val;


    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_INC_VALUE);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }
    else
    {
        goto cleanup_1;
    }


    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}


int g_CryptoVerifyCa_Random(UINT32 len, CHAR* output)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_OUTPUT,TEEC_NONE, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].tmpref.size = len;
    l_operation.params[0].tmpref.buffer = output;

    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_GEN_RANDOM_OPER);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }

    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}



int g_CryptoVerifyCa_Sha(CHAR* pData, UINT32 len, EN_SHA_MODE shaMode, CHAR* output, UINT32 outLen)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,TEEC_VALUE_INPUT, 
                                              TEEC_MEMREF_TEMP_OUTPUT, TEEC_NONE);
    l_operation.params[0].tmpref.size = len;
    l_operation.params[0].tmpref.buffer = pData;
    l_operation.params[1].value.a = shaMode;
    l_operation.params[2].tmpref.size = outLen;
    l_operation.params[2].tmpref.buffer = output;

    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_SHA_OPER);
    TF("The respond data length is 0x%02x\n", outLen);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }

    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}


int g_CryptoVerifyCa_hmac(UINT32 len, CHAR* output, UINT32 count)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT,TEEC_VALUE_INPUT, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].tmpref.size = len;
    l_operation.params[0].tmpref.buffer = output;
    l_operation.params[1].value.a = count;

    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_HMAC_OPER);
    TF("The respond data length is 0x%02x\n", len);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }

    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}



int g_CryptoVerifyCa_Aes(CHAR* pData, UINT32 len, EN_AES_MODE aesMode, 
                         EN_AES_OPERATION_ACTION operAction, CHAR* output)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    AesOperModeInfo l_aesMode;
    int l_RetVal = FAIL;       /* Define the return value of function */

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    l_aesMode.active = operAction;
    l_aesMode.mode = aesMode;

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INPUT, TEEC_MEMREF_TEMP_INPUT, 
                                              TEEC_MEMREF_TEMP_OUTPUT, TEEC_VALUE_INPUT);
    l_operation.params[0].value.a = operAction;
    l_operation.params[0].value.b = aesMode;
    l_operation.params[1].tmpref.size = len;
    l_operation.params[1].tmpref.buffer = pData;
    l_operation.params[2].tmpref.size = len;
    l_operation.params[2].tmpref.buffer = output;
    l_operation.params[3].value.a = len;

    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_AES_OPER);
    TF("The respond data length is 0x%02x\n", len);
    
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }

    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}




int g_CryptoVerifyCa_Pbkdf(UINT32 len, CHAR* output)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INOUT,TEEC_NONE, 
                                              TEEC_NONE, TEEC_NONE);
    l_operation.params[0].tmpref.size = len;
    l_operation.params[0].tmpref.buffer = output;

    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_PBKDF_OPER);
    TF("The respond data length is 0x%02x\n", len);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }

    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}




int g_CryptoVerifyCa_Rsa(RsaCaPara rsaPara)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    AesOperModeInfo l_aesMode;
    int l_RetVal = FAIL;       /* Define the return value of function */
    TF("The send command id is: %d\n", rsaPara.cmdId);

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT, TEEC_MEMREF_TEMP_OUTPUT, 
                                              TEEC_VALUE_INPUT, TEEC_NONE);
    l_operation.params[0].tmpref.size = rsaPara.m_InputLen;
    l_operation.params[0].tmpref.buffer = rsaPara.m_pInput;
    l_operation.params[1].tmpref.size = rsaPara.m_OutputLen;
    l_operation.params[1].tmpref.buffer = rsaPara.m_pOutput;
    l_operation.params[2].value.a = rsaPara.Rsa_Elect;
    

    /**4) Send command to TA */    
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, rsaPara.cmdId);
    TF("The respond data length is 0x%02x\n", rsaPara.m_OutputLen);
    g_CA_PrintfBuffer(rsaPara.m_pOutput, rsaPara.m_OutputLen);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }

    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);

    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}





int g_CryptoVerifyCa_base64(CHAR* input, UINT32 lenIn, CHAR* output, UINT32 lenOut, UINT32 oper)
{
    TEEC_Session   l_session;    /* Define the session of TA&CA */
    TEEC_Operation l_operation;  /* Define the operation for communicating between TA&CA */
    int l_RetVal = FAIL;       /* Define the return value of function */

    /**1) Initialize this task */
    l_RetVal = l_CryptoVerifyCa_TaskInit();
    if(FAIL == l_RetVal)
    {
        goto cleanup_1;
    }

    /**2) Open session */
    l_RetVal = l_CryptoVerifyCa_OpenSession(&l_session);
    if(FAIL == l_RetVal)
    {
        goto cleanup_2;
    }

    /**3) Set the communication context between CA&TA */
    memset(&l_operation, 0x0, sizeof(TEEC_Operation));
    l_operation.started = 1;
    l_operation.paramTypes = TEEC_PARAM_TYPES(TEEC_MEMREF_TEMP_INPUT,TEEC_MEMREF_TEMP_OUTPUT, 
                                              TEEC_VALUE_INPUT, TEEC_NONE);
    l_operation.params[0].tmpref.size = lenIn;
    l_operation.params[0].tmpref.buffer = input;
    l_operation.params[1].tmpref.size = lenOut;
    l_operation.params[1].tmpref.buffer = output;
    l_operation.params[2].value.a = oper;

    /**4) Send command to TA */
    l_RetVal = l_CryptoVerifyCa_SendCommand(&l_operation, &l_session, CMD_BASE64_OPER);
    TF("The respond data length is 0x%02x\n", lenOut);
    if(FAIL == l_RetVal)
    {
        goto cleanup_3;
    }

    /**5) The clean up operation */
    cleanup_3:
        TEEC_CloseSession(&l_session);
    cleanup_2:
        TEEC_FinalizeContext(&g_TaskContext);
    cleanup_1:
        return l_RetVal;
}
















/**
 * @}
 */

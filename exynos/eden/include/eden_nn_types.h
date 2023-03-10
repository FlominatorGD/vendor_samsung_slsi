/*
 * Copyright (C) 2018 Samsung Electronics Co. LTD
 *
 * This software is proprietary of Samsung Electronics.
 * No part of this software, either material or conceptual may be copied or distributed, transmitted,
 * transcribed, stored in a retrieval system or translated into any human or computer language in any form by any means,
 * electronic, mechanical, manual or otherwise, or disclosed
 * to third parties without the express written permission of Samsung Electronics.
 */

/**
 * @file    eden_nn_types.h
 * @brief   This is common EDEN data structure types.
 * @details This header defines EDEN data structure used by EDEN framework.
 *          They are compatible with C-language.
 * @author  minsu.jeon (minsu.jeon@samsung.com)
 */

#ifndef COMMON_EDEN_NN_TYPES_H_
#define COMMON_EDEN_NN_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  RET_OK = 0,

  ////////////////////////////////////////////////
  ///////////////////// NN ///////////////////////
  ////////////////////////////////////////////////
  // Will be added later
  RET_EDEN_NN_IS_NULL = 1,
  RET_MODEL_ID_IS_INVALID = 2,

  // Runtime related error.
  RET_ERROR_ON_RT_INIT,
  RET_ERROR_ON_RT_OPEN_MODEL,
  RET_ERROR_ON_RT_ALLOCATE_INPUT_BUFFERS,
  RET_ERROR_ON_RT_ALLOCATE_OUTPUT_BUFFERS,
  RET_ERROR_ON_RT_EXECUTE_MODEL,
  RET_ERROR_ON_RT_FREE_BUFFERS,
  RET_ERROR_ON_RT_CLOSE_MODEL,
  RET_ERROR_ON_RT_SHUTDOWN,
  RET_ERROR_ON_RT_GET_INPUT_BUFFER_SHAPE,
  RET_ERROR_ON_RT_GET_OUTPUT_BUFFER_SHAPE,
  RET_ERROR_ON_RT_GET_VERSION,

  ////////////////////////////////////////////////
  /////////////////// MODEL///////////////////////
  ////////////////////////////////////////////////
  RET_MODEL_FILE_PATH_IS_INVALID = 1000,
  RET_MODEL_FILE_READ_IS_FAILED,
  RET_NO_INPUT_TENSOR_FOR_MODEL,
  RET_NO_OUTPUT_TENSOR_FOR_MODEL,
  RET_MODEL_ALREADY_HAS_VALID_MODEL_ID,

  RET_MODEL_IS_NULL,
  RET_OPERATION_ID_IS_NOT_UNIQUE,
  RET_NOT_SUPPORTED_OPERATOR,
  RET_NO_OPERATION_MATCHED_TO_ID,

  RET_INVALID_BUFFER_IS_DELIVERED_TO_BE_FREED,
  RET_NO_MATCHED_BUFFERS,
  RET_UNSUPPORTED_MEM_TYPE,
  RET_INVALID_BUFFER_LAYOUT,

  RET_INVALID_SEQUENCIAL_ORDER,
  RET_NOT_SUPPORTED_FEATURE,

  // EMA related error.
  RET_ERROR_ON_MEM_ALLOCATE,
  RET_ERROR_ON_MEM_FREE,

  // Warning code start
  RET_MODEL_ID_IS_ALREADY_REGISTERED,
  RET_MODEL_ID_IS_NOT_REGISTERED,

  RET_PARAM_INVALID,
  RET_SERVICE_NOT_AVAILABLE,

  RET_INVALID_CODE = 0xffffffff
} NnRet;

#ifdef __cplusplus
}
#endif

#endif  // COMMON_EDEN_NN_TYPES_H_


#pragma once

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <float.h>

/*
 * �v���b�g�t�H�[�����Ɉ�ԑ��x���o��^�B
 * �ʏ�͂��̌^���g�p����B
 */
typedef int_fast8_t T_INT8;
typedef int_fast16_t T_INT16;
typedef int_fast32_t T_INT32;
typedef int_fast64_t T_INT64;

typedef uint_fast8_t T_UINT8;
typedef uint_fast16_t T_UINT16;
typedef uint_fast32_t T_UINT32;
typedef uint_fast64_t T_UINT64;

typedef float T_FLOAT;
typedef double T_DOUBLE;

/*
* �v���b�g�t�H�[���Ɉˑ����Ȃ��A�Œ肳�ꂽ�T�C�Y�̌^�B
* �V���A���C�Y���A�T�C�Y���v���b�g�t�H�[����
* �ˑ����ė~�����Ȃ��P�[�X�Ŏg�p����B
*/
typedef int8_t T_FIXED_INT8;
typedef int16_t T_FIXED_INT16;
typedef int32_t T_FIXED_INT32;
typedef int64_t T_FIXED_INT64;

typedef uint8_t T_FIXED_UINT8;
typedef uint16_t T_FIXED_UINT16;
typedef uint32_t T_FIXED_UINT32;
typedef uint64_t T_FIXED_UINT64;

typedef float T_FIXED_FLOAT;
typedef double T_FIXED_DOUBLE;

namespace Limit
{

const T_INT8 T_INT8_MIN = INT_FAST8_MIN;
const T_INT8 T_INT8_MAX = INT_FAST8_MAX;
const T_INT16 T_INT16_MIN = INT_FAST16_MIN;
const T_INT16 T_INT16_MAX = INT_FAST16_MAX;
const T_INT32 T_INT32_MIN = INT_FAST32_MIN;
const T_INT32 T_INT32_MAX = INT_FAST32_MAX;
const T_INT64 T_INT64_MIN = INT_FAST64_MIN;
const T_INT64 T_INT64_MAX = INT_FAST64_MAX;

const T_UINT8 T_UINT8_MIN = 0;
const T_UINT8 T_UINT8_MAX = UINT_FAST8_MAX;
const T_UINT16 T_UINT16_MIN = 0;
const T_UINT16 T_UINT16_MAX = UINT_FAST16_MAX;
const T_UINT32 T_UINT32_MIN = 0;
const T_UINT32 T_UINT32_MAX = UINT_FAST32_MAX;
const T_UINT64 T_UINT64_MIN = 0;
const T_UINT64 T_UINT64_MAX = UINT_FAST64_MAX;

const T_FLOAT T_FLOAT_MIN = -FLT_MAX;
const T_FLOAT T_FLOAT_MAX = FLT_MAX;
const T_DOUBLE T_DOUBLE_MIN = -DBL_MAX;
const T_DOUBLE T_DOUBLE_MAX = DBL_MAX;

const T_FIXED_INT8 T_FIXED_INT8_MIN = INT8_MIN;
const T_FIXED_INT8 T_FIXED_INT8_MAX = INT8_MAX;
const T_FIXED_INT16 T_FIXED_INT16_MIN = INT16_MIN;
const T_FIXED_INT16 T_FIXED_INT16_MAX = INT16_MAX;
const T_FIXED_INT32 T_FIXED_INT32_MIN = INT32_MIN;
const T_FIXED_INT32 T_FIXED_INT32_MAX = INT32_MAX;
const T_FIXED_INT64 T_FIXED_INT64_MIN = INT64_MIN;
const T_FIXED_INT64 T_FIXED_INT64_MAX = INT64_MAX;

const T_FIXED_UINT8 T_FIXED_UINT8_MIN = 0;
const T_FIXED_UINT8 T_FIXED_UINT8_MAX = UINT8_MAX;
const T_FIXED_UINT16 T_FIXED_UINT16_MIN = 0;
const T_FIXED_UINT16 T_FIXED_UINT16_MAX = UINT16_MAX;
const T_FIXED_UINT32 T_FIXED_UINT32_MIN = 0;
const T_FIXED_UINT32 T_FIXED_UINT32_MAX = UINT32_MAX;
const T_FIXED_UINT64 T_FIXED_UINT64_MIN = 0;
const T_FIXED_UINT64 T_FIXED_UINT64_MAX = UINT64_MAX;

const T_FIXED_FLOAT T_FIXED_FLOAT_MIN = -FLT_MAX;
const T_FIXED_FLOAT T_FIXED_FLOAT_MAX = FLT_MAX;
const T_FIXED_DOUBLE T_FIXED_DOUBLE_MIN = -DBL_MAX;
const T_FIXED_DOUBLE T_FIXED_DOUBLE_MAX = DBL_MAX;

}

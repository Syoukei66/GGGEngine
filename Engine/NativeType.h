#ifndef HAL_ENGINE_NATIVE_NATIVETYPE_H_
#define HAL_ENGINE_NATIVE_NATIVETYPE_H_

#define __STDC_LIMIT_MACROS
#include <stdint.h>
#include <float.h>
#include <assert.h>

/* =================================================================
	�e�v���b�g�t�H�[���ōœK�Ȍ^���`
 * ================================================================= */

 //TODO:���󂾂�Release�r���h��NATIVE_ASSERT���̏������s���Ȃ����߁A�K���K�v�ȏ�����Cause�ɋL�q���Ȃ��悤�ɏC�����邱��
#define NATIVE_ASSERT(Cause, Message) assert(Cause && Message)

 // =================================================================
 // primitive
 // =================================================================

typedef int_fast8_t T_INT8;
typedef int_fast16_t T_INT16;
typedef int_fast32_t T_INT32;
typedef int_fast64_t T_INT64;

static const T_INT8 T_INT8_MIN = INT_FAST8_MIN;
static const T_INT8 T_INT8_MAX = INT_FAST8_MAX;
static const T_INT16 T_INT16_MIN = INT_FAST16_MIN;
static const T_INT16 T_INT16_MAX = INT_FAST16_MAX;
static const T_INT32 T_INT32_MIN = INT_FAST32_MIN;
static const T_INT32 T_INT32_MAX = INT_FAST32_MAX;
static const T_INT64 T_INT64_MIN = INT_FAST64_MIN;
static const T_INT64 T_INT64_MAX = INT_FAST64_MAX;

typedef uint_fast8_t T_UINT8;
typedef uint_fast16_t T_UINT16;
typedef uint_fast32_t T_UINT32;
typedef uint_fast64_t T_UINT64;

static const T_UINT8 T_UINT8_MIN = 0;
static const T_UINT8 T_UINT8_MAX = UINT_FAST8_MAX;
static const T_UINT16 T_UINT16_MIN = 0;
static const T_UINT16 T_UINT16_MAX = UINT_FAST16_MAX;
static const T_UINT32 T_UINT32_MIN = 0;
static const T_UINT32 T_UINT32_MAX = UINT_FAST32_MAX;
static const T_UINT64 T_UINT64_MIN = 0;
static const T_UINT64 T_UINT64_MAX = UINT_FAST64_MAX;

typedef float T_FLOAT;
typedef double T_DOUBLE;

static const T_FLOAT T_FLOAT_MIN = -FLT_MAX;
static const T_FLOAT T_FLOAT_MAX = FLT_MAX;
static const T_DOUBLE T_DOUBLE_MIN = -DBL_MAX;
static const T_DOUBLE T_DOUBLE_MAX = DBL_MAX;

// =================================================================
// blendMode
// =================================================================


typedef T_UINT32 T_PACKED_COLOR_UINT32;

// ===================================================================================
// �l�C�e�B�u�����ŗp�ӂ����C���X�^���X���i�[���邽�߂̌^
// void*���Ɗ֐��̈����ɂ����ہA������|�C���^�^���󂯓����悤�ɂȂ��Ă��܂���肪����
// �Ƃ͂���int*�ł���肪���邽�߁A
// ���struct��p�ӂ�����������̂�������Ȃ�
// ===================================================================================

typedef int* LP_DEVICE;
typedef int* LP_TEXTURE;
typedef int* LP_MATERIAL;

typedef int* LP_MODEL;

typedef int* LP_MATRIX_4x4_STACK;
typedef int* LP_MATRIX_4x4;

typedef int* LP_VERTEX_BUFFER;

typedef int* LP_LIGHT;

#endif//HAL_ENGINE_NATIVE_NATIVETYPE_H_

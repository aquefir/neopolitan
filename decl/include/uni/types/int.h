/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_INT_H
#define INC_API__UNI_TYPES_INT_H

#if defined( NULL )
#undef NULL
#endif /* defined( NULL ) */

#define NULL 0

enum
{
	SIZEOF_CHAR = 1,
	SIZEOF_PTR = 8,
	S8_MIN = -128,
	S8_MAX = 127,
	S16_MIN = -32768,
	S16_MAX = 32767,
	S32_MIN = -2147483648,
	S32_MAX = 2147483647,
	S64_MIN = -9223372036854775808,
	S64_MAX = 9223372036854775807,
	U8_MAX = 255,
	U16_MAX = 65535,
	U32_MAX = 4294967295,
	U64_MAX = 18446744073709551615,
	PTRI_MAX = U64_MAX
};

#if defined( __clang__ ) || defined( __GNUC__ )
typedef __INT64_TYPE__ s64;
typedef __INT32_TYPE__ s32;
typedef __INT16_TYPE__ s16;
typedef __INT8_TYPE__ s8;
typedef __UINT64_TYPE__ u64;
typedef __UINT32_TYPE__ u32;
typedef __UINT16_TYPE__ u16;
typedef __UINT8_TYPE__ u8;
typedef __UINTPTR_TYPE__ ptri;
typedef __INTPTR_TYPE__ offs;
#elif defined( __TINYC__ )
#include <stdint.h>
typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
typedef uintptr_t ptri;
typedef intptr_t offs;
#else
#error "Unsupported compiler. Please use clang or GCC."
#endif

typedef u16 char16;
typedef u32 char32;

#endif /* INC_API__UNI_TYPES_INT_H */

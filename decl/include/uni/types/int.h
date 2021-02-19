/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_INT_H
#define INC_API__UNI_TYPES_INT_H

/* XXX: Copied from <uni/decl.h> */
#if !defined( UNI_DEPRECATED )
#if !defined( UNI_NODEPREC )
#if defined( __GNUC__ ) || defined( __clang__ )
#define UNI_DEPRECATED __attribute__( ( deprecated ) )
#elif defined( _MSC_VER )
#define UNI_DEPRECATED __declspec( deprecated )
#else
#pragma message( \
	"WARNING: You need to implement UNI_DEPRECATED for this compiler" )
#define UNI_DEPRECATED
#endif
#else
#define UNI_DEPRECATED
#endif /* !defined( UNI_NODEPREC ) */
#endif /* !defined( UNI_DEPRECATED ) */

enum
{
	SIZEOF_CHAR = 1,
	SIZEOF_PTR  = 8,
	S8_MIN      = -128,
	S8_MAX      = 127,
	S16_MIN     = -32768,
	S16_MAX     = 32767,
	U8_MAX      = 255,
	U16_MAX     = 65535
};

enum
{
	S32_MIN = -2147483648,
	S32_MAX = 2147483647,
};

enum
{
	U32_MAX = 4294967295U
};

enum
{
	U64_MAX  = 18446744073709551615UL,
	PTRI_MAX = U64_MAX
};

enum
{
	S64_MIN  = -9223372036854775808LL,
	S64_MAX  = 9223372036854775807LL,
	OFFS_MIN = S64_MIN,
	OFFS_MAX = S64_MAX
};

#define U128_MAX ( ( ( U64_MAX + 1 ) * ( U64_MAX + 1 ) ) - 1 )
#define S128_MIN ( ( ( S64_MIN * -1 ) * ( S64_MIN * -1 ) ) * -1 )
#define S128_MAX ( ( ( S64_MAX + 1 ) * ( S64_MAX + 1 ) ) - 1 )

#if defined( __clang__ ) || defined( __GNUC__ )
#define UNI_HAVE_S128( ) 1
typedef __int128_t s128;
typedef __INT64_TYPE__ s64;
typedef __INT32_TYPE__ s32;
typedef __INT16_TYPE__ s16;
typedef __INT8_TYPE__ s8;
#define UNI_HAVE_U128( ) 1
typedef __uint128_t u128;
typedef __UINT64_TYPE__ u64;
typedef __UINT32_TYPE__ u32;
typedef __UINT16_TYPE__ u16;
typedef __UINT8_TYPE__ u8;
typedef __UINTPTR_TYPE__ ptri;
typedef __INTPTR_TYPE__ offs;
#elif defined( __TINYC__ )
#include <stdint.h>
#define UNI_HAVE_S128( ) 0
typedef int64_t s64;
typedef int32_t s32;
typedef int16_t s16;
typedef int8_t s8;
#define UNI_HAVE_U128( ) 0
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

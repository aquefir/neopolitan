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

#if defined( __clang__) || defined( __GNUC__ )
#define UNI_HAS_I128( ) 1
#define UNI_HAS_I64( ) 1
#elif defined( __TINYC__ )
#define UNI_HAVE_I128( ) 0
#define UNI_HAVE_I64( ) 1
#endif /* defined( __clang__ ) || defined( __GNUC__ ) */

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

#if UNI_HAS_I64( )
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
#endif /* UNI_HAS_I64( ) */

#if UNI_HAS_I128( )
#define U128_MAX ( ( ( U64_MAX + 1 ) * ( U64_MAX + 1 ) ) - 1 )
#define S128_MIN ( ( ( S64_MIN * -1 ) * ( S64_MIN * -1 ) ) * -1 )
#define S128_MAX ( ( ( S64_MAX + 1 ) * ( S64_MAX + 1 ) ) - 1 )
#endif /* UNI_HAS_I128( ) */

#if defined( __clang__ ) || defined( __GNUC__ )
typedef signed __int128 s128;
typedef __INT64_TYPE__ s64;
typedef __INT32_TYPE__ s32;
typedef __INT16_TYPE__ s16;
typedef __INT8_TYPE__ s8;
typedef unsigned __int128 u128;
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

/* XXX: Already in a release, so must be supported. Consider deprecating */
#define UNI_HAS_S128( ) UNI_HAS_I128( )
#define UNI_HAS_U128( ) UNI_HAS_I128( )

typedef volatile s8 vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
#if UNI_HAS_I64( )
typedef volatile s64 vs64;
#endif /* UNI_HAS_I64( ) */
#if UNI_HAS_I128( )
typedef volatile s128 vs128;
#endif /* UNI_HAS_I128( ) */

typedef volatile u8 vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
#if UNI_HAS_I64( )
typedef volatile u64 vu64;
#endif /* UNI_HAS_I64( ) */
#if UNI_HAS_I128( )
typedef volatile u128 vu128;
#endif /* UNI_HAS_I128( ) */

typedef volatile ptri vptri;
typedef volatile offs voffs;

typedef volatile char vchar;
typedef volatile char16 vchar16;
typedef volatile char32 vchar32;

#endif /* INC_API__UNI_TYPES_INT_H */

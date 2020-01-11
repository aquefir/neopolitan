/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC__UNILIB_SHAND_H
#define INC__UNILIB_SHAND_H

#ifdef _MSC_VER
typedef unsigned __int8 u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;
typedef signed __int8 s8;
typedef signed __int16 s16;
typedef signed __int32 s32;
typedef signed __int64 s64;
#ifdef _M_IX86
typedef unsigned __int32 ptri;
#elif defined( _M_X64 )
typedef unsigned __int64 ptri;
#else
#error "Must be compiling for i386 or AMD64 when targeting Windows"
#endif /* _M_ arch */
/* UNIX land */
#elif defined( __clang__ ) || defined( __GNUC__ )
typedef __INT64_TYPE__ s64;
typedef __INT32_TYPE__ s32;
typedef __INT16_TYPE__ s16;
typedef __INT8_TYPE__ s8;
typedef __UINT64_TYPE__ u64;
typedef __UINT32_TYPE__ u32;
typedef __UINT16_TYPE__ u16;
typedef __UINT8_TYPE__ u8;
typedef __UINTPTR_TYPE__ ptri;
#endif

typedef long double f80;
typedef double f64;
typedef float f32;

#if defined( __clang__) && (defined( __arm__) || defined( __aarch64__ ))
typedef _Float16 f16;
#else
/* this is unsupported outside ARM because of ABIs */
typedef f32 f16;
#endif

#endif /* INC__UNILIB_SHAND_H */

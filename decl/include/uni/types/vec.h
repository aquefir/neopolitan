/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_VEC_H
#define INC_API__UNI_TYPES_VEC_H

#include "float.h"
#include "int.h"

typedef s8 s8v2 __attribute__( ( vector_size( 2 ) ) );
typedef s8 s8v4 __attribute__( ( vector_size( 4 ) ) );
typedef s8 s8v8 __attribute__( ( vector_size( 8 ) ) );
typedef s8 s8v16 __attribute__( ( vector_size( 16 ) ) );
typedef s8 s8v32 __attribute__( ( vector_size( 32 ) ) );
typedef s8 s8v64 __attribute__( ( vector_size( 64 ) ) );
typedef u8 u8v2 __attribute__( ( vector_size( 2 ) ) );
typedef u8 u8v4 __attribute__( ( vector_size( 4 ) ) );
typedef u8 u8v8 __attribute__( ( vector_size( 8 ) ) );
typedef u8 u8v16 __attribute__( ( vector_size( 16 ) ) );
typedef u8 u8v32 __attribute__( ( vector_size( 32 ) ) );
typedef u8 u8v64 __attribute__( ( vector_size( 64 ) ) );

typedef s16 s16v2 __attribute__( ( vector_size( 4 ) ) );
typedef s16 s16v4 __attribute__( ( vector_size( 8 ) ) );
typedef s16 s16v8 __attribute__( ( vector_size( 16 ) ) );
typedef s16 s16v16 __attribute__( ( vector_size( 32 ) ) );
typedef s16 s16v32 __attribute__( ( vector_size( 64 ) ) );
typedef u16 u16v2 __attribute__( ( vector_size( 4 ) ) );
typedef u16 u16v4 __attribute__( ( vector_size( 8 ) ) );
typedef u16 u16v8 __attribute__( ( vector_size( 16 ) ) );
typedef u16 u16v16 __attribute__( ( vector_size( 32 ) ) );
typedef u16 u16v32 __attribute__( ( vector_size( 64 ) ) );

typedef f16 f16v2 __attribute__( ( vector_size( 8 ) ) );
typedef f16 f16v4 __attribute__( ( vector_size( 16 ) ) );
typedef f16 f16v8 __attribute__( ( vector_size( 32 ) ) );
typedef f16 f16v16 __attribute__( ( vector_size( 64 ) ) );
typedef f16 f16v32 __attribute__( ( vector_size( 64 ) ) );

typedef s32 s32v2 __attribute__( ( vector_size( 8 ) ) );
typedef s32 s32v4 __attribute__( ( vector_size( 16 ) ) );
typedef s32 s32v8 __attribute__( ( vector_size( 32 ) ) );
typedef s32 s32v16 __attribute__( ( vector_size( 64 ) ) );
typedef u32 u32v2 __attribute__( ( vector_size( 8 ) ) );
typedef u32 u32v4 __attribute__( ( vector_size( 16 ) ) );
typedef u32 u32v8 __attribute__( ( vector_size( 32 ) ) );
typedef u32 u32v16 __attribute__( ( vector_size( 64 ) ) );

typedef f32 f32v2 __attribute__( ( vector_size( 8 ) ) );
typedef f32 f32v4 __attribute__( ( vector_size( 16 ) ) );
typedef f32 f32v8 __attribute__( ( vector_size( 32 ) ) );
typedef f32 f32v16 __attribute__( ( vector_size( 64 ) ) );

#if UNI_HAS_I64( )
typedef s64 s64v2 __attribute__( ( vector_size( 16 ) ) );
typedef s64 s64v4 __attribute__( ( vector_size( 32 ) ) );
typedef s64 s64v8 __attribute__( ( vector_size( 64 ) ) );
typedef u64 u64v2 __attribute__( ( vector_size( 16 ) ) );
typedef u64 u64v4 __attribute__( ( vector_size( 32 ) ) );
typedef u64 u64v8 __attribute__( ( vector_size( 64 ) ) );
#endif /* UNI_HAS_I64( ) */

typedef f64 f64v2 __attribute__( ( vector_size( 16 ) ) );
typedef f64 f64v4 __attribute__( ( vector_size( 32 ) ) );
typedef f64 f64v8 __attribute__( ( vector_size( 64 ) ) );

#if UNI_HAS_I128( )
typedef s128 s128v2 __attribute__( ( vector_size( 16 ) ) );
typedef s128 s128v4 __attribute__( ( vector_size( 32 ) ) );
typedef u128 u128v2 __attribute__( ( vector_size( 16 ) ) );
typedef u128 u128v4 __attribute__( ( vector_size( 32 ) ) );
#endif /* UNI_HAS_I128( ) */

#if UNI_HAS_F128( )
typedef f128 f128v2 __attribute__( ( vector_size( 16 ) ) );
typedef f128 f128v4 __attribute__( ( vector_size( 32 ) ) );
#endif /* UNI_HAS_F128( ) */

typedef volatile s8v2 vs8v2;
typedef volatile s8v4 vs8v4;
typedef volatile s8v8 vs8v8;
typedef volatile s8v16 vs8v16;
typedef volatile s8v32 vs8v32;
typedef volatile s8v64 vs8v64;
typedef volatile u8v2 vu8v2;
typedef volatile u8v4 vu8v4;
typedef volatile u8v8 vu8v8;
typedef volatile u8v16 vu8v16;
typedef volatile u8v32 vu8v32;
typedef volatile u8v64 vu8v64;

typedef volatile s16v2 vs16v2;
typedef volatile s16v4 vs16v4;
typedef volatile s16v8 vs16v8;
typedef volatile s16v16 vs16v16;
typedef volatile s16v32 vs16v32;
typedef volatile u16v2 vu16v2;
typedef volatile u16v4 vu16v4;
typedef volatile u16v8 vu16v8;
typedef volatile u16v16 vu16v16;
typedef volatile u16v32 vu16v32;

typedef volatile f16v2 vf16v2;
typedef volatile f16v4 vf16v4;
typedef volatile f16v8 vf16v8;
typedef volatile f16v16 vf16v16;
typedef volatile f16v32 vf16v32;

typedef volatile s32v2 vs32v2;
typedef volatile s32v4 vs32v4;
typedef volatile s32v8 vs32v8;
typedef volatile s32v16 vs32v16;
typedef volatile u32v2 vu32v2;
typedef volatile u32v4 vu32v4;
typedef volatile u32v8 vu32v8;
typedef volatile u32v16 vu32v16;

typedef volatile f32v2 vf32v2;
typedef volatile f32v4 vf32v4;
typedef volatile f32v8 vf32v8;
typedef volatile f32v16 vf32v16;

#if UNI_HAS_I64( )
typedef volatile s64v2 vs64v2;
typedef volatile s64v4 vs64v4;
typedef volatile s64v8 vs64v8;
typedef volatile u64v2 vu64v2;
typedef volatile u64v4 vu64v4;
typedef volatile u64v8 vu64v8;
#endif /* UNI_HAS_I64( ) */

typedef volatile f64v2 vf64v2;
typedef volatile f64v4 vf64v4;
typedef volatile f64v8 vf64v8;

#if UNI_HAS_I128( )
typedef volatile s128v2 vs128v2;
typedef volatile s128v4 vs128v4;
typedef volatile u128v2 vu128v2;
typedef volatile u128v4 vu128v4;
#endif /* UNI_HAS_I128 */

#if UNI_HAS_F128( )
typedef volatile f128v2 vf128v2;
typedef volatile f128v4 vf128v4;
#endif /* UNI_HAS_F128 */

#endif /* INC_API__UNI_TYPES_VEC_H */

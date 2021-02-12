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

typedef s64 s64v2 __attribute__( ( vector_size( 16 ) ) );
typedef s64 s64v4 __attribute__( ( vector_size( 32 ) ) );
typedef s64 s64v8 __attribute__( ( vector_size( 64 ) ) );
typedef u64 u64v2 __attribute__( ( vector_size( 16 ) ) );
typedef u64 u64v4 __attribute__( ( vector_size( 32 ) ) );
typedef u64 u64v8 __attribute__( ( vector_size( 64 ) ) );
typedef f64 f64v2 __attribute__( ( vector_size( 16 ) ) );
typedef f64 f64v4 __attribute__( ( vector_size( 32 ) ) );
typedef f64 f64v8 __attribute__( ( vector_size( 64 ) ) );

#endif /* INC_API__UNI_TYPES_VEC_H */

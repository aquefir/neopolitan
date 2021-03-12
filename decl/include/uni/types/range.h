/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_RANGE_H
#define INC_API__UNI_TYPES_RANGE_H

#include "int.h"

struct _uni_rs8
{
	s64 lo, hi;
};

struct _uni_rs16
{
	s64 lo, hi;
};

struct _uni_rs32
{
	s64 lo, hi;
};

#if UNI_HAS_I64( )
struct _uni_rs64
{
	s64 lo, hi;
};
#endif /* UNI_HAS_I64( ) */

#if UNI_HAS_I128( )
struct _uni_rs128
{
	s128 lo, hi;
};
#endif /* UNI_HAS_I128( ) */

struct _uni_ru8
{
	u64 lo, hi;
};

struct _uni_ru16
{
	u64 lo, hi;
};

struct _uni_ru32
{
	u64 lo, hi;
};

#if UNI_HAS_I64( )
struct _uni_ru64
{
	u64 lo, hi;
};
#endif /* UNI_HAS_I64( ) */

#if UNI_HAS_I128( )
struct _uni_ru128
{
	u128 lo, hi;
};
#endif /* UNI_HAS_I128( ) */

typedef struct _uni_rs8 rs8;
typedef volatile struct _uni_rs8 vrs8;
typedef struct _uni_rs16 rs16;
typedef volatile struct _uni_rs16 vrs16;
typedef struct _uni_rs32 rs32;
typedef volatile struct _uni_rs32 vrs32;
#if UNI_HAS_I64( )
typedef struct _uni_rs64 rs64;
typedef volatile struct _uni_rs64 vrs64;
#endif /* UNI_HAS_I64( ) */
#if UNI_HAS_I128( )
typedef struct _uni_rs128 rs128;
typedef volatile struct _uni_rs128 vrs128;
#endif /* UNI_HAS_I128( ) */

typedef struct _uni_ru8 ru8;
typedef volatile struct _uni_ru8 vru8;
typedef struct _uni_ru16 ru16;
typedef volatile struct _uni_ru16 vru16;
typedef struct _uni_ru32 ru32;
typedef volatile struct _uni_ru32 vru32;
#if UNI_HAS_I64( )
typedef struct _uni_ru64 ru64;
typedef volatile struct _uni_ru64 vru64;
#endif /* UNI_HAS_I64( ) */
#if UNI_HAS_I128( )
typedef struct _uni_ru128 ru128;
typedef volatile struct _uni_ru128 vru128;
#endif /* UNI_HAS_I128( ) */

#endif /* INC_API__UNI_TYPES_RANGE_H */

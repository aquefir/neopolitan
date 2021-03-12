/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_QUANT_H
#define INC_API__UNI_TYPES_QUANT_H

#include "float.h"

struct _uni_q16d2
{
	f16 x, y;
};

struct _uni_q32d2
{
	f32 x, y;
};

struct _uni_q64d2
{
	f64 x, y;
};

#if UNI_HAS_F128( )
struct _uni_q128d2
{
	f128 x, y;
};
#endif /* UNI_HAS_F128( ) */

struct _uni_q16d3
{
	f16 x, y, z;
};

struct _uni_q32d3
{
	f32 x, y, z;
};

struct _uni_q64d3
{
	f64 x, y, z;
};

#if UNI_HAS_F128( )
struct _uni_q128d3
{
	f128 x, y, z;
};
#endif /* UNI_HAS_F128( ) */

struct _uni_q16d4
{
	f16 x, y, z, a;
};

struct _uni_q32d4
{
	f32 x, y, z, a;
};

struct _uni_q64d4
{
	f64 x, y, z, a;
};

#if UNI_HAS_F128( )
struct _uni_q128d4
{
	f128 x, y, z, a;
};
#endif /* UNI_HAS_F128( ) */

struct _uni_q16d5
{
	f16 x, y, z, a, b;
};

struct _uni_q32d5
{
	f32 x, y, z, a, b;
};

struct _uni_q64d5
{
	f64 x, y, z, a, b;
};

#if UNI_HAS_F128( )
struct _uni_q128d5
{
	f128 x, y, z, a, b;
};
#endif /* UNI_HAS_F128( ) */

struct _uni_q16d6
{
	f16 x, y, z, a, b, c;
};

struct _uni_q32d6
{
	f32 x, y, z, a, b, c;
};

struct _uni_q64d6
{
	f64 x, y, z, a, b, c;
};

#if UNI_HAS_F128( )
struct _uni_q128d6
{
	f128 x, y, z, a, b, c;
};
#endif /* UNI_HAS_F128( ) */

typedef struct _uni_q16d2 q16d2;
typedef volatile struct _uni_q16d2 q16d2;
typedef struct _uni_q32d2 q32d2;
typedef volatile struct _uni_q32d2 q32d2;
typedef struct _uni_q64d2 q64d2;
typedef volatile struct _uni_q64d2 q64d2;
#if UNI_HAS_F128( )
typedef struct _uni_q128d2 q128d2;
typedef volatile struct _uni_q128d2 q128d2;
#endif /* UNI_HAS_F128( ) */

typedef struct _uni_q16d3 q16d3;
typedef volatile struct _uni_q16d3 q16d3;
typedef struct _uni_q32d3 q32d3;
typedef volatile struct _uni_q32d3 q32d3;
typedef struct _uni_q64d3 q64d3;
typedef volatile struct _uni_q64d3 q64d3;
#if UNI_HAS_F128( )
typedef struct _uni_q128d3 q128d3;
typedef volatile struct _uni_q128d3 q128d3;
#endif /* UNI_HAS_F128( ) */

typedef struct _uni_q16d4 q16d4;
typedef volatile struct _uni_q16d4 q16d4;
typedef struct _uni_q32d4 q32d4;
typedef volatile struct _uni_q32d4 q32d4;
typedef struct _uni_q64d4 q64d4;
typedef volatile struct _uni_q64d4 q64d4;
#if UNI_HAS_F128( )
typedef struct _uni_q128d4 q128d4;
typedef volatile struct _uni_q128d4 q128d4;
#endif /* UNI_HAS_F128( ) */

typedef struct _uni_q16d5 q16d5;
typedef volatile struct _uni_q16d5 q16d5;
typedef struct _uni_q32d5 q32d5;
typedef volatile struct _uni_q32d5 q32d5;
typedef struct _uni_q64d5 q64d5;
typedef volatile struct _uni_q64d5 q64d5;
#if UNI_HAS_F128( )
typedef struct _uni_q128d5 q128d5;
typedef volatile struct _uni_q128d5 q128d5;
#endif /* UNI_HAS_F128( ) */

typedef struct _uni_q16d6 q16d6;
typedef volatile struct _uni_q16d6 q16d6;
typedef struct _uni_q32d6 q32d6;
typedef volatile struct _uni_q32d6 q32d6;
typedef struct _uni_q64d6 q64d6;
typedef volatile struct _uni_q64d6 q64d6;
#if UNI_HAS_F128( )
typedef struct _uni_q128d6 q128d6;
typedef volatile struct _uni_q128d6 q128d6;
#endif /* UNI_HAS_F128( ) */

#endif /* INC_API__UNI_TYPES_QUANT_H */

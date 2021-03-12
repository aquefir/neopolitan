/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_POINT_H
#define INC_API__UNI_TYPES_POINT_H

#include "int.h"

struct _uni_p8d2
{
	s8 x, y;
};

struct _uni_p16d2
{
	s16 x, y;
};

struct _uni_p32d2
{
	s32 x, y;
};

#if UNI_HAS_I64( )
struct _uni_p64d2
{
	s64 x, y;
};
#endif /* UNI_HAS_I64( ) */

#if UNI_HAS_I128( )
struct _uni_p128d2
{
	s128 x, y;
};
#endif /* UNI_HAS_I128( ) */

struct _uni_p8d3
{
	u8 s, y, z;
};

struct _uni_p16d3
{
	s16 x, y, z;
};

struct _uni_p32d3
{
	s32 x, y, z;
};

#if UNI_HAS_I64( )
struct _uni_p64d3
{
	s64 x, y, z;
};
#endif /* UNI_HAS_I64( ) */

#if UNI_HAS_I128( )
struct _uni_p128d3
{
	s128 x, y, z;
};
#endif /* UNI_HAS_I128( ) */

struct _uni_p8d4
{
	u8 s, y, z, a;
};

struct _uni_p16d4
{
	s16 x, y, z, a;
};

struct _uni_p32d4
{
	s32 x, y, z, a;
};

#if UNI_HAS_I64( )
struct _uni_p64d4
{
	s64 x, y, z, a;
};
#endif /* UNI_HAS_I64( ) */

#if UNI_HAS_I128( )
struct _uni_p128d4
{
	s128 x, y, z, a;
};
#endif /* UNI_HAS_I128( ) */

struct _uni_p8d5
{
	u8 s, y, z, a, b;
};

struct _uni_p16d5
{
	s16 x, y, z, a, b;
};

struct _uni_p32d5
{
	s32 x, y, z, a, b;
};

#if UNI_HAS_I64( )
struct _uni_p64d5
{
	s64 x, y, z, a, b;
};
#endif /* UNI_HAS_I64( ) */

#if UNI_HAS_I128( )
struct _uni_p128d5
{
	s128 x, y, z, a, b;
};
#endif /* UNI_HAS_I128( ) */

struct _uni_p8d6
{
	u8 s, y, z, a, b, c;
};

struct _uni_p16d6
{
	s16 x, y, z, a, b, c;
};

struct _uni_p32d6
{
	s32 x, y, z, a, b, c;
};

#if UNI_HAS_I64( )
struct _uni_p64d6
{
	s64 x, y, z, a, b, c;
};
#endif /* UNI_HAS_I64( ) */

#if UNI_HAS_I128( )
struct _uni_p128d6
{
	s128 x, y, z, a, b, c;
};
#endif /* UNI_HAS_I128( ) */

typedef struct _uni_p8d2 p8d2;
typedef volatile struct _uni_p8d2 p8d2;
typedef struct _uni_p16d2 p16d2;
typedef volatile struct _uni_p16d2 p16d2;
typedef struct _uni_p32d2 p32d2;
typedef volatile struct _uni_p32d2 p32d2;
#if UNI_HAS_I64( )
typedef struct _uni_p64d2 p64d2;
typedef volatile struct _uni_p64d2 p64d2;
#endif /* UNI_HAS_I64( ) */
#if UNI_HAS_I128( )
typedef struct _uni_p128d2 p128d2;
typedef volatile struct _uni_p128d2 p128d2;
#endif /* UNI_HAS_I128( ) */

typedef struct _uni_p8d3 p8d3;
typedef volatile struct _uni_p8d3 p8d3;
typedef struct _uni_p16d3 p16d3;
typedef volatile struct _uni_p16d3 p16d3;
typedef struct _uni_p32d3 p32d3;
typedef volatile struct _uni_p32d3 p32d3;
#if UNI_HAS_I64( )
typedef struct _uni_p64d3 p64d3;
typedef volatile struct _uni_p64d3 p64d3;
#endif /* UNI_HAS_I64( ) */
#if UNI_HAS_I128( )
typedef struct _uni_p128d3 p128d3;
typedef volatile struct _uni_p128d3 p128d3;
#endif /* UNI_HAS_I128( ) */

typedef struct _uni_p8d4 p8d4;
typedef volatile struct _uni_p8d4 p8d4;
typedef struct _uni_p16d4 p16d4;
typedef volatile struct _uni_p16d4 p16d4;
typedef struct _uni_p32d4 p32d4;
typedef volatile struct _uni_p32d4 p32d4;
#if UNI_HAS_I64( )
typedef struct _uni_p64d4 p64d4;
typedef volatile struct _uni_p64d4 p64d4;
#endif /* UNI_HAS_I64( ) */
#if UNI_HAS_I128( )
typedef struct _uni_p128d4 p128d4;
typedef volatile struct _uni_p128d4 p128d4;
#endif /* UNI_HAS_I128( ) */

typedef struct _uni_p8d5 p8d5;
typedef volatile struct _uni_p8d5 p8d5;
typedef struct _uni_p16d5 p16d5;
typedef volatile struct _uni_p16d5 p16d5;
typedef struct _uni_p32d5 p32d5;
typedef volatile struct _uni_p32d5 p32d5;
#if UNI_HAS_I64( )
typedef struct _uni_p64d5 p64d5;
typedef volatile struct _uni_p64d5 p64d5;
#endif /* UNI_HAS_I64( ) */
#if UNI_HAS_I128( )
typedef struct _uni_p128d5 p128d5;
typedef volatile struct _uni_p128d5 p128d5;
#endif /* UNI_HAS_I128( ) */

typedef struct _uni_p8d6 p8d6;
typedef volatile struct _uni_p8d6 p8d6;
typedef struct _uni_p16d6 p16d6;
typedef volatile struct _uni_p16d6 p16d6;
typedef struct _uni_p32d6 p32d6;
typedef volatile struct _uni_p32d6 p32d6;
#if UNI_HAS_I64( )
typedef struct _uni_p64d6 p64d6;
typedef volatile struct _uni_p64d6 p64d6;
#endif /* UNI_HAS_I64( ) */
#if UNI_HAS_I128( )
typedef struct _uni_p128d6 p128d6;
typedef volatile struct _uni_p128d6 p128d6;
#endif /* UNI_HAS_I128( ) */

#endif /* INC_API__UNI_TYPES_POINT_H */

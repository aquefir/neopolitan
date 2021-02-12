/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_MATHPRIM_H
#define INC_API__UNI_TYPES_MATHPRIM_H

#include "int.h"

#define UNI_SIZEOF_RANGE( R ) \
	( ( ( ( R ).lo > ( R ).hi ) ? ( ( R ).lo - ( ( R ).hi - 1 ) ) \
				    : ( ( ( R ).hi - 1 ) - ( R ).lo ) ) + \
		1 )

struct point2
{
	s32 x, y;
};

struct point2l
{
	s64 x, y;
};

struct point3
{
	s32 x, y, z;
};

struct point3l
{
	s64 x, y, z;
};

struct bound2
{
	u32 l, w;
};

struct bound2l
{
	u64 l, w;
};

struct bound3
{
	u32 l, w, h;
};

struct bound3l
{
	u64 l, w, h;
};

struct range
{
	s32 lo, hi;
};

struct rangel
{
	s64 lo, hi;
};

struct rangep
{
	ptri lo, hi;
};

#endif /* INC_API__UNI_TYPES_MATHPRIM_H */

/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC_API__UNILIB_GEOMETRY_H
#define INC_API__UNILIB_GEOMETRY_H

#include <unilib/shand.h>

#define UNI_SIZEOF_RANGE( RANGE ) \
	( ( ( ( RANGE ).lo > ( RANGE ).hi ) ? ( ( RANGE ).lo - ( RANGE ).hi ) \
	                                    : ( ( RANGE ).hi - ( RANGE ).lo ) ) + \
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

#endif /* INC_API__UNILIB_GEOMETRY_H */

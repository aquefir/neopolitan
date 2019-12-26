/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC__UNILIB_GEOMETRY_H
#define INC__UNILIB_GEOMETRY_H

#include "shand.h"

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

#endif /* INC__UNILIB_GEOMETRY_H */

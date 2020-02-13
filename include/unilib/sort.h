/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC_API__UNILIB_SORT_H
#define INC_API__UNILIB_SORT_H

#include "array.h"

struct uni_vec2
{
	struct uni_vec vec[2];
};

struct uni_vec uni_mergesort( struct uni_vec );
struct uni_vec2 uni_omergesort2( struct uni_vec2 );

#endif /* INC_API__UNILIB_SORT_H */
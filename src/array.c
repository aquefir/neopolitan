/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#include "array.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <tes/program.h>
#include <unilib/decl.h>
#include <unilib/err.h>
#include <unilib/shand.h>

UNI_API struct uni_vec uni_vec_init( ptri i_sz, ptri ini_cap )
{
	struct uni_vec ret = { 0, ini_cap, i_sz, NULL };

	if(i_sz == 0 || ini_cap == 0)
	{
		return ret;
	}

	ret.data = malloc( sizeof(u8) * (ini_cap * i_sz) );

	if(ret.data == NULL)
	{
		return ret;
	}

	return ret;
}

UNI_API struct uni_vec uni_vec_init_ex( ptri i_sz, ptri cap, void* data )
{
	struct uni_vec ret = { cap, cap, i_sz, data };

	return ret;
}

UNI_API struct uni_vec uni_vec_dup( struct uni_vec v )
{
	struct uni_vec tmp = uni_vec_init( v.elem_sz, v.sz );
	struct rangep range = { 0, v.sz };

	return uni_vec_emplace( tmp, v, range );
}

UNI_API void uni_vec_fini( struct uni_vec v )
{
	if(v.data != NULL)
	{
		free( v.data );
	}
}

UNI_API struct uni_vec uni_vec_reserve( struct uni_vec v, ptri count )
{
	struct uni_vec ret = { v.sz, v.cap, v.elem_sz, v.data };

	ASSERT_RETVAL( ret.data != NULL, ret );
	ASSERT_RETVAL( ret.cap > 0, ret ); /* ensure it’s not a slice */

	if(v.elem_sz == 0 || count == 0)
	{
		/* nothing to change, we’re done */
		return ret;
	}

	/* make new space, calculated by-byte */
	ret.data = realloc( v.data, sizeof(u8) * ((ret.cap * ret.elem_sz) +
		(count * ret.elem_sz)) );

	ASSERT_RETVAL( ret.data != NULL, ret );

	/* record and store the new capacity */
	ret.cap += count;

	return ret;
}

UNI_API struct uni_vec uni_vec_emplace( struct uni_vec v, struct uni_vec nu,
struct rangep r )
{
	/* all of these values are in units of elements, not bytes */
	const ptri r_sz = UNI_SIZEOF_RANGE( r );
	const ptri new_needed = r_sz > nu.sz ? 0 : r_sz - nu.sz;
	struct uni_vec ret = { v.sz, v.cap, v.elem_sz, v.data };
	const ptri shift_sz = new_needed - (ret.cap - ret.sz);
	u8* data = (u8*)(ret.data);

	ASSERT_RETVAL( data != NULL, ret );
	ASSERT_RETVAL( r.hi <= ret.sz, ret );
	ASSERT_RETVAL( ret.cap > 0, ret ); /* ensure it’s not a slice */

	/* reserve new space if necessary */
	if(ret.cap - ret.sz < new_needed)
	{
		ret = uni_vec_reserve( ret, shift_sz );

		ASSERT_RETVAL( ret.data != NULL, ret );
	}

	if(r_sz < nu.sz)
	{
		/* range of v to overwrite is smaller than the new data
		 * so we need to shift the old data over to make room */
		/* shift size is the number of newly allocated elements */
		const ptri latter_sz = v.sz - r.hi;
		ptri i;

		for(i = 0; i < latter_sz; ++i)
		{
			data[v.cap - i - 1] = data[v.sz - i - 1];
		}
	}

	/* now we can copy over the new data */
	memcpy( data + r.lo, ((u8*)nu.data), r_sz );

	return ret;
}

UNI_API struct uni_vec uni_vec_slackoff( struct uni_vec v )
{
	struct uni_vec ret = { v.sz, v.cap, v.elem_sz, v.data };

	ASSERT_RETVAL( ret.data != NULL, ret );
	ASSERT_RETVAL( ret.cap > 0, ret ); /* ensure it’s not a slice */

	if(ret.sz < ret.cap)
	{
		ret.data = realloc( v.data, sizeof(u8) * (v.sz) );

		ASSERT_RETVAL( ret.data != NULL, ret );
	}

	return ret;
}

#if 0
UNI_API struct uni_vec uni_vec_slice( struct uni_vec v, struct rangep r )
{
	struct uni_vec ret;

	ret.sz = UNI_SIZEOF_RANGE( r );
	ret.cap = 0;

	return ret;
}
#endif /* 0 */

/* *** */

/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
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
	struct uni_vec ret = {0, ini_cap, i_sz, NULL};

	if( i_sz == 0 || ini_cap == 0 )
	{
		return ret;
	}

	ret.data = malloc( sizeof( u8 ) * ( ini_cap * i_sz ) );

	if( ret.data == NULL )
	{
		return ret;
	}

	ret.sz = ini_cap;

	return ret;
}

UNI_API struct uni_vec uni_vec_init_ex( ptri i_sz, ptri cap, void* data )
{
	struct uni_vec ret = {cap, cap, i_sz, NULL};
	u8* tmp;

	tmp = malloc( i_sz * cap );

	ASSERT_RETVAL( tmp != NULL, ret );

	memcpy( tmp, data, cap );

	ret.data = tmp;

	return ret;
}

UNI_API void uni_vec_fini( struct uni_vec v )
{
	if( v.data != NULL )
	{
		free( v.data );
	}
}

UNI_API struct uni_vec uni_vec_dup( struct uni_vec v )
{
	struct uni_vec tmp  = uni_vec_init( v.elem_sz, v.sz );
	struct rangep range = {0, v.sz};

	return uni_vec_emplace( tmp, v, range );
}

UNI_API void* uni_vec_getone( struct uni_vec v, ptri index )
{
	u8* ret;

	ret = v.data + ( sizeof( v.elem_sz ) * index );

	return ret;
}

UNI_API struct uni_vec uni_vec_reserve( struct uni_vec v, ptri count )
{
	struct uni_vec ret = {v.sz, v.cap, v.elem_sz, v.data};

	ASSERT_RETVAL( ret.data != NULL, ret );
	ASSERT_RETVAL( ret.cap > 0, ret ); /* ensure it’s not a slice */

	if( v.elem_sz == 0 || count == 0 )
	{
		/* nothing to change, we’re done */
		return ret;
	}

	/* make new space, calculated by-byte */
	ret.data = realloc( v.data,
	   sizeof( u8 ) * ( ( ret.cap * ret.elem_sz ) + ( count * ret.elem_sz ) ) );

	ASSERT_RETVAL( ret.data != NULL, ret );

	/* record and store the new capacity */
	ret.cap += count;

	return ret;
}

UNI_API struct uni_vec uni_vec_emplace(
	struct uni_vec v1, struct uni_vec v2, struct rangep r )
{
	/* all lengths & sizes are in elements, not bytes unless noted otherwise */
	const ptri r_len = UNI_SIZEOF_RANGE( r );
	const ptri nu_elems_needed = r_len > v2.sz ? r_len - v2.sz : 0;
	const ptri remainder = nu_elems_needed - ( v1.cap - v1.sz );
	u8* data_b = (u8*)v1.data;

	/* reserve new space if needed */
	if( v1.cap - v1.sz < nu_elems_needed )
	{
		struct uni_vec tmp;

		tmp = uni_vec_reserve( v1, remainder );

		ASSERT_RETVAL( tmp.data != NULL, v1 );
	}

	if( r_len < v2.sz )
	{
		/* range of v1 to overwrite is smaller than the new data,
		 * so we need to shift the old data over to make room
		 * shift size is the number of newly allocated elements */
		ptri i;

		for( i = v1.sz; i >= r.hi + remainder; --i)
		{
			memcpy( data_b + (v1.elem_sz * i),
				data_b + (v1.elem_sz * (i - remainder)),
				v1.elem_sz );
		}
	}
	else if( r_len > v2.sz )
	{
		/* range of v1 to overwrite is larger than the new data,
		 * so we need to shift the old data in to keep the vector
		 * contiguous */
		ptri i;
		ptri diff = r_len - v2.sz;

		for( i = r.lo + v2.sz; i < v1.sz - diff; ++i )
		{
			memcpy( data_b + (v1.elem_sz * i),
				data_b + (v1.elem_sz * (i + diff)), v1.elem_sz );
		}

		v1.sz -= diff;
	}

	/* copy over the new data, if needed */
	if( v2.data != NULL )
	{
		memcpy( data_b + (v1.elem_sz * r.lo),
			( (u8*)v2.data ), (v1.elem_sz * v2.sz) );
	}

	return v1;
}

UNI_API struct uni_vec uni_vec_slice( struct uni_vec v, struct rangep r )
{
	struct uni_vec ret;

	/* new size is the size of the range, of course */
	ret.sz      = UNI_SIZEOF_RANGE( r );
	ret.cap     = 0; /* This is a sentinel! */
	ret.elem_sz = v.elem_sz;
	ret.data    = v.data;

	/* sorry, can’t slice beyond the input vector! */
	ASSERT_RETVAL( r.hi <= v.sz, ret );

	/* finally, advance the pointer in ret */
	ret.data += ret.elem_sz * r.lo;

	return ret;
}

/* *** */

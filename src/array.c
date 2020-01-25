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
#include <unilib/err.h>
#include <unilib/shand.h>

static const ptri header_sz = sizeof( struct uni_vec_header );

UNI_API struct uni_vec uni_vec_init( ptri i_sz, ptri ini_cap )
{
	struct uni_vec ret = { 0, ini_cap, i_sz, NULL };

	if(i_sz == 0)
	{
		return ret;
	}

	ret.data = malloc( sizeof(u8) * (header_sz + (ini_cap * i_sz)) );

	if(ret.data == NULL)
	{
		return ret;
	}

	memcpy( ret.data, &head, header_sz );

	return ret;
}

UNI_API struct uni_vec uni_vec_init_ex( ptri i_sz, ptri cap, void* data )
{
	return { cap, cap, i_sz, data };
}

UNI_API struct uni_vec uni_vec_dup( struct uni_vec v )
{
	struct uni_vec tmp = uni_vec_init( v.elem_sz, v.sz );
	struct rangep range = { 0, v.sz - 1 };

	return uni_vec_emplace( tmp, v, range )
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
	ptri sz, cap;
	struct uni_vec ret = { v.sz, v.cap, v.elem_sz, v.data };

	ASSERT_RETVAL( ret.data != NULL, ret );
	ASSERT_RETVAL( ret.cap > 0 ); /* ensure it’s not a slice */

	if(v.elem_sz == 0 || count == 0)
	{
		/* nothing to change, we’re done */
		return ret;
	}

	/* make new space, calculated by-byte */
	ret.data = realloc( v.data, sizeof(u8) * (header_sz + 
		(ret.cap * ret.elem_sz) + (count * ret.elem_sz)) );

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

	/* reserve new space if necessary */
	if(ret.cap - ret.sz < new_needed)
	{
		ASSERT_RETVAL( ret.cap > 0, ret ); /* ensure it’s not a slice */

		ret = uni_vec_reserve( ret, shift_sz );

		if(ret.data == NULL)
		{
			return NULL;
		}
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
	ASSERT_RETVAL( ret.cap > 0 ); /* ensure it’s not a slice */

	if(ret.sz < ret.cap)
	{
		ret.data = realloc( v.data, sizeof(u8) * (v.sz) );

		ASSERT_RETVAL( ret.data != NULL, ret );
	}

	return ret;
}

UNI_API struct uni_vec uni_vec_slice( struct uni_vec v, struct rangep r )
{
	struct uni_vec ret;
	
	ret.sz = UNI_SIZEOF_RANGE( r );
	ret.cap = 0;
}

/* *** */

ptri uni_vec_getoffs( ptri item_sz )
{
	const ptri header_len =
	   ( header_sz / item_sz ) + ( ( header_sz % item_sz ) ? 1 : 0 );

	return item_sz * header_len;
}

void* uni_vec_getmemstart( void* vec, ptri item_sz )
{
	ASSERT( vec != NULL );

	return ( (u8*)vec ) - uni_vec_getoffs( item_sz );
}

struct uni_vec_header uni_vec_getheader( void* vec, ptri item_sz )
{
	struct uni_vec_header ret;
	u8* src;

	src = uni_vec_getmemstart( vec, item_sz );

	memcpy( &ret, src, header_sz );

	return ret;
}

void uni_vec_setheader( void* vec, ptri item_sz, struct uni_vec_header head )
{
	u8* dst;

	dst = uni_vec_getmemstart( vec, item_sz );
	memcpy( dst, &head, header_sz );
}

void* uni_vec_init( ptri item_sz, ptri init_cap )
{
	struct uni_vec_header head = {0, init_cap};
	void* vec;

	ASSERT( item_sz > 0 );
	ASSERT( init_cap > 0 );
	ASSERT( init_cap < ( PTRI_MAX / item_sz ) );

	vec = malloc( init_cap * item_sz );

	if( vec == NULL )
	{
		return NULL;
	}

	vec = ( (u8*)vec ) + uni_vec_getoffs( item_sz );
	uni_vec_setheader( vec, item_sz, head );

	return vec;
}

struct uni_vec_header uni_vec_header_addcap( struct uni_vec_header head )
{
	ASSERT( head.sz <= head.cap );

	if( head.sz == PTRI_MAX )
	{
		head.sz = head.cap = 0;
	}
	else if( head.sz == head.cap )
	{
		head.cap =
		   ( head.cap >= ( PTRI_MAX / 2 ) ) ? PTRI_MAX : ( head.cap * 2 );
	}

	return head;
}

void* uni_vec_addcap( void* vec, ptri item_sz )
{
	struct uni_vec_header head;
	void* vec_mem_start     = uni_vec_getmemstart( vec, item_sz );
	void* new_vec_mem_start = vec_mem_start;
	const ptri head_offs    = uni_vec_getoffs( item_sz );

	ASSERT( vec );
	ASSERT( item_sz );
	ASSERT( head_offs );

	head = uni_vec_header_addcap( uni_vec_getheader( vec, item_sz ) );

	if( head.cap == 0 || head.cap > ( PTRI_MAX - head_offs ) / item_sz )
	{
		uni_perror( "uni_vec_addcap() failed\n" );

		return NULL;
	}

	new_vec_mem_start =
	   realloc( vec_mem_start, head_offs + ( item_sz * head.cap ) );

	if( !new_vec_mem_start )
	{
		uni_perror( "uni_vec_addcap() failed\n" );

		return NULL;
	}

	{
		void* new_vec = ( (u8*)new_vec_mem_start ) + head_offs;

		uni_vec_setheader( new_vec, item_sz, head );

		return new_vec;
	}
}

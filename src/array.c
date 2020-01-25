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

#include <unilib/err.h>
#include <unilib/shand.h>

static const ptri header_sz = sizeof( struct uni_vec_header );

TES_STATIC void write_sz( void* v, ptri sz )
{
	if( v != NULL && sz > 0 )
	{
		memcpy( v, (u8*)(&sz), sizeof(ptri) );
	}
}

TES_STATIC void write_cap( void* v, ptri cap )
{
	if( v != NULL && cap > 0 )
	{
		memcpy( ((u8*)v) + sizeof(ptri), (u8*)(&cap), sizeof(ptri) );
	}
}

UNI_API void* uni_vec_init( ptri i_sz, ptri ini_cap )
{
	const struct uni_vec_header head = { 0, ini_cap };
	void* ret;

	if(i_sz == 0)
	{
		return NULL;
	}

	ret = malloc( sizeof(u8) * (header_sz + (ini_cap * i_sz)) );

	if(ret == NULL)
	{
		return NULL;
	}

	memcpy( ret, &head, header_sz );

	return ret;
}

UNI_API void uni_vec_fini( void* v )
{
	if(v != NULL)
	{
		free( v );
	}
}

UNI_API void* uni_vec_reserve( void* v, ptri i_sz, ptri count )
{
	ptri sz, cap;
	void* ret;

	ASSERT_RETNUL( v != NULL );

	if(i_sz == 0 || count == 0)
	{
		/* nothing to change, we’re done */
		return v;
	}

	/* get header data */
	sz = uni_vec_readsz( v );
	cap = uni_vec_readcap( v );

	ret = realloc( v, sizeof(u8) * (header_sz + (cap * i_sz) + \
		(count * i_sz)) );

	if(ret == NULL)
	{
		uni_perror( "realloc() failed in uni_vec_reserve()\n" );

		return v;
	}

	/* record and store the new capacity */
	cap += count;

	write_cap( v, cap );

	return ret;
}

UNI_API void* uni_vec_emplace( void* v, ptri i_sz, void* in, ptri in_sz,
struct rangep r )
{
	const ptri r_sz = UNI_SIZEOF_RANGE( r );
	const ptri new_needed = r_sz > in_sz ? 0 : r_sz - in_sz;
	ptri sz, cap;

	ASSERT_RETNUL( v != NULL );

	sz = uni_vec_readsz( v );
	cap = uni_vec_readcap( v );
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

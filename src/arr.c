/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "arr.h"

#include <uni/err.h>
#include <uni/memory.h>

struct uni_arr* uni_arr_init( u32 elemsz )
{
	struct uni_arr* ret;

	if( !elemsz )
	{
		uni_die( );
	}

	ret = uni_alloc( sizeof( struct uni_arr ) );

	ret->data   = NULL;
	ret->sz     = 0;
	ret->cap    = 0;
	ret->elemsz = elemsz;

	return ret;
}

struct uni_arr* uni_arr_initsz( u32 elemsz, u32 count )
{
	struct uni_arr* ret;

	if( !elemsz )
	{
		uni_die( );
	}

	ret = uni_alloc( sizeof( struct uni_arr ) );

	if( count )
	{
		ptri sz = 16;

		while( sz <= count )
		{
			sz <<= 1; /* *= 2 */
		}

		ret->data = uni_alloc0( elemsz * sz );
		ret->cap  = sz;
		ret->sz   = count;
	}
	else
	{
		ret->data = NULL;
		ret->cap  = 0;
		ret->sz   = 0;
	}

	ret->elemsz = elemsz;

	return ret;
}

void uni_arr_fini( struct uni_arr* arr )
{
	if( !arr )
	{
		uni_die( );
	}

	if( arr->data )
	{
		uni_free( arr->data );
		arr->data = NULL;
		arr->cap  = 0;
		arr->sz   = 0;
	}

	uni_free( arr );
}

struct uni_arr* uni_arr_dup( struct uni_arr* arr )
{
	struct uni_arr* ret;
	ptri sz;

	if( !arr )
	{
		uni_die( );
	}

	sz        = arr->elemsz * arr->sz;
	ret       = uni_alloc( sizeof( struct uni_arr ) );
	ret->data = uni_alloc( sz );
	uni_memcpy( ret->data, arr->data, sz );
	ret->sz     = arr->sz;
	ret->cap    = arr->sz;
	ret->elemsz = arr->elemsz;

	return ret;
}

ptri uni_arr_getsz( struct uni_arr* arr )
{
	if( !arr )
	{
		uni_die( );
	}

	return arr->sz;
}

void* uni_arr_make( struct uni_arr* arr )
{
	void* ret;
	ptri sz;

	if( !arr )
	{
		uni_die( );
	}

	if( !arr->data )
	{
		return NULL;
	}

	sz  = arr->elemsz * arr->sz;
	ret = uni_alloc( sz );
	uni_memcpy( ret, arr->data, sz );

	return ret;
}

void* uni_arr_mkslice( struct uni_arr* arr, struct rangep r )
{
	if( !arr )
	{
		uni_die( );
	}

	{
		void* ret;
		ptri sz;

		if( !arr->data || r.hi >= arr->sz || r.lo >= r.hi )
		{
			return NULL;
		}

		sz  = arr->elemsz * ( r.hi - r.lo );
		ret = uni_alloc( sz );
		uni_memcpy( ret, arr->data + ( arr->elemsz * r.lo ), sz );

		return ret;
	}
}

int uni_arr_app( struct uni_arr* arr, void* data )
{
	if( !arr )
	{
		uni_die( );
	}

	while( arr->sz >= arr->cap )
	{
		arr->data = uni_realloc( arr->data, arr->cap << 1 );
		arr->cap <<= 1; /* *= 2 */
	}

	uni_memcpy( arr->data + ( arr->sz * arr->elemsz ), data, arr->elemsz );
	arr->sz++;

	return 0;
}

int uni_arr_prep( struct uni_arr* arr, void* data )
{
	if( !arr )
	{
		uni_die( );
	}

	if( arr->sz >= arr->cap )
	{
		u8* newdata;

		newdata = uni_alloc( arr->elemsz * arr->cap << 1 );
		arr->cap <<= 1;
		uni_memcpy( newdata + arr->elemsz, arr->data, arr->elemsz * arr->sz );
		uni_memcpy( newdata, data, arr->elemsz );
		uni_free( arr->data );
		arr->data = newdata;
	}
	else
	{
		ptri i;

		for( i = arr->sz; i > 0; --i )
		{
			uni_memcpy( arr->data + ( arr->elemsz * i ),
			   arr->data + ( arr->elemsz * ( i - 1 ) ),
			   arr->elemsz );
		}

		uni_memcpy( arr->data, data, arr->elemsz );
	}

	return 0;
}

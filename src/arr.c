/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "arr.h"

#include <stdarg.h>
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
	if( !arr )
	{
		uni_die( );
	}

	{
		void* ret;
		ptri sz;

		if( !arr->data )
		{
			return NULL;
		}

		sz  = arr->elemsz * arr->sz;
		ret = uni_alloc( sz );
		uni_memcpy( ret, arr->data, sz );

		return ret;
	}
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

		if( !arr->data || r.hi <= r.lo || r.hi > arr->sz )
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
	if( !arr || !data )
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
	if( !arr || !data )
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

int uni_arr_ins( struct uni_arr* arr, ptri ind, void* data )
{
	if( !arr || !data || ind > arr->sz )
	{
		uni_die( );
	}

	while( arr->sz >= arr->cap )
	{
		arr->data = uni_realloc( arr->data, arr->cap << 1 );
		arr->cap <<= 1; /* *= 2 */
	}

	if( ind < arr->sz )
	{
		ptri i;

		for( i = arr->sz - 1; i >= ind; --i )
		{
			uni_memcpy( arr->data + ( arr->elemsz * ( i + 1 ) ),
			   arr->data + ( arr->elemsz * i ),
			   arr->elemsz );
		}

		uni_memcpy( arr->data + ( arr->elemsz * ind ), data, arr->elemsz );
	}
	else
	{
		uni_memcpy( arr->data + ( arr->elemsz * arr->sz ), data, arr->elemsz );
	}

	return 0;
}

void uni_arr_ovr( struct uni_arr* arr, ptri ind, void* data )
{
	if( !arr || !data || ind >= arr->sz )
	{
		uni_die( );
	}

	uni_memcpy( arr->data + ( arr->elemsz * ind ), data, arr->elemsz );
}

struct uni_arr* uni_arr_conc( struct uni_arr* arr, ... )
{
	if( !arr )
	{
		uni_die( );
	}

	{
		struct uni_arr* ret;
		struct uni_arr* cur;
		ptri newsz, i;
		u32 elemsz;
		va_list args;

		va_start( args, arr );

		cur    = va_arg( args, struct uni_arr* );
		elemsz = 0;
		newsz  = 0;

		while( cur )
		{
			newsz += cur->sz;
			elemsz = elemsz == 0 ? cur->elemsz : elemsz;

			if( cur->elemsz != elemsz )
			{
				return NULL;
			}

			cur = va_arg( args, struct uni_arr* );
		}

		va_end( args );

		ret = uni_arr_initsz( elemsz, newsz );

		va_start( args, arr );

		cur = va_arg( args, struct uni_arr* );
		i   = 0;

		while( cur )
		{
			uni_memcpy( ret->data + ( ret->elemsz * i ),
			   cur->data,
			   ( ret->elemsz * cur->sz ) );
			i += cur->sz;

			va_arg( args, struct uni_arr* );
		}

		return ret;
	}
}

struct uni_arr* uni_arr_concv( struct uni_arr** arr )
{
	if( !arr )
	{
		uni_die( );
	}

	{
		struct uni_arr* ret;
		ptri newsz, i;
		u32 elemsz;

		for( i = 0, newsz = 0, elemsz = 0; arr[i] != NULL; ++i )
		{
			elemsz = elemsz == 0 ? arr[i]->elemsz : elemsz;
			newsz += arr[i]->sz;

			if( arr[i]->elemsz != elemsz )
			{
				return NULL;
			}
		}

		ret = uni_arr_initsz( elemsz, newsz );

		for( i = 0; arr[i] != NULL; ++i )
		{
			uni_memcpy( ret->data + ( ret->elemsz * i ),
			   arr[i]->data,
			   ret->elemsz * arr[i]->sz );
		}

		return ret;
	}
}

struct uni_arr* uni_arr_slice( struct uni_arr* arr, struct rangep r )
{
	if( !arr || r.hi <= r.lo || r.hi > arr->sz )
	{
		uni_die( );
	}

	{
		struct uni_arr* ret;
		const ptri sz = r.hi - r.lo;

		ret = uni_arr_initsz( arr->elemsz, sz );

		uni_memcpy(
		   ret->data, arr->data + ( arr->elemsz * r.lo ), arr->elemsz * sz );

		return ret;
	}
}

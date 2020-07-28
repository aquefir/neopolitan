/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/memory.h>

#include <stdlib.h>
#include <string.h>

#ifndef CFG_GBA

void* uni_alloc( ptri sz )
{
	void* ret;

	if( sz == 0 )
	{
		abort( );
	}

	ret = malloc( sz );

	if( ret == NULL )
	{
		abort( );
	}

	return ret;
}

void* uni_alloc0( ptri sz )
{
	void* ret;

	ret = uni_alloc( sz );

	memset( ret, 0, sz );

	return ret;
}

void* uni_realloc( void* p, ptri sz )
{
	void* ret;

	if( p == NULL || sz == 0 )
	{
		abort( );
	}

	ret = realloc( p, sz );

	if( ret == NULL )
	{
		abort( );
	}

	return ret;
}

void* uni_tryalloc( ptri sz ) { return malloc( sz ); }

void* uni_tryalloc0( ptri sz )
{
	void* ret;

	if( sz == 0 )
	{
		return NULL;
	}

	ret = malloc( sz );

	if( ret != NULL )
	{
		memset( ret, 0, sz );
	}

	return ret;
}

void* uni_tryrealloc( void* p, ptri sz )
{
	if( p == NULL || sz == 0 )
	{
		return NULL;
	}

	return realloc( p, sz );
}

void uni_free( void* p )
{
	if( p != NULL )
	{
		free( p );
	}
}

void uni_memset( void* p, u8 n, ptri sz )
{
	if( p != NULL && sz > 0 )
	{
		memset( p, n, sz );
	}
}

void uni_memcpy( void* dst, const void* src, ptri sz )
{
	if( dst != NULL && src != NULL && sz > 0 )
	{
		memcpy( dst, src, sz );
	}
}

int uni_memcmp( const void* a, const void* b, ptri sz )
{
	if( a && b && sz )
	{
		u8* aa = (u8*)a;
		u8* bb = (u8*)b;
		ptri i;

		for( i = 0; i < sz; ++i )
		{
			if( aa[i] != bb[i] )
			{
				return 0;
			}
		}

		return 1;
	}

	return 0;
}

#endif /* CFG_GBA */

/****************************************************************************\
 *                                  unilib                                  *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "table.h"

#include <mt19937/random.h>
#include <uni/memory.h>

uni_tblkey_t uni_new_tblkey( void )
{
	uni_tblkey_t ret;
	struct mt_prng* prng;

	prng = mt_prng_init( );
	ret  = mt_range_u32( prng, 1, U32_MAX - 1 );
	mt_prng_fini( prng );

	return ret;
}

int uni_chk_tblkey( struct uni_tbl* tbl, uni_tblkey_t key )
{
	if( !tbl || !key )
	{
		uni_die( );
	}

	{
		ptri i;

		for( i = 0; i < tbl->rowct; ++i )
		{
			if( tbl->keys[i] == key )
			{
				return 1;
			}
		}
	}

	return 0;
}

struct uni_tbl* uni_tbl_init( u32 elemsz )
{
	if( !elemsz )
	{
		uni_die( );
	}

	{
		struct uni_tbl* ret;

		ret = uni_alloc( sizeof( struct uni_tbl ) );

		ret->elemsz = elemsz;
		ret->rowct  = 0;
		ret->rowcap = 0;
		ret->keys   = NULL;
		ret->data   = NULL;

		return ret;
	}
}

void uni_tbl_fini( struct uni_tbl* tbl )
{
	if( !tbl )
	{
		uni_die( );
	}

	if( tbl->data )
	{
		uni_free( tbl->data );
		tbl->data = NULL;
	}

	if( tbl->keys )
	{
		uni_free( tbl->keys );
		tbl->keys = NULL;
	}

	uni_free( tbl );
}

void uni_tbl_ins( struct uni_tbl* tbl, uni_tblkey_t key, const void* data )
{
	if( !tbl || !key || !data )
	{
		uni_die( );
	}

	if( !tbl->data || !tbl->keys )
	{
		tbl->data = uni_alloc( tbl->elemsz << 4 /* * 16 */ );
		tbl->keys =
			uni_alloc( sizeof( uni_tblkey_t ) << 4 /* * 16 */ );
		tbl->rowct  = 1;
		tbl->rowcap = 16;
	}
	else
	{
		while( tbl->rowct >= tbl->rowcap )
		{
			tbl->rowcap <<= 1; /* *= 2 */
		}

		tbl->data =
			uni_realloc( tbl->data, tbl->elemsz * tbl->rowcap );
		tbl->keys = uni_realloc(
			tbl->keys, sizeof( uni_tblkey_t ) * tbl->rowcap );
	}

	{
		ptri i;

		for( i = 0; i < tbl->rowct; ++i )
		{
			if( tbl->keys[i] == key )
			{
				uni_die( );
			}
		}

		tbl->keys[tbl->rowct] = key;
		uni_memcpy( (u8*)( tbl->data ) + ( tbl->rowct * tbl->elemsz ),
			data,
			tbl->elemsz );
		tbl->rowct++;
	}
}

void* uni_tbl_get( struct uni_tbl* tbl, uni_tblkey_t key )
{
	if( !tbl || !key )
	{
		uni_die( );
	}

	{
		ptri i;

		for( i = 0; i < tbl->rowct; ++i )
		{
			if( tbl->keys[i] == key )
			{
				return (void*)( (u8*)tbl->data +
					( tbl->elemsz * i ) );
			}
		}

		return NULL;
	}
}

void uni_tbl_del( struct uni_tbl* tbl, uni_tblkey_t key )
{
	if( !tbl || !key )
	{
		uni_die( );
	}

	{
		ptri i;
		int present = 0;

		for( i = 0; i < tbl->rowct; ++i )
		{
			if( tbl->keys[i] == key )
			{
				present = 1;

				break;
			}
		}

		if( present )
		{
			for( i += 1; i < tbl->rowct; ++i )
			{
				uni_memcpy( (u8*)tbl->data +
						( tbl->elemsz * ( i - 1 ) ),
					(u8*)tbl->data + ( tbl->elemsz * i ),
					tbl->elemsz );
				tbl->keys[i - 1] = tbl->keys[i];
			}

			tbl->rowct--;
		}
	}
}

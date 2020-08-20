/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/futils.h>

#ifndef CFG_GBA
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#endif
#include <uni/err.h>
#include <uni/memory.h>
#include <uni/types/options.h>
#include <uni/types/int.h>

/* This should be pure C compatible, so no fstat. */
/* PURE FUNCTION */
UNI_OPTION( ptri ) uni_filesz( const char* fname )
{
	UNI_OPTION( ptri ) ret = { 0, 0 };

#ifndef CFG_GBA
	FILE* f;
	long sz;

	f = fopen( fname, "rb" );

	if( !f )
	{
		return ret;
	}

	if( fseek( f, 0, SEEK_END ) != 0 )
	{
		fclose( f );

		return ret;
	}

	sz = ftell( f );
	/* LONG_MAX may be returned, meaning it failed */
	ret.is  = sz == S64_MAX ? 0 : 1;
	ret.val = sz == S64_MAX ? 0 : (ptri)sz;

	fclose( f );
#endif

	return ret;
}

int uni_buffile( const char* fname, u8* ret, ptri ret_sz )
{
#ifndef CFG_GBA
	FILE* f;
	ptri readsz;

	ASSERT( fname != NULL );
	ASSERT( ret != NULL );

	f = fopen( fname, "rb" );
	if( !f )
	{
		return 1;
	}

	readsz = fread( ret, 1, ret_sz, f );
	fclose( f );

	return readsz != ret_sz ? 1 : 0;
#else
	return 1;
#endif
}

#define BUFFER_SZ 1024

int uni_loadfile( const char* fname, u8** ret, ptri* ret_sz )
{
#ifndef CFG_GBA
	u8 buffer[BUFFER_SZ];
	u8* data;
	ptri data_sz;
	FILE* f;

	ASSERT( ret != NULL );
	ASSERT( ret_sz != NULL );

	f = fname == NULL ? stdin : fopen( fname, "rb" );

	if(!f)
	{
		return 1;
	}

	if(!fname)
	{
		f = freopen( NULL, "rb", stdin );
	}

	data = NULL;
	data_sz = 0;

	for(;;)
	{
		ptri r = fread( buffer, sizeof( u8 ), BUFFER_SZ, f );

		data = !data ? uni_alloc( sizeof(u8) * r )
			: uni_realloc( data, sizeof(u8) * (data_sz + r) );

		uni_memcpy( data + data_sz, buffer, sizeof(u8) * r );

		data_sz += r;

		if(r < BUFFER_SZ)
		{
			if(ferror( f ))
			{
				uni_perror( "Error occured in reading file. Exiting..." );

				return 1;
			}

			break;
		}
	}

	if(!fname)
	{
		f = freopen( NULL, "r", stdin );
	}

	*ret = data;
	*ret_sz = data_sz;

	return 0;
#else
	return 1;
#endif
}

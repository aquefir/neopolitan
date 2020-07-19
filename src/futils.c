/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/futils.h>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <uni/err.h>
#include <uni/types/options.h>
#include <uni/types/int.h>

/* This should be pure C compatible, so no fstat. */
/* PURE FUNCTION */
UNI_OPTION( ptri ) uni_filesz( const char* fname )
{
	FILE* f;
	UNI_OPTION( ptri ) ret;
	long sz;

	ret.val = 0;
	ret.is  = 0;

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

	return ret;
}

int uni_buffile( const char* fname, u8* ret, ptri ret_sz )
{
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
}

int uni_loadfile( const char* fname, u8** ret, ptri* ret_sz )
{
	UNI_OPTION( ptri ) sz;

	ASSERT( fname != NULL );
	ASSERT( ret != NULL );
	ASSERT( ret_sz != NULL );

	sz = uni_filesz( fname );

	if( !sz.is )
	{
		return 1;
	}

	*ret_sz = sz.val;
	*ret    = malloc( *ret_sz );

	if( *ret == NULL && *ret_sz > 0 )
	{
		return 1;
	}

	return uni_buffile( fname, *ret, *ret_sz );
}

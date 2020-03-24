/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/futils.h>

#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* returns negative value on error. This should be pure C compatible, so no
 * fstat. */
/* PURE FUNCTION */
long uni_filesz( const char* fname )
{
	FILE* f;
	long sz;

	assert( fname != NULL );

	f = fopen( fname, "rb" );

	if( !f )
	{
		return -1;
	}

	if( fseek( f, 0, SEEK_END ) != 0 )
	{
		fclose( f );
		return -1;
	}

	sz = ftell( f );
	/* LONG_MAX may be returned, meaning it failed */
	sz = sz == LONG_MAX ? -1 : sz;

	fclose( f );
	return sz;
}

int uni_buffile( const char* fname, unsigned char* ret, size_t ret_sz )
{
	FILE* f;
	size_t readsz;

	assert( fname != NULL );
	assert( ret != NULL );

	f = fopen( fname, "rb" );
	if( !f )
	{
		return 1;
	}

	readsz = fread( ret, 1, ret_sz, f );
	fclose( f );

	return readsz != ret_sz ? 1 : 0;
}

int uni_loadfile( const char* fname, unsigned char** ret, size_t* ret_sz )
{
	long sz;

	assert( fname != NULL );
	assert( ret != NULL );
	assert( ret_sz != NULL );

	sz = uni_filesz( fname );

	if( sz < 0 )
	{
		return 1;
	}

	*ret_sz = (size_t)sz;
	*ret    = malloc( *ret_sz );

	if( *ret == NULL && *ret_sz > 0 )
	{
		return 1;
	}

	return uni_buffile( fname, *ret, *ret_sz );
}

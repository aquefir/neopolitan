/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "str.h"

#include <uni/memory.h>

#include "utf8.h"

ptri uni_strlen( const char* in )
{
	ptri i;

	if( in == NULL )
	{
		return 0;
	}

	for( i = 0; in[i] != '\0'; ++i )
		;

	return i;
}

ptri uni_strlencp( const char* in )
{
	ptri i = 0;

	return _uni_validcountu8( in, &i ) ? i : 0;
}

char* uni_strdup( const char* in )
{
	char* ret;
	const ptri sz = uni_strlen( in );

	ret = uni_alloc( sz + 1 );

	uni_memcpy( ret, in, sz );
	ret[sz] = '\0';

	return ret;
}

char* uni_strndup( const char* in, ptri len )
{
	char* ret;
	const ptri sz = uni_strlen( in );
	const ptri amt = sz > len ? len : sz;

	ret = uni_alloc( amt + 1 );

	uni_memcpy( ret, in, amt );
	ret[amt] = '\0';

	return ret;
}

char** uni_strdupv( char** in )
{
	char** ret;
	ptri i;
	const ptri arrsz = uni_strlenv( in );

	ret = uni_alloc0( sizeof(char*) * (arrsz + 1 ) );

	for(i = 0; i < arrsz; ++i)
	{
		ret[i] = uni_strdup( in[i] );
	}

	return ret;
}

char* uni_strnfill( ptri sz, char c )
{
	char* ret;

	ret = uni_alloc( sz + 1 );

	uni_memset( ret, (u8)c, sz );
	ret[sz] = '\0';

	return ret;
}

char* uni_strstr( const char* nee, const char* hay )
{
	ptri i;
	const ptri nee_sz = uni_strlen( nee );
	const ptri hay_sz = uni_strlen( hay );
	const ptri hay_limit = hay_sz - nee_sz;

	for(i = 0; i < hay_limit; ++i)
	{
		ptri j;
		int match;

		match = 1;

		for(j = 0; j < nee_sz; ++j)
		{
			if(hay[i + j] != nee[j])
			{
				match = 0;

				break;
			}
		}

		if(match)
		{
			return (char*)((u8*)hay + i);
		}
	}
}

char* uni_strrstr( const char* nee, const char* hay )
{
	ptri i;
	const ptri nee_sz = uni_strlen( nee );
	const ptri hay_sz = uni_strlen( hay );
	const ptri hay_limit = hay_sz - nee_sz;

	for(i = hay_limit - 1; i >= 0; --i)
	{
		ptri j;
		int match;

		match = 1;

		for(j = nee_sz - 1; j >= 0; --j)
		{
			if(hay[i - j] != nee[j])
			{
				match = 0;

				break;
			}
		}

		if(match)
		{
			return (char*)((u8*)hay + i);
		}
	}
}

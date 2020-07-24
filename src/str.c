/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "str.h"

#include <uni/err.h>
#include <uni/memory.h>

#include "utf8.h"

ptri uni_strlen( const char* in )
{
	ptri i;

	if( in == NULL )
	{
		uni_die( );
	}

	for( i = 0; in[i] != '\0'; ++i )
		;

	return i;
}

ptri uni_strlencp( const char* in )
{
	ptri i = 0;

	if(!in)
	{
		uni_die( );
	}

	return _uni_validcountu8( in, &i ) ? i : 0;
}

char* uni_strdup( const char* in )
{
	if(!in)
	{
		uni_die( );
	}

	{
		char* ret;
		const ptri sz = uni_strlen( in );

		ret = uni_alloc( sz + 1 );

		uni_memcpy( ret, in, sz );
		ret[sz] = '\0';

		return ret;
	}
}

char* uni_strndup( const char* in, ptri len )
{
	if(!in || !len)
	{
		uni_die( );
	}

	{
		char* ret;
		const ptri sz = uni_strlen( in );
		const ptri amt = sz > len ? len : sz;

		ret = uni_alloc( amt + 1 );

		uni_memcpy( ret, in, amt );
		ret[amt] = '\0';

		return ret;
	}
}

char** uni_strdupv( char** in )
{
	if(!in)
	{
		uni_die( );
	}

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
}

char* uni_strnfill( ptri sz, char c )
{
	char* ret;

	if(!sz)
	{
		uni_die( );
	}

	ret = uni_alloc( sz + 1 );

	uni_memset( ret, (u8)c, sz );
	ret[sz] = '\0';

	return ret;
}

char* uni_strstr( const char* nee, const char* hay )
{
	if(!nee || !hay)
	{
		uni_die( );
	}

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
				return hay + i;
			}
		}

		return NULL;
	}
}

char* uni_strrstr( const char* nee, const char* hay )
{
	if(!nee || !hay)
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri nee_sz = uni_strlen( nee );
		const ptri hay_sz = uni_strlen( hay );
		const ptri hay_limit = hay_sz - nee_sz;
		char* ret;

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
				ret = hay + i;
			}
		}

		return ret;
	}
}

int uni_strequ( const char* a, const char* b )
{
	if(!a || !b)
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri a_sz = uni_strlen( a );
		const ptri b_sz = uni_strlen( b );

		if(b_sz != a_sz)
		{
			return 0;
		}

		for(i = 0; i < b_sz; ++i)
		{
			if(a[i] != b[i])
			{
				return 0;
			}
		}

		return 1;
	}
}

int uni_strpre( const char* a, const char* b )
{
	if(!a || !b)
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri a_sz = uni_strlen( a );
		const ptri b_sz = uni_strlen( b );

		if(b_sz > a_sz)
		{
			return 0;
		}

		for(i = 0; i < b_sz; ++i)
		{
			if(a[i] != b[i])
			{
				return 0;
			}
		}

		return 1;
	}
}

int uni_strsuf( const char* a, const char* b )
{
	if(!a || !b)
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri a_sz = uni_strlen( a );
		const ptri b_sz = uni_strlen( b );

		if(b_sz > a_sz)
		{
			return 0;
		}

		for(i = a_sz - b_sz; i < a_sz; ++i)
		{
			if(a[i] != b[i])
			{
				return 0;
			}
		}

		return 1;
	}
}

int uni_isascii( const char* in )
{
	if(!in)
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri in_sz = uni_strlen( in );

		for(i = 0; i < in_sz; ++i)
		{
			if((u8)(in[i]) >= 0x80)
			{
				return 0;
			}
		}

		return 1;
	}
}

int uni_isalnum( char c )
{
	return uni_isalpha( c ) || uni_isdigit( c );
}

int uni_isalpha( char c )
{
	return uni_isupper( c ) || uni_islower( c );
}

int uni_isdigit( char c )
{
	return (u8)c >= 0x30 && (u8)c <= 0x39;
}

int uni_isxdigit( char c )
{
	return ((u8)c >= 0x30 && (u8)c <= 0x39) || \
		((u8)c >= 0x41 && (u8)c <= 0x46) || \
		((u8)c >= 0x61 && (u8)c <= 0x66);
}

int uni_iscntrl( char c )
{
	return ((u8)c >= 0x01 && (u8)c <= 0x1F) || (u8)c == 0x7F;
}

int uni_isprint( char c )
{
	return (u8)c >= 0x20 && (u8)c <= 0x7E;
}

int uni_ispunct( char c )
{
	const u8 ch = (u8)c;

	return (ch >= 0x21 && ch <= 0x2F) || (ch >= 0x3A && ch <= 0x40) || \
		(ch >= 0x5B && ch <= 0x60) || (ch >= 0x7B && ch <= 0x7E);
}

int uni_isspace( char c )
{
	return (u8)c == 0x20 || ((u8)c >= 0x09 && (u8)c <= 0x0D);
}

int uni_isupper( char c )
{
	return (u8)c >= 0x41 && (u8)c <= 0x5A;
}

int uni_isupper( char c )
{
	return (u8)c >= 0x61 && (u8)c <= 0x7A;
}

int uni_digitval( char c )
{
	if((u8)c < 0x30)
	{
		return 0;
	}

	return (u8)c - 0x30;
}

int uni_xdigitval( char c )
{
	/* decimal digit, or out of bounds. digitval will handle it */
	if((u8)c <= 0x39)
	{
		return uni_digitval( c );
	}
	/* lowercase alpha */
	else if((u8)c >= 0x61)
	{
		return (u8)c - 0x57;
	}

	/* else: uppercase alpha */
	return (u8)c - 0x37;
}

char* uni_strchomp( char* in, char c )
{
	if(!in || !c)
	{
		uni_die( );
	}

	{
		char* ret;
		ptri i, offs;
		const ptri in_sz = uni_strlen( in );

		for(i = 0; i < in_sz; ++i)
		{
			if(in[i] != c)
			{
				break;
			}
		}

		offs = i;

		for(i = offs; i < in_sz; ++i)
		{
			in[i - offs] = in[i];
		}

		in[in_sz - offs] = '\0';

		return in;
	}
}

char* uni_strchug( char* in, char c )
{
	if(!in || !c)
	{
		uni_die( );
	}

	{
		ptri i, offs;
		const ptri in_sz = uni_strlen( in );

		for(i = in_sz - 1, offs = 0; i >= 0; --i, ++offs)
		{
			if(in[i] != c)
			{
				break;
			}
		}

		in[in_sz - offs] = '\0';

		return in;
	}
}

/****************************************************************************\
 *                            neopolitan strings                            *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "str.h"

#include <stdarg.h>
#include <uni/err.h>
#include <uni/memory.h>

#include "utf8.h"

ptri uni_strlen( const char * in )
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

ptri uni_strlencp( const char * in )
{
	ptri i = 0;

	if( !in )
	{
		uni_die( );
	}

	return !_uni_scanu8( in, NULL, &i, 0, 0, 0 ) ? i : 0;
}

char * uni_strdup( const char * in )
{
	if( !in )
	{
		uni_die( );
	}

	{
		char * ret;
		const ptri sz = uni_strlen( in );

		ret = uni_alloc( sz + 1 );

		uni_memcpy( ret, in, sz );
		ret[sz] = '\0';

		return ret;
	}
}

char * uni_strndup( const char * in, ptri len )
{
	if( !in || !len )
	{
		uni_die( );
	}

	{
		char * ret;
		const ptri sz  = uni_strlen( in );
		const ptri amt = sz > len ? len : sz;

		ret = uni_alloc( amt + 1 );

		uni_memcpy( ret, in, amt );
		ret[amt] = '\0';

		return ret;
	}
}

char ** uni_strdupv( char ** in )
{
	if( !in )
	{
		uni_die( );
	}

	{
		char ** ret;
		ptri i;
		const ptri arrsz = uni_strlenv( in );

		ret = uni_alloc0( sizeof( char * ) * ( arrsz + 1 ) );

		for( i = 0; i < arrsz; ++i )
		{
			ret[i] = uni_strdup( in[i] );
		}

		return ret;
	}
}

char * uni_strnfill( ptri sz, char c )
{
	char * ret;

	if( !sz )
	{
		uni_die( );
	}

	ret = uni_alloc( sz + 1 );

	uni_memset( ret, (u8)c, sz );
	ret[sz] = '\0';

	return ret;
}

char * uni_strstr( const char * nee, const char * hay )
{
	if( !nee || !hay )
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri nee_sz    = uni_strlen( nee );
		const ptri hay_sz    = uni_strlen( hay );
		const ptri hay_limit = hay_sz - nee_sz;

		for( i = 0; i < hay_limit; ++i )
		{
			ptri j;
			int match;

			match = 1;

			for( j = 0; j < nee_sz; ++j )
			{
				if( hay[i + j] != nee[j] )
				{
					match = 0;

					break;
				}
			}

			if( match )
			{
				return (char *)( hay + i );
			}
		}

		return NULL;
	}
}

char * uni_strrstr( const char * nee, const char * hay )
{
	if( !nee || !hay )
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri nee_sz    = uni_strlen( nee );
		const ptri hay_sz    = uni_strlen( hay );
		const ptri hay_limit = hay_sz - nee_sz;
		char * ret;

		for( i = 0; i < hay_limit; ++i )
		{
			ptri j;
			int match;

			match = 1;

			for( j = 0; j < nee_sz; ++j )
			{
				if( hay[i + j] != nee[j] )
				{
					match = 0;

					break;
				}
			}

			if( match )
			{
				ret = (char *)( hay + i );
			}
		}

		return ret;
	}
}

int uni_strequ( const char * a, const char * b )
{
	if( !a || !b )
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri a_sz = uni_strlen( a );
		const ptri b_sz = uni_strlen( b );

		if( b_sz != a_sz )
		{
			return 0;
		}

		for( i = 0; i < b_sz; ++i )
		{
			if( a[i] != b[i] )
			{
				return 0;
			}
		}

		return 1;
	}
}

int uni_strpre( const char * a, const char * b )
{
	if( !a || !b )
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri a_sz = uni_strlen( a );
		const ptri b_sz = uni_strlen( b );

		if( b_sz > a_sz )
		{
			return 0;
		}

		for( i = 0; i < b_sz; ++i )
		{
			if( a[i] != b[i] )
			{
				return 0;
			}
		}

		return 1;
	}
}

int uni_strsuf( const char * a, const char * b )
{
	if( !a || !b )
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri a_sz = uni_strlen( a );
		const ptri b_sz = uni_strlen( b );

		if( b_sz > a_sz )
		{
			return 0;
		}

		for( i = 0; i < b_sz; ++i )
		{
			if( a[a_sz - b_sz + i] != b[i] )
			{
				return 0;
			}
		}

		return 1;
	}
}

int uni_isascii( const char * in )
{
	if( !in )
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri in_sz = uni_strlen( in );

		for( i = 0; i < in_sz; ++i )
		{
			if( ( u8 )( in[i] ) >= 0x80 )
			{
				return 0;
			}
		}

		return 1;
	}
}

int uni_isalnum( char c ) { return uni_isalpha( c ) || uni_isdigit( c ); }

int uni_isalpha( char c ) { return uni_isupper( c ) || uni_islower( c ); }

int uni_isdigit( char c ) { return (u8)c >= 0x30 && (u8)c <= 0x39; }

int uni_isxdigit( char c )
{
	return ( (u8)c >= 0x30 && (u8)c <= 0x39 ) ||
		( (u8)c >= 0x41 && (u8)c <= 0x46 ) ||
		( (u8)c >= 0x61 && (u8)c <= 0x66 );
}

int uni_iscntrl( char c )
{
	return ( (u8)c >= 0x01 && (u8)c <= 0x1F ) || (u8)c == 0x7F;
}

int uni_isprint( char c ) { return (u8)c >= 0x20 && (u8)c <= 0x7E; }

int uni_ispunct( char c )
{
	const u8 ch = (u8)c;

	return ( ch >= 0x21 && ch <= 0x2F ) || ( ch >= 0x3A && ch <= 0x40 ) ||
		( ch >= 0x5B && ch <= 0x60 ) || ( ch >= 0x7B && ch <= 0x7E );
}

int uni_isspace( char c )
{
	return (u8)c == 0x20 || ( (u8)c >= 0x09 && (u8)c <= 0x0D );
}

int uni_isupper( char c ) { return (u8)c >= 0x41 && (u8)c <= 0x5A; }

int uni_islower( char c ) { return (u8)c >= 0x61 && (u8)c <= 0x7A; }

int uni_digitval( char c )
{
	if( (u8)c < 0x30 )
	{
		return 0;
	}

	return (u8)c - 0x30;
}

int uni_xdigitval( char c )
{
	/* decimal digit, or out of bounds. digitval will handle it */
	if( (u8)c <= 0x39 )
	{
		return uni_digitval( c );
	}
	/* lowercase alpha */
	else if( (u8)c >= 0x61 )
	{
		return (u8)c - 0x57;
	}

	/* else: uppercase alpha */
	return (u8)c - 0x37;
}

char * uni_strchomp( char * in, char c )
{
	if( !in || !c )
	{
		uni_die( );
	}

	{
		ptri i, offs;
		const ptri in_sz = uni_strlen( in );

		for( i = 0; i < in_sz; ++i )
		{
			if( in[i] != c )
			{
				break;
			}
		}

		offs = i;

		for( i = offs; i < in_sz; ++i )
		{
			in[i - offs] = in[i];
		}

		in[in_sz - offs] = '\0';

		return in;
	}
}

char * uni_strchug( char * in, char c )
{
	if( !in || !c )
	{
		uni_die( );
	}

	{
		ptri i, offs;
		const ptri in_sz = uni_strlen( in );

		for( i = in_sz - 1, offs = 0; i >= 0; --i, ++offs )
		{
			if( in[i] != c )
			{
				break;
			}
		}

		in[in_sz - offs] = '\0';

		return in;
	}
}

char ** uni_strsplit( const char * in, const char * delim, int max )
{
	if( !in || !delim )
	{
		uni_die( );
	}

	{
		char ** ret;
		ptri i, last_i, sz, ret_i, ret_sz;
		const ptri in_sz    = uni_strlen( in );
		const ptri delim_sz = uni_strlen( delim );

		if( delim_sz > in_sz )
		{
			return uni_alloc0( sizeof( char * ) );
		}

		if( max < 1 )
		{
			max    = S32_MAX;
			ret_sz = 0;
			ret    = NULL;
		}
		else
		{
			ret_sz = max + 1;
			ret    = uni_alloc( sizeof( char * ) * ret_sz );
		}

		ret_i  = 0;
		last_i = 0;

		for( i = 0; i < in_sz - delim_sz + 1; ++i )
		{
			if( uni_memcmp( in + i, delim, delim_sz ) )
			{
				/* we hit a delimiter. allocate it off */
				if( ret_sz == 0 )
				{
					ret = uni_alloc(
						sizeof( char * ) * 2 );
					ret_sz = 2;
				}
				else
					while( ret_i >= ret_sz )
					{
						ret = uni_realloc( ret,
							sizeof( char * ) *
								( ret_sz *
									2 ) );
						ret_sz <<= 1; /* *= 2 */
					}

				sz         = i - last_i;
				ret[ret_i] = uni_alloc(
					sizeof( char ) * ( sz + 1 ) );
				i += delim_sz - 1;

				if( sz > 0 )
				{
					uni_memcpy(
						ret[ret_i], in + last_i, sz );
				}

				last_i         = i + 1;
				ret[ret_i][sz] = '\0';
				ret_i++;

				if( ret_i >= max - 1 )
				{
					/* set counter to the end so remainder
					 * gets scooped up */
					i = in_sz - delim_sz + 1;

					break;
				}
			}
		}

		if( !ret_i && !ret_sz )
		{
			ret    = uni_alloc( sizeof( char * ) * 2 );
			ret[0] = uni_strdup( in );
			ret[1] = NULL;

			return ret;
		}

		while( ret_i >= ret_sz )
		{
			ret = uni_realloc(
				ret, sizeof( char * ) * ( ret_sz << 1 ) );
			ret_sz <<= 1; /* *= 2 */
		}

		sz         = i - last_i + delim_sz;
		ret[ret_i] = uni_alloc( sizeof( char ) * ( sz + 1 ) );

		if( sz > 0 )
		{
			uni_memcpy( ret[ret_i], in + last_i, sz );
		}

		ret[ret_i][sz] = '\0';
		ret_i++;

		while( ret_i >= ret_sz )
		{
			ret = uni_realloc(
				ret, sizeof( char * ) * ( ret_sz << 1 ) );
			ret_sz <<= 1; /* *= 2 */
		}

		ret[ret_i] = NULL;
		ret_i++;

		return ret;
	}
}

ptri uni_strlenv( char ** arr )
{
	if( !arr )
	{
		uni_die( );
	}

	{
		ptri i;

		for( i = 0; arr[i] != NULL; ++i )
			;

		return i;
	}
}

void uni_strfreev( char ** arr )
{
	if( !arr )
	{
		uni_die( );
	}

	{
		ptri i;

		for( i = 0; arr[i] != NULL; ++i )
		{
			uni_free( arr[i] );
		}

		uni_free( arr );
	}
}

int uni_strequv( char ** arr_a, char ** arr_b )
{
	if( !arr_a || !arr_b )
	{
		uni_die( );
	}

	{
		ptri i;
		const ptri arr_a_sz = uni_strlenv( arr_a );
		const ptri arr_b_sz = uni_strlenv( arr_b );

		if( arr_a_sz != arr_b_sz )
		{
			return 0;
		}

		for( i = 0; i < arr_a_sz; ++i )
		{
			if( !uni_strequ( arr_a[i], arr_b[i] ) )
			{
				return 0;
			}
		}

		return 1;
	}
}

char * uni_strjoin( const char * delim, ... )
{
	if( !delim )
	{
		uni_die( );
	}

	{
		va_list args;
		char * s;
		char * ret;
		ptri sz, sz2, i;
		const ptri delim_sz = uni_strlen( delim );

		va_start( args, delim );

		s = va_arg( args, char * );

		if( !s )
		{
			ret = uni_strdup( "" );
			va_end( args );

			return ret;
		}

		/* get the total size to allocate first */
		sz = uni_strlen( s ) + 1;

		s = va_arg( args, char * );

		while( s )
		{
			sz += delim_sz + uni_strlen( s );
			s = va_arg( args, char * );
		}

		va_end( args );

		/* build the newly joined string */
		ret = uni_alloc( sizeof( char ) * ( sz + 1 ) );

		va_start( args, delim );

		s   = va_arg( args, char * );
		sz2 = uni_strlen( s );
		uni_memcpy( ret, s, sz2 );
		i = sz2;

		s = va_arg( args, char * );

		while( s )
		{
			sz2 = uni_strlen( s );
			uni_memcpy( ret + i, delim, delim_sz );
			uni_memcpy( ret + i + delim_sz, s, sz2 );
			i += sz2 + delim_sz;
			s = va_arg( args, char * );
		}

		ret[i] = '\0';
		va_end( args );

		return ret;
	}
}

char * uni_strjoinv( const char * delim, char ** arr )
{
	if( !delim || !arr )
	{
		uni_die( );
	}

	{
		ptri i, j, sz;
		char * ret;
		const ptri delim_sz = uni_strlen( delim );
		const ptri arr_sz   = uni_strlenv( arr );

		for( i = 0, sz = 0; i < arr_sz; ++i )
		{
			sz += uni_strlen( arr[i] ) + ( i > 0 ? delim_sz : 0 );
		}

		ret = uni_alloc( sizeof( char ) * ( sz + 1 ) );

		for( i = 0, j = 0; i < arr_sz; ++i )
		{
			const ptri str_sz = uni_strlen( arr[i] );

			if( i )
			{
				uni_memcpy( ret + j, delim, delim_sz );
				j += delim_sz;
			}

			uni_memcpy( ret + j, arr[i], str_sz );
			j += str_sz;
		}

		ret[j] = '\0';

		return ret;
	}
}

struct uni_str * uni_str_init( const char * init )
{
	struct uni_str * ret;

	ret       = uni_alloc( sizeof( struct uni_str ) );
	ret->data = init ? uni_strdup( init ) : NULL;
	ret->sz   = init ? uni_strlen( init ) : 0;
	ret->cap  = ret->sz + 1;

	return ret;
}

struct uni_str * uni_str_initsz( ptri size )
{
	struct uni_str * ret;

	ret       = uni_alloc( sizeof( struct uni_str ) );
	ret->data = size ? uni_alloc0( sizeof( char ) * ( size + 1 ) ) : NULL;
	ret->sz   = size;
	ret->cap  = ret->sz + 1;

	return ret;
}

void uni_str_fini( struct uni_str * str )
{
	if( str )
	{
		if( str->data )
		{
			uni_free( str->data );
		}

		uni_free( str );
	}
}

struct uni_str * uni_str_dup( struct uni_str * str )
{
	if( !str )
	{
		uni_die( );
	}

	{
		struct uni_str * ret;

		ret       = uni_alloc( sizeof( struct uni_str ) );
		ret->data = str->data
			? uni_alloc( sizeof( char ) * str->sz + 1 )
			: NULL;
		ret->sz   = str->sz;
		ret->cap  = str->sz + 1;

		return ret;
	}
}

ptri uni_str_getsz( struct uni_str * str )
{
	if( !str )
	{
		uni_die( );
	}

	return str->sz;
}

char * uni_str_make( struct uni_str * str )
{
	if( !str )
	{
		uni_die( );
	}

	{
		char * ret;

		ret = uni_alloc( sizeof( char ) * str->sz + 1 );
		uni_memcpy( ret, str->data, str->sz );
		ret[str->sz] = '\0';

		return ret;
	}
}

char * uni_str_mkslice( struct uni_str * str, struct rangep r )
{
	if( !str || r.hi <= r.lo || r.hi > str->sz )
	{
		uni_die( );
	}

	{
		char * ret;
		const ptri sz = r.hi - r.lo;

		ret = uni_alloc( sizeof( char ) * ( sz + 1 ) );
		uni_memcpy( ret, str->data + r.lo, sz );
		ret[sz] = '\0';

		return ret;
	}
}

int uni_str_app( struct uni_str * str, const char * in )
{
	if( !str || !in )
	{
		uni_die( );
	}

	{
		const ptri in_sz = uni_strlen( in );

		while( str->sz + in_sz + 1 >= str->cap )
		{
			str->cap <<= 1; /* *= 2 */
		}

		str->data =
			uni_realloc( str->data, sizeof( char ) * str->cap );

		uni_memcpy( (u8 *)( str->data ) + str->sz, in, in_sz );
		str->sz += in_sz;
		str->data[str->sz] = '\0';

		return 0;
	}
}

int uni_str_appch( struct uni_str * str, char in )
{
	if( !str )
	{
		uni_die( );
	}

	{
		while( str->sz + 2 >= str->cap )
		{
			str->cap <<= 1; /* *= 2 */
		}

		str->data =
			uni_realloc( str->data, sizeof( char ) * str->cap );

		str->data[str->sz] = in;
		str->sz++;
		str->data[str->sz] = '\0';

		return 0;
	}
}

int uni_str_prep( struct uni_str * str, const char * in )
{
	if( !str || !in )
	{
		uni_die( );
	}

	{
		const ptri in_sz = uni_strlen( in );
		char * tmpbuf;

		while( str->sz + in_sz + 1 >= str->cap )
		{
			str->cap <<= 1; /* *= 2 */
		}

		tmpbuf = uni_alloc( sizeof( char ) * str->cap );

		uni_memcpy( tmpbuf, in, in_sz );
		uni_memcpy( (u8 *)( tmpbuf ) + in_sz, str->data, str->sz );
		str->sz += in_sz;
		tmpbuf[str->sz] = '\0';

		uni_free( str->data );
		str->data = tmpbuf;

		return 0;
	}
}

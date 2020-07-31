/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "str.h"
#include <uni/types/int.h>
#include "utf8.h"

int uni_validu8( const char* in ) { return _uni_validcountu8( in, NULL ); }

int _uni_validcountu8( const char* in, ptri* szout )
{
	ptri i, q, sz;

	if( in == NULL )
	{
		return 0;
	}

	for( i = 0, q = 0, sz = uni_strlen( in ); i < sz; ++i, ++q )
	{
		int j, n;
		const u8 c = in[i];

		if( c > 0 && c <= 0x7F )
		{
			n = 0;
		}
		else if( ( c & 0xE0 ) == 0xC0 )
		{
			n = 1;
		}
		else if( c == 0xED && i < ( sz - 1 ) &&
		   ( ( u8 )( in[i + 1] ) & 0xA0 ) == 0xA0 )
		{
			/* U+D800 - U+DFFF */
			return 0;
		}
		else if( ( c & 0xF0 ) == 0xE0 )
		{
			n = 2;
		}
		else if( ( c & 0xF8 ) == 0xF0 )
		{
			n = 3;
		}
		else if( ( c & 0xFC ) == 0xF8 )
		{
			n = 4;
		}
		else if( ( c & 0xFE ) == 0xFC )
		{
			n = 5;
		}
		else
		{
			return 0;
		}

		for( j = 0; j < n && i < sz; ++j )
		{
			if( ( ++i == sz ) ||
			   ( ( u8 )( in[i] ) & 0xC0 ) != 0x80 )
			{
				return 0;
			}
		}
	}

	if( szout != NULL )
	{
		*szout = q;
	}

	return 1;
}

int uni_u8dec( char* in, char32* out )
{
	char32 o;

	if( !uni_validu8( in ) )
	{
		return 1;
	}

	if( !( in[0] & 0x80 ) )
	{
		o = (char32)in[0];
	}
	else if( ( in[0] & 0xFE ) == 0xFC )
	{
		o = in[5] & 0x3F;
		o |= ( in[4] & 0x3F ) << 6;
		o |= ( in[3] & 0x3F ) << 12;
		o |= ( in[2] & 0x3F ) << 18;
		o |= ( in[1] & 0x3F ) << 24;
		o |= ( in[0] & 0x1 ) << 30;
	}
	else if( ( in[0] & 0xFC ) == 0xF8 )
	{
		o = in[4] & 0x3F;
		o |= ( in[3] & 0x3F ) << 6;
		o |= ( in[2] & 0x3F ) << 12;
		o |= ( in[1] & 0x3F ) << 18;
		o |= ( in[0] & 0x3 ) << 24;
	}
	else if( ( in[0] & 0xF8 ) == 0xF0 )
	{
		o = in[3] & 0x3F;
		o |= ( in[2] & 0x3F ) << 6;
		o |= ( in[1] & 0x3F ) << 12;
		o |= ( in[0] & 0x7 ) << 18;
	}
	else if( ( in[0] & 0xF0 ) == 0xE0 )
	{
		o = in[2] & 0x3F;
		o |= ( in[1] & 0x3F ) << 6;
		o |= ( in[0] & 0xF ) << 12;
	}
	else if( in[0] & 0xC0 )
	{
		o = in[1] & 0x3F;
		o |= ( in[0] & 0x1F ) << 6;
	}

	*out = o;

	return 0;
}

u32 uni_u8decsz( char* in )
{
	return ( in[0] & 0xFE ) == 0xFC
	   ? 6
	   : ( in[0] & 0xFC ) == 0xF8 ? 5
	                              : ( in[0] & 0xF8 ) == 0xF0
	         ? 4
	         : ( in[0] & 0xF0 ) == 0xE0 ? 3
	                                    : ( in[0] & 0xE0 ) == 0xC0 ? 2 : 1;
}

int uni_u8enc( char32 in, char* out )
{
	if( in >= 0x10FFFF )
	{
		return 1;
	}

	if( in >= 0x8000000 )
	{
		out[0] = 0xFC | ( ( in >> 30 ) & 0x1 );
		out[1] = 0x80 | ( ( in >> 24 ) & 0x3F );
		out[2] = 0x80 | ( ( in >> 18 ) & 0x3F );
		out[3] = 0x80 | ( ( in >> 12 ) & 0x3F );
		out[4] = 0x80 | ( ( in >> 6 ) & 0x3F );
		out[5] = 0x80 | ( in & 0x3F );
	}
	else if( in >= 0x200000 )
	{
		out[0] = 0xF8 | ( ( in >> 24 ) & 0x3 );
		out[1] = 0x80 | ( ( in >> 18 ) & 0x3F );
		out[2] = 0x80 | ( ( in >> 12 ) & 0x3F );
		out[3] = 0x80 | ( ( in >> 6 ) & 0x3F );
		out[4] = 0x80 | ( in & 0x3F );
	}
	else if( in >= 0x10000 )
	{
		out[0] = 0xF0 | ( ( in >> 18 ) & 0x7 );
		out[1] = 0x80 | ( ( in >> 12 ) & 0x3F );
		out[2] = 0x80 | ( ( in >> 6 ) & 0x3F );
		out[3] = 0x80 | ( in & 0x3F );
	}
	else if( in >= 0x800 )
	{
		out[0] = 0xE0 | ( ( in >> 12 ) & 0xF );
		out[1] = 0x80 | ( ( in >> 6 ) & 0x3F );
		out[2] = 0x80 | ( in & 0x3F );
	}
	else if( in >= 0x80 )
	{
		out[0] = 0xC0 | ( in & 0x1F );
		out[1] = 0x80 | ( ( in >> 5 ) & 0x3F );
	}
	else
	{
		/* ASCII */
		out[0] = (char)( in & 0x7F );
	}

	return 0;
}

u32 uni_u8encsz( char32 c )
{
	return c >= 0x8000000 ? 6
	                      : c >= 0x200000
	      ? 5
	      : c >= 0x10000 ? 4 : c >= 0x800 ? 3 : c >= 0x80 ? 2 : 1;
}

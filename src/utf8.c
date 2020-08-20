/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "str.h"
#include <uni/err.h>
#include <uni/types/int.h>
#include "utf8.h"

int uni_validu8( const char* in )
{
	return !_uni_scanu8( in, NULL, NULL, 0, 0, 0 );
}

int _uni_scanu8( const char* in,
	ptri* byct,
	ptri* cpct,
	int stop,
	ptri stop_i,
	int stop_i_bytes )
{
	if( !in )
	{
		uni_die( );
	}

	{
		ptri by_i, cp_i;
		const ptri sz = uni_strlen( in );

		for( by_i = 0, cp_i = 0; by_i < sz; ++by_i, ++cp_i )
		{
			ptri j;
			const u8 ch = in[by_i];
			const s32 n = uni_u8decsz( ch );
			int done = 0, miderr = 0;

			if( stop && stop_i_bytes && by_i >= stop_i )
			{
				if( byct )
				{
					*byct = by_i;
				}

				if( cpct )
				{
					*cpct = cp_i;

					if( by_i > stop_i )
					{
						*cpct -= 1;

						miderr = 1;
					}
				}

				done = 1;
			}
			else if( stop && !stop_i_bytes && cp_i >= stop_i )
			{
				if( byct )
				{
					*byct = by_i;
				}

				if( cpct )
				{
					*cpct = cp_i;
				}

				done = 1;
			}

			if( n < 0 )
			{
				return 1;
			}

			for( j = 0; j < n - 1; ++j )
			{
				if( ++by_i == sz ||
					( ( u8 )( in[by_i] ) & 0xC0 ) != 0x80 )
				{
					return 1;
				}
			}

			if( done )
			{
				return miderr;
			}
		}

		if( byct )
		{
			*byct = by_i;
		}

		if( cpct )
		{
			*cpct = cp_i;
		}

		return 0;
	}
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
	else
	{
		return 1;
	}

	*out = o;

	return 0;
}

s32 uni_u8decsz( char in )
{
	const u8 ch = (u8)in;
	if( ch <= 0x7F )
	{
		return 1;
	}
	else if( ( ch & 0xE0 ) == 0xC0 )
	{
		return 2;
	}
	else if( ( ch & 0xF0 ) == 0xE0 )
	{
		return 3;
	}
	else if( ( ch & 0xF8 ) == 0xF0 )
	{
		return 4;
	}
	else if( ( ch & 0xFC ) == 0xF8 )
	{
		return 5;
	}
	else if( ( ch & 0xFE ) == 0xFC )
	{
		return 6;
	}
	else
	{
		return -1;
	}
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

u32 uni_u8encsz( char32 ch )
{
	return ch >= 0x8000000 ? 6
			       : ch >= 0x200000
			? 5
			: ch >= 0x10000 ? 4
					: ch >= 0x800 ? 3 : ch >= 0x80 ? 2 : 1;
}

struct uni_u8pos uni_u8by2cp( const char* in, ptri by_pos )
{
	struct uni_u8pos ret;

	ret.mid = _uni_scanu8( in, NULL, &ret.pos, 1, by_pos, 1 );

	return ret;
}

ptri uni_u8cp2by( const char* in, ptri cp_pos )
{
	ptri ret;

	if( !_uni_scanu8( in, &ret, NULL, 1, cp_pos, 0 ) )
	{
		return ret;
	}

	return 0;
}

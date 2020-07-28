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
			if( ( ++i == sz ) || ( ( u8 )( in[i] ) & 0xC0 ) != 0x80 )
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

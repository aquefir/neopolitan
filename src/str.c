/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include "str.h"

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

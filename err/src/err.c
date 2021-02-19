/****************************************************************************\
 *                        neopolitan error handling.                        *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/err.h>

#include <uni/log.h>

void uni_die( void ) { abort( ); }

void uni_assert_fail( const char * expr,
	const char * file,
	unsigned line,
	const char * func )
{
	__assert_fail( expr, file, line );
}

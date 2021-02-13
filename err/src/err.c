/****************************************************************************\
 *                        neopolitan error handling.                        *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/err.h>

#include <uni/log.h>

void abort( void );

void uni_die( void )
{
	abort( );
}

void __assert_fail(const char *, const char *, int);

void uni_assert_fail( const char * expr,
	const char * file,
	unsigned line,
	const char * func )
{
	__assert_fail(expr, file, line);
}

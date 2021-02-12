/****************************************************************************\
 *                            neopolitan logging                            *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/log.h>

#include <stdarg.h>
#ifndef CFG_GBA
#include <stdio.h>

#include <uni/err.h>

int uni_print( const char * fmt, ... )
{
	va_list args;

	ASSERT_RETNEG1( fmt != NULL );
	fprintf( stdout, "\n[info] " );
	va_start( args, fmt );
	vprintf( fmt, args );
	va_end( args );
	fflush( stdout );

	return 0;
}

int uni_pwarn( const char * fmt, ... )
{
	va_list args;

	ASSERT_RETNEG1( fmt != NULL );
	fprintf( stdout, "\n[warn] " );
	va_start( args, fmt );
	vprintf( fmt, args );
	va_end( args );
	fflush( stdout );

	return 0;
}

int uni_perror( const char * fmt, ... )
{
	va_list args;

	ASSERT_RETNEG1( fmt != NULL );
	fprintf( stderr, "\n[fail] " );
	va_start( args, fmt );
	vprintf( fmt, args );
	va_end( args );
	fflush( stderr );

	return 0;
}

#endif

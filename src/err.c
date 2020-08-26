/****************************************************************************\
 *                                  unilib                                  *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/err.h>

#ifdef CFG_GBA
#include <uni/gbabios.h>
#else
#include <stdlib.h>
#endif /* CFG_GBA */
#include <uni/log.h>

void uni_die( void )
{
#ifdef CFG_GBA
	_bios_halt( );
#else
	abort( );
#endif
}

void uni_assert_fail(
	const char* expr, const char* file, unsigned line, const char* func )
{
	uni_perror(
		"Assertion failed in file \"%s\" on line \"%u\", in function"
		" \"%s\".\nExpression: %s",
		file,
		line,
		func,
		expr );

#ifdef CFG_GBA
	_bios_halt( );
#else
	abort( );
#endif
}

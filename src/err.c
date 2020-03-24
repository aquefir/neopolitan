/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/err.h>

#include <stdlib.h>
#include <uni/log.h>

void uni_assert_fail(
   const char* expr, const char* file, unsigned line, const char* func )
{
	uni_perror( "Assertion failed in file \"%s\" on line \"%u\", in function"
	            " \"%s\".\nExpression: %s",
	   file,
	   line,
	   func,
	   expr );

	abort( );
}

/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#include <unilib/err.h>

#include <stdlib.h>
#include <unilib/log.h>

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

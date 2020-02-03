/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                           All rights reserved.                           *
\****************************************************************************/

#include <tes/battery.h>

extern int testing_vec( void );

extern void tes_pre( int ac, char* av[] ) {}

extern int tes_tests( void )
{
	int r;

	r = testing_vec( );

	return r;
}

extern void tes_post( void ) {}

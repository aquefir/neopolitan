/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                           All rights reserved.                           *
\****************************************************************************/

#include <tes/battery.h>

#include <stddef.h>

#include <unilib/array.h>
#include <unilib/shand.h>
#include <unilib/log.h>

int testing_vec( void )
{
	struct uni_vec v, v2, v3;
	struct rangep range = {0, 16};
	ptri i;
	u8 samp[8] = {127, 127, 127, 127, 127, 127, 127, 127};

	v = uni_vec_init( sizeof( u8 ), 16 );

	TES_ASSERT_NE( v.data, NULL );
	TES_ASSERT_EQ( v.sz, 16 );
	TES_ASSERT_EQ( v.elem_sz, sizeof( u8 ) );

	for( i = 0; i < 16; ++i )
	{
		v.data[i] = 0;
	}

	v2 = uni_vec_reserve( v, 48 );

	TES_ASSERT_EQ( v2.cap, 64 );
	TES_ASSERT_EQ( v2.sz, 16 );

	v = v2;

	/* make vector from stack-allocated array */
	v3 = uni_vec_init_ex( sizeof( u8 ), 8, samp );

	TES_ASSERT_NE( v3.data, NULL );

	/* emplace new data */
	v2 = uni_vec_emplace( v, v3, range );

	TES_ASSERT_NE( v2.data, NULL );

	v = v2;

	TES_ASSERT_EQ( v.sz, 8 );
	TES_ASSERT_EQ( v.cap, 64 );

	for( i = 0; i < 8; ++i )
	{
		TES_ASSERT_EQ( v.data[i], samp[i] );
	}

	/* emplace for removal of last 2 elements, no insertion */
	v2.data = NULL;
	v2.sz = v2.cap = 0;
	range.lo       = 6;
	range.hi       = 8;

	v2 = uni_vec_emplace( v, v2, range );

	TES_ASSERT_NE( v2.data, NULL );
	v = v2;

	TES_ASSERT_EQ( v.sz, 6 );

	uni_vec_fini( v3 );
	uni_vec_fini( v );

	return 0;
}

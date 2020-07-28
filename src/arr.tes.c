/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <tes/battery.h>

#include "arr.h"

TES_OPEN( );

{
	struct uni_arr* s32array;
	struct uni_arr* u16array;
	struct uni_arr* tmparray;
	struct uni_arr** bigarray;
	struct rangep range;
	s32 a, b;
	u16 c;
	s32* s32made;
	u16* u16made;

	s32array = uni_arr_init( sizeof( s32 ) );
	u16array = uni_arr_initsz( sizeof( u16 ), 4 );

	TES_ASSERT_NE( s32array, NULL );
	TES_ASSERT_EQ( uni_arr_getelemsz( s32array ), sizeof( s32 ) );
	TES_ASSERT_NE( u16array, NULL );
	TES_ASSERT_EQ( uni_arr_getelemsz( u16array ), sizeof( u16 ) );
	TES_ASSERT_EQ( uni_arr_getsz( u16array ), 4 );

	a = -5555;
	uni_arr_app( s32array, &a );
	TES_ASSERT_EQ( uni_arr_getsz( s32array ), 1 );

	tmparray = uni_arr_dup( s32array );
	TES_ASSERT_NE( tmparray, NULL );
	TES_ASSERT_EQ( tmparray->elemsz, sizeof( s32 ) );
	uni_arr_fini( tmparray );

	a = 16;
	b = 999;
	uni_arr_app( s32array, &a );
	uni_arr_app( s32array, &b );
	TES_ASSERT_EQ( uni_arr_getsz( s32array ), 3 );
	uni_arr_app( s32array, &b );
	uni_arr_app( s32array, &b );
	uni_arr_app( s32array, &a );
	TES_ASSERT_EQ( uni_arr_getsz( s32array ), 6 );
	uni_arr_app( s32array, &a );
	TES_ASSERT_EQ( uni_arr_getsz( s32array ), 7 );

	range.lo = 2;
	range.hi = 6;
	tmparray = uni_arr_slice( s32array, range );
	TES_ASSERT_EQ( uni_arr_getsz( tmparray ), 4 );

	s32made = uni_arr_make( tmparray );
	TES_ASSERT_NE( s32made, NULL );
	uni_arr_fini( tmparray );
	TES_ASSERT_EQ( s32made[0], b );
	TES_ASSERT_EQ( s32made[1], b );
	TES_ASSERT_EQ( s32made[2], b );
	TES_ASSERT_EQ( s32made[3], a );
	uni_free( s32made );

	TES_ASSERT_EQ( uni_arr_conc( s32array, u16array, NULL ), NULL );
	tmparray = uni_arr_conc( u16array, u16array, u16array, NULL );
	TES_ASSERT_NE( tmparray, NULL );
	TES_ASSERT_EQ( uni_arr_getsz( tmparray ), 12 );

	c = 123;
	uni_arr_prep( tmparray, &c );
	TES_ASSERT_EQ( uni_arr_getsz( tmparray ), 13 );

	uni_arr_app( tmparray, &c );
	TES_ASSERT_EQ( uni_arr_getsz( tmparray ), 14 );

	c = 66;
	uni_arr_ins( tmparray, 13, &c );
	TES_ASSERT_EQ( uni_arr_getsz( tmparray ), 15 );

	c = 7877;
	uni_arr_ovr( tmparray, 9, &c );
	TES_ASSERT_EQ( uni_arr_getsz( tmparray ), 15 );

	range.lo = 9;
	range.hi = 15;
	u16made  = uni_arr_mkslice( tmparray, range );
	TES_ASSERT_EQ( u16made[0], 7877 );
	TES_ASSERT_EQ( u16made[1], 0 );
	TES_ASSERT_EQ( u16made[2], 0 );
	TES_ASSERT_EQ( u16made[3], 0 );
	TES_ASSERT_EQ( u16made[4], 66 );
	TES_ASSERT_EQ( u16made[5], 123 );
	uni_free( u16made );

	uni_arr_fini( tmparray );
	uni_arr_fini( u16array );
	uni_arr_fini( s32array );
}

TES_CLOSE( );

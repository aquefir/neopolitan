/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                           All rights reserved.                           *
\****************************************************************************/

#include <tes/battery.h>

#include <unilib/array.h>
#include <unilib/log.h>
#include <unilib/shand.h>
#include <unilib/sort.h>

static int cmple_s32s( ptri sz, void* a, void* b )
{
	return sz != 4 ? 0 : *((s32*)a) <= *((s32*)b);
}

static int cmple_u16s( ptri sz, void* a, void* b )
{
	return sz != 2 ? 0 : *((u16*)a) <= *((u16*)b);
}

int testing_sort( void )
{
	s32 nums_in[10] = { 2, 1, 6, 5, 7, 8, 3, 4, -2, -10 };
	s32 nums_out[10] = { -10, -2, 1, 2, 3, 4, 5, 6, 7, 8 };
	u32 ids_in[8] = { 32, 33, 34, 35, 36, 37, 38, 39 };
	u32 ids_out[8] = { 39, 38, 37, 36, 35, 34, 33, 32 };
	u16 datas[8] = { 495, 485, 475, 465, 455, 445, 435, 425 };
	struct uni_vec nv, new_nv;
	struct uni_vec2 v, new_v;
	ptri i;

	v.vec[0] = uni_vec_init_ex( sizeof( u16 ), 8, datas );
	v.vec[1] = uni_vec_init_ex( sizeof( u32 ), 8, ids_in );
	nv = uni_vec_init_ex( sizeof( s32 ), 10, nums_in );

	new_nv = uni_mergesort( nv, cmple_s32s );
	new_v = uni_omergesort2( v, cmple_u16s );

	for(i = 0; i < 10; ++i)
	{
		uni_print( "Expected: %i --- Actual: %i\n", nums_out[i],
			*((s32*)uni_vec_getone( new_nv, i )) );
		TES_ASSERT_EQ(*((s32*)uni_vec_getone( new_nv, i )),
			nums_out[i] );
	}

	for(i = 0; i < 8; ++i)
	{
		TES_ASSERT_EQ( *((u32*)uni_vec_getone( new_v.vec[0], i )), ids_out[i] );
	}

	return 0;
}

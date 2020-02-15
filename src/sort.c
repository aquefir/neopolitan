/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                           All rights reserved.                           *
\****************************************************************************/

#include <string.h>

#include <unilib/array.h>
#include <unilib/sort.h>
#include <tes/program.h>

TES_STATIC void tdmerge( struct uni_vec a, ptri lo, ptri mid, ptri hi,
struct uni_vec b, PFN_uni_cmpdata cmp )
{
	ptri i, j, k;

	i = lo;
	j = mid;

	/* loop through the run */
	for(k = lo; k < hi; ++k)
	{
		void* cur_ai = ((u8*)a.data) + (a.elem_sz * i);
		void* cur_aj = ((u8*)a.data) + (a.elem_sz * j);
		void* cur_b = ((u8*)b.data) + (b.elem_sz * k);

		if(i < mid && (j >= hi || cmp( a.elem_sz, cur_ai, cur_aj )))
		{
			memcpy( cur_b, cur_ai, a.elem_sz );
			i++;
		}
		else
		{
			memcpy( cur_b, cur_aj, a.elem_sz );
			j++;
		}
	}
}

TES_STATIC void tdmerge2( struct uni_vec2 a, ptri lo, ptri mid, ptri hi,
struct uni_vec2 b, PFN_uni_cmpdata cmp )
{
	ptri i, j, k;

	i = lo;
	j = mid;

	for(k = 0; k < hi; ++k)
	{
		void* cur_ai = ((u8*)a.vec[0].data) + (a.vec[0].elem_sz * i);
		void* cur_aj = ((u8*)a.vec[0].data) + (a.vec[0].elem_sz * j);
		void* cur_b = ((u8*)b.vec[0].data) + (b.vec[0].elem_sz * k);
		void* cur_ai2 = ((u8*)a.vec[1].data) + (a.vec[1].elem_sz * i);
		void* cur_aj2 = ((u8*)a.vec[1].data) + (a.vec[1].elem_sz * j);
		void* cur_b2 = ((u8*)b.vec[1].data) + (b.vec[1].elem_sz * k);

		if(i < mid && (j >= hi || cmp( a.vec[0].elem_sz, cur_ai, cur_aj )))
		{
			memcpy( cur_b, cur_ai, a.vec[0].elem_sz );
			memcpy( cur_b2, cur_ai2, a.vec[1].elem_sz );
			i++;
		}
		else
		{
			memcpy( cur_b, cur_aj, a.vec[0].elem_sz );
			memcpy( cur_b2, cur_aj2, a.vec[1].elem_sz );
			j++;
		}
	}
}

TES_STATIC void td_splmerge( struct uni_vec b, ptri lo, ptri hi,
struct uni_vec a, PFN_uni_cmpdata cmp )
{
	ptri mid;

	/* if the array size is one, it is sorted */
	if(hi - lo == 1)
	{
		return;
	}

	/* split the run into halves by finding the mid-point */
	mid = (hi + lo) / 2;

	/* recursively sort each half */
	td_splmerge( a, lo, mid, b, cmp );
	td_splmerge( a, mid, hi, b, cmp );

	/* merge the runs back together */
	tdmerge( b, lo, mid, hi, a, cmp );
}

TES_STATIC void td_splmerge2( struct uni_vec2 b, ptri lo, ptri hi,
struct uni_vec2 a, PFN_uni_cmpdata cmp )
{
	ptri mid;

	if(hi - lo == 1)
	{
		return;
	}

	mid = (hi + lo) / 2;

	td_splmerge2( a, lo, mid, b, cmp );
	td_splmerge2( a, mid, hi, b, cmp );

	tdmerge2( b, lo, mid, hi, a, cmp );
}

struct uni_vec uni_mergesort( struct uni_vec a, PFN_uni_cmpdata cmp )
{
	struct uni_vec b;
	ptri n;

	b = uni_vec_dup( a );
	n = b.sz;

	td_splmerge( b, 0, n, a, cmp );

	return a;
}

struct uni_vec2 uni_omergesort2( struct uni_vec2 a, PFN_uni_cmpdata cmp )
{
	struct uni_vec2 b;
	ptri n;

	b.vec[0] = uni_vec_dup( a.vec[0] );
	b.vec[1] = uni_vec_dup( a.vec[1] );
	n = b.vec[0].sz;

	td_splmerge2( b, 0, n, a, cmp );

	return a;
}

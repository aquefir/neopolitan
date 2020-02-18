/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                           All rights reserved.                           *
\****************************************************************************/

#include <string.h>

#include <unilib/array.h>
#include <unilib/err.h>
#include <unilib/sort.h>
#include <tes/program.h>

TES_STATIC void merge( struct uni_vec a, ptri lo, ptri mid, ptri hi,
PFN_uni_cmpdata cmp )
{
	ptri i, j, k, l_sz, r_sz;
	struct uni_vec l, r, tmp;
	struct rangep l_rng, r_rng, range;

	/* create temporary vectors of left/right halves
	 * set up their ranges and sizes */
	l_rng.lo = lo;
	l_rng.hi = r_rng.lo = mid;
	r_rng.hi = hi;
	l_sz = mid - lo + 1;
	r_sz = hi - mid;

	/* slice out the left and right ranges */
	l = uni_vec_slice( a, l_rng );
	r = uni_vec_slice( a, r_rng );

	i = 0; /* init index of left subvector */
	j = 0; /* init index of right subvector */

	/* merge left and right together */
	for(k = lo; i < l_sz && j < r_sz; ++k)
	{
		void* left = uni_vec_getone( l, i );
		void* right = uni_vec_getone( r, j );

		range.lo = k;
		range.hi = k + 1;

		uni_print( "lo = %lu, hi = %lu", range.lo, range.hi );
		uni_print( "len = %lu", a.sz );

		if( cmp( a.elem_sz, left, right ) )
		{
			tmp = uni_vec_emplace( a, l, range );

			ASSERT_RET( tmp.data != NULL );

			a = tmp;
			i++;
		}
		else
		{
			tmp = uni_vec_emplace( a, r, range );

			ASSERT_RET( tmp.data != NULL );

			a = tmp;
			j++;
		}
	}

	/* copy the remaining elements of l, if any */
	while( i < l_sz )
	{
		range.lo = k;
		range.hi = k + 1;
		tmp = uni_vec_emplace( a, l, range );

		ASSERT_RET( tmp.data != NULL );

		a = tmp;
		i++;
		k++;
	}

	/* copy the remaining elements of r, if any */
	while( j < r_sz )
	{
		range.lo = k;
		range.hi = k + 1;
		tmp = uni_vec_emplace( a, r, range );

		ASSERT_RET( tmp.data != NULL );

		a = tmp;
		j++;
		k++;
	}
}

TES_STATIC void splitmerge( struct uni_vec vec, ptri lo, ptri hi,
PFN_uni_cmpdata cmp )
{
	if( lo < hi && hi - lo > 1 )
	{
		ptri mid = lo + (hi - lo) / 2;

		splitmerge( vec, lo, mid, cmp );
		splitmerge( vec, mid, hi, cmp );

		merge( vec, lo, mid, hi, cmp );
	}
}

struct uni_vec uni_mergesort( struct uni_vec vec, PFN_uni_cmpdata cmp )
{
	struct uni_vec dupvec;

	dupvec = uni_vec_dup( vec );

	splitmerge( dupvec, 0, dupvec.sz, cmp );

	return dupvec;
}

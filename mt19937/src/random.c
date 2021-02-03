/****************************************************************************\
 *                 Mersenne-Twister Algorithm 19937, 32-bit                 *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir.                      *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <mt19937/random.h>

#include <uni/err.h>
#include <uni/memory.h>
#include <uni/types/int.h>

#if defined( CFG_LINUX ) || defined( CFG_DARWIN )
#define _GNU_SOURCE 1
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#elif defined( CFG_GBA )
extern u32 _rand_seed[4];
#endif

#if defined( __VSCODE_INTELLISENSE__ )
/* Quiet IntelliSense. Not sure why these appear undefined */
#define CLOCK_REALTIME 0
#define _IONBF 2
#endif /* defined( __VSCODE_INTELLISENSE__ ) */

/* period parameters */
#define MATRIX_A ( 0x9908B0DFu )
#define UPPER_MASK ( 0x80000000u )
#define TEMPER_MASK_B ( 0x9D2C5680u )
#define TEMPER_MASK_C ( 0xEFC60000u )

enum
{
	N          = 624,
	M          = 397,
	LOWER_MASK = 0x7FFFFFFF
};

struct mt_prng
{
	u32 mt[N];
	u32 mti;
};

static void set_seed_arr( struct mt_prng *, u32 *, ptri );
static void set_seed( struct mt_prng *, u32 );

static u32 temper_shift_u( u32 y ) { return y >> 11; }

static u32 temper_shift_s( u32 y ) { return y << 7; }

static u32 temper_shift_t( u32 y ) { return y << 15; }

static u32 temper_shift_l( u32 y ) { return y >> 18; }

#if defined( CFG_LINUX ) || defined( CFG_DARWIN )
static u64 get_rtime( void )
{
	struct timespec tspec;

	clock_gettime( CLOCK_REALTIME, &tspec );

	return tspec.tv_nsec;
}
#endif

struct mt_prng * mt_prng_init( void )
{
	struct mt_prng * ret;
	u32 seed[4];

#if !defined( CFG_WINDOWS )
	ret = uni_alloc0( sizeof( struct mt_prng ) );
#else
	return NULL;
#endif

#if defined( CFG_LINUX ) || defined( CFG_DARWIN )
	{
		FILE * dev_urandom;
		int urandom_avail = 1;

		dev_urandom = fopen( "/dev/urandom", "rb" );

		if( dev_urandom )
		{
			int r;

			setvbuf( dev_urandom, NULL, _IONBF, 0 );

			r = fread( seed, sizeof( seed ), 1, dev_urandom );

			if( r != 1 )
			{
				urandom_avail = 0;
			}

			fclose( dev_urandom );
		}
		else
		{
			urandom_avail = 0;
		}

		if( !urandom_avail )
		{
			u64 now = get_rtime( );

			seed[0] = now / 1000000000;
			seed[1] = now % 1000000000;
			seed[2] = getpid( );
			seed[3] = getppid( );
		}
	}
#elif defined( CFG_WINDOWS )
#if( defined( _MSC_VER ) && _MSC_VER >= 1400 ) || \
	defined( __MINGW64_VERSION_MAJOR )
	{
		int i;

		for( i = 0; i < 4; ++i )
		{
			rand_s( &seed[i] );
		}
	}
#else
#warning Using insecure seed for random number generation because of missing rand_s() in Windows XP
	{
		u64 now = get_rtime( );

		seed[0] = now / 1000000000;
		seed[1] = now % 1000000000;
		seed[2] = getpid( );
		seed[3] = 0;
	}
#endif
#elif defined( CFG_GBA )
	uni_memcpy( seed, _rand_seed, sizeof( seed ) );
#endif

	set_seed_arr( ret, seed, 4 );

	return ret;
}

void mt_prng_fini( struct mt_prng * prng )
{
	if( !prng )
	{
		uni_die( );
	}

	uni_free( prng );
}

static void set_seed( struct mt_prng * prng, u32 seed )
{
	if( !prng )
	{
		uni_die( );
	}

	prng->mt[0] = seed;

	for( prng->mti = 1; prng->mti < N; ++prng->mti )
	{
		prng->mt[prng->mti] = 1812433253u *
				( prng->mt[prng->mti - 1] ^
					( prng->mt[prng->mti - 1] >> 30 ) ) +
			prng->mti;
	}
}

static void set_seed_arr( struct mt_prng * prng, u32 * seed, ptri seed_sz )
{
	u32 i, j, k;

	if( !prng || !seed || !seed_sz )
	{
		uni_die( );
	}

	set_seed( prng, 19650218u );

	for( i = j = 0, k = N > seed_sz ? N : seed_sz; k != 0; --k )
	{
		prng->mt[i] = ( prng->mt[i] ^
				      ( ( prng->mt[i - 1] ^
						( prng->mt[i - 1] >> 30 ) ) *
					      1664525u ) ) +
			seed[j] + j;
		prng->mt[i] &=
			0xFFFFFFFFu; /* for 64-bit and larger machines */

		i++;
		j++;

		if( i >= N )
		{
			prng->mt[0] = prng->mt[N - 1];
			i           = 1;
		}

		if( j >= seed_sz )
		{
			j = 0;
		}
	}

	for( k = N - 1; k != 0; --k )
	{
		prng->mt[i] = ( prng->mt[i] ^
				      ( ( prng->mt[i - 1] ^
						( prng->mt[i - 1] >> 30 ) ) *
					      1566083941u ) ) -
			i;
		prng->mt[i] &=
			0xFFFFFFFFu; /* for 64-bit and larger machines */

		if( i >= N )
		{
			prng->mt[0] = prng->mt[N - 1];
			i           = 1;
		}
	}

	prng->mt[0] = 0x80000000u;
}

#define DOUBLE_TRANSFORM ( 2.3283064365386962890625e-10 )

static const u32 mag01[2] = { 0, MATRIX_A };

s32 mt_random_s32( struct mt_prng * prng )
{
	u32 y;

	if( !prng )
	{
		uni_die( );
	}

	if( prng->mti >= N )
	{
		int kk;

		for( kk = 0; kk < N - M; ++kk )
		{
			y = ( prng->mt[kk] & UPPER_MASK ) |
				( prng->mt[kk + 1] & LOWER_MASK );
			prng->mt[kk] =
				prng->mt[kk + M] ^ ( y >> 1 ) ^ mag01[y & 1];
		}

		for( ; kk < N - 1; ++kk )
		{
			y = ( prng->mt[kk] & UPPER_MASK ) |
				( prng->mt[kk + 1] & LOWER_MASK );
			prng->mt[kk] = prng->mt[kk + ( M - N )] ^ ( y >> 1 ) ^
				mag01[y & 1];
		}

		y = ( prng->mt[N - 1] & UPPER_MASK ) |
			( prng->mt[0] & LOWER_MASK );
		prng->mt[N - 1] = prng->mt[M - 1] ^ ( y >> 1 ) ^ mag01[y & 1];

		prng->mti = 0;
	}

	y = prng->mt[prng->mti++];
	y ^= temper_shift_u( y );
	y ^= temper_shift_s( y ) & TEMPER_MASK_B;
	y ^= temper_shift_t( y ) & TEMPER_MASK_C;
	y ^= temper_shift_l( y );

	return (int)y;
}

u32 mt_random_u32( struct mt_prng * prng )
{
	return (u32)mt_random_s32( prng );
}

s64 mt_random_s64( struct mt_prng * prng )
{
	return (s64)mt_random_s32( prng ) |
		( (s64)mt_random_s32( prng ) << 32 );
}

u64 mt_random_u64( struct mt_prng * prng )
{
	return (u64)mt_random_s64( prng );
}

s32 mt_range_s32( struct mt_prng * prng, s32 begin, s32 end )
{
	if( begin < end || !prng )
	{
		uni_die( );
	}

	if( begin == end )
	{
		return begin;
	}

	{
		s32 ret;

		do
		{
			ret = mt_random_s32( prng );
		} while( ret < begin || ret > end );

		return ret;
	}
}

u32 mt_range_u32( struct mt_prng * prng, u32 begin, u32 end )
{
	if( begin < end || !prng )
	{
		uni_die( );
	}

	if( begin == end )
	{
		return begin;
	}

	{
		u32 ret;

		do
		{
			ret = mt_random_u32( prng );
		} while( ret < begin || ret > end );

		return ret;
	}
}

s64 mt_range_s64( struct mt_prng * prng, s64 begin, s64 end )
{
	if( begin < end || !prng )
	{
		uni_die( );
	}

	if( begin == end )
	{
		return begin;
	}

	{
		s64 ret;

		do
		{
			ret = mt_random_s64( prng );
		} while( ret < begin || ret > end );

		return ret;
	}
}

u64 mt_range_u64( struct mt_prng * prng, u64 begin, u64 end )
{
	if( begin < end || !prng )
	{
		uni_die( );
	}

	if( begin == end )
	{
		return begin;
	}

	{
		u64 ret;

		do
		{
			ret = mt_random_u64( prng );
		} while( ret < begin || ret > end );

		return ret;
	}
}

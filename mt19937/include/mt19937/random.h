/****************************************************************************\
 *                 Mersenne-Twister Algorithm 19937, 32-bit                 *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir.                      *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__MT19937_RANDOM_H
#define INC_API__MT19937_RANDOM_H

/* STATE MODULE */

#ifdef __cplusplus
extern "C" {
#endif

struct prng;

struct mt_prng* mt_prng_init( void );
void mt_prng_fini( struct mt_prng* );

int mt_range_s32( struct mt_prng*, int, int );
unsigned mt_range_u32( struct mt_prng*, unsigned, unsigned );
#if !defined( CFG_GBA )
long long mt_range_s64( struct mt_prng*, long long, long long );
unsigned long long mt_range_u64(
	struct mt_prng*, unsigned long long, unsigned long long );
#endif

int mt_random_s32( struct mt_prng* );
unsigned mt_random_u32( struct mt_prng* );
#if !defined( CFG_GBA )
long long mt_random_s64( struct mt_prng* );
unsigned long long mt_random_u64( struct mt_prng* );
#endif

#ifdef __cplusplus
}
#endif

#endif /* INC_API__MT19937_RANDOM_H */

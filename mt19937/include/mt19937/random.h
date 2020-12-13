/****************************************************************************\
 *                 Mersenne-Twister Algorithm 19937, 32-bit                 *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir.                      *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__MT19937_RANDOM_H
#define INC_API__MT19937_RANDOM_H

/* STATE MODULE */

#include <uni/types/int.h>

#ifdef __cplusplus
extern "C" {
#endif

struct prng;

struct mt_prng *mt_prng_init(void);
void mt_prng_fini(struct mt_prng *);

s32 mt_range_s32(struct mt_prng *, s32, s32);
u32 mt_range_u32(struct mt_prng *, u32, u32);
#if !defined(CFG_GBA)
s64 mt_range_s64(struct mt_prng *, s64, s64);
u64 mt_range_u64(struct mt_prng *, u64, u64);
#endif

s32 mt_random_s32(struct mt_prng *);
u32 mt_random_u32(struct mt_prng *);
#if !defined(CFG_GBA)
s64 mt_random_s64(struct mt_prng *);
u64 mt_random_u64(struct mt_prng *);
#endif

#ifdef __cplusplus
}
#endif

#endif /* INC_API__MT19937_RANDOM_H */

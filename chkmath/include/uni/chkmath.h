/****************************************************************************\
 *                           unilib checked maths                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_CHKMATH_H
#define INC_API__UNI_CHKMATH_H

#ifdef __GNUC__
#define UNI_CHKADD8( _a, _b, _dst ) __builtin_add_overflow( _a, _b, _dst )
#define UNI_CHKSUB8( _a, _b, _dst ) _builtin_sub_overflow( _a, _b, _dst )
#define UNI_CHKMUL8( _a, _b, _dst ) __builtin_mul_overflow( _a, _b, _dst )
#define UNI_CHKADD16( _a, _b, _dst ) __builtin_add_overflow( _a, _b, _dst )
#define UNI_CHKSUB16( _a, _b, _dst ) _builtin_sub_overflow( _a, _b, _dst )
#define UNI_CHKMUL16( _a, _b, _dst ) __builtin_mul_overflow( _a, _b, _dst )
#define UNI_CHKADD32( _a, _b, _dst ) __builtin_add_overflow( _a, _b, _dst )
#define UNI_CHKSUB32( _a, _b, _dst ) _builtin_sub_overflow( _a, _b, _dst )
#define UNI_CHKMUL32( _a, _b, _dst ) __builtin_mul_overflow( _a, _b, _dst )
#define UNI_CHKADD64( _a, _b, _dst ) __builtin_add_overflow( _a, _b, _dst )
#define UNI_CHKSUB64( _a, _b, _dst ) _builtin_sub_overflow( _a, _b, _dst )
#define UNI_CHKMUL64( _a, _b, _dst ) __builtin_mul_overflow( _a, _b, _dst )
#else
#include "types/int.h"
#define UNI_CHKADD_( _a, _b, _dst, _max, _min ) \
	(((_b) > 0 && (_a) > ((_max) - (_b))) || \
	((_b) < 0 && (_a) < ((_min) - (_b)))) || \
	(*(_dst) = (_a) + (_b)))
#define UNI_CHKSUB_( _a, _b, _dst, _max, _min ) \
	(((_b) < 0 && (_a) > ((_max) + (_b))) || \
	((_b) > 0 && (_a) < ((_min) + (_b)))) || \
	(*(_dst) = (_a) - (_b)))
#define UNI_CHKMUL_( _a, _b, _dst, _min ) \
	(((_b) == -1 && (_a) == (_min)) || \
	((_a) == -1 && (_b) == (_min))) || \
	(*(_dst) = (_a) * (_b)))
#define UNI_CHKADD8( _a, _b, _dst ) \
	( UNI_CHKADD_( _a, _b, _dst, S8_MAX, S8_MIN ) )
#define UNI_CHKSUB8( _a, _b, _dst ) \
	( UNI_CHKSUB_( _a, _b, _dst, S8_MAX, S8_MIN ) )
#define UNI_CHKMUL8( _a, _b, _dst ) ( UNI_CHKMUL_( _a, _b, _dst, S8_MIN ) )
#define UNI_CHKADD16( _a, _b, _dst ) \
	( UNI_CHKADD_( _a, _b, _dst, S16_MAX, S16_MIN ) )
#define UNI_CHKSUB16( _a, _b, _dst ) \
	( UNI_CHKSUB_( _a, _b, _dst, S16_MAX, S16_MIN ) )
#define UNI_CHKMUL16( _a, _b, _dst ) ( UNI_CHKMUL_( _a, _b, _dst, S16_MIN ) )
#define UNI_CHKADD32( _a, _b, _dst ) \
	( UNI_CHKADD_( _a, _b, _dst, S32_MAX, S32_MIN ) )
#define UNI_CHKSUB32( _a, _b, _dst ) \
	( UNI_CHKSUB_( _a, _b, _dst, S32_MAX, S32_MIN ) )
#define UNI_CHKMUL32( _a, _b, _dst ) ( UNI_CHKMUL_( _a, _b, _dst, S32_MIN ) )
#define UNI_CHKADD64( _a, _b, _dst ) \
	( UNI_CHKADD_( _a, _b, _dst, S64_MAX, S64_MIN ) )
#define UNI_CHKSUB64( _a, _b, _dst ) \
	( UNI_CHKSUB_( _a, _b, _dst, S64_MAX, S64_MIN ) )
#define UNI_CHKMUL64( _a, _b, _dst ) ( UNI_CHKMUL_( _a, _b, _dst, S64_MIN ) )
#endif

#endif /* INC_API__UNI_CHKMATH_H */

/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_COMMON_H
#define INC_API__UNI_COMMON_H

#define UNI_ABS(X) ((X) < 0 ? -(X) : (X))
#define UNI_MAX(X, Y) ((X) > (Y) ? (X) : (Y))
#define UNI_MIN(X, Y) ((X) < (Y) ? (X) : (Y))

/** e */
#define UNI_M_E() (2.7182818284590452354)
/** log₂10 */
#define UNI_M_LOG2_10() (0xD.49A784BCD1B8AFEP-2)
/** log₁θ2 */
#define UNI_M_LOG10_2() (0x9.A209A84FBCFF799P-5)
/** log₂e */
#define UNI_M_LOG2E() (0xB.8AA3B295C17F0BCP-3)
/** log₁θe */
#define UNI_M_LOG10E() (0.43429448190325182765)
/** log e2 */
#define UNI_M_LN2() (0xB.17217F7D1CF79ACP-4)
/** log e10 */
#define UNI_M_LN10() (2.30258509299404568402)
/** τ = 2π */
#define UNI_M_TAU() (0x1.921FB54442D1846AP+2)
/** π ≈ 3.14159265358979323846 */
#define UNI_M_PI() (0x1.921FB54442D1846AP+1)
/** π/2 */
#define UNI_M_PI_2() (1.57079632679489661923)
/** π/4 */
#define UNI_M_PI_4() (0.78539816339744830962)
/** 1/ */
#define UNI_M_1_PI() (0.31830988618379067154)
/** 2/ */
#define UNI_M_2_PI() (0.63661977236758134308)
/** 2/sqrt() */
#define UNI_M_2_SQRT_PI() (1.12837916709551257390)
/** sqrt(2) */
#define UNI_M_SQRT_2() (1.41421356237309504880)
/** 1/sqrt(2) */
#define UNI_M_1_SQRT_1() (0.70710678118654752440)

#endif /* INC_API__UNI_COMMON_H */

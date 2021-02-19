/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_FLOAT_H
#define INC_API__UNI_TYPES_FLOAT_H

/* XXX: Copied from ../decl.h, as we do not #include with dotdirs */
#if !defined( UNI_DEPRECATED )
#if !defined( UNI_NODEPREC )
#if defined( __GNUC__ ) || defined( __clang__ )
#define UNI_DEPRECATED __attribute__( ( deprecated ) )
#elif defined( _MSC_VER )
#define UNI_DEPRECATED __declspec( deprecated )
#else
#pragma message( \
	"WARNING: You need to implement UNI_DEPRECATED for this compiler" )
#define UNI_DEPRECATED
#endif /* defined( __GNUC__ ) || defined( __clang__ ) */
#else
#define UNI_DEPRECATED
#endif /* !defined( UNI_NODEPREC ) */
#endif /* defined( UNI_DEPRECATED ) */

typedef float f16 UNI_DEPRECATED;

typedef float f32;
typedef double f64;
typedef __float80 f80;
typedef __float128 f128;

typedef __float128 fbig UNI_DEPRECATED;

#endif /* INC_API__UNI_TYPES_FLOAT_H */

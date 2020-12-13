/****************************************************************************\
 *                         unilib base declarations                         *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
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

/* VS Code complains that __fp16 is undefined... */
#if defined( __clang__ ) && !defined( __VSCODE_INTELLISENSE__ )
#if( defined( __arm__ ) || defined( __aarch64__ ) )
typedef _Float16 f16;
#else
/* this is unsupported outside ARM because of ABIs */
typedef __fp16 f16;
#endif
#else
typedef float f16;
#endif

typedef float f32;
typedef double f64;
typedef long double f80 UNI_DEPRECATED;
typedef long double fbig;

#endif /* INC_API__UNI_TYPES_FLOAT_H */

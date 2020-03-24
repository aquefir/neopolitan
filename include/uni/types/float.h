/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_FLOAT_H
#define INC_API__UNI_TYPES_FLOAT_H

/* VS Code complains that __fp16 is undefined... */
#if defined( __clang__ ) && !defined( __VSCODE_INTELLISENSE__ )
#if ( defined( __arm__ ) || defined( __aarch64__ ) )
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
typedef long double f80;

#endif /* INC_API__UNI_TYPES_FLOAT_H */

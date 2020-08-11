/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_DECL_H
#define INC_API__UNI_DECL_H

#ifdef __cplusplus
#define UNI_C_API extern "C"
#else
#define UNI_C_API
#endif

#ifndef UNI_NODEPREC
#if defined( __GNUC__ ) || defined( __clang__ )
#define UNI_DEPRECATED __attribute__( ( deprecated ) )
#elif defined( _MSC_VER )
#define UNI_DEPRECATED __declspec( deprecated )
#else
#pragma message( \
	"WARNING: You need to implement UNI_DEPRECATED for this compiler" )
#define UNI_DEPRECATED
#endif
#else
#define UNI_DEPRECATED
#endif

#endif /* INC_API__UNI_DECL_H */

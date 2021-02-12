/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_DECL_H
#define INC_API__UNI_DECL_H

#ifdef __cplusplus
#define UNI_C_API extern "C"
#else
#define UNI_C_API
#endif

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
#endif
#else
#define UNI_DEPRECATED
#endif /* !defined( UNI_NODEPREC ) */
#endif /* !defined( UNI_DEPRECATED ) */

#define UNI_PACKED __attribute__( ( packed ) )

#define UNI_ALIGN( _x ) __attribute__( ( aligned( _x ) ) )

#endif /* INC_API__UNI_DECL_H */

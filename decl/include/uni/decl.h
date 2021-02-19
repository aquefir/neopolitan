/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_DECL_H
#define INC_API__UNI_DECL_H

#if !defined( UNI_C_API )
#if defined( __cplusplus )
#define UNI_C_API extern "C"
#else
#define UNI_C_API
#endif
#endif /* !defined( UNI_C_API ) */

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

#if !defined( UNI_PACKED )
#define UNI_PACKED __attribute__( ( packed ) )
#endif /* !defined( UNI_PACKED ) */

#if !defined( UNI_ALIGN )
#define UNI_ALIGN( _x ) __attribute__( ( aligned( _x ) ) )
#endif /* !defined( UNI_ALIGN ) */

#endif /* INC_API__UNI_DECL_H */

/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_MATHPRIM_H
#define INC_API__UNI_TYPES_MATHPRIM_H

#pragma message( \
	"DEPRECATED: Please #include <uni/types/bound.h>, <uni/types/point.h>, <uni/types/quant.h>, or <uni/types/range.h>. <uni/types/mathprim.h> is deprecated" )

#include "int.h"

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

#define UNI_SIZEOF_RANGE( R ) \
	( ( ( ( R ).lo > ( R ).hi ) ? ( ( R ).lo - ( ( R ).hi - 1 ) ) \
				    : ( ( ( R ).hi - 1 ) - ( R ).lo ) ) + \
		1 )

struct point2
{
	s32 x, y;
} UNI_DEPRECATED;

struct point2l
{
	s64 x, y;
} UNI_DEPRECATED;

struct point3
{
	s32 x, y, z;
} UNI_DEPRECATED;

struct point3l
{
	s64 x, y, z;
} UNI_DEPRECATED;

struct bound2
{
	u32 l, w;
} UNI_DEPRECATED;

struct bound2l
{
	u64 l, w;
} UNI_DEPRECATED;

struct bound3
{
	u32 l, w, h;
} UNI_DEPRECATED;

struct bound3l
{
	u64 l, w, h;
} UNI_DEPRECATED;

struct range
{
	s32 lo, hi;
} UNI_DEPRECATED;

struct rangel
{
	s64 lo, hi;
} UNI_DEPRECATED;

struct rangep
{
	ptri lo, hi;
} UNI_DEPRECATED;

#endif /* INC_API__UNI_TYPES_MATHPRIM_H */

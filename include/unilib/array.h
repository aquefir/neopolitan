/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNILIB_ARRAY_H
#define INC_API__UNILIB_ARRAY_H

#include <unilib/geometry.h>
#include <unilib/shand.h>

#define UNI_ARRAY( TYPE ) struct arr_##TYPE
#define UNI_ARRAYP( TYPE ) struct arrp_##TYPE
#define UNI_DECL_ARR( TYPE ) \
	UNI_ARRAY( TYPE ) \
	{ \
		TYPE* val; \
		ptri sz; \
	}; \
	struct _dummy
#define UNI_DECL_ARR_S( TYPE ) \
	UNI_ARRAY( TYPE ) \
	{ \
		struct TYPE* val; \
		ptri sz; \
	}; \
	struct _dummy
#define UNI_DECL_ARR_P( TYPE ) \
	UNI_ARRAY( TYPE ) \
	{ \
		TYPE** val; \
		ptri sz; \
	}; \
	struct _dummy
#define UNI_DECL_ARR_SP( TYPE ) \
	UNI_ARRAY( TYPE ) \
	{ \
		struct TYPE** val; \
		ptri sz; \
	}; \
	struct _dummy

#endif /* INC_API__UNILIB_ARRAY_H */

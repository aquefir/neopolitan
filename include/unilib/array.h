/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC__UNILIB_ARRAY_H
#define INC__UNILIB_ARRAY_H

#include "shand.h"

#define UNI_ARRAY( TYPE ) struct arr_##TYPE
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

#endif /* INC__UNILIB_ARRAY_H */

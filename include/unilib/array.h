/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC_API__UNILIB_ARRAY_H
#define INC_API__UNILIB_ARRAY_H

#include "geometry.h"
#include "shand.h"

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

struct uni_vec_header
{
	ptri sz, cap;
};

void* uni_vec_init( ptri, ptri );
void uni_vec_fini( void* );
void* uni_vec_reserve( void*, ptri, ptri );
void* uni_vec_emplace( void*, ptri, void*, ptri, struct rangep );
void* uni_vec_slackoff( void*, ptri );
void* uni_vec_slice( void*, ptri, struct rangep );
ptri uni_vec_readsz( void* );
ptri uni_vec_readcap( void* );

ptri uni_vec_getoffs( ptri );
void* uni_vec_getmemstart( void*, ptri );
struct uni_vec_header uni_vec_getheader( void*, ptri );
void uni_vec_setheader( void*, ptri, struct uni_vec_header );
void* uni_vec_init( ptri, ptri );
struct uni_vec_header uni_vec_header_addcap( struct uni_vec_header );
void* uni_vec_addcap( void*, ptri );

#endif /* INC_API__UNILIB_ARRAY_H */

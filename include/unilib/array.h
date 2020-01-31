/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                           All rights reserved.                           *
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

struct uni_vec
{
	ptri sz, cap, elem_sz;
	u8* data;
};

struct uni_vec uni_vec_init( ptri, ptri );
struct uni_vec uni_vec_init_ex( ptri, ptri, void* );
void uni_vec_fini( struct uni_vec );
struct uni_vec uni_vec_dup( struct uni_vec );
struct uni_vec uni_vec_reserve( struct uni_vec, ptri );
struct uni_vec uni_vec_emplace(
   struct uni_vec, struct uni_vec, struct rangep );
struct uni_vec uni_vec_slackoff( struct uni_vec );
struct uni_vec uni_vec_slice( struct uni_vec, struct rangep );

#endif /* INC_API__UNILIB_ARRAY_H */

/****************************************************************************\
 *                               unilib himem                               *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_MEMORY_H
#define INC_API__UNI_MEMORY_H

#include <uni/types/int.h>

void * uni_alloc( ptri );
void * uni_alloc0( ptri );
void * uni_realloc( void *, ptri );
void * uni_tryalloc( ptri );
void * uni_tryalloc0( ptri );
void * uni_tryrealloc( void *, ptri );
void uni_free( void * );

void uni_memset( void *, u8, ptri );
void uni_memcpy( void *, const void *, ptri );
int uni_memcmp( const void *, const void *, ptri );

#endif /* INC_API__UNI_MEMORY_H */

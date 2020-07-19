/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_MEMORY_H
#define INC_API__UNI_MEMORY_H

#include "types/int.h"

void* uni_alloc( ptri );
void* uni_alloc0( ptri );
void* uni_realloc( void*, ptri );
void* uni_tryalloc( ptri );
void* uni_tryalloc0( ptri );
void* uni_tryrealloc( void*, ptri );
void uni_free( void* );

#endif /* INC_API__UNI_MEMORY_H */

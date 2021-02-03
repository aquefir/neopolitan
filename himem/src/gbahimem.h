/****************************************************************************\
 *                               unilib himem                               *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC__UNI_GBAHIMEM_H
#define INC__UNI_GBAHIMEM_H

#ifdef CFG_GBA

#include <uni/types/int.h>

void initheap( void );
void * malloc( ptri );
void free( void * );

void memset( void *, u8, ptri );
void memcpy( void *, const void *, ptri );

ptri _memsize( void * );

#endif

#endif /* INC__UNI_GBAHIMEM_H */

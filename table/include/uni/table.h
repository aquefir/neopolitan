/****************************************************************************\
 *                              unilib tables.                              *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TABLE_H
#define INC_API__UNI_TABLE_H

#include <uni/types/int.h>

typedef u32 uni_tblkey_t;

struct uni_tbl;

uni_tblkey_t uni_new_tblkey( void );
int uni_chk_tblkey( struct uni_tbl*, uni_tblkey_t );

struct uni_tbl* uni_tbl_init( u32 );
void uni_tbl_fini( struct uni_tbl* );

void uni_tbl_ins( struct uni_tbl*, uni_tblkey_t, const void* );
void* uni_tbl_get( struct uni_tbl*, uni_tblkey_t );
void uni_tbl_del( struct uni_tbl*, uni_tblkey_t );

#endif /* INC_API__UNI_TABLE_H */

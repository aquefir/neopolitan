/****************************************************************************\
 *                            neopolitan tables.                            *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TABLE_H
#define INC_API__UNI_TABLE_H

#include <uni/types/int.h>

enum
{
	UNI_TBLKEY_INVALID = 0
};

/* valid range for uni_tblkey_t is currently 1..U32_MAX-1 */
typedef u32 uni_tblkey_t;

struct uni_tbl;

uni_tblkey_t uni_new_tblkey( void );
int uni_chk_tblkey( struct uni_tbl *, uni_tblkey_t );

struct uni_tbl * uni_tbl_init( u32 );
void uni_tbl_fini( struct uni_tbl * );

void uni_tbl_ins( struct uni_tbl *, uni_tblkey_t, const void * );
void * uni_tbl_get( struct uni_tbl *, uni_tblkey_t );
uni_tblkey_t uni_tbl_getfirstkey( struct uni_tbl *, const void * );
void uni_tbl_del( struct uni_tbl *, uni_tblkey_t );

#endif /* INC_API__UNI_TABLE_H */

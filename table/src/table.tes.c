/****************************************************************************\
 *                            neopolitan tables.                            *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <tes/battery.h>

#include "table.h"

#include <uni/types/int.h>

TES_OPEN( );

struct uni_tbl* tbl1;
struct uni_tbl* tbl2;
uni_tblkey_t key1, key2, key3;
u8* data1 = {0, 1, 2, 3};
u8* data2 = {0, 0, 0, 0};

tbl1 = uni_tbl_init( sizeof(s32) );
key1 = uni_new_tblkey( );
key2 = uni_new_tblkey( );
key3 = uni_new_tblkey( );

uni_tbl_ins( tbl1, key1, data1 );
data2 = uni_tbl_get( tbl1, key1 );

TES_ASSERT_EQ( data1[0], data2[0] );
TES_ASSERT_EQ( data1[1], data2[1] );
TES_ASSERT_EQ( data1[2], data2[2] );
TES_ASSERT_EQ( data1[3], data2[3] );

TES_CLOSE( );

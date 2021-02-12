/****************************************************************************\
 *                            neopolitan tables.                            *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC__UNI_TABLE_H
#define INC__UNI_TABLE_H

#include <uni/table.h>
#include <uni/types/int.h>

struct uni_tbl
{
	uni_tblkey_t * keys;
	void * data;
	ptri elemsz, rowct, rowcap;
};

#endif /* INC__UNI_TABLE_H */

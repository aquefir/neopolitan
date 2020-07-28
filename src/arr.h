/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC__UNI_ARR_H
#define INC__UNI_ARR_H

#include <uni/arr.h>

struct uni_arr
{
	u8* data;
	ptri sz, cap;
	u32 elemsz;
};

#endif /* INC__UNI_ARR_H */

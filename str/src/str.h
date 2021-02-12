/****************************************************************************\
 *                            neopolitan strings                            *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC__UNI_STR_H
#define INC__UNI_STR_H

#include <uni/str.h>

struct uni_str
{
	char * data;
	ptri sz, cap, cpct;
};

#endif /* INC__UNI_STR_H */

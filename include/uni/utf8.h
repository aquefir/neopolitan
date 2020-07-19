/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_UTF8_H
#define INC_API__UNI_UTF8_H

#include "types/int.h"
#include "types/options.h"

int uni_validu8( const char* );
UNI_OPTION( ptri ) uni_u8cpcount( const char* );

#endif /* INC_API__UNI_UTF8_H */

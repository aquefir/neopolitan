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

int uni_u8dec( char*, char32* );
int uni_u8enc( char32, char* );
u32 uni_u8decsz( char* );
u32 uni_u8encsz( char32 );

int uni_validu8( const char* );

#endif /* INC_API__UNI_UTF8_H */

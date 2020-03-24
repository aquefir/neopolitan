/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_FUTILS_H
#define INC_API__UNI_FUTILS_H

#include "decl.h"
#include "option.h"
#include "types/int.h"

UNI_DECL_OPT( ptri );

UNI_OPTION( ptri ) uni_filesz( const char* );
int uni_buffile( const char*, u8*, ptri );
int uni_loadfile( const char*, u8**, ptri* );

#endif /* INC_API__UNI_FUTILS_H */

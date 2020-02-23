/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNILIB_FUTILS_H
#define INC_API__UNILIB_FUTILS_H

#include "shand.h"

long uni_filesz( const char* );
int uni_buffile( const char*, u8*, ptri );
int uni_loadfile( const char*, u8**, ptri* );

#endif /* INC_API__UNILIB_FUTILS_H */

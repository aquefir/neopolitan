/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC__UNILIB_FUTILS_H
#define INC__UNILIB_FUTILS_H

#include "shand.h"

long uni_filesz( const char* );
int uni_buffile( const char*, u8*, ptri );
int uni_loadfile( const char*, u8**, ptri* );

#endif /* INC__UNILIB_FUTILS_H */

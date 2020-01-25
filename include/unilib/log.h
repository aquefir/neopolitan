/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC_API__UNILIB_LOG_H
#define INC_API__UNILIB_LOG_H

int uni_print( const char* fmt, ... );
int uni_pwarn( const char* fmt, ... );
int uni_perror( const char* fmt, ... );

#endif /* INC_API__UNILIB_LOG_H */

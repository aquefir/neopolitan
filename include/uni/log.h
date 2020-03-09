/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_LOG_H
#define INC_API__UNI_LOG_H

int uni_print( const char* fmt, ... );
int uni_pwarn( const char* fmt, ... );
int uni_perror( const char* fmt, ... );

#endif /* INC_API__UNI_LOG_H */
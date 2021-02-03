/****************************************************************************\
 *                              unilib logging                              *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_LOG_H
#define INC_API__UNI_LOG_H

int uni_print( const char *, ... );
int uni_pwarn( const char *, ... );
int uni_perror( const char *, ... );

#endif /* INC_API__UNI_LOG_H */

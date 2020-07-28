/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_STR_H
#define INC_API__UNI_STR_H

#include "types/mathprim.h"
#include "types/int.h"
#include "types/opt.h"

struct uni_str;

struct uni_str* uni_str_init( const char* );
struct uni_str* uni_str_initsz( ptri );
void uni_str_fini( struct uni_str* );
struct uni_str* uni_str_dup( struct uni_str* );
ptri uni_str_getsz( struct uni_str* );
char* uni_str_make( struct uni_str* );
char* uni_str_mkslice( struct uni_str*, struct rangep );

int uni_str_app( struct uni_str*, const char* );
int uni_str_appch( struct uni_str*, char );
int uni_str_appu8( struct uni_str*, char32 );
int uni_str_prep( struct uni_str*, const char* );
int uni_str_prepch( struct uni_str*, char );
int uni_str_prepu8( struct uni_str*, char32 );
int uni_str_ins( struct uni_str*, ptri, const char* );
int uni_str_insch( struct uni_str*, ptri, char );
int uni_str_insu8( struct uni_str*, ptri, char32 );
int uni_str_ovr( struct uni_str*, ptri, const char* );
int uni_str_ovrch( struct uni_str*, ptri, char );
int uni_str_ovru8( struct uni_str*, ptri, char32 );

ptri uni_strlen( const char* );
ptri uni_strlencp( const char* );
char* uni_strdup( const char* );
char* uni_strndup( const char*, ptri );
char** uni_strdupv( char** );
char* uni_strnfill( ptri, char );
char* uni_strstr( const char*, const char* );
char* uni_strrstr( const char*, const char* );
int uni_strequ( const char*, const char* );
int uni_strpre( const char*, const char* );
int uni_strsuf( const char*, const char* );
int uni_isascii( const char* );
int uni_isalnum( char );
int uni_isalpha( char );
int uni_isdigit( char );
int uni_isxdigit( char );
int uni_iscntrl( char );
int uni_isprint( char );
int uni_ispunct( char );
int uni_isspace( char );
int uni_isupper( char );
int uni_islower( char );
int uni_digitval( char );
int uni_xdigitval( char );
char* uni_strchomp( char*, char );
char* uni_strchug( char*, char );
char** uni_strsplit( const char*, const char*, int );
char* uni_strjoin( const char*, ... );
char* uni_strjoinv( const char*, char** );
ptri uni_strlenv( char** );
int uni_strequv( char**, char** );
void uni_strfreev( char** );

#endif /* INC_API__UNI_STR_H */

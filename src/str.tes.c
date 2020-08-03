/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <tes/battery.h>

#include "str.h"
#include <uni/memory.h>

TES_OPEN( );

{
	char** tmpsv;
	char* tmp2[] = { "aaa", "bc", "xzx", "134", NULL };
	char* tmp;

	TES_ASSERT_EQ( uni_strlen( "123456789" ), 9 );
	TES_ASSERT_EQ( uni_strlen( "hello world" ), 11 );
	TES_ASSERT_EQ( uni_strlen( "" ), 0 );
	TES_ASSERT_NE( uni_strlen( "aaa\0aaa" ), 7 );

	TES_ASSERT_EQ( uni_strlencp( "hello world" ), 11 );
	TES_ASSERT_EQ( uni_strlencp( "ol\303\241 mundo" ), 9 );
	TES_ASSERT_EQ(
	   uni_strlencp( "\344\275\240\345\245\275\344\270\226\347\225\214" ),
	   4 );
	TES_ASSERT_EQ( uni_strlencp( "\240\241" ), 0 );
	TES_ASSERT_EQ( uni_strlencp( "" ), 0 );

	tmpsv = uni_strsplit( "red blahh  cccc do", " ", -1 );
	TES_ASSERT_EQ( uni_strlenv( tmpsv ), 5 );
	TES_ASSERT_STR_EQ( tmpsv[0], "red" );
	TES_ASSERT_STR_EQ( tmpsv[1], "blahh" );
	TES_ASSERT_STR_EQ( tmpsv[2], "" );
	TES_ASSERT_STR_EQ( tmpsv[3], "cccc" );
	TES_ASSERT_STR_EQ( tmpsv[4], "do" );
	TES_ASSERT_EQ( tmpsv[5], NULL );
	uni_strfreev( tmpsv );

	tmpsv = uni_strsplit( "red blahh  cccc do", "  ", -1 );
	TES_ASSERT_EQ( uni_strlenv( tmpsv ), 2 );
	TES_ASSERT_STR_EQ( tmpsv[0], "red blahh" );
	TES_ASSERT_STR_EQ( tmpsv[1], "cccc do" );
	TES_ASSERT_EQ( tmpsv[2], NULL );
	uni_strfreev( tmpsv );

	tmpsv = uni_strsplit( "red blahh  cccc do", "blah", -1 );
	TES_ASSERT_EQ( uni_strlenv( tmpsv ), 2 );
	TES_ASSERT_STR_EQ( tmpsv[0], "red " );
	TES_ASSERT_STR_EQ( tmpsv[1], "h  cccc do" );
	TES_ASSERT_EQ( tmpsv[2], NULL );
	uni_strfreev( tmpsv );

	tmpsv = uni_strsplit( "red blahh  cccc do", "c", 2 );
	TES_ASSERT_EQ( uni_strlenv( tmpsv ), 2 );
	TES_ASSERT_STR_EQ( tmpsv[0], "red blahh  " );
	TES_ASSERT_STR_EQ( tmpsv[1], "ccc do" );
	TES_ASSERT_EQ( tmpsv[2], NULL );
	uni_strfreev( tmpsv );

	tmp = uni_strjoinv( ";;", tmp2 );
	TES_ASSERT_STR_EQ( tmp, "aaa;;bc;;xzx;;134" );
	uni_free( tmp );
	tmp = uni_strjoin( ";;", "aaa", "bc", "xzx", "134", NULL );
	TES_ASSERT_STR_EQ(
	   tmp,
	   "aaa;;bc;;xzx;;134" );
	uni_free( tmp );
}

TES_CLOSE( );

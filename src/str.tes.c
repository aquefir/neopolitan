/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <tes/battery.h>

#include "str.h"

TES_OPEN( );

TES_ASSERT_EQ( uni_strlen( "123456789" ), 9 );
TES_ASSERT_EQ( uni_strlen( "hello world" ), 11 );
TES_ASSERT_EQ( uni_strlen( "" ), 0 );
TES_ASSERT_EQ( uni_strlen( NULL ), 0 );
TES_ASSERT_NE( uni_strlen( "aaa\0aaa" ), 7 );

TES_ASSERT_EQ( uni_strlencp( "hello world" ), 11 );
TES_ASSERT_EQ( uni_strlencp( "ol\303\241 mundo" ), 9 );
TES_ASSERT_EQ( uni_strlencp( "\344\275\240\345\245\275\344\270\226\347\225\214" ), 4 );
TES_ASSERT_EQ( uni_strlencp( "\240\241" ), 0 );
TES_ASSERT_EQ( uni_strlencp( "" ), 0 );

TES_CLOSE( );

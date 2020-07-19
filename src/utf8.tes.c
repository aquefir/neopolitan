/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <tes/battery.h>

#include <uni/utf8.h>

TES_OPEN( );

/* length: 11 */
TES_ASSERT_TRUE( uni_validu8( "hello world" ) );
/* length: 9 */
TES_ASSERT_TRUE( uni_validu8( "ol\303\241 mundo" ) );
/* length: 4 */
TES_ASSERT_TRUE(
   uni_validu8( "\344\275\240\345\245\275\344\270\226\347\225\214" ) );
TES_ASSERT_FALSE( uni_validu8( NULL ) );
TES_ASSERT_FALSE( uni_validu8( "\240\241" ) );

TES_CLOSE( );

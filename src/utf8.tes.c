/****************************************************************************\
 *                           Aquefir One Library™                           *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <tes/battery.h>

#include <stdio.h>
#include <uni/utf8.h>

TES_OPEN( );

{
	char tempch[7]  = { 0, 0, 0, 0, 0, 0, 0 };
	char32 tempch32 = 0;

	/* length: 11 */
	TES_ASSERT_TRUE( uni_validu8( "hello world" ) );
	/* length: 9 */
	TES_ASSERT_TRUE( uni_validu8( "ol\303\241 mundo" ) );
	/* length: 4 */
	TES_ASSERT_TRUE(
	   uni_validu8( "\344\275\240\345\245\275\344\270\226\347\225\214" ) );
	TES_ASSERT_FALSE( uni_validu8( NULL ) );
	TES_ASSERT_FALSE( uni_validu8( "\240\241" ) );

	TES_ASSERT_EQ( uni_u8encsz( 0x3000 ), 3 );
	TES_ASSERT_EQ( uni_u8decsz( "\343\200\200" ), 3 );

	TES_ASSERT_FALSE( uni_u8dec( "\343\200\200", &tempch32 ) );
	printf( "0x%x\n", tempch32 );
	TES_ASSERT_EQ( tempch32, 0x3000 );

	TES_ASSERT_FALSE( uni_u8enc( 0x3000, tempch ) );
	TES_ASSERT_STR_EQ( "\343\200\200", tempch );
}

TES_CLOSE( );

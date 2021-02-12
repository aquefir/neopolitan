/****************************************************************************\
 *                            neopolitan strings                            *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <tes/battery.h>

#include <uni/utf8.h>

TES_OPEN( );

char tempch[7]  = { 0, 0, 0, 0, 0, 0, 0 };
char32 tempch32 = 0;
struct uni_u8pos u8pos;

/* length: 11 */
TES_ASSERT_TRUE( uni_validu8( "hello world" ) );
/* length: 9 */
TES_ASSERT_TRUE( uni_validu8( "ol\303\241 mundo" ) );
/* length: 4 */
TES_ASSERT_TRUE(
	uni_validu8( "\344\275\240\345\245\275\344\270\226\347\225\214" ) );
TES_ASSERT_FALSE( uni_validu8( "\240\241" ) );

TES_ASSERT_EQ( uni_u8encsz( 0x3000 ), 3 );
TES_ASSERT_EQ( uni_u8decsz( '\343' ), 3 );

TES_ASSERT_FALSE( uni_u8dec( "\343\200\200", &tempch32 ) );
TES_ASSERT_EQ( tempch32, 0x3000 );

TES_ASSERT_FALSE( uni_u8enc( 0x3000, tempch ) );
TES_ASSERT_STR_EQ( "\343\200\200", tempch );

TES_ASSERT_EQ(
	uni_u8cp2by( "\344\275\240\345\245\275\344\270\226\347\225\214", 1 ),
	3 );
u8pos = uni_u8by2cp( "\344\275\240\345\245\275\344\270\226\347\225\214", 3 );
TES_ASSERT_EQ( u8pos.pos, 1 );
TES_ASSERT_FALSE( u8pos.mid );
u8pos = uni_u8by2cp( "\344\275\240\345\245\275\344\270\226\347\225\214", 2 );
TES_ASSERT_EQ( u8pos.pos, 0 );
TES_ASSERT_TRUE( u8pos.mid );

TES_CLOSE( );

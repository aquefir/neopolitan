/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC__UNILIB_ERR_H
#define INC__UNILIB_ERR_H

enum /* err */
{
	UNI_ERR_SUCCESS = 0,
	UNI_ERR_NULLREF,
	UNI_ERR_SDL_FAIL,
	UNI_ERR_SDLIMG_FAIL,
	UNI_ERR_SDLTTF_FAIL,
	UNI_MAX_BUILTIN_ERR = 0x7FFF,
	UNI_MIN_CUSTOM_ERR = 0x8000,
	UNI_MAX_CUSTOM_ERR = 0xFFFE,
	UNI_MAX_ERR = 0xFFFF
};

#if defined( NDEBUG )
#define ASSERT( cnd ) ( (void)0 )
#else /* !defined(NDEBUG) */
#define ASSERT( cnd ) \
	( ( cnd ) ? (void)0 \
	          : uni_assert_fail( #cnd, __FILE__, __LINE__, __func__ ) )
#endif /* defined(NDEBUG) */

#define ASSERT_RET( cnd ) \
	do \
	{ \
		if( cnd ) \
		{ \
		} \
		else \
		{ \
			return; \
		} \
	} while( 0 )
#define ASSERT_RETNEG1( cnd ) \
	do \
	{ \
		if( cnd ) \
		{ \
		} \
		else \
		{ \
			return -1; \
		} \
	} while( 0 )
#define ASSERT_RETRET( r ) \
	do \
	{ \
		if( ( r ) == 0 ) \
		{ \
		} \
		else \
		{ \
			return ( r ); \
		} \
	} while( 0 )

#define IMPL_ASSERT_SDL( v, r, file, line ) \
	do \
	{ \
		if( v ) \
		{ \
		} \
		else \
		{ \
			fprintf( stderr, \
			  "SDL error @ %s L%u: %s\n", \
			  file, \
			  line, \
			  SDL_GetError( ) ); \
			if( r ) \
			{ \
				return r; \
			} \
		} \
	} while( 0 )

#define IMPL_ASSERT_TTF( v, r, file, line ) \
	do \
	{ \
		if( v ) \
		{ \
		} \
		else \
		{ \
			fprintf( stderr, \
			  "SDL_TTF error @ %s L%u: %s\n", \
			  file, \
			  line, \
			  TTF_GetError( ) ); \
			if( r ) \
			{ \
				return r; \
			} \
		} \
	} while( 0 )

#define IMPL_ASSERT_LODEPNG( v, r, file, line ) \
	do \
	{ \
		if( v ) \
		{ \
		} \
		else \
		{ \
			fprintf( stderr, \
			  "LodePNG error @ %s L%u: %s\n", \
			  file, \
			  line, \
			  lodepng_error_text( v ) ); \
			if( r ) \
			{ \
				return r; \
			} \
		} \
	} while( 0 )

#define ASSERT_SDL( v ) IMPL_ASSERT_SDL( v, 0, __FILE__, __LINE__ )
#define ASSERT_SDLRET( v ) IMPL_ASSERT_SDL( v, 1, __FILE__, __LINE__ )
#define ASSERT_LODEPNG( v ) IMPL_ASSERT_LODEPNG( v, 0, __FILE__, __LINE__ )
#define ASSERT_LODEPNGRET( v ) IMPL_ASSERT_LODEPNG( v, 1, __FILE__, __LINE__ )
#define ASSERT_TTF( v ) IMPL_ASSERT_TTF( v, 0, __FILE__, __LINE__ )
#define ASSERT_TTFRET( v ) IMPL_ASSERT_TTF( v, 1, __FILE__, __LINE__ )

extern void uni_assert_fail(
  const char*, const char*, unsigned, const char* );

#endif /* INC__UNILIB_ERR_H */

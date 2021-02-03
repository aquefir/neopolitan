/****************************************************************************\
 *                          unilib error handling.                          *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_ERR_H
#define INC_API__UNI_ERR_H

#include <uni/log.h>

enum /* err */
{
	UNI_ERR_SUCCESS = 0,
	UNI_ERR_NULLREF,
	UNI_MAX_BUILTIN_ERR = 0x7FFF,
	UNI_MIN_CUSTOM_ERR  = 0x8000,
	UNI_MAX_CUSTOM_ERR  = 0xFFFE,
	UNI_MAX_ERR         = 0xFFFF
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
			uni_perror( \
				"Assertion failed in file \"%s\" on line \"%u\", in " \
				"function \"%s\".\nExpression: %s", \
				__FILE__, \
				__LINE__, \
				__func__, \
				#cnd ); \
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
			uni_perror( \
				"Assertion failed in file \"%s\" on line \"%u\", in " \
				"function \"%s\".\nExpression: %s", \
				__FILE__, \
				__LINE__, \
				__func__, \
				#cnd ); \
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
			uni_perror( \
				"Assertion failed in file \"%s\" on line \"%u\", in " \
				"function \"%s\".\nExpression: %s", \
				__FILE__, \
				__LINE__, \
				__func__, \
				#r ); \
			return ( r ); \
		} \
	} while( 0 )
#define ASSERT_RETNUL( cnd ) \
	do \
	{ \
		if( cnd ) \
		{ \
		} \
		else \
		{ \
			uni_perror( \
				"Assertion failed in file \"%s\" on line \"%u\", in " \
				"function \"%s\".\nExpression: %s", \
				__FILE__, \
				__LINE__, \
				__func__, \
				#cnd ); \
			return NULL; \
		} \
	} while( 0 )
#define ASSERT_RETVAL( cnd, val ) \
	do \
	{ \
		if( cnd ) \
		{ \
		} \
		else \
		{ \
			uni_perror( \
				"Assertion failed in file \"%s\" on line \"%u\", in " \
				"function \"%s\".\nExpression: %s", \
				__FILE__, \
				__LINE__, \
				__func__, \
				#cnd ); \
			return val; \
		} \
	} while( 0 )

#define IMPL_ASSERT_NOP( x, o, file, line ) \
	do \
	{ \
		if( x ) \
		{ \
		} \
		else \
		{ \
			fprintf( stderr, \
				"!!! Assert failed @ %s L%u: %s\n", \
				file, \
				line, \
				#x ); \
			o.is = 0; \
			return ( o ); \
		} \
	} while( 0 )

#define ASSERT_NOP( x, o ) IMPL_ASSERT_NOP( ( x ), ( o ), __FILE__, __LINE__ )

extern void uni_die( void );
extern void uni_assert_fail(
	const char *, const char *, unsigned, const char * );

#endif /* INC_API__UNI_ERR_H */

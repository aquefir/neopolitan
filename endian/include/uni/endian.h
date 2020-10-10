/****************************************************************************\
 *                            unilib endianness.                            *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_ENDIAN_H
#define INC_API__UNI_ENDIAN_H

#define UNI_LILENDIAN 1
#define UNI_BIGENDIAN 2

#if defined( CFG_LILENDIAN )
#define UNI_ENDIANNESS UNI_LILENDIAN
#elif defined( CFG_BIGENDIAN )
#define UNI_ENDIANNESS UNI_BIGENDIAN
#else
#pragma message( \
	"WARNING: No endianness defined by synthconfig. Defaulting to little endian; this may not be desired!" )
#define UNI_ENDIANNESS UNI_LILENDIAN
#endif

#define UNI_SWAPENDIAN16( _val ) \
	( ( (_val)&0x00FFu ) << 8 ) | ( ( (_val)&0xFF00u ) >> 8 )
#define UNI_SWAPENDIAN32( _val ) \
	( ( (_val)&0x000000FFu ) << 24 ) | ( ( (_val)&0x0000FF00u ) << 8 ) | \
		( ( (_val)&0x00FF0000u ) >> 8 ) | \
		( ( (_val)&0xFF000000u ) >> 24 )
#define UNI_SWAPENDIAN64( _val ) \
	( ( (_val)&0x00000000000000FFu ) << 56 ) | \
		( ( (_val)&0x000000000000FF00u ) << 40 ) | \
		( ( (_val)&0x0000000000FF0000u ) << 24 ) | \
		( ( (_val)&0x00000000FF000000u ) << 8 ) | \
		( ( (_val)&0x000000FF00000000u ) >> 8 ) | \
		( ( (_val)&0x0000FF0000000000u ) >> 24 ) | \
		( ( (_val)&0x00FF000000000000u ) >> 40 ) | \
		( ( (_val)&0xFF00000000000000u ) >> 56 )

#if UNI_ENDIANNESS == UNI_LILENDIAN
#define UNI_HOST2NET16( _val ) ( UNI_SWAPENDIAN16( _val ) )
#define UNI_HOST2NET32( _val ) ( UNI_SWAPENDIAN32( _val ) )
#define UNI_HOST2NET64( _val ) ( UNI_SWAPENDIAN64( _val ) )
#define UNI_NET2HOST16( _val ) ( UNI_SWAPENDIAN16( _val ) )
#define UNI_NET2HOST32( _val ) ( UNI_SWAPENDIAN32( _val ) )
#define UNI_NET2HOST64( _val ) ( UNI_SWAPENDIAN64( _val ) )
#else /* UNI_ENDIANNESS == UNI_BIGENDIAN */
#define UNI_HOST2NET16( _val ) ( _val )
#define UNI_HOST2NET32( _val ) ( _val )
#define UNI_HOST2NET64( _val ) ( _val )
#define UNI_NET2HOST16( _val ) ( _val )
#define UNI_NET2HOST32( _val ) ( _val )
#define UNI_NET2HOST64( _val ) ( _val )
#endif /* UNI_ENDIANNESS */

#endif /* INC_API__UNI_ENDIAN_H */

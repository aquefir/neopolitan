/****************************************************************************\
 *                                  unilib                                  *
 *                                                                          *
 *                      Copyright © 2019-2020 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_VER_H
#define INC_API__UNI_VER_H

#define UNI_MAKEVER( _maj, _min, _pat ) \
	( ( ( (_maj)&0x3FF ) << 22 ) | ( ( (_min)&0x3FF ) << 12 ) | \
		( (_pat)&0xFFF ) )

#define UNI_GETVER_MAJOR( _ver ) ( ( ( _ver ) >> 22 ) & 0x3FF )
#define UNI_GETVER_MINOR( _ver ) ( ( ( _ver ) >> 12 ) & 0x3FF )
#define UNI_GETVER_PATCH( _ver ) ( (_ver)&0xFFF )

/* NOTE: patch version should always be set to 0 */
#define UNI_API_VER UNI_MAKEVER( 1, 0, 0 )

#endif /* INC_API__UNI_VER_H */

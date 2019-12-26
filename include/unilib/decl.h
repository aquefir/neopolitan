/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC__UNILIB_DECL_H
#define INC__UNILIB_DECL_H

#ifdef UNI_TEST
#define UNI_STATIC
#else
#define UNI_STATIC static
#endif

#ifdef __cplusplus
#define UNI_API extern "C"
#else
#define UNI_API extern
#endif

#endif /* INC__UNILIB_DECL_H */

/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                    Copyright © 2019-2020 ARQADIUM LLC                    *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC_API__UNILIB_DECL_H
#define INC_API__UNILIB_DECL_H

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

#endif /* INC_API__UNILIB_DECL_H */

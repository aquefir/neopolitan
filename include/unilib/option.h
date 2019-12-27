/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#ifndef INC__UNILIB_OPTION_H
#define INC__UNILIB_OPTION_H

#include "shand.h"

#define UNI_OPTION(TYPE) struct opt_##TYPE
#define UNI_OPTIONP(TYPE) struct optp_##TYPE
#define UNI_DECL_OPT(TYPE)                                                     \
  UNI_OPTION(TYPE) {                                                           \
    TYPE val;                                                                  \
    u8 is;                                                                     \
  };                                                                           \
  struct _dummy
#define UNI_DECL_OPT_S(TYPE)                                                   \
  UNI_OPTION(TYPE) {                                                           \
    struct TYPE val;                                                           \
    u8 is;                                                                     \
  };                                                                           \
  struct _dummy
#define UNI_DECL_OPT_P(TYPE)                                                   \
  UNI_OPTIONP(TYPE) {                                                          \
    TYPE *val;                                                                 \
    u8 is;                                                                     \
  };                                                                           \
  struct _dummy
#define UNI_DECL_OPT_SP(TYPE)                                                  \
  UNI_OPTIONP(TYPE) {                                                          \
    struct TYPE *val;                                                          \
    u8 is;                                                                     \
  };                                                                           \
  struct _dummy

#endif /* INC__UNILIB_OPTION_H */

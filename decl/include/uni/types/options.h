/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TYPES_OPTIONS_H
#define INC_API__UNI_TYPES_OPTIONS_H

#include "float.h"
#include "mathprim.h"
#include "int.h"
#include "opt.h"
#include "vec.h"

UNI_DECL_OPT( u8 );
UNI_DECL_OPT( u16 );
UNI_DECL_OPT( u32 );
UNI_DECL_OPT( u64 );
UNI_DECL_OPT( s8 );
UNI_DECL_OPT( s16 );
UNI_DECL_OPT( s32 );
UNI_DECL_OPT( s64 );
UNI_DECL_OPT( ptri );
UNI_DECL_OPT( offs );

UNI_DECL_OPT( f16 );
UNI_DECL_OPT( f32 );
UNI_DECL_OPT( f64 );
UNI_DECL_OPT( f80 );
UNI_DECL_OPT( f128 );
UNI_DECL_OPT( fbig );

UNI_DECL_OPT_S( point2 );
UNI_DECL_OPT_S( point2l );
UNI_DECL_OPT_S( point3 );
UNI_DECL_OPT_S( point3l );
UNI_DECL_OPT_S( bound2 );
UNI_DECL_OPT_S( bound2l );
UNI_DECL_OPT_S( bound3 );
UNI_DECL_OPT_S( bound3l );
UNI_DECL_OPT_S( range );
UNI_DECL_OPT_S( rangel );
UNI_DECL_OPT_S( rangep );

UNI_DECL_OPT( s8v2 );
UNI_DECL_OPT( s8v4 );
UNI_DECL_OPT( s8v8 );
UNI_DECL_OPT( s8v16 );
UNI_DECL_OPT( s8v32 );
UNI_DECL_OPT( s8v64 );
UNI_DECL_OPT( u8v2 );
UNI_DECL_OPT( u8v4 );
UNI_DECL_OPT( u8v8 );
UNI_DECL_OPT( u8v16 );
UNI_DECL_OPT( u8v32 );
UNI_DECL_OPT( u8v64 );

UNI_DECL_OPT( s16v2 );
UNI_DECL_OPT( s16v4 );
UNI_DECL_OPT( s16v8 );
UNI_DECL_OPT( s16v16 );
UNI_DECL_OPT( s16v32 );
UNI_DECL_OPT( u16v2 );
UNI_DECL_OPT( u16v4 );
UNI_DECL_OPT( u16v8 );
UNI_DECL_OPT( u16v16 );
UNI_DECL_OPT( u16v32 );

UNI_DECL_OPT( s32v2 );
UNI_DECL_OPT( s32v4 );
UNI_DECL_OPT( s32v8 );
UNI_DECL_OPT( s32v16 );
UNI_DECL_OPT( u32v2 );
UNI_DECL_OPT( u32v4 );
UNI_DECL_OPT( u32v8 );
UNI_DECL_OPT( u32v16 );

UNI_DECL_OPT( s64v2 );
UNI_DECL_OPT( s64v4 );
UNI_DECL_OPT( s64v8 );
UNI_DECL_OPT( u64v2 );
UNI_DECL_OPT( u64v4 );
UNI_DECL_OPT( u64v8 );

#endif /* INC_API__UNI_TYPES_OPTIONS_H */

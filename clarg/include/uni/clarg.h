/****************************************************************************\
 *                       neopolitan command line args                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir.                      *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_CLARG_H
#define INC_API__UNI_CLARG_H

#include <uni/types/int.h>
#include <uni/types/mathprim.h>

enum /* uni_clarg_tmpl_flags */
{
	UNI_CLARG_TMPL_FLAG_TAKESVAL,
	UNI_CLARG_TMPL_FLAG_VALREQD
};

enum /* uni_clarg_tmpl_masks */
{
	UNI_CLARG_TMPL_MASK_TAKESVAL = 1 << UNI_CLARG_TMPL_FLAG_TAKESVAL,
	UNI_CLARG_TMPL_MASK_VALREQD = 1 << UNI_CLARG_TMPL_FLAG_VALREQD
};

struct uni_clarg_tmpl;

struct uni_clarg_out;

struct uni_clarg_tmpl * uni_clarg_tmpl_init(
	const char *, const char *, const char *, struct range, const char * );
void uni_clarg_tmpl_fini( struct uni_clarg_tmpl * );

void uni_clarg_tmpl_add(
	struct uni_clarg_tmpl *, char, const char *, u32, const char * );

struct uni_clarg_out * uni_clarg_tmpl_parse(
	s32, char **, struct uni_clarg_tmpl * );

const char * uni_clarg_out_readc( struct uni_clarg_out *, char );
const char * uni_clarg_out_reads( struct uni_clarg_out *, const char * );
int uni_clarg_out_checkc( struct uni_clarg_out *, char );
int uni_clarg_out_checks( struct uni_clarg_out *, const char * );

const char ** uni_clarg_out_getpargs( struct uni_clarg_out * );
const char * uni_clarg_out_print( struct uni_clarg_out * );

#endif /* INC_API__UNI_CLARG_H */

/****************************************************************************\
 *                       neopolitan command line args                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir.                      *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC__UNI_CLARG_H
#define INC__UNI_CLARG_H

#include <uni/arr.h>
#include <uni/types/mathprim.h>

struct uni_clarg_tmpl
{
	/* these are all indexed together.
	 * push ‘\0’ if no short name is given, NULL if no long name is given.
	 */
	struct uni_arr * snames;
	struct uni_arr * lnames;
	struct uni_arr * opts;
	struct uni_arr * descs;
	const char * title;
	const char * briefdesc;
	struct range copy_year;
	const char * copy_name;
	const char * usage;
};

struct uni_clarg_outarg
{
	/* index in the uni_clarg_tmpl struct */
	u32 tmpl_i;
	const char * val;
};

struct uni_clarg_out
{
	struct uni_arr * outargs;
	const char ** pargs;
};

#endif /* INC__UNI_CLARG_H */

/****************************************************************************\
 *                        neopolitan error handling.                        *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#include <uni/err.h>

#include <uni/log.h>

static const char * const k_err_desc[UNI_MAX_ERR_DESC] = {
	"Success", "Out of memory" };

static const char * const k_err_mod[UNI_MAX_ERR_MOD] = { "Common",
	"Neopolitan array",
	"Neopolitan CLI args",
	"Neopolitan file utils",
	"Neopolitan HiMem",
	"Neopolitan logging",
	"Neopolitan MT19937",
	"Neopolitan strings",
	"Neopolitan tables",
	"Cosmopolitan",
	"Windows NT",
	"System V" };

static const char * const k_err_lvl[UNI_ERR_LVL_FATAL + 1] = { "Success",
	"Info",
	"Status",
	"Temporary",
	"Permanent",
	"Usage",
	"Reset",
	"Fatal" };

static const char * const k_err_eflags[UNI_ERR_EFLAG_RESERVED3 + 1] = {
	"Blocking",
	"Out of resources",
	"Not found",
	"Bad state",
	"Not supported",
	"Bad input",
	"Internal",
	"Reserved (1)",
	"Reserved (2)",
	"Reserved (3)" };

void uni_die( void ) { abort( ); }

void uni_assert_fail( const char * expr,
	const char * file,
	unsigned line,
	const char * func )
{
	__assert_fail( expr, file, line );
}

const char * uni_err_desc_tostr( u32 n )
{
	UNI_ASSERT( n < UNI_MAX_ERR_DESC );

	return k_err_desc[n];
}

const char * uni_err_mod_tostr( u32 n )
{
	UNI_ASSERT( n < UNI_MAX_ERR_MOD );

	return k_err_mod[n];
}

const char * uni_err_lvl_tostr( u32 n )
{
	UNI_ASSERT( n <= UNI_ERR_LVL_FATAL );

	return k_err_lvl[n];
}

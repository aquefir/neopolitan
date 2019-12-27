/****************************************************************************\
 *                           Universal C Library™                           *
 *                                                                          *
 *                      Copyright © 2019 ARQADIUM, LLC                      *
 *                           All rights reserved.                           *
\****************************************************************************/

#include <unilib/log.h>

#include <stdarg.h>
#include <stdio.h>

#include <unilib/err.h>

int uni_print(const char *fmt, ...) {
  va_list args;

  ASSERT_RETNEG1(fmt != NULL);
  fprintf(stdout, "\n[info] ");
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  fflush(stdout);

  return 0;
}

int uni_pwarn(const char *fmt, ...) {
  va_list args;

  ASSERT_RETNEG1(fmt != NULL);
  fprintf(stdout, "\n[warn] ");
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  fflush(stdout);

  return 0;
}

int uni_perror(const char *fmt, ...) {
  va_list args;

  ASSERT_RETNEG1(fmt != NULL);
  fprintf(stderr, "\n[fail] ");
  va_start(args, fmt);
  vprintf(fmt, args);
  va_end(args);
  fflush(stderr);

  return 0;
}

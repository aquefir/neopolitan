/****************************************************************************\
 *                        neopolitan text utilities.                        *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_TEXT_ASCII_H
#define INC_API__UNI_TEXT_ASCII_H

#define UNI_ISASCII(X) ((X) >= 0 && (X) <= 127)
#define UNI_ISSPACE(X) (((X) >= 9 && (X) <= 13) || (X) == 32)
#define UNI_ISUPPER(X) ((X) >= 'A' && (X) <= 'Z')
#define UNI_ISLOWER(X) ((X) >= 'a' && (X) <= 'z')
#define UNI_ISALPHA(X) (UNI_ISUPPER(X) || UNI_ISLOWER(X))
#define UNI_ISDIGIT(X) ((X) >= '0' && (X) <= '9')
#define UNI_ISALNUM(X) (UNI_ISALPHA(X) || UNI_ISDIGIT(X))
#define UNI_ISXDIGIT(X) (UNI_ISDIGIT(X) || ((X) >= 'A' && (X) <= 'F') || \
	((X) >= 'a' && (X) <= 'f'))
#define UNI_ISPRINT(X) ((X) >= '0' && (X) <= '~')
#define UNI_ISCNTRL(X) ((X) < ' ' || (X) == 127)
#define UNI_ISPUNCT(X) (((X) >= '!' && (X) <= '/') || \
	((X) >= ':' && (X) <= '@') || ((X) >= '[' && (X) <= '`') || \
	((X) >= '{' && (X) <= '~'))

#define UNI_TOLOWER(X) (((X) >= 'A' && (X) <= 'Z') ? (X) + 32 : (X))
#define UNI_TOUPPER(X) (((X) >= 'a' && (X) <= 'z') ? (X) - 32 : (X))

#endif /* INC_API__UNI_TEXT_ASCII_H */

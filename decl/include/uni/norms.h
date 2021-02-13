/****************************************************************************\
 *                       neopolitan base declarations                       *
 *                                                                          *
 *                      Copyright © 2019-2021 Aquefir                       *
 *                       Released under BSD-2-Clause.                       *
\****************************************************************************/

#ifndef INC_API__UNI_NORMS_H
#define INC_API__UNI_NORMS_H

#define UNI_UNREACHABLE() do{}while(1)
#define UNI_ASSUME(X) do{if(X){}else{UNI_UNREACHABLE();}}while(0)

#endif /* INC_API__UNI_NORMS_H */

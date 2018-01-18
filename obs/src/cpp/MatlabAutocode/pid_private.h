/*
 * PID_private.h
 *
 * Real-Time Workshop code generation for Simulink model "PID.mdl".
 *
 * Model Version                        : 1.15
 * Real-Time Workshop file version      : 5.0 $Date: 2004/01/16 06:53:50 $
 * Real-Time Workshop file generated on : Mon Jun 02 11:22:38 2003
 * TLC version                          : 5.0 (Jun 18 2002)
 * C source code generated on           : Mon Jun 02 11:22:38 2003
 */

#ifndef _RTW_HEADER_PID_private_h_
# define _RTW_HEADER_PID_private_h_

/* Private Macros used by the generated code to access rtModel */

#ifndef rtmIsMajorTimeStep
# define rtmIsMajorTimeStep(rtm) (1)
#endif

#ifndef rtmIsMinorTimeStep
# define rtmIsMinorTimeStep(rtm) (0)
#endif

#ifndef _RTW_COMMON_DEFINES_
# define _RTW_COMMON_DEFINES_

#ifndef TRUE
# define TRUE (1)
#endif
#ifndef FALSE
# define FALSE (0)
#endif
#endif                                  /* _RTW_COMMON_DEFINES_ */

#ifndef UCHAR_MAX
#include <limits.h>
#endif

#if ( UCHAR_MAX != (0xFFU) )
#error Fixed point code was generated for compiler with different sized uchars.
#endif

#if ( SCHAR_MAX != (0x7F) )
#error Fixed point code was generated for compiler with different sized chars.
#endif

#if ( USHRT_MAX != (0xFFFFU) )
#error Fixed point code was generated for compiler with different sized ushorts.
#endif

#if ( SHRT_MAX != (0x7FFF) )
#error Fixed point code was generated for compiler with different sized shorts.
#endif

#if ( UINT_MAX != (0xFFFFFFFFU) )
#error Fixed point code was generated for compiler with different sized uints.
#endif

#if ( INT_MAX != (0x7FFFFFFF) )
#error Fixed point code was generated for compiler with different sized ints.
#endif

#if ( ULONG_MAX != (0xFFFFFFFFU) )
#error Fixed point code was generated for compiler with different sized ulongs.
#endif

#if ( LONG_MAX != (0x7FFFFFFF) )
#error Fixed point code was generated for compiler with different sized longs.
#endif

#endif                                  /* _RTW_HEADER_PID_private_h_ */

/*
 * PID.h
 *
 * Real-Time Workshop code generation for Simulink model "PID.mdl".
 *
 * Model Version                        : 1.15
 * Real-Time Workshop file version      : 5.0 $Date: 2004/01/16 06:53:50 $
 * Real-Time Workshop file generated on : Mon Jun 02 11:22:38 2003
 * TLC version                          : 5.0 (Jun 18 2002)
 * C source code generated on           : Mon Jun 02 11:22:38 2003
 */

#ifndef _RTW_HEADER_PID_h_
# define _RTW_HEADER_PID_h_

#ifndef _PID_COMMON_INCLUDES_
# define _PID_COMMON_INCLUDES_
#include <math.h>
#include <float.h>
#include <string.h>

#include "tmwtypes.h"
#include "simstruc_types.h"
#include "rtlibsrc.h"

#endif                                  /* _PID_COMMON_INCLUDES_ */

#include "PID_types.h"

/* Intrinsic types */
#ifndef POINTER_T
# define POINTER_T
typedef void * pointer_T;
#endif

/* Block signals (auto storage) */
typedef struct _BlockIO_PID {
  real_T Discrete_Time_Int;             /* '<Root>/Discrete-Time Integrator' */
} BlockIO_PID;

/* Block states (auto storage) for system: '<Root>' */
typedef struct D_Work_PID_tag {
  real_T Discrete_Time_Int_DSTATE;      /* <Root>/Discrete-Time Integrator */
  real_T Discrete_Transfer_Fcn_DSTATE; /* <Root>/Discrete Transfer Fcn */
  boolean_T Discrete_Time_Int_SYSTEM_ENABLE; /* <Root>/Discrete-Time Integrator */
} D_Work_PID;

/* Real-time Model Data Structure */
struct _RT_MODEL_PID_Tag {
  const char *errorStatus;
};

/* Real-time Model object */
extern RT_MODEL_PID *PID_M;

/* Macros for accessing real-time model data structure  */

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm) (rtm)->errorStatus
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val) (rtm)->errorStatus = ((val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm) (0.0)
#endif

/* Backward compatibility for real-time model name change */
#define PID_rtO                         PID_M
#define PID_RT_OBJECT                   RT_MODEL_PID

/* Block signals (auto storage) */
extern BlockIO_PID PID_B;

/* Block states (auto storage) */
extern D_Work_PID PID_DWork;

/*
 * Exported Global Signals
 *
 * Note: Exported global signals are block signals with an exported global
 * storage class designation.  RTW declares the memory for these signals
 * and exports their symbols.
 *
 */

extern real_T Output;                   /* '<Root>/Sum' */
extern real_T Input;                    /* '<Root>/Input' */

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  RTW declares the memory for these
 * parameters and exports their symbols.
 *
 */

extern real_T Kd;                       /* Variable: Kd
                                         * '<Root>/D Gain'
                                         */
extern real_T Ki;                       /* Variable: Ki
                                         * '<Root>/I Gain'
                                         */
extern real_T Kp;                       /* Variable: Kp
                                         * '<Root>/P Gain'
                                         */

/* Model entry point functions */
extern void PID_initialize(boolean_T firstTime);
extern void PID_step(void);
extern void PID_terminate(void);

/* 
 * The generated code includes comments that allow you to trace directly 
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : PID
 */

#endif                                  /* _RTW_HEADER_PID_h_ */

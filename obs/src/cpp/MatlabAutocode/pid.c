#pragma warning(disable:4001)

#include "../GeneralInclude/CompilerSwitches.h"

#ifndef HAVE_SIMULINK

/*
 * We need this to keep Visual C++ happy: trying to compile an empty file is
 * a fatal error (sic).
 * On the other side, we have to comment out the whole file if we want to be able
 * to compile the Obs Framework on machines where Matlab + Simulink are not installed.
 */
void PID_dummy(void) {
    return;
}

#else

/*
 * Real-Time Workshop code generation for Simulink model "PID.mdl".
 *
 * Model Version                        : 1.15
 * Real-Time Workshop file version      : 5.0 $Date: 2004/01/16 06:53:50 $
 * Real-Time Workshop file generated on : Mon Jun 02 11:22:38 2003
 * TLC version                          : 5.0 (Jun 18 2002)
 * C source code generated on           : Mon Jun 02 11:22:38 2003
 */

#include "PID.h"
#include "PID_private.h"

/* Exported block signals */
real_T Output;                          /* <Root>/Sum */
real_T Input;                           /* <Root>/Input */

/* Exported block parameters */
real_T Kd = 1.0;
real_T Ki = 1.0;
real_T Kp = -1.0;

/* Block signals (auto storage) */
BlockIO_PID PID_B;

/* Block states (auto storage) */
D_Work_PID PID_DWork;

/* Real-time model */
RT_MODEL_PID PID_M_;
RT_MODEL_PID *PID_M = &PID_M_;

/* Model step function */
void PID_step(void)
{
  /* local block i/o variables */
  real_T rtb_I_Gain;
  real_T rtb_D_Gain;
  real_T rtb_Discrete_Transfer_Fcn;

  /* Gain: '<Root>/I Gain' incorporates:
   *   Inport: '<Root>/Input'
   *
   * Regarding '<Root>/I Gain':
   *   Gain value: Ki
   */
  rtb_I_Gain = Input * Ki;

  /* DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   *
   * Regarding '<Root>/Discrete-Time Integrator':
   *    Unlimited, w/o Saturation Port
   */
  /* system was just enabled */
  if ( PID_DWork.Discrete_Time_Int_SYSTEM_ENABLE) {
    PID_DWork.Discrete_Time_Int_SYSTEM_ENABLE = false;
    PID_B.Discrete_Time_Int = PID_DWork.Discrete_Time_Int_DSTATE;
  } else {
    PID_B.Discrete_Time_Int = PID_DWork.Discrete_Time_Int_DSTATE + 0.125 *
      rtb_I_Gain;
  }

  /* Gain: '<Root>/D Gain' incorporates:
   *   Inport: '<Root>/Input'
   *
   * Regarding '<Root>/D Gain':
   *   Gain value: Kd
   */
  rtb_D_Gain = Input * Kd;

  /* DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' */
  rtb_Discrete_Transfer_Fcn = 4.0*rtb_D_Gain;
  rtb_Discrete_Transfer_Fcn += -4.0*PID_DWork.Discrete_Transfer_Fcn_DSTATE;

  /* Sum: '<Root>/Sum' incorporates:
   *   Gain: '<Root>/P Gain'
   *   Inport: '<Root>/Input'
   *
   * Regarding '<Root>/P Gain':
   *   Gain value: Kp
   */
  Output = (Input * Kp) + PID_B.Discrete_Time_Int + rtb_Discrete_Transfer_Fcn;

  /* DiscreteIntegrator Block: <Root>/Discrete-Time Integrator */
  PID_DWork.Discrete_Time_Int_DSTATE = PID_B.Discrete_Time_Int + 0.125 *
    rtb_I_Gain;

  /* DiscreteTransferFcn Block: <Root>/Discrete Transfer Fcn */
  {
    PID_DWork.Discrete_Transfer_Fcn_DSTATE = rtb_D_Gain +
      (0.0)*PID_DWork.Discrete_Transfer_Fcn_DSTATE;
  }
}

/* Model initialize function */
void PID_initialize(boolean_T firstTime)
{
  if (firstTime) {
    /* registration code */
    rtmSetErrorStatus(PID_M, (const char_T *)0);

    /* block I/O */
    {
      void *b = (void *) &PID_B;
      {
        int_T i;

        b =&PID_B.Discrete_Time_Int;
        for (i = 0; i < 1; i++) {
          ((real_T*)b)[i] = 0.0;
        }
      }

      /* exported global signals */
      Output = 0.0;
    }

    /* data type work */
    (void)memset((char_T *) &PID_DWork, 0, sizeof(D_Work_PID));
    {
      int_T i;
      real_T *dwork_ptr = (real_T *) &PID_DWork.Discrete_Time_Int_DSTATE;

      for (i = 0; i < 2; i++) {
        dwork_ptr[i] = 0.0;
      }
    }

    /* external inputs */
    Input = 0.0;

    /* external outputs */
    Output = 0.0;
  }

  /* DiscreteIntegrator Block: <Root>/Discrete-Time Integrator */
  PID_DWork.Discrete_Time_Int_SYSTEM_ENABLE = true;
}

/* Model terminate function */
void PID_terminate(void)
{
  /* (no terminate code required) */
}

#endif

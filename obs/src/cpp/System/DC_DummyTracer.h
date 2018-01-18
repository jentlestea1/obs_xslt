//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTracer.h
//
// Version	1.0
// Date		30.09.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_DummyTracerH
#define DC_DummyTracerH

#include "Tracer.h"
#include "../GeneralInclude/BasicTypes.h"

/** Implementation of a dummy tracer that does not forward trace signals to
 * any external test set up. The dummy tracer can be useful either in a test
 * context or in an application where trace signals are not used. Note that
 * the <code>CC_RootObject</code> class requires a tracer component as one
 * of its plug-in components. This dummy tracer can be used where no physical
 * tracer component is available.
 * @see CC_RootObject
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyTracer : public Tracer {

  public:

    /**
     * Instantiate a dummy tracer object.
     * The enabled status of the tracer is set to "disabled". This minimizes the
     * overheads associated to the presence of the tracer in an application where
     * no trace signals need be generated.
     * @see Tracer#setEnabled
     */
    DC_DummyTracer(void);

  protected:

    /**
     * This is a dummy method that returns without taking any action
     * @see Tracer#sendRawTrace
     * @param traceItem the trace item to be sent to the test set-up
     */
    virtual void sendRawTrace(TD_TraceItem traceItem) const;

};

#endif

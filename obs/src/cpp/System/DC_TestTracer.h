//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_TestTracer.h
//
// Version	1.0
// Date		30.09.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_TestTracerH
#define DC_TestTracerH

#include <stdio.h>
#include "Tracer.h"
#include "../GeneralInclude/BasicTypes.h"

/** Implementation of a test tracer that sends the trace signals to a <i>log file</i>.
 * The dummy tracer can be useful during a test phase
 * when no external test set-up is available. The log file simulates the
 * external test set-up.
 * Depending on the value of a compiler switch, the log file is either a proper
 * file or the standard output. The latter case may allow use of this component
 * in an embedded environment where no file system is available.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_TestTracer : public Tracer {

  private:
   FILE* logFile;

  public:

    /**
     * Instantiate a test tracer object.
     * The log file is opened and a header is written to it. If the MS_HOST compiler
     * switch is defined, the log file is a proper file. Otherwise, it is the
     * standard output. In the former case, the name of the
     * log file is hardcoded as a <i>test constant</i>.
     * Note that responsibility for closing the log file rests with the user
     * (through method <code>closeLogFile</code>).
     * @see #closeLogFile
     * @see MS_HOST
     * @see TEST_TRACER_LOG_FILE
     * @see Tracer#setEnabledStatus
     */
    DC_TestTracer(void);

    /**
     * In a desktop environment, flush and close the log file. In an embedded
     * environment, no action is taken. This method should not be called more
     * than once. There is no way to open the log file after it has been closed.
     * @see #closeLogFile
     * @see TestCompilerSwitches#MS_HOST
     * @see TestConstants#TEST_TRACER_LOG_FILE
     * @see Tracer#setEnabled
     */
    void closeLogFile(void);

    /**
     * In a desktop environment, return the name of the log file. In an embedded
     * environment, return pNULL.
     * @see TEST_TRACER_LOG_FILE
     * @return the name of the log file or pNULL if the standard output is used as
     * log file
     */
    const char* const getLogFileName(void);

  protected:

    /**
     * Wwrite the trace item to the log file. The trace item is written using the
     * <code>printf</code> (embedded environment) or <code>fprintf</code> (desktop
     * environment) library function with the
     * <code>%x</code> format specifier. It is assumed that the <code>TD_TraceItem</code>
     * is compatible with this this specifier.
     * This method should be called only when the log file is still open.
     * @see #closeLogFile
     * @see Tracer#sendRawTrace
     * @param traceItem the trace item to be sent to the test set-up
     */
    virtual void sendRawTrace(TD_TraceItem traceItem) const;

};

#endif

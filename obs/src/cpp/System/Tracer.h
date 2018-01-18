//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// Tracer.h
//
// Version	1.0
// Date		30.09.02
// Author	A. Pasetti (P&P Software)

#ifndef TracerH
#define TracerH

#include "../Base/CC_RootObject.h"
#include "../GeneralInclude/BasicTypes.h"

/**
 * Base class from which all tracer classes are derived.
 * A tracer is a component that can send trace signals to an external test
 * set-up.
 * A trace signal is made up of one or more <i>trace items</i>. A trace item
 * is an elementary item of trace information that is sent to the test set-up
 * in one single operation.
 * <p>
 * Two types of trace signals are recognized: a <i>Synch Trace</i>, and a
 * <i>Packet Trace</i>. A synch trace consists of one single trace item. A
 * packet trace consists of a sequence of trace items.
 * <p>
 * The tracer can be enabled or disabled.
 * Calls to the services to send trace signals in a tracer that is disabled
 * have no effect.
 * <p>
 * This class is abstract because the implementation of the services that
 * send the trace signals
 * must be specified in the derived classes that implement concrete tracers.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class Tracer : public CC_RootObject {

  private:
     bool enabledStatus;

  public:

    /**
     * Instantiate a tracer object.
     * The enabled status of the tracer must be initialized to "enabled".
     */
    Tracer(void);

    /**
     * Send a Synch trace signal if the tracer is enabled.
     * If the tracer is disabled, the method call has no effect.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *    if ( isEnabled() )
     *    {  sendRawTrace(traceId);
     *    } </PRE>
     * The <CODE>sendRawTrace()</CODE> method is abstract and encapsulates
     * the implementation of the raw trace signal
     * sending.
     * Thus, this class enforces the management of the enabled status but
     * delegates implementation of
     * the sending mechanism to
     * derived classes implementing concrete tracers.
     * @param traceId the trace identifier
     */
    void sendSynchTrace(TD_TraceItem traceId) const;

    /**
     * Send a packet trace signal if the tracer is enabled.
     * If the tracer is disabled, the method call has no effect.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *    if ( isEnabled() )
     *    {  for (int i=0; i smaller than number of items in packet; i++)
     *       {  TD_TraceItem b = . . .  // form i-th item of the packet trace
     *          sendRawTrace(b);
     *       }
     *    } </PRE>
     * The <CODE>sendRawTrace()</CODE> method is abstract and encapsulates
     * the implementation of the raw trace signal
     * sending.
     * Thus, this class enforces the management of the enabled status and
     * transform the sequence of trace
     * data into elementary trace item to be sent to the test set-up in sequence
     * but delegates
     * implementation of the sending mechanism to
     * derived classes implementing concrete tracers.
     * @param n number of trace data elements
     * @param traceData array of trace data
     */
    void sendPacketTrace(unsigned int n, TD_TraceItem traceData[]) const;

    /**
     * Set the enable status of the tracer.
     * When the tracer is disabled, a call to its trace sending methods has
     * no effect.
     * @param isEnabled if true, then the tracer is enabled; if false, then
     * the profile is disabled
     */
    virtual void setEnabled(bool isEnabled);

    /**
     * Check the enable status of the tracer.
     * <p>
     * @return true if the profile is enabled, false otherwise
     */
    inline bool isEnabled(void) const;

  protected:

    /**
     * Encapsulate the mechanism to send one single tracer item over the trace
     * channel to the external test
     * set-up.
     * This method is called by methods <CODE>sendLedTrace()</CODE>,
     * <CODE>sendSynchTrace()</CODE> and
     * <CODE>sendPacketTrace()</CODE> in this same class.
     * User of a tracer object do not see method <CODE>sendRawTrace()</CODE>,
     * they only see the <CODE>sendXxxTrace()</CODE> methods.
     * <p>
     * @see #sendSynchTrace
     * @see #sendPacketTrace
     * @param rawItem the trace item to be sent to the test set-up
     */
    virtual void sendRawTrace(TD_TraceItem rawItem) const = 0;

};

#include "Tracer_inl.h"

#endif

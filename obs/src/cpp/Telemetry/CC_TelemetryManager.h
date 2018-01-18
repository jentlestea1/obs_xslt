//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_TelemetryManager.h
//
// Version	1.0
// Date		02.03.03
// Author	A. Pasetti (P&P Software)

#ifndef CC_TelemetryManagerH
#define CC_TelemetryManagerH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryModeManager.h"
#include "TelemetryStream.h"

/**
 * This class encapsulates a telemetry manager.
 * The telemetry manager is responsible for controlling the dispatch
 * of telemetry packets to the telemetry stream.
 * The telemetry packets can be dispatched to the telemetry stream in two
 * modes: <ul>
 * <li><i>Repetitive Mode</i>: the packets are provided by a <i>telemetry mode
 * manager</i>.
 * This dispatch mode is typically used for packets that must be written to the
 * telemetry stream on a regular basis.</li>
 * <li><i>Immediate Mode</i>: the packets are direclty loaded by an external
 * client and are dispatched to the telemetry stream at the next activation of
 * the telemetry manager. They are only dispatched once. This dispatch mode
 * is typically used for packets that must be dispatched on an occasional basis.</li>
 * </ul>
 * The telemetry mode manager is a plug-in component that must be configured
 * with the telemetry packets by an external client. The packets for immediate
 * dispatch are instead loaded in an internal queue (the <i>immediate
 * dispatch queue</i>) whose size must be defined as part of the configuration
 * procedure of the telemetry manager.
 * <p>
 * The telemetry packets are written to the telemetry stream when the telemetry
 * stream is <i>activated</i> (invocation of method <code>activate</code>). At this
 * time, the telemetry packets that were directly loaded since the last activation
 * and the telemetry packets that are provided by the telemetry mode manager are
 * first updated and then their written to the telemetry stream.
 * <p>
 * The telemetry manager contributes to the management of the "in use" status of
 * telemetry packets. More precisely, packets that are submitted for immediate
 * dispatch are marked as "no longer in use" after being processed.
 * <p>
 * The telemetry stream component
 * is a plug-in component of the telemetry manager.
 * <p>
 * The configuration procedure for a newly instantiated telemetry
 * manager is as follows: <ol>
 * <li>Load a telemetry stream component (method
 * <code>setTelemetryStream</code>).</li>
 * <li>Load a telemetry mode manager component (method
 * <code>setTelemetryModeManager</code>).</li>
 * <li>Set the size of the immediate dispatch queue (method
 * <code>setImmediateQueueSize</code>).</li>
 * </ol>
 * The above operations can be executed in any order.
 * <p>
 * @see TelemetryPacket
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup FunctionalityManagers
 * @ingroup Telemetry
 */
class CC_TelemetryManager : public CC_RootObject {

  private:
    TelemetryModeManager* pTmModeManager;
    TelemetryStream* pTmStream;
    int packetQueueSize;
    TelemetryPacket** pPacketQueue;

  public:

    /**
     * Instantiate a telemetry manager.
     * The class identifier is set and all internal data structures are initialized
     * to illegal values to signify that the component is not yet configured.
     */
    CC_TelemetryManager(void);

    /**
     * Load the telemetry mode manager.
     * @param pTmModeManager the telemetry mode manager
     */
    void setTelemetryModeManager(TelemetryModeManager* pTmModeManager);

    /**
     * Get the telemetry mode manager.
     * @return the telemetry mode manager
     */
    TelemetryModeManager* getTelemetryModeManager(void) const;

    /**
     * Load the telemetry stream component. The telemetry stream is reset
     * immediately after being loaded.
     * @param pTmStream the telemetry stream component
     */
    void setTelemetryStream(TelemetryStream* pTmStream);

    /**
     * Get the telemetry stream component.
     * @return the telemetry stream component
     */
    TelemetryStream* getTelemetryStream(void) const;

    /**
     * Set the size of the immediate dispatch queue.
     * This is an initialization method. It should only be called once.
     * The size of the immediate dispatch queue can be zero for the
     * case of applications where the immediate load service is disabled.
     * @param size the size of the immediate load packet queue
     */
    void setImmediateQueueSize(unsigned int size);

    /**
     * Return the size of the immediate dispatch queue.
     * @return the size of the immediate dispatch queue
     */
    unsigned int getImmediateQueueSize();

    /**
     * Return the i-th entry in the immediate dispatch queue.
     * The index i should lie in the range [0,N-1] where N is the size of the queue.
     * If the value of i is out of range, a null pointer is returned. A null
     * pointer will also be returned if the i-the entry in the queue is empty.
     * This method is only intended for testing purposes. It should not be used
     * in an operational context. This method may return null
     * @return the size of the immediate dispatch queue
     */
    TelemetryPacket* getImmediateQueueEntry(unsigned int i);

    /**
     * Return true if the size of the immediate dispatch queue is 
     * zero or if the immediate dispatch queue is full.
     * @return true if the immediate dispatch queue is full
     */
    bool isImmediateQueueFull();

    /**
     * Dispatch the telemetry packets to the telemetry stream.
     * Both the telemetry packets provided by the telemetry mode manager and those
     * loaded for immediate dispatch since the last activation are written to the
     * telemetry stream.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      for (all pTmPacket items in the immediate dispatch queue) {
     *          pTmPacket->update();
     *          if ( !pTmPacket->isValid() ) {
     *              createEventReport(EVT_TM_WORD_NOT_VALID);
     *              pTmPacket->setInUse(false);
     *          }
     *          if ( !pTmPacket fits in telemetry stream )
     *              createEventReport(EVT_TOO_MANY_TM_BYTES);
     *              pTmPacket->setInUse(false);
     *          }
     *          pTmStream->write(pTmPacket)
     *          pTmPacket->setInUse(false);
     *      }
     *      . . .   // clear immediate dispatch queue
     *      for (all pTmPacket items provided by the telemetry mode manager) {
     *          pTmPacket->update();
     *          if ( !pTmPacket->isValid() ) {
     *              createEventReport(EVT_TM_WORD_NOT_VALID);
     *          }
     *          if ( !pTmPacket fits in telemetry stream )
     *              createEventReport(EVT_TOO_MANY_TM_BYTES);
     *          }
     *          pTmStream->write(pTmPacket)
     *      }
     *      pTmStream->flush(); </PRE>
     * In the above pseudo-code, <code>pTmStream</code> is the telemetry stream where
     * the telemetry packets are written and <code>pTmFactory</code> is the telemetry
     * packet factory.
     * <p>
     * Each telemetry packet is first <i>updated</i> and its <i>validity</i> is then
     * checked. If validity is confirmed, it is checked that the packet fits in the telemetry stream.
     * If it does, it is written to the telemetry stream. In the case of telemetry packets
     * from the immediate dispatch queue, the packets are marked as "no longer in use"
     * after being processed.
     * If the telemetry packet is not valid or if it does not
     * fit in the telemetry channel, event reports are generated.
     * After all telemetry packets have been processed, the telemetry stream is flushed.
     * @see TD_EventType
     */
    virtual void activate(void);

    /**
     * Add the argument telemetry packet to the immediate dispatch queue.
     * The telemetry packet will be dispatched to the telemetry stream at the
     * next activation of the telemetry manager.
     * If the queue is already full, then an event report of type EVT_TM_QUEUE_FULL
     * is generated.
     * @param pTmPacket the telemetry packet component
     */
    void sendTelemetryPacket(TelemetryPacket* pTmPacket);

    /**
     * Check if the argument telemetry packet is currently in the immediate dispatch queue and,
     * if it is, remove it.
     * Failure to find the argument packet is treated as a nominal situation and is therefore
     * not recorded through an event report.
     * @param pTmPacket the telemetry packet component
     */
    void unloadTelemetryPacket(TelemetryPacket* pTmPacket);

    /**
     * Return the number of telemetry packets currently loaded in the immediate dispatch queue.
     * @return the number of telemetry packets currently loaded in the immediate dispatch queue
     */
    unsigned int getImmediateQueueLoaded();

    /**
     * Perform a class-specific configuration check on the telemetry
     * manager: verify that the telemetry stream and telemetry mode manager
     * have been loaded and that the size of the immediate load packet queue
     * has been set.
     * @return true if the telemetry manager is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif

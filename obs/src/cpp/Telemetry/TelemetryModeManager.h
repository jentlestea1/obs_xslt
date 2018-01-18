//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TelemetryModeManager.h
//
// Version	1.0
// Date		24.01.04
// Author	A. Pasetti (P&P Software)

#ifndef TelemetryModeManagerH
#define TelemetryModeManagerH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ModeManager.h"

/**
 * Base abstract class for mode manager components for the telemetry
 * manager.
 * A telemetry mode manager handles one single <i>strategy</i>, which
 * is represented by a set of <i>telemetry packet</i> components.
 * To every operational mode, the telemetry mode manager associates 
 * a set of telemetry packets. 
 * Client access the items in this set through four
 * <i>iteration methods</i>: <code>first</code>, <code>next</code>,
 * <code>isIterationFinished</code>, and <code>getIterationTelemetryPacket</code>.
 * <p>
 * This is an abstract class because it specifies neither the implementation
 * mechanism for the set of telemetry packets nor the mode update mechanism.
 * @see CC_TelemetryManager
 * @see TelemetryPacket
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup ModeManagement
 * @ingroup Telemetry
 */
class TelemetryModeManager : public ModeManager {

  public:

    /**
     * Instantiate a telemetry mode manager. This constructor returns
     * without taking any action.
     */
    TelemetryModeManager(void);

    /**
     * Iteration method to iterate through the items in the set of
     * telemetry packets applicable to the current operational mode. 
	 * This method should be used jointly with methods: <code>next</code>,
     * <code>isIterationFinished</code> and <code>getTelemetryPacket</code>. 
	 * Taken together,
     * these methods allow all the items in the currently applicable set 
	 * of telemetry packets to be scanned. 
	 * During an iteration cycle, an internal pointer, the <i>iteration
	 * pointer</i>, is made to scan over all the items in the currently applicable
	 * set of telemetry packets.
     * The item currently pointed at by the iteration counter can be retrieved
     * through method <code>getTelemetryPacket</code>.
     * Thus, a typical iteration cycle might be organized as follows: <PRE>
     *      for (first(); !isIterationFinished(); next()) {
     *          pItem = getTelemetryPacket();
     *          . . .    // process pItem
     *      }  </PRE>
     * @see #getIterationItem
     */
    virtual void first(void) = 0;

    /**
     * Iteration method to be used in conjunction with methods <code>first</code>
     * and <code>isIterationFinished</code>.
     * @see #first
     */
    virtual void next(void) = 0;

    /**
     * Iteration method to be used in conjunction with methods <code>first</code>
     * and <code>next</code>.
     * This method should only be used as part of an iteration cycle. The result
     * of calling it before ever calling <code>first</code>
     * is undefined.
     * @see #first
     * @return true if the end of the iteration has been reached, false otherwise
     */
    virtual bool isIterationFinished(void) = 0;

    /**
     * Return the telemetry packet pointed at by the iterator.
     * This method is a type-safe wrapper for method <code>getIteratorItem</code>
     * in the superclass.
     * @see #first
     * @return the telemetry packet pointed at by the iterator
     */
    virtual TelemetryPacket* getIterationTelemetryPacket(void) = 0;

};

#endif

//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SimpleTelemetryModeManager.h
//
// Version	1.0
// Date		02.03.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_SimpleTelemetryModeManagerH
#define DC_SimpleTelemetryModeManagerH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "TelemetryListModeManager.h"

/**
 * Telemetry list mode manager with a single and fixed mode.
 * This mode manager has a trivial implementation of the update
 * service that returns without taking any action. It is typically
 * used when the telemetry format is fixed.
 * <p>
 * An initialization sequence for this class consists of the following
 * steps (to be performed in the order given here): <ul>
 * <li>Set the length of the single telemetry packet list through method
 * <code>setListLength</code></li>
 * <li>Load the individual items through method <code>setListTelemetryPacket</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @see TelemetryPacket
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_SimpleTelemetryModeManager : public TelemetryListModeManager {

  public:

    /**
     * Instantiate a telemetry mode manager. This constructor sets the
     * class identifier and it configures its superclass to manage only
     * one single mode. A pseudo-code implementation is as follows: <PRE>
     *      setClassId(ID_SIMPLETELEMETRYMODEMANAGER);
     *      setNumberOfModes(1);
     *      setDefaultMode(0);  </PRE>
     */
    DC_SimpleTelemetryModeManager(void);

    /**
     * Since this is a fixed-mode mode manager, this method returns without
     * taking any action.
     */
    virtual void update(void);
};

#endif

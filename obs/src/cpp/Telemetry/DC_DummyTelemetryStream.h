//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTelemetryStream.h
//
// Version	1.0
// Date		21.11.03
// Author	R. Totaro

#ifndef DC_DummyTelemetryStreamH
#define DC_DummyTelemetryStreamH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryStream.h"

/**
 * Dummy implementation of the <code>TelemetryStream</code> interface
 * useful for testing purposes.
 * This class uses the default implementations provided by the super class and provides
 * a dummy implementation of its only pure virtual method <code>write</code>.
 * @author Roberto Totaro
 * @version 1.0
 */
class DC_DummyTelemetryStream : public TelemetryStream {

  public:
    /**
     * Instantiate a telemetry stream component. The class identifier is set.
     */
    DC_DummyTelemetryStream(void);

    /**
     * Write the content of the telemetry packet to the telemetry stream. This
     * implementation does nothing.
     * @param tmItem the telemetry packet to be written to the telemetry stream
     */
    virtual void write(TelemetryPacket *tmItem);
};

#endif

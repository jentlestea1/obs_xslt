//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_FileTelemetryStream.h
//
// Version	1.0
// Date		02.03.03 (Version 1.1)
// Author	A. Pasetti (P&P Software)

#ifndef DC_FileTelemetryStreamH
#define DC_FileTelemetryStreamH

#include <stdio.h>

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryStream.h"

/**
 * File-oriented telemetry stream. The data written to the telemetry
 * stream are written to an output file. The output file can be either
 * a named file or the standard output. This will allow usage both
 * in a desktop environment and in many embedded environments. This
 * type of telemetry stream is primarily intended for testing purposes.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_FileTelemetryStream : public TelemetryStream {

  private:
    FILE* out;

  public:

    /**
     * Instantiate a file telemetry stream component. This constructor sets the
     * the class identifier.
     */
    DC_FileTelemetryStream(void);

    /**
     * Set the output stream to which the telemetry data are written and
     * write a header to the output stream. If the
     * argument is <code>pNULL</code>, then the output stream is assumed to be the standard
     * ouptut.
     * @param outputStream the ouptut file or <code>pNULL</code> if the telemetry data must be
     * written to the standard output
     */
    void setOutputStream(FILE* outputStream);

    /**
     * Return the output stream to which the telemetry data are written.
     * The return value can be <code>pNULL</code> to signify that the output stream is
     * the standard ouptut.
     * @return the ouptut file or <code>pNULL</code> if the telemetry data must be
     * written to the standard output
     */
    FILE* getOutputStream(void);

    /**
     * Write an "end-of-TM-frame" message to the output stream and flush it.
     * The "end-of-TM-frame" message consists of a single straight line. If the output
     * stream is the standard output, no action is taken.
     */
    virtual void flush(void);

    /**
     * Write the full content of the telemetry packet to the output stream.
     * First, the value of all the attributes (the telemetry time tag, the
     * telemetry type and subtype, the telemetry destination) are written.
     * Then the telemetry packet data are written as a sequence of bytes.
     * @param tmItem the telemetry packet to be written to the output
     * stream.
     */
    virtual void write(TelemetryPacket* tmItem);

};

#endif

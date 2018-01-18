//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// Tracer.cpp
//
// Version	1.0
// Date		30.09.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "Tracer.h"

Tracer::Tracer(void) {
   enabledStatus = ENABLED;
}

void Tracer::sendSynchTrace(TD_TraceItem traceId) const {
   if ( isEnabled() )
       sendRawTrace(traceId);
}

void Tracer::sendPacketTrace(unsigned int n, TD_TraceItem traceData[]) const {
    if ( isEnabled() ) {
        for (unsigned int i=0; i<n; i++)
            sendRawTrace(traceData[i]);
    }
}

void Tracer::setEnabled(bool isEnabled) {
   enabledStatus = isEnabled;
}

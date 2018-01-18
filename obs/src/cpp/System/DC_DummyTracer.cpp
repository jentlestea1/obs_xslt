//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTracer.cpp
//
// Version	1.0
// Date		30.09.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyTracer.h"

DC_DummyTracer::DC_DummyTracer(void) {
   Tracer::setEnabled(DISABLED);
   setClassId(ID_DUMMYTRACER);
}

void DC_DummyTracer::sendRawTrace(TD_TraceItem rawItem) const {
   return;
}


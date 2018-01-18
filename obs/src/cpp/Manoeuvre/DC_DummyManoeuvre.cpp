//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyManoeuvre.cpp
//
// Version	1.0
// Date		10.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_DummyManoeuvre.h"

DC_DummyManoeuvre::DC_DummyManoeuvre(void) {
    setClassId(ID_DUMMYMANOEUVRE);
}

void DC_DummyManoeuvre::doInternalContinue(void) {
    assert(isInUse() && isExecuting());
}

bool DC_DummyManoeuvre::isFinished(void) {
    assert(isInUse() && isExecuting());
    return MAN_HAS_TERMINATED;
}

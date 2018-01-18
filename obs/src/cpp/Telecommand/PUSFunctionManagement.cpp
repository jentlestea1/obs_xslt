//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSFunctionManagement.cpp
//
// Version	1.0
// Date		4.01.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "PUSFunctionManagement.h"

PUSFunctionManagement::PUSFunctionManagement(void) {
    setType(PUS_TYPE_TC_FNC);
    setSubType(PUS_ST_TC_FNC_PER);
}


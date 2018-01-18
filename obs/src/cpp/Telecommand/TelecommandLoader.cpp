//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TelecommandLoader.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"
#include "TelecommandLoader.h"

TelecommandLoader::TelecommandLoader(void) {
    pTelecommandManager=pNULL;
}

bool TelecommandLoader::isObjectConfigured(void) {
   return (CC_RootObject::isObjectConfigured() && pTelecommandManager!=pNULL);
}

//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DataItem16TmWord.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_RawDataItem.h"
#include "DC_DataItem16TmWord.h"

DC_DataItem16TmWord::DC_DataItem16TmWord(void) {
    setNumberOfBytes(2);
    setUnsignedShort(0,0);
    pDataItem = pNULL;
    setClassId(ID_DATAITEM16TMWORD);
}

void DC_DataItem16TmWord::update(void) {
    assert( pDataItem != pNULL );
    setUnsignedShort(0,pDataItem->getUnsignedShort());
}

void DC_DataItem16TmWord::setDataItem(DC_RawDataItem* pDataItem) {
    this->pDataItem = pDataItem;
}

bool DC_DataItem16TmWord::isObjectConfigured(void) {
   return (StructuredTelemetryPacket::isObjectConfigured() && pDataItem!=pNULL);
}

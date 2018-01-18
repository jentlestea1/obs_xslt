//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicDataPool.cpp
//
// Version	1.0
// Date		10.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyDataPool.h"

DC_DummyDataPool::DC_DummyDataPool(void) {
    setClassId(ID_DUMMYDATAPOOL);
    setDataPoolSize(sizeof(TD_Integer));
    setValue(0,(TD_Integer)0);
}


//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyDatabase.cpp
//
// Version	1.0
// Date		12.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_DummyDatabase.h"

DC_DummyDatabase::DC_DummyDatabase(void) {
   setClassId(ID_DUMMYDATABASE);
   setTableLength(1);
   setOperationalTable(&table);
   setDefaultTable(&table);
   reset();
   setParameter(0,(char)0);
}

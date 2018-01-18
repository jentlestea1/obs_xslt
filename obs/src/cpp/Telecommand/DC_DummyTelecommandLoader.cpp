//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTelecommandLoader.cpp
//
// Version	1.0
// Date		4.12.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "CC_TelecommandManager.h"
#include "DC_DummyTelecommandLoader.h"

// The constant N_SAMPLE_TC was initially defined in the header file
// as follows:
//   static int const N_SAMPLE_TC = 3;
// This however gives an error with some compiler settings and was
// therefore replaced with an initialization performed in the
// constructor

DC_DummyTelecommandLoader::DC_DummyTelecommandLoader(void) {
    N_SAMPLE_TC = 3;
    pSampleTelecommand = new Telecommand*[N_SAMPLE_TC];
    for (unsigned int i=0; i<N_SAMPLE_TC; i++)
        pSampleTelecommand[i] = pNULL;
    allocationCounter = 0;
    setClassId(ID_DUMMYTELECOMMANDLOADER);
}

void DC_DummyTelecommandLoader::activate(void) {
    assert( isObjectConfigured() );
    int i = allocationCounter % N_SAMPLE_TC;
    allocationCounter++;
    getTelecommandManager()->load(pSampleTelecommand[i]);
}

void DC_DummyTelecommandLoader::release(Telecommand* pTc) {
    assert( isObjectConfigured() );
    assert( allocationCounter>0 );
    allocationCounter--;
}

void DC_DummyTelecommandLoader::setSampleTelecommand(
                unsigned int i, Telecommand* pSampleTc) {
    assert( i<N_SAMPLE_TC );
    pSampleTelecommand[i] = pSampleTc;
}

unsigned int DC_DummyTelecommandLoader::getAllocationCounter(void) {
    assert( isObjectConfigured() );
    return allocationCounter;
}

bool DC_DummyTelecommandLoader::isObjectConfigured(void) {
   // Check configuration of super object
   if ( !TelecommandLoader::isObjectConfigured() )
       return NOT_CONFIGURED;

    for (unsigned int i=0; i<N_SAMPLE_TC; i++)
        if ( pSampleTelecommand[i] == pNULL )
            return NOT_CONFIGURED;

   return CONFIGURED;
}

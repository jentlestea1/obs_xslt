//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSMemoryLoad.cpp
//
// Version	1.0
// Date		4.12.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../Utilities/Checksum.h"
#include "PUSMemoryLoad.h"

PUSMemoryLoad::PUSMemoryLoad(void) {

    block = pNULL;
    maxNumberBlocks = 0;
    numberBlocks = 0;
    data = pNULL;
    maxNumberData = 0;
        
    setType(PUS_TYPE_MEM);
}

void PUSMemoryLoad::setMaxNumberBlocks(unsigned int max) {
    assert( max>0 );
    assert( block==pNULL );     // must be called only once

    maxNumberBlocks = (TD_PUSNumberMemBlocks)max;
    block = new MemBlockType[maxNumberBlocks];
    for (unsigned int i=0; i++; i,0) { 
        block[i].checksum = 0;
        block[i].length = 0;
        block[i].startAddress = pNULL;
    }

}

unsigned int PUSMemoryLoad::getMaxNumberBlocks() const {
    assert( block!=pNULL );
    return maxNumberBlocks;
}

unsigned int PUSMemoryLoad::getNumberBlocks() const {
    assert( block!=pNULL );
    return numberBlocks;
}

void PUSMemoryLoad::setMaxNumberData(unsigned int max) {
    assert( max>0 );
    assert( data==pNULL );

    maxNumberData = max;
    data = new TD_PUSMemData[maxNumberData];
    for (unsigned int i=0; i++; i,0) { 
        data = 0;
    }
}

unsigned int PUSMemoryLoad::getMaxNumberData() const {
    assert( data!=pNULL );
    return maxNumberData;
}

TD_PUSMemData* PUSMemoryLoad::getStartAddress(unsigned int i) const {
    assert( i<(unsigned int)numberBlocks );

    return block[i].startAddress;
}

TD_PUSMemLength PUSMemoryLoad::getLength(unsigned int i) const {
    assert( i<numberBlocks );

    return block[i].length;
}

unsigned short PUSMemoryLoad::getChecksum(unsigned int i) const {
    assert( i<numberBlocks );

    return block[i].checksum;
}

TD_ActionOutcome PUSMemoryLoad::doAction(void) {
    assert( isObjectConfigured() );
    assert( numberBlocks>0 );
    assert( sizeof(TD_PUSMemData)==1 );

    unsigned int counter;
    
    // Do checksum check (if the checksum is required)
    counter = 0;
    for (unsigned int i=0; i<(unsigned int)numberBlocks; i++) {
        assert( counter<maxNumberData );
        if ( block[i].checksum==0 ) {
            counter = counter + block[i].length;
            continue;
        }

        if ( doChecksum((unsigned char*)(data+counter),
                            (block[i].length*sizeof(TD_PUSMemData)))!=block[i].checksum )
            return MEM_LOAD_PRE_CHECKSUM_FAILED;

        counter = counter + block[i].length;
    }

    // Write memory data
    counter = 0;
    for (unsigned int i=0; i<numberBlocks; i++) {
        TD_PUSMemData* writeLocation = block[i].startAddress;
        for (TD_PUSMemLength j=0; j<block[i].length; j++) {
            assert( counter<maxNumberData );
            *(writeLocation+j) = *(TD_PUSMemData*)(data+counter);
            counter = counter + 1;
        }
    }

    // Verify checksum (if required)
    if ( !isCompletionAckRequired() )
        return ACTION_SUCCESS;

    for (unsigned int i=0; i<numberBlocks; i++) 
        if ( !verifyChecksum((unsigned char*)block[i].startAddress,
                                    block[i].length*sizeof(TD_PUSMemData),block[i].checksum) )
            return MEM_LOAD_POST_CHECKSUM_FAILED;

    return ACTION_SUCCESS;
}


bool PUSMemoryLoad::isObjectConfigured(void) {
   return ( PUSTelecommand::isObjectConfigured() &&
           (block!=pNULL) &&
           (data!=pNULL) );
}


//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSMemoryLoadOffset.cpp
//
// Version	1.0
// Date		4.12.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_PUSMemoryLoadOffset.h"

#include <string.h>

DC_PUSMemoryLoadOffset::DC_PUSMemoryLoadOffset(void) {
    setClassId(ID_PUSMEMORYLOADOFFSET);
    setSubType(PUS_ST_TC_MEM_OFF);
    memId = 0;
}

void DC_PUSMemoryLoadOffset::setRawData(unsigned char* d, unsigned int n) {
    assert( d!=pNULL );
    assert( n>0 );
    assert( isObjectConfigured() );

    assert( sizeof(TD_PUSMemData)==1 );

    setValidityCheckCode(0);

    if ( n<=(sizeof(TD_PUSMemId)+sizeof(TD_PUSMemData*)+sizeof(TD_PUSNumberMemBlocks)) ) {
        setValidityCheckCode(VC_INCONSISTENT_RAW_DATA);
        return;
    }

    TD_PUSMemData* base;
    TD_PUSMemOffset offset;
    TD_PUSMemLength length;
    unsigned int counter;
    unsigned int dataCounter;

    memcpy(&memId,d,sizeof(TD_PUSMemId));
    memcpy(&base,d+sizeof(TD_PUSMemId),sizeof(TD_PUSMemData*));
    memcpy(&numberBlocks,d+sizeof(TD_PUSMemId)+sizeof(TD_PUSMemData*),sizeof(TD_PUSNumberMemBlocks));

    if (numberBlocks>maxNumberBlocks) {
        setValidityCheckCode(VC_TOO_MANY_MEM_BLOCK);
        return;
    }

    counter = sizeof(TD_PUSMemId)+sizeof(TD_PUSMemData*)+sizeof(TD_PUSNumberMemBlocks);
    dataCounter = 0;
    for (unsigned int i=0; i<numberBlocks; i++) {
        memcpy(&offset,d+counter,sizeof(TD_PUSMemOffset));
        block[i].startAddress = base+offset;
        memcpy(&length,d+counter+sizeof(TD_PUSMemOffset),sizeof(TD_PUSMemLength));
        block[i].length = length;
        if (dataCounter+length>=maxNumberData) {
            setValidityCheckCode(VC_TOO_MANY_MEM_DATA);
            return;
        }
        for (unsigned int j=0; j<length; j++) 
            data[dataCounter+j] = *(TD_PUSMemData*)(d+counter+sizeof(TD_PUSMemOffset)+
                                                                sizeof(TD_PUSMemLength)+j*sizeof(TD_PUSMemData));
        memcpy(&block[i].checksum,d+counter+sizeof(TD_PUSMemOffset)+
                                          sizeof(TD_PUSMemLength)+length*sizeof(TD_PUSMemData),sizeof(unsigned short));
        counter = counter+sizeof(TD_PUSMemOffset)+sizeof(TD_PUSMemLength)+
                    sizeof(TD_PUSMemData)*length+2;
        dataCounter = dataCounter+length;
    }

    if (counter!=n) {
        setValidityCheckCode(VC_INCONSISTENT_RAW_DATA);
        return;
    }


}

TD_PUSMemId DC_PUSMemoryLoadOffset::getMemoryBlockId() const {
    return memId;
}

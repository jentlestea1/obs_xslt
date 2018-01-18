//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSMemoryLoadAbsolute.cpp
//
// Version	1.0
// Date		4.12.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "DC_PUSMemoryLoadAbsolute.h"

#include <string.h>

DC_PUSMemoryLoadAbsolute::DC_PUSMemoryLoadAbsolute(void) {
    setClassId(ID_PUSMEMORYLOADABSOLUTE);
    setSubType(PUS_ST_TC_MEM_ABS);
    memId = 0;
}

void DC_PUSMemoryLoadAbsolute::setRawData(unsigned char* d, unsigned int n) {
    assert( d!=pNULL );
    assert( n>0 );
    assert( isObjectConfigured() );

    assert( sizeof(TD_PUSMemData)==1 );

    setValidityCheckCode(0);

    if ( n<=(sizeof(TD_PUSMemId)+sizeof(TD_PUSNumberMemBlocks)) ) {
        setValidityCheckCode(VC_INCONSISTENT_RAW_DATA);
        return;
    }

    TD_PUSMemLength length;
    unsigned int counter;
    unsigned int dataCounter;

    memcpy(&memId,d,sizeof(TD_PUSMemId));
    memcpy(&numberBlocks,d+sizeof(TD_PUSMemId),sizeof(TD_PUSNumberMemBlocks));

    if (numberBlocks>maxNumberBlocks) {
        setValidityCheckCode(VC_TOO_MANY_MEM_BLOCK);
        return;
    }

    counter = sizeof(TD_PUSMemId)+sizeof(TD_PUSNumberMemBlocks);
    dataCounter = 0;
    for (unsigned int i=0; i<numberBlocks; i++) {
        memcpy(&block[i].startAddress,d+counter,sizeof(TD_PUSMemData*));
        memcpy(&block[i].length,d+counter+sizeof(TD_PUSMemData*),sizeof(TD_PUSMemLength));
        length = block[i].length;
        if (dataCounter+length>=maxNumberData) {
            setValidityCheckCode(VC_TOO_MANY_MEM_DATA);
            return;
        }
        for (unsigned int j=0; j<length; j++) 
            data[dataCounter+j] = *(TD_PUSMemData*)(d+counter+sizeof(TD_PUSMemData*)+
                                                        sizeof(TD_PUSMemLength)+j*sizeof(TD_PUSMemData));
        memcpy(&block[i].checksum,d+counter+sizeof(TD_PUSMemData*)+
                                      sizeof(TD_PUSMemLength)+length*sizeof(TD_PUSMemData),sizeof(unsigned short));
        counter = counter+sizeof(TD_PUSMemData*)+sizeof(TD_PUSMemLength)+sizeof(TD_PUSMemData)*length+2;
        dataCounter = dataCounter+length;
    }

    if (counter!=n) {
        setValidityCheckCode(VC_INCONSISTENT_RAW_DATA);
        return;
    }
}

TD_PUSMemId DC_PUSMemoryLoadAbsolute::getMemoryBlockId() const {
    return memId;
}

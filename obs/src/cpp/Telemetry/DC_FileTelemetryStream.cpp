//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_FileTelemetryStream.cpp
//
// Version	1.0
// Date		04.03.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/CC_RootObject.h"
#include "TelemetryPacket.h"
#include "DC_FileTelemetryStream.h"
#include <stdio.h>
#include <time.h>

DC_FileTelemetryStream::DC_FileTelemetryStream(void) {
    setClassId(ID_FILETELEMETRYSTREAM);
    out = pNULL;
}

void DC_FileTelemetryStream::flush(void) {
    if ( out!=pNULL ) {
        fprintf(out,"---------------------------------------------------------------------\n");
        fflush(out);
    }
    else
        printf("---------------------------------------------------------------------\n");
}

void DC_FileTelemetryStream::setOutputStream(FILE* outputStream) {
    out = outputStream;
#ifdef MS_HOST
    time_t ltime;
    time( &ltime );
    if ( out!=pNULL )
        fprintf(out,"File-Oriented Output Stream -- Data Written on %s \n",ctime( &ltime ));
    else
        printf("File-Oriented Output Stream -- Data Written on %s \n",ctime( &ltime ));
#endif
}

FILE* DC_FileTelemetryStream::getOutputStream(void) {
    return out;
}

void DC_FileTelemetryStream::write(TelemetryPacket* tmItem) {
    assert( tmItem!=pNULL );
    if (out!=pNULL) {
        fprintf(out,"Telemetry Item Type (hex):  %8x \n",tmItem->getType());
        fprintf(out,"Telemetry Item Subtype (hex):  %8x \n",tmItem->getSubType());
        fprintf(out,"Telemetry Item Destination (hex):  %8x \n",tmItem->getDestination());
        fprintf(out,"Telemetry Item Time Tag (hex):  %8x \n",tmItem->getTimeTag());
        for (unsigned int i=0; i<tmItem->getNumberOfBytes(); i++)
            fprintf(out,"Byte %8x (hex):  %8x \n",i,tmItem->getUnsignedByte(i));
    }
    else {
        printf("Telemetry Item Type (hex):  %8x \n",tmItem->getType());
        printf("Telemetry Item Subtype (hex):  %8x \n",tmItem->getSubType());
        printf("Telemetry Item Destination (hex):  %8x \n",tmItem->getDestination());
        printf("Telemetry Item Time Tag (hex):  %8x \n",tmItem->getTimeTag());
        for (unsigned int i=0; i<tmItem->getNumberOfBytes(); i++)
            printf("Byte %8x (hex):  %8x \n",i,tmItem->getUnsignedByte(i));
    }
}



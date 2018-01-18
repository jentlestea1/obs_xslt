//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDataItem16TmWord_1.cpp
//
// Version	1.1
// Date		18.04.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/TestConstants.h"
#include "../Telemetry/DC_DataItem16TmWord.h"
#include "../Base/CC_RootObject.h"
#include "../Event/DC_EventRepository.h"
#include "../Data/DC_RawDataItem.h"
#include "../Data/DC_DataItem.h"
#include "TestCaseDataItem16TmWord_1.h"

#include <string.h>

TestCaseDataItem16TmWord_1::TestCaseDataItem16TmWord_1(void) :
	TestCaseGenericSetUp(ID_DATAITEM16TMWORD*10+1,"TestCaseDataItem16TmWord_1") {
		return;
}

void TestCaseDataItem16TmWord_1::runTestCase(void) {

   unsigned short usTemp;
   unsigned char ucTemp;
   unsigned char* pTemp;

   // Create a data item component
   unsigned short var = 0xaabb;
   DC_RawDataItem* pd1 = new DC_RawDataItem( &var );

   // Create the DataItem16TmWord_1 component
   DC_DataItem16TmWord* pTmWord = new DC_DataItem16TmWord();

   // Check the value of the class identifier
   if ( pTmWord->getClassId() != ID_DATAITEM16TMWORD )
   {    setTestResult(TEST_FAILURE, "Wrong class identifier");
        return;
   }

   // Check that the DataItem16TmWord_1 is not configured
   if ( pTmWord->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong object configuration status");
        return;
   }

   // Load the data item into the DataItem16TmWord_1 object and check that the
   // DataItem16TmWord_1 object becomes configured
   pTmWord->setDataItem(pd1);
   if ( !pTmWord->isObjectConfigured() )
   {    setTestResult(TEST_FAILURE, "Wrong object configuration status");
        return;
   }

   // Check the correct validity status
   if ( !pTmWord->isValid() )
   {    setTestResult(TEST_FAILURE, "Wrong validity status");
        return;
   }

   // Check the correct number of bytes
   if ( pTmWord->getNumberOfBytes() != 2)
   {    setTestResult(TEST_FAILURE, "Wrong number of bytes");
        return;
   }

   // Send an update request to DataItem16TmWord_1 and check the
   // data acquired from it are correct
   pTmWord->update();
   if ( pTmWord->getUnsignedShort(0) != 0xaabb )
   {    setTestResult(TEST_FAILURE, "Wrong data acquisition result");
        return;
   }
   usTemp = pd1->getUnsignedShort();
   pTemp = (unsigned char*)&usTemp;
   memcpy(&ucTemp,pTemp,1);
   if ( pTmWord->getUnsignedByte(0) != ucTemp )
   {    setTestResult(TEST_FAILURE, "Wrong data acquisition result");
        return;
   }
   memcpy(&ucTemp,pTemp+1,1);
   if ( pTmWord->getUnsignedByte(1) != ucTemp )
   {    setTestResult(TEST_FAILURE, "Wrong data acquisition result");
        return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;

}

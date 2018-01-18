//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSMemoryLoadOffset_1.cpp
//
// Version	1.0
// Date		04.02.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telecommand/DC_PUSMemoryLoadOffset.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCasePUSMemoryLoadOffset_1.h"

#include <assert.h>
#include <string.h>

TestCasePUSMemoryLoadOffset_1::TestCasePUSMemoryLoadOffset_1(void) :
	TestCaseWithEvtCheck(ID_PUSMEMORYLOADOFFSET*10+1,"TestCasePUSMemoryLoadOffset_1") {
		return;
}

void TestCasePUSMemoryLoadOffset_1::runTestCase(void) {

   DC_PUSMemoryLoadOffset* pML = new DC_PUSMemoryLoadOffset();

   // Set dummy values for the configuration parameters defined at
   // the level of Telecommand and PUSTelecommand superclasses
   pML->setTimeTag(0);
   pML->setSource(1);
   pML->setTelecommandId(2);

   // Memory area where telecommand data will be loaded
   const unsigned int paSize =100;
   TD_PUSMemData pa[paSize];
   for (unsigned int i=0; i<paSize; i++)
        pa[i]=0;

   // Data area for the telecommand packet
   const unsigned short defPacketSize = 100;
   unsigned char packet[defPacketSize];

   // Check the correctness of the class identifier
   if ( (pML->getClassId() != ID_PUSMEMORYLOADOFFSET) )
   {	setTestResult(TEST_FAILURE,"Wrong class identifier");
        return;
   }

   // Check configuration status
   if ( pML->isObjectConfigured() )
   {	setTestResult(TEST_FAILURE,"Wrong configuration status at initialization");
    	return;
   }

   // Set maximum number of blocks
   pML->setMaxNumberBlocks(3);
   if ( pML->getMaxNumberBlocks()!=3 )
   {	setTestResult(TEST_FAILURE,"Wrong configuration parameter");
    	return;
   }

   // Set maximum number of data
   pML->setMaxNumberData(10);
   if ( pML->getMaxNumberData()!=10 )
   {	setTestResult(TEST_FAILURE,"Wrong configuration parameter");
    	return;
   }

   // Check configuration status
   if ( !pML->isObjectConfigured() )
   {	setTestResult(TEST_FAILURE,"Wrong configuration status after initialization");
    	return;
   }

   // Define fixed part of the memory load PUS packet 
   unsigned int offset = 0;
   TD_PUSMemId id = 12;
   TD_PUSMemData* base = pa;
   memcpy(packet+offset,&id,sizeof(TD_PUSMemId));
   offset += sizeof(TD_PUSMemId);
   memcpy(packet+offset,&base,sizeof(TD_PUSMemData*));
   offset += sizeof(TD_PUSMemData*);

   // Define the first load packet (one block with two data)
   TD_PUSMemOffset os1 = 2;
   TD_PUSMemLength len1 = 2;
   TD_PUSMemData d1 = 1;
   TD_PUSMemData d2 = 2;
   TD_PUSNumberMemBlocks nmb = 1;
   unsigned short checkSum = 0;

   memcpy(packet+offset,&nmb,sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   memcpy(packet+offset,&os1,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&len1,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&d1,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d2,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&checkSum,2);
   offset += sizeof(unsigned short);

   // Load packet and check validity
   if ( pML->getValidityCheckCode()!=0 )
   {	setTestResult(TEST_FAILURE,"Wrong validity code");
    	return;
   }
   pML->setRawData(packet,offset);
   if ( pML->getValidityCheckCode()!=0 )
   {	setTestResult(TEST_FAILURE,"Wrong validity code");
    	return;
   }

   // Execute TC and check correctness
   if ( pML->execute()!=ACTION_SUCCESS )
   {	setTestResult(TEST_FAILURE,"Wrong execution outcome");
    	return;
   }
   if ( (pa[os1]!=d1) || (pa[os1+1]!=d2) )
   {	setTestResult(TEST_FAILURE,"Wrong loaded data");
    	return;
   }

   // Define the second load packet (three blocks with three data each)
   offset = sizeof(TD_PUSMemId)+sizeof(unsigned char*);
   os1 = 2;
   TD_PUSMemOffset os2 = 20;
   TD_PUSMemOffset os3 = 30;
   TD_PUSMemLength len = 3;
   d1 = 3;
   d2 = 4;
   TD_PUSMemData d3 = 5;
   nmb = 3;
   checkSum = 0;

   memcpy(packet+offset,&nmb,sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   memcpy(packet+offset,&os1,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&len,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&d1,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d2,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d3,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&checkSum,2);
   offset += sizeof(unsigned short);

   d1 = d1*2;
   d2 = d2*2;
   d3 = d3*2;
   memcpy(packet+offset,&os2,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&len,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&d1,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d2,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d3,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&checkSum,2);
   offset += sizeof(unsigned short);

   d1 = d1*3;
   d2 = d2*3;
   d3 = d3*3;
   memcpy(packet+offset,&os3,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&len,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&d1,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d2,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d3,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&checkSum,2);
   offset += sizeof(unsigned short);


   // Load packet and check validity
   if ( pML->getValidityCheckCode()!=0 )
   {	setTestResult(TEST_FAILURE,"Wrong validity code");
    	return;
   }
   pML->setRawData(packet,offset);
   if ( pML->getValidityCheckCode()!=0 )
   {	setTestResult(TEST_FAILURE,"Wrong validity code");
    	return;
   }

   // Execute TC and check correctness
   if ( pML->execute()!=ACTION_SUCCESS )
   {	setTestResult(TEST_FAILURE,"Wrong execution outcome");
    	return;
   }
   if ( (pa[os1]!=d1/6) || (pa[os1+1]!=d2/6) || (pa[os1+2]!=d3/6) )
   {	setTestResult(TEST_FAILURE,"Wrong loaded data");
    	return;
   }
   if ( (pa[os2]!=d1/3) || (pa[os2+1]!=d2/3) || (pa[os2+2]!=d3/3) )
   {	setTestResult(TEST_FAILURE,"Wrong loaded data");
    	return;
   }
   if ( (pa[os3]!=d1) || (pa[os3+1]!=d2) || (pa[os3+2]!=d3) )
   {	setTestResult(TEST_FAILURE,"Wrong loaded data");
    	return;
   }

   // Define the third load packet (four blocks)
   offset = sizeof(TD_PUSMemId)+sizeof(unsigned char*);
   nmb = 4;
   memcpy(packet+offset,&nmb,sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   offset += 10;   // dummy: just to simulate presence of memory load data 
       
   // Load packet and check validity
   pML->setRawData(packet,offset);
   if ( pML->getValidityCheckCode()!=VC_TOO_MANY_MEM_BLOCK )
   {	setTestResult(TEST_FAILURE,"Wrong validity code");
    	return;
   }

   // Define the fourth load packet (one block with 2 data, one block with nine data)
   offset = sizeof(TD_PUSMemId)+sizeof(unsigned char*);
   os1 = 2;
   os2 = 10;
   len1 = 2;
   TD_PUSMemLength len2 = 9;
   nmb = 2;
   checkSum = 0;

   d1 = 0;
   d2 = 0;
   memcpy(packet+offset,&nmb,sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   memcpy(packet+offset,&os1,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&len1,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&d1,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d2,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d3,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&checkSum,2);
   offset += sizeof(unsigned short);
   memcpy(packet+offset,&os2,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&len2,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);

   // Load packet and check validity
   pML->setRawData(packet,offset);
   if ( pML->getValidityCheckCode()!=VC_TOO_MANY_MEM_DATA )
   {	setTestResult(TEST_FAILURE,"Wrong validity code");
    	return;
   }

   // Load packet with invalid number of bytes and check validity
   pML->setRawData(packet,1);
   if ( pML->getValidityCheckCode()!=VC_INCONSISTENT_RAW_DATA )
   {	setTestResult(TEST_FAILURE,"Wrong validity code");
    	return;
   }

   // Define the first load packet again (one block with two data)
   offset = sizeof(TD_PUSMemId)+sizeof(unsigned char*);
   os1 = 2;
   len1 = 2;
   d1 = 1;
   d2 = 2;
   nmb = 1;
   checkSum = 0;

   memcpy(packet+offset,&nmb,sizeof(TD_PUSNumberMemBlocks));
   offset += sizeof(TD_PUSNumberMemBlocks);
   memcpy(packet+offset,&os1,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&len1,sizeof(TD_PUSMemLength));
   offset += sizeof(TD_PUSMemLength);
   memcpy(packet+offset,&d1,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&d2,sizeof(TD_PUSMemData));
   offset += sizeof(TD_PUSMemData);
   memcpy(packet+offset,&checkSum,2);
   offset += sizeof(unsigned short);

   // Load packet with wrong number of bytes and check validity
   pML->setRawData(packet,offset+1);
   if ( pML->getValidityCheckCode()!=VC_INCONSISTENT_RAW_DATA )
   {	setTestResult(TEST_FAILURE,"Wrong validity code");
    	return;
   }


   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}

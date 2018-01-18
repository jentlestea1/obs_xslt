//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSMemoryLoadOffset_2.cpp
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
#include "TestCasePUSMemoryLoadOffset_2.h"

#include <assert.h>
#include <string.h>

TestCasePUSMemoryLoadOffset_2::TestCasePUSMemoryLoadOffset_2(void) :
	TestCaseWithEvtCheck(ID_PUSMEMORYLOADOFFSET*10+2,"TestCasePUSMemoryLoadOffset_2") {
		return;
}

void TestCasePUSMemoryLoadOffset_2::runTestCase(void) {

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

   // Define the load packet (one block with four data) with the valid checksum
   // The data and their checksum are taken from one of the examples
   // in the appendix 3 of the PUS
   TD_PUSMemOffset os1 = 2;
   TD_PUSMemLength len1 = 4;
   TD_PUSMemData d1 = 0xAB;
   TD_PUSMemData d2 = 0xCD;
   TD_PUSMemData d3 = 0xEF;
   TD_PUSMemData d4 = 0x01;
   TD_PUSNumberMemBlocks nmb = 1;
   unsigned short checkSum = 0x9CF8;

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
   memcpy(packet+offset,&d4,sizeof(TD_PUSMemData));
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
   if ( (pa[os1]!=d1) || (pa[os1+1]!=d2) || (pa[os1+2]!=d3) || (pa[os1+3]!=d4) )
   {	setTestResult(TEST_FAILURE,"Wrong loaded data");
    	return;
   }

   // Clear patch memory area
   for (unsigned int i=0; i<paSize; i++)
        pa[i]=0;

   // Define the load packet (one block with four data) with the invalid checksum
   // The data and their checksum are taken from one of the examples
   // in the appendix 3 of the PUS
   offset = sizeof(TD_PUSMemId)+sizeof(unsigned char*);
   os1 = 2;
   len1 = 4;
   d1 = 0xAB;
   d2 = 0xCD;
   d3 = 0xEF;
   d4 = 0x01;
   nmb = 1;
   checkSum = 0x9CF9;

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
   memcpy(packet+offset,&d4,sizeof(TD_PUSMemData));
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

   // Execute TC and check correctness of outcome
   if ( pML->execute()!=MEM_LOAD_PRE_CHECKSUM_FAILED )
   {	setTestResult(TEST_FAILURE,"Wrong execution outcome");
    	return;
   }

   // Check that no data were written to patch area
   for (unsigned int i=0; i<paSize; i++)
        if (pa[i]!=0)
        {	setTestResult(TEST_FAILURE,"Wrong loaded data");
        	return;
        }


   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}

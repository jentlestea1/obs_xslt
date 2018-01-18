//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSMemoryDumpOffset_1.cpp
//
// Version	1.0
// Date		04.02.04
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_PUSMemoryDumpOffset.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCasePUSMemoryDumpOffset_1.h"

#include <assert.h>
#include <string.h>

TestCasePUSMemoryDumpOffset_1::TestCasePUSMemoryDumpOffset_1(void) :
	TestCaseWithEvtCheck(ID_PUSMEMORYDUMPOFFSET*10+1,"TestCasePUSMemoryDumpOffset_1") {
		return;
}

void TestCasePUSMemoryDumpOffset_1::runTestCase(void) {

   DC_PUSMemoryDumpOffset* pMD = new DC_PUSMemoryDumpOffset();

   // Set dummy values for the configuration parameters defined at
   // the level of telemetry packet and PUS telemmetry packet superclasses
   pMD->setTimeTag(0);
   pMD->setDestination(1);

   // Memory area from where telemetry data will be collected
   const unsigned int paSize =100;
   TD_PUSMemData pa[paSize];
   for (TD_PUSMemData i=0; i<paSize; i++)
        pa[i]=i;

   // Data area for the telemetry packet packet
   const unsigned short defPacketSize = 100;
   unsigned char packet[defPacketSize];

   // Check the correctness of the class identifier
   if ( (pMD->getClassId() != ID_PUSMEMORYDUMPOFFSET) )
   {	setTestResult(TEST_FAILURE,"Wrong class identifier");
        return;
   }

   // Check the correctness of the type and subtype
   if ( (pMD->getType() != 6) || (pMD->getSubType() != 4) )
   {	setTestResult(TEST_FAILURE,"Wrong type or subtype");
        return;
   }

   // Check configuration status
   if ( pMD->isObjectConfigured() )
   {	setTestResult(TEST_FAILURE,"Wrong configuration status at initialization");
    	return;
   }

   // Set maximum number of blocks
   TD_PUSNumberMemBlocks numberBlocks = 3;
   pMD->setMaxNumberBlocks(numberBlocks);
   if ( pMD->getMaxNumberBlocks()!=numberBlocks )
   {	setTestResult(TEST_FAILURE,"Wrong configuration parameter");
    	return;
   }

   // Set maximum number of data
   TD_PUSMemLength maxNumberData = 50;
   pMD->setDumpBufferSize(maxNumberData);
   if ( pMD->getDumpBufferSize()!=maxNumberData )
   {	setTestResult(TEST_FAILURE,"Wrong configuration parameter");
    	return;
   }

   // Check configuration status
   if ( !pMD->isObjectConfigured() )
   {	setTestResult(TEST_FAILURE,"Wrong configuration status after initialization");
    	return;
   }

   // Check initial value of checksum flag
   if ( pMD->isChecksumFlagSet() )
   {	setTestResult(TEST_FAILURE,"Wrong value of checksum flag");
    	return;
   }

   // Set base address and check success
   pMD->setBaseAddress(pa);
   if ( pMD->getBaseAddress()!=pa )
   {	setTestResult(TEST_FAILURE,"Wrong value of base address");
    	return;
   }

   // Set memory ID and check success
   TD_PUSMemId memId = 12;
   pMD->setMemoryId(memId);
   if ( pMD->getMemoryId()!=memId )
   {	setTestResult(TEST_FAILURE,"Wrong value of memory id");
    	return;
   }

   // Check availability of fast acquisition service
   if ( !pMD->isFastAcquisitionImplemented() )
   {	setTestResult(TEST_FAILURE,"Missing fast acquisition service");
    	return;
   }

   // Configure the packet to dump two blocks of three locations each
   TD_PUSMemOffset osa = 2;
   TD_PUSMemOffset osb = 5;
   TD_PUSMemLength lena = 2;
   TD_PUSMemLength lenb = 3;
   pMD->setNumberBlocks(2);
   pMD->defineBlock(0,pa+osa,lena);
   pMD->defineBlock(1,pa+osb,lenb);
   if ( (pMD->getStartAddress(0)!=(pa+osa)) || (pMD->getStartAddress(1)!=(pa+osb)) )
   {	setTestResult(TEST_FAILURE,"Wrong block configuration values");
    	return;
   }
   if ( (pMD->getLength(0)!=lena) || (pMD->getLength(1)!=lenb) )
   {	setTestResult(TEST_FAILURE,"Wrong block configuration values");
    	return;
   }

   // Do a data update
   pMD->update();

   // Compute expected size of the telemetry packet
   unsigned int fixedLength = sizeof(TD_PUSMemId)+sizeof(TD_PUSMemData*)+sizeof(TD_PUSNumberMemBlocks);
   unsigned int blockLength_1 = sizeof(TD_PUSMemOffset)+sizeof(TD_PUSMemLength)+
                                    sizeof(unsigned short)+lena*sizeof(TD_PUSMemData);
   unsigned int blockLength_2 = sizeof(TD_PUSMemOffset)+sizeof(TD_PUSMemLength)+
                                    sizeof(unsigned short)+lenb*sizeof(TD_PUSMemData);
   if (pMD->getNumberOfBytes()!=(fixedLength+blockLength_1+blockLength_2))
   {	setTestResult(TEST_FAILURE,"Wrong packet size");
    	return;
   }

   // Do data acquisition and check success
   for (unsigned int i=0; i<pMD->getNumberOfBytes(); i++) 
       packet[i]=pMD->getUnsignedByte(i);

   bool testFailed = false;
   unsigned int offset = 0;
   if ( memcmp(packet+offset,&memId,sizeof(TD_PUSMemId))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemId);
   TD_PUSMemData* miTemp = pa;
   if ( memcmp(packet+offset,&miTemp,sizeof(TD_PUSMemData*))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemData*);
   TD_PUSNumberMemBlocks nmbTemp = 2;
   if ( memcmp(packet+offset,&nmbTemp,sizeof(TD_PUSNumberMemBlocks))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSNumberMemBlocks);

   // -- first block --
   if ( memcmp(packet+offset,&osa,sizeof(TD_PUSMemOffset))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemOffset);
   if ( memcmp(packet+offset,&lena,sizeof(TD_PUSMemLength))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemLength);
   for (TD_PUSMemOffset i=osa; i<osa+lena; i++) {
        TD_PUSMemData mpTemp = (TD_PUSMemData)(i);
        if ( memcmp(packet+offset,&mpTemp,sizeof(TD_PUSMemData))!=0 )
            testFailed = true;
        offset += sizeof(TD_PUSMemData);
   }
   unsigned short usTemp = 0;
   if ( memcmp(packet+offset,&usTemp,2)!=0 )
       testFailed = true;
   offset += sizeof(unsigned short);

   // -- second block --
   if ( memcmp(packet+offset,&osb,sizeof(TD_PUSMemOffset))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemOffset);
   if ( memcmp(packet+offset,&lenb,sizeof(TD_PUSMemLength))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemLength);
   for (TD_PUSMemOffset i=osb; i<osb+lenb; i++) {
        TD_PUSMemData mpTemp = (TD_PUSMemData)(i);
        if ( memcmp(packet+offset,&mpTemp,sizeof(TD_PUSMemData))!=0 )
            testFailed = true;
        offset += sizeof(TD_PUSMemData);
   }
   usTemp = 0;
   if ( memcmp(packet+offset,&usTemp,2)!=0 )
       testFailed = true;
   offset += sizeof(unsigned short);
   // -- end second block --

   if ( testFailed )
   {	setTestResult(TEST_FAILURE,"Wrong telemetry packet content");
    	return;
   }

   // Change setting of checksum flag and check success
   pMD->setChecksumFlag(true);
   if ( !pMD->isChecksumFlagSet() )
   {	setTestResult(TEST_FAILURE,"Wrong checksum value");
    	return;
   }

   // Configure the packet to dump one block of one location. The offset is chosen to be zero so as
   // to ensure that the dumped location has value zero and its expected checksum is then "FF FF".
   osa = 0;
   lena = 1;
   pMD->setNumberBlocks(1);
   pMD->defineBlock(0,pa+osa,lena);

   // Do a data update
   pMD->update();

   // Do data acquisition and check success
   for (unsigned int i=0; i<pMD->getNumberOfBytes(); i++) 
       packet[i]=pMD->getUnsignedByte(i);

   testFailed = false;
   offset = 0;
   if ( memcmp(packet+offset,&memId,sizeof(TD_PUSMemId))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemId);
   miTemp = pa;
   if ( memcmp(packet+offset,&miTemp,sizeof(TD_PUSMemData*))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemData*);
   nmbTemp = 1;
   if ( memcmp(packet+offset,&nmbTemp,sizeof(TD_PUSNumberMemBlocks))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSNumberMemBlocks);

   // -- first block --
   if ( memcmp(packet+offset,&osa,sizeof(TD_PUSMemOffset))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemOffset);
   if ( memcmp(packet+offset,&lena,sizeof(TD_PUSMemLength))!=0 )
       testFailed = true;
   offset += sizeof(TD_PUSMemLength);
   for (TD_PUSMemOffset i=osa; i<osa+lena; i++) {
        TD_PUSMemData mpTemp = (TD_PUSMemData)(i);
        if ( memcmp(packet+offset,&mpTemp,sizeof(TD_PUSMemData))!=0 )
            testFailed = true;
        offset += sizeof(TD_PUSMemData);
   }
   usTemp = 0xFFFF;
   if ( memcmp(packet+offset,&usTemp,2)!=0 )
       testFailed = true;
   offset += sizeof(unsigned short);

   if ( testFailed )
   {	setTestResult(TEST_FAILURE,"Wrong telemetry packet content");
    	return;
   }

   // Do non-nominal behaviour checks and check event generation
   if ( isNonNominalCheckAllowed() ) {
       unsigned int nEvt = getNumberOfEvents();

       // Try defining a non-existent block
       pMD->defineBlock(3,pa+osa,lena);       
       if ( !verifyLatestEvent(nEvt+1,EVT_PUS_ILLEGAL_BLOCK_INDEX) )
           return;

       // Try loading too many blocks
       pMD->setNumberBlocks(5);
       if ( !verifyLatestEvent(nEvt+2,EVT_PUS_TOO_MANY_DUMP_BLOCKS) )
           return;

       // Try dumping more memory locations than fit in the dump buffer
       pMD->defineBlock(0,pa+osb,maxNumberData+1);    
       pMD->update();
       if ( !verifyLatestEvent(nEvt+3,EVT_PUS_TOO_MANY_MEM_DATA) )
           return;
   }

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}

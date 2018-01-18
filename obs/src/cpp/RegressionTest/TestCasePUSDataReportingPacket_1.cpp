//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSDataReportingPacket_1.cpp
//
// Version	1.0
// Date		04.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCasePUSDataReportingPacket_1.h"

#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>

TestCasePUSDataReportingPacket_1::TestCasePUSDataReportingPacket_1(void) :
	TestCaseWithEvtCheck(ID_PUSDATAREPORTINGPACKET*10+1,"TestCasePUSDataReportingPacket_1") {
		return;
}

void TestCasePUSDataReportingPacket_1::runTestCase(void) {

   DC_SampleFullDataPool* pDP = new DC_SampleFullDataPool();
   unsigned int nEvt = getNumberOfEvents();
   DC_PUSDataReportingPacket* pTMP = new DC_PUSDataReportingPacket();

   // Configure and load the data pool
   pDP->setObsClock(DC_PUSDataReportingPacket::getObsClock());
   DataPool* pOldDP = CC_RootObject::getDataPool();
   CC_RootObject::setDataPool(pDP);

   // Define the PUS packet
   TD_SID sid = 12;
   TD_PUSCollectionInterval collectionInterval = 3;
   TD_PUSNumberOfParameters NPAR1 = 2;
   TD_DataPoolId par1 = 1;
   TD_Integer val1 = 11;
   TD_DataPoolId par2 = 2;
   TD_Float val2 = 12.0;

   // Construct the packet
   TD_PUSNumberOfParameters const defPacketSize = 30;
   unsigned char packet[defPacketSize];
   TD_PUSNumberOfParameters offset = 0;
   memcpy(packet+offset,&sid,sizeof(TD_SID));
   offset += sizeof(TD_SID);
   memcpy(packet+offset,&collectionInterval,sizeof(TD_PUSCollectionInterval));
   offset += sizeof(TD_PUSCollectionInterval);
   memcpy(packet+offset,&NPAR1,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&par1,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset,&par2,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);

   assert(offset<defPacketSize);

   // Check the correctness of the class identifier
   if ( (pTMP->getClassId() != ID_PUSDATAREPORTINGPACKET) )
   {	setTestResult(TEST_FAILURE,"Wrong class identifier for the FSM class");
        return;
   }

   // Check configuration status
   if ( pTMP->isObjectConfigured() )
   {	setTestResult(TEST_FAILURE,"Wrong configuration status at initialization");
    	return;
   }

   // Set maximum number of FA arrays and check correctness
   pTMP->setMaxNumberFA(2);
   if ( pTMP->getMaxNumberFA()!=2 )
   {	setTestResult(TEST_FAILURE,"Wrong number of FA arrays");
    	return;
   }

   // Set maximum size of the packet definition buffer and check correctness
   pTMP->setDefinitionBufferSize(defPacketSize);
   if ( pTMP->getDefinitionBufferSize()!=defPacketSize )
   {	setTestResult(TEST_FAILURE,"Wrong definition buffer size");
    	return;
   }

   // Set maximum size of the packet value buffer and check correctness
   unsigned int valBufferSize = 30;
   pTMP->setValueBufferSize(valBufferSize);
   if ( pTMP->getValueBufferSize()!=valBufferSize )
   {	setTestResult(TEST_FAILURE,"Wrong value buffer size");
    	return;
   }

   // Load the packet subtype and time tag check configuration status
   pTMP->setTimeTag(0);
   pTMP->setSubType(PUS_ST_DATA_REP_PAR_HK_REP);
   if ( !pTMP->isObjectConfigured() )
   {	setTestResult(TEST_FAILURE,"Wrong configuration status");
    	return;
   }

   // Check that packet is disabled
   if ( (pTMP->isEnabled() == ENABLED) )
   {	setTestResult(TEST_FAILURE,"Wrong enable status");
    	return;
   }

   // Load the packet definition
   for (unsigned short i=0; i<offset; i++)
        pTMP->setDefinitionBuffer(i,packet[i]);

   if (pTMP->getDefinitionBufferLength()!=offset)
   {	setTestResult(TEST_FAILURE,"Wrong definition buffer length");
    	return;
   }

   // Send three update requests and check that there are no data to be acquired
   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }

   // Enable the component and check correctness
   pTMP->setEnabled(ENABLED);
   if ( (pTMP->isEnabled() == DISABLED) )
   {	setTestResult(TEST_FAILURE,"Wrong enable status");
    	return;
   }

   // Send two update requests and check that there are no data to be acquired
   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }

   // Update the values of the data pool items
   pDP->setValue(par1,val1);
   pDP->setValue(par2,val2);

   // Send an update request and check data acquisition service
   pTMP->update();
   unsigned int n1, n2, n3;
   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE?1:0);
   n3 = sizeof(TD_Float)+sizeof(TD_Integer);
   unsigned int expNumberOfBytes = n1+n2+n3;
   if (pTMP->getNumberOfBytes()!=expNumberOfBytes)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }

   // Collect the packet data and check their values
   unsigned char* valBuffer = new unsigned char[valBufferSize];
   for (unsigned int i=0; i<pTMP->getNumberOfBytes(); i++)
       valBuffer[i] = pTMP->getUnsignedByte(i);

   unsigned int valOffset = 0;
   TD_SID sidTemp = 0;
   TD_Integer intTemp = 0;
   TD_Float flTemp = 0;

   memcpy(&sidTemp,valBuffer+valOffset,sizeof(TD_SID));
   if ( sidTemp != sid )
   {	setTestResult(TEST_FAILURE,"Wrong sid field");
    	return;
   }
   valOffset += sizeof(TD_SID);

   if ( PUS_DATA_REP_MODE?valBuffer[valOffset]!=0:false )
   {	setTestResult(TEST_FAILURE,"Wrong mode field");
    	return;
   }
   valOffset += (PUS_DATA_REP_MODE?1:0);

   memcpy(&intTemp,valBuffer+valOffset,sizeof(TD_Integer));
   if ( intTemp != (TD_Integer)val1 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp - (TD_Float)val2)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   assert(valOffset<valBufferSize);

   // Check that the fast version of the data acquisition service is implemented
   if ( !pTMP->isFastAcquisitionImplemented() )
   {	setTestResult(TEST_FAILURE,"Fast data acquisition service should be implemented");
    	return;
   }

   // Collect the packet data using the fast version of the data acquisition 
   // service and check their values
   unsigned char* temp = pTMP->getStartAddress();
   for (unsigned int i=0; i<pTMP->getNumberOfBytes(); i++)
       valBuffer[i] = temp[i];

   valOffset = 0;
   memcpy(&sidTemp,valBuffer+valOffset,sizeof(TD_SID));
   if ( sidTemp != sid )
   {	setTestResult(TEST_FAILURE,"Wrong sid field");
    	return;
   }
   valOffset += sizeof(TD_SID);

   if ( PUS_DATA_REP_MODE?valBuffer[valOffset]!=0:false )
   {	setTestResult(TEST_FAILURE,"Wrong mode field");
    	return;
   }
   valOffset += (PUS_DATA_REP_MODE?1:0);

   memcpy(&intTemp,valBuffer+valOffset,sizeof(TD_Integer));
   if ( intTemp != (TD_Integer)val1 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);
   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp - (TD_Float)val2)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   assert(valOffset<valBufferSize);

   // Update the values in the data pool
   pDP->setValue(par1,(TD_Integer)(2*val1));
   pDP->setValue(par2,(TD_Float)(2*val2));

   // Send three update requests and check data acquisition service
   pTMP->update();
   pTMP->update();
   pTMP->update();
   for (unsigned int i=0; i<pTMP->getNumberOfBytes(); i++)
       valBuffer[i] = pTMP->getUnsignedByte(i);

   valOffset = 0;
   memcpy(&sidTemp,valBuffer+valOffset,sizeof(TD_SID));
   if ( sidTemp != sid )
   {	setTestResult(TEST_FAILURE,"Wrong sid field");
    	return;
   }
   valOffset += sizeof(TD_SID);

   if ( PUS_DATA_REP_MODE?valBuffer[valOffset]!=0:false )
   {	setTestResult(TEST_FAILURE,"Wrong mode field");
    	return;
   }
   valOffset += (PUS_DATA_REP_MODE?1:0);

   memcpy(&intTemp,valBuffer+valOffset,sizeof(TD_Integer));
   if ( intTemp != (TD_Integer)2*val1 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp - (TD_Float)2*val2)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   assert(valOffset<valBufferSize);

   // Update the values in the data pool
   pDP->setValue(par1,(TD_Integer)(3*val1));
   pDP->setValue(par2,(TD_Float)(3*val2));

   // Define a new PUS packet
   sid = 13;
   collectionInterval = 2;
   NPAR1 = 1;

   // Construct the packet
   offset = 0;
   memcpy(packet+offset,&sid,sizeof(TD_SID));
   offset += sizeof(TD_SID);
   memcpy(packet+offset,&collectionInterval,sizeof(TD_PUSCollectionInterval));
   offset += sizeof(TD_PUSCollectionInterval);
   memcpy(packet+offset,&NPAR1,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&par2,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);

   assert(offset<defPacketSize);

   // Load the packet definition
   for (unsigned short i=0; i<offset; i++)
        pTMP->setDefinitionBuffer(i,packet[i]);

   if (pTMP->getDefinitionBufferLength()!=offset)
   {	setTestResult(TEST_FAILURE,"Wrong definition buffer length");
    	return;
   }

   // Send an update request and check that there are no data to be acquired
   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }

   // Update the values of the data pool items
   pDP->setValue(par2,4*val2);

   // Send an update request and check data acquisition service
   pTMP->update();
   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE?1:0);
   n3 = sizeof(TD_Float);
   expNumberOfBytes = n1+n2+n3;
   if (pTMP->getNumberOfBytes()!=expNumberOfBytes)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }

   // Collect the packet data and check their values
   valBuffer = new unsigned char[valBufferSize];
   for (unsigned int i=0; i<pTMP->getNumberOfBytes(); i++)
       valBuffer[i] = pTMP->getUnsignedByte(i);

   valOffset = 0;
   memcpy(&sidTemp,valBuffer+valOffset,sizeof(TD_SID));
   if ( sidTemp != sid )
   {	setTestResult(TEST_FAILURE,"Wrong sid field");
    	return;
   }
   valOffset += sizeof(TD_SID);

   if ( PUS_DATA_REP_MODE?valBuffer[valOffset]!=0:false )
   {	setTestResult(TEST_FAILURE,"Wrong mode field");
    	return;
   }

   valOffset += (PUS_DATA_REP_MODE?1:0);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp - (TD_Float)4*val2)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   assert(valOffset<valBufferSize);

   // Simulate an attempt to load a larger-than-legal definition packet
   if (isNonNominalCheckAllowed()) {
        pTMP->setDefinitionBuffer(defPacketSize,0); // the maximum value of the first par is (defPacketSize-1)
        if ( !verifyLatestEvent(nEvt+1,EVT_ILLEGAL_PUS_REP_PACKET) )
            return;
        nEvt = nEvt+1;         
   }

   // Restore the original data pool
   CC_RootObject::setDataPool(pOldDP);

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}

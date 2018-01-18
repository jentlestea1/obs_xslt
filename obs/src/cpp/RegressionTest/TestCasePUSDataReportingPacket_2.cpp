//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSDataReportingPacket_2.cpp
//
// Version	1.0
// Date		04.12.03
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/DC_PUSDataReportingPacket.h"
#include "../Data/DC_SampleFullDataPool.h"
#include "../Utilities/TestCaseWithEvtCheck.h"
#include "TestCasePUSDataReportingPacket_2.h"

#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>

TestCasePUSDataReportingPacket_2::TestCasePUSDataReportingPacket_2(void) :
	TestCaseWithEvtCheck(ID_PUSDATAREPORTINGPACKET*10+2,"TestCasePUSDataReportingPacket_2") {
		return;
}

void TestCasePUSDataReportingPacket_2::runTestCase(void) {

   DC_SampleFullDataPool* pDP = new DC_SampleFullDataPool();
   unsigned int nEvt = getNumberOfEvents();
   DC_PUSDataReportingPacket* pTMP = new DC_PUSDataReportingPacket();

   // Configure and load the data pool
   pDP->setObsClock(DC_PUSDataReportingPacket::getObsClock());
   DataPool* pOldDP = CC_RootObject::getDataPool();
   CC_RootObject::setDataPool(pDP);

   // Define the PUS packet
   TD_SID sid = 12;
   TD_PUSCollectionInterval collectionInterval = 6;
   TD_PUSNumberOfParameters NPAR1 = 0;
   unsigned char NFA = 1;
   unsigned char NREP2 = 2;
   TD_PUSNumberOfParameters NPAR2 = 2;
   TD_DataPoolId par1 = 1;
   TD_Integer val1 = 11;
   TD_DataPoolId par2 = 2;
   TD_Float val2 = 12.0;

   // Construct the packet
   unsigned short defPacketSize = 50;
   unsigned char* packet = new unsigned char[defPacketSize];
   unsigned int offset = 0;
   memcpy(packet+offset,&sid,sizeof(TD_SID));
   offset += sizeof(TD_SID);
   memcpy(packet+offset,&collectionInterval,sizeof(TD_PUSCollectionInterval));
   offset += sizeof(TD_PUSCollectionInterval);
   memcpy(packet+offset,&NPAR1,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&NFA,1);
   offset += 1;
   memcpy(packet+offset,&NREP2,1);
   offset += 1;
   memcpy(packet+offset,&NPAR2,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&par1,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset,&par2,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);

   assert(offset<defPacketSize);

   // Configure the data reporting packet and check configuration status
   pTMP->setMaxNumberFA(1);
   pTMP->setDefinitionBufferSize(defPacketSize);
   unsigned int valBufferSize = 100;
   pTMP->setValueBufferSize(valBufferSize);
   pTMP->setSubType(PUS_ST_DATA_REP_PAR_HK_REP);
   pTMP->setTimeTag(0);
   pTMP->setEnabled(ENABLED);
   if ( !pTMP->isObjectConfigured() )
   {	setTestResult(TEST_FAILURE,"Wrong configuration status");
    	return;
   }

   // Load the packet definition
   for (unsigned short i=0; i<offset; i++)
        pTMP->setDefinitionBuffer(i,packet[i]);

   if (pTMP->getDefinitionBufferLength()!=offset)
   {	setTestResult(TEST_FAILURE,"Wrong definition buffer length");
    	return;
   }

   // Set the values of the data pool items
   pDP->setValue(par1,val1);
   pDP->setValue(par2,val2);

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

   // Update the values of the data pool items
   pDP->setValue(par1,(TD_Integer)(2*val1));
   pDP->setValue(par2,(TD_Float)(2*val2));

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

   // Send an update request and check data acquisition service
   pTMP->update();
   unsigned int n1, n2, n3;
   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE?1:0);
   n3 = 2*(sizeof(TD_Float)+sizeof(TD_Integer));
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

   // Update the values of the data pool items
   pDP->setValue(par1,(TD_Integer)(3*val1));
   pDP->setValue(par2,(TD_Float)(3*val2));

   // Send six update requests and check data acquisition service
   pTMP->update();
   pTMP->update();
   pTMP->update();
   pDP->setValue(par1,(TD_Integer)(4*val1));
   pDP->setValue(par2,(TD_Float)(4*val2));
   pTMP->update();
   pTMP->update();
   pTMP->update();

   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE?1:0);
   n3 = 2*(sizeof(TD_Float)+sizeof(TD_Integer));
   expNumberOfBytes = n1+n2+n3;
   if (pTMP->getNumberOfBytes()!=expNumberOfBytes)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }

   // Collect the packet data and check their values
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
   if ( intTemp != (TD_Integer)3*val1 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp - (TD_Float)3*val2)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&intTemp,valBuffer+valOffset,sizeof(TD_Integer));
   if ( intTemp != (TD_Integer)4*val1 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp - (TD_Float)4*val2)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   assert(valOffset<valBufferSize);

   // Define a new PUS packet with two FA arrays of one parameter each
   sid = 12;
   collectionInterval = 3;
   NPAR1 = 0;
   NFA = 2;
   NREP2 = 2;
   NPAR2 = 1;
   par1 = 1;
   val1 = 11;
   unsigned char NREP3 = 3;
   TD_PUSNumberOfParameters NPAR3 = 1;
   par2 = 2;
   val2 = 12.0;

   // Construct the packet
   defPacketSize = 50;
   packet = new unsigned char[defPacketSize];
   offset = 0;
   memcpy(packet+offset,&sid,sizeof(TD_SID));
   offset += sizeof(TD_SID);
   memcpy(packet+offset,&collectionInterval,sizeof(TD_PUSCollectionInterval));
   offset += sizeof(TD_PUSCollectionInterval);
   memcpy(packet+offset,&NPAR1,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&NFA,1);
   offset += 1;
   memcpy(packet+offset,&NREP2,1);
   offset += 1;
   memcpy(packet+offset,&NPAR2,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&par1,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset,&NREP3,1);
   offset += 1;
   memcpy(packet+offset,&NPAR3,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&par2,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);

   assert(offset<defPacketSize);

   // Load the packet definition
   if (isNonNominalCheckAllowed()) {
       for (unsigned short i=0; i<offset; i++)
           pTMP->setDefinitionBuffer(i,packet[i]);
       nEvt = this->getNumberOfEvents();
       if ( !verifyLatestEvent(nEvt,EVT_ILLEGAL_PUS_REP_PACKET) )
            return;
   }

   // Restore the original data pool
   CC_RootObject::setDataPool(pOldDP);

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}

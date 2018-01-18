//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSDataReportingPacket_3.cpp
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
#include "TestCasePUSDataReportingPacket_3.h"

#include <math.h>
#include <float.h>
#include <assert.h>
#include <string.h>

TestCasePUSDataReportingPacket_3::TestCasePUSDataReportingPacket_3(void) :
	TestCaseWithEvtCheck(ID_PUSDATAREPORTINGPACKET*10+3,"TestCasePUSDataReportingPacket_3") {
		return;
}

void TestCasePUSDataReportingPacket_3::runTestCase(void) {

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
   TD_PUSNumberOfParameters NPAR1 = 1;
   unsigned char NFA = 2;
   unsigned char NREP2 = 2;
   TD_PUSNumberOfParameters NPAR2 = 2;
   unsigned char NREP3 = 3;
   TD_PUSNumberOfParameters NPAR3 = 1;
   TD_DataPoolId par1 = 1;
   TD_Integer val1 = 11;
   TD_DataPoolId par2 = 2;
   TD_Float val2 = 12.0;
   TD_DataPoolId par3 = 4;
   TD_Integer val3 = 14;
   TD_DataPoolId par4 = 5;
   TD_Float val4 = 15.0;

   // Construct the packet
   unsigned short defPacketSize = 300;
   unsigned char* packet = new unsigned char[defPacketSize];
   unsigned int offset = 0;

   memcpy(packet+offset,&sid,sizeof(TD_SID));
   offset += sizeof(TD_SID);
   memcpy(packet+offset,&collectionInterval,sizeof(TD_PUSCollectionInterval));
   offset += sizeof(TD_PUSCollectionInterval);
   memcpy(packet+offset,&NPAR1,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&par1,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset,&NFA,1);
   offset += 1;
   memcpy(packet+offset,&NREP2,1);
   offset += 1;
   memcpy(packet+offset,&NPAR2,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&par2,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset,&par3,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);
   memcpy(packet+offset,&NREP3,1);
   offset += 1;
   memcpy(packet+offset,&NPAR3,sizeof(TD_PUSNumberOfParameters));
   offset += sizeof(TD_PUSNumberOfParameters);
   memcpy(packet+offset,&par4,sizeof(TD_DataPoolId));
   offset += sizeof(TD_DataPoolId);

   assert(offset<defPacketSize);

   // Configure the data reporting packet and check configuration status
   pTMP->setMaxNumberFA(2);
   pTMP->setDefinitionBufferSize(defPacketSize);
   unsigned int valBufferSize = 75;
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
   pDP->setValue(par3,val3);
   pDP->setValue(par4,val4);

   // Send five update requests and check that there are no data to be acquired
   // The data pool item values are updated after each update request
   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(2*val1));
   pDP->setValue(par2,(TD_Float)(2*val2));
   pDP->setValue(par3,(TD_Integer)(2*val3));
   pDP->setValue(par4,(TD_Float)(2*val4));

   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(3*val1));
   pDP->setValue(par2,(TD_Float)(3*val2));
   pDP->setValue(par3,(TD_Integer)(3*val3));
   pDP->setValue(par4,(TD_Float)(3*val4));

   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(4*val1));
   pDP->setValue(par2,(TD_Float)(4*val2));
   pDP->setValue(par3,(TD_Integer)(4*val3));
   pDP->setValue(par4,(TD_Float)(4*val4));

   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(5*val1));
   pDP->setValue(par2,(TD_Float)(5*val2));
   pDP->setValue(par3,(TD_Integer)(5*val3));
   pDP->setValue(par4,(TD_Float)(5*val4));

   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(6*val1));
   pDP->setValue(par2,(TD_Float)(6*val2));
   pDP->setValue(par3,(TD_Integer)(6*val3));
   pDP->setValue(par4,(TD_Float)(6*val4));

   // Send the sixth update request and check data acquisition service
   pTMP->update();
   pDP->setValue(par1,(TD_Integer)(7*val1));
   pDP->setValue(par2,(TD_Float)(7*val2));
   pDP->setValue(par3,(TD_Integer)(7*val3));
   pDP->setValue(par4,(TD_Float)(7*val4));

   unsigned int n1, n2, n3;
   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE?1:0);
   n3 = 1*sizeof(TD_Integer)+2*sizeof(TD_Float)+2*sizeof(TD_Integer)+3*sizeof(TD_Float);
   unsigned int expNumberOfBytes = n1+n2+n3;
   if (pTMP->getNumberOfBytes()!=expNumberOfBytes)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }

   // Collect the packet data and check their values
   unsigned char* valBuffer = new unsigned char[valBufferSize];
   for (unsigned int i=0; i<pTMP->getNumberOfBytes(); i++) {
       valBuffer[i] = pTMP->getUnsignedByte(i);
       assert(i<valBufferSize);
   }

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
   if ( intTemp != (TD_Integer)6*val1 )
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
   if ( intTemp != (TD_Integer)3*val3 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 3 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp - (TD_Float)6*val2)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&intTemp,valBuffer+valOffset,sizeof(TD_Integer));
   if ( intTemp  != (TD_Integer)6*val3 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 3 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp  - (TD_Float)2*val4)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp  - (TD_Float)4*val4)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp  - (TD_Float)6*val4)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 4 field");
    	return;
   }

   assert(valOffset<valBufferSize);

   // Send five update requests and check that there are no data to be acquired
   // The data pool item values are updated after each update request
   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(8*val1));
   pDP->setValue(par2,(TD_Float)(8*val2));
   pDP->setValue(par3,(TD_Integer)(8*val3));
   pDP->setValue(par4,(TD_Float)(8*val4));

   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(9*val1));
   pDP->setValue(par2,(TD_Float)(9*val2));
   pDP->setValue(par3,(TD_Integer)(9*val3));
   pDP->setValue(par4,(TD_Float)(9*val4));

   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(10*val1));
   pDP->setValue(par2,(TD_Float)(10*val2));
   pDP->setValue(par3,(TD_Integer)(10*val3));
   pDP->setValue(par4,(TD_Float)(10*val4));

   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(11*val1));
   pDP->setValue(par2,(TD_Float)(11*val2));
   pDP->setValue(par3,(TD_Integer)(11*val3));
   pDP->setValue(par4,(TD_Float)(11*val4));

   pTMP->update();
   if (pTMP->getNumberOfBytes()!=0)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }
   pDP->setValue(par1,(TD_Integer)(12*val1));
   pDP->setValue(par2,(TD_Float)(12*val2));
   pDP->setValue(par3,(TD_Integer)(12*val3));
   pDP->setValue(par4,(TD_Float)(12*val4));

   // Send the sixth update request and check data acquisition service
   pTMP->update();

   n1, n2, n3;
   n1 = sizeof(TD_SID);
   n2 = (PUS_DATA_REP_MODE?1:0);
   n3 = 1*sizeof(TD_Integer)+2*sizeof(TD_Float)+2*sizeof(TD_Integer)+3*sizeof(TD_Float);
   expNumberOfBytes = n1+n2+n3;
   if (pTMP->getNumberOfBytes()!=expNumberOfBytes)
   {	setTestResult(TEST_FAILURE,"Wrong number of bytes");
    	return;
   }

   // Collect the packet data and check their values
   for (unsigned int i=0; i<pTMP->getNumberOfBytes(); i++) {
       valBuffer[i] = pTMP->getUnsignedByte(i);
       assert(i<valBufferSize);
   }

   valOffset = 0;
   memcpy(&sidTemp,valBuffer+valOffset,sizeof(TD_SID));
   if ( memcmp(valBuffer+valOffset,&sid,sizeof(TD_SID))!=0 )
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
   if ( intTemp != (TD_Integer)12*val1 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 1 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp  - (TD_Float)9*val2)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&intTemp,valBuffer+valOffset,sizeof(TD_Integer));
   if ( intTemp != (TD_Integer)9*val3 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 3 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp  - (TD_Float)12*val2)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 2 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&intTemp,valBuffer+valOffset,sizeof(TD_Integer));
   if ( intTemp != (TD_Integer)12*val3 )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 3 field");
    	return;
   }
   valOffset += sizeof(TD_Integer);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp  - (TD_Float)8*val4)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp  - (TD_Float)10*val4)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);

   memcpy(&flTemp,valBuffer+valOffset,sizeof(TD_Float));
   if ( fabs((float)(flTemp  - (TD_Float)12*val4)) > FLT_EPSILON )
   {	setTestResult(TEST_FAILURE,"Wrong parameter 4 field");
    	return;
   }
   valOffset += sizeof(TD_Float);
   assert(valOffset<valBufferSize);

   // Construct a packet that will cause the packet value buffer to overflow
   if (isNonNominalCheckAllowed()) {
       unsigned int nIntPar = (unsigned int)(valBufferSize - sizeof(TD_SID) -
                                                (PUS_DATA_REP_MODE?1:0))/sizeof(TD_Integer)+1;
       sid = 13;
       collectionInterval = 1;
       NPAR1 = (TD_PUSNumberOfParameters)nIntPar;
       NFA = 0;
       par1 = 1;

       offset = 0;                                  // the new packet is defined
       memcpy(packet+offset,&sid,sizeof(TD_SID));
       offset += sizeof(TD_SID);
       memcpy(packet+offset,&collectionInterval,sizeof(TD_PUSCollectionInterval));
       offset += sizeof(TD_PUSCollectionInterval);
       memcpy(packet+offset,&NPAR1,sizeof(TD_PUSNumberOfParameters));
       offset += sizeof(TD_PUSNumberOfParameters);

       for (unsigned int i=0; i<NPAR1; i++) {
            memcpy(packet+offset,&par1,sizeof(TD_DataPoolId));
            offset += sizeof(TD_DataPoolId);
       }
       assert(offset<defPacketSize);

       for (unsigned short i=0; i<offset; i++)      // the new packet definition is loaded
            pTMP->setDefinitionBuffer(i,packet[i]);

       pTMP->update();

       if ( !verifyLatestEvent(nEvt+1,EVT_PUS_DATA_REP_PACKET_TOO_LARGE) )
            return;
       nEvt = nEvt+1;
   }

   // Restore the original data pool
   CC_RootObject::setDataPool(pOldDP);

   setTestResult(TEST_SUCCESS,"Test Successful");
   return;
}

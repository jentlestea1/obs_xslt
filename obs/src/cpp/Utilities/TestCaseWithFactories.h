//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseWithFactories.h
//
// Version	1.0
// Date		28.01.04
// Author	A. Pasetti
//
// Change Record:

#ifndef TestCaseWithFactoriesH
#define TestCaseWithFactoriesH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../Event/DC_EventRepository.h"
#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Base class for test cases that need to access the dynamic factories.
 * In the test set-up procedure, the dynamic factories for the
 * telemetry packets, telecommands and manouvres are initialized and
 * are loaded. The type of the items that are loaded are defined by the 
 * structure of the factories. Any change in the structure of the
 * factories should be reflected by a corresponding change in this
 * class. Test cases that need to access the dynamic factories 
 * should be constructed as subclasses of this class.
 * <p/>
 * The factory initialization and loading is only done the first time the
 * test case is executed. 
 * <p/>
 * This test case also defines a shut down procedure where all items in
 * the factories have their status set to "item not in use". This ensures
 * that all test cases that inherit from this class can start with all
 * the items in the factories being available for their use.
 * @todo Use this class as base class for test cases that use items that
 * could be provided by a dynamic factory
 * @see CC_TelemetryPacketFactory
 * @see CC_TelecommandFactory
 * @see CC_ManoeuvreFactory
 * @author A. Pasetti
 * @version 1.0
 * @ingroup TestCases
 */
class TestCaseWithFactories : public TestCaseWithEvtCheck {
 
  private:
     static bool firstActivation;

     static DC_DummyPUSTelemetryPacket* pTmDum1;
     static DC_DummyPUSTelemetryPacket* pTmDum2;
     static DC_PUSTcVerificationPacket* pTmTVP1;
     static DC_PUSDataReportingPacket* pTmDRP1;
     static DC_PUSDataReportingPacket* pTmDRP2;
     static DC_PUSMemoryDumpOffset* pTmMDO;
     static DC_PUSMemoryDumpAbsolute* pTmMDA;

     static DC_DummyConfigurableManoeuvre* pManCD;
     static DC_TestPUSConfigurableManoeuvre* pManTP;
     static DC_DummyManoeuvre* pManDum;

     static DC_DummyPUSTelecommand* pTcPDum;
     static DC_DummyTelecommand* pTcDum1;
     static DC_DummyTelecommand* pTcDum2;
     static DC_PUSControlDataReporting* pTcCDR;
     static DC_PUSDefineDataReporting* pTcDDR;
     static DC_TestPUSTelecommand* pTcTPT1;
     static DC_TestPUSTelecommand* pTcTPT2;
     static DC_TestPUSTelecommand* pTcTPT3;
     static DC_PUSDumpMemoryOffset* pTcDMO;
     static DC_PUSDumpMemoryAbsolute* pTcDMA;
     static DC_PUSMemoryLoadOffset* pTcMLO;
     static DC_PUSMemoryLoadAbsolute* pTcMLA1;
     static DC_PUSMemoryLoadAbsolute* pTcMLA2;

public:
	/**
	 * Set the identifier and the name of the test case.
	 * @param testId the test identifier
	 * @param testName the name of the test
	 */
	TestCaseWithFactories(int testId,char *testName);

	/**
	 * Call the test setup service of the super class and then initialize the
     * dynamic factories.
	 * A pseudo-code implementation of this method is as follows: <PRE>
	 *   if ( !TestCaseWithEvtCheck::setUpTestCase() )
	 *      return false;
	 *   else {
     *    if (first activation of this method) {
     *      retrieve the telemetry packet factory
	 *      create telemetry packets for the telemetry packet factory
     *      configure telemetry packets 
	 *      load telemetry packets in the telemetry packet factory
     *  
     *      retrieve the telecommand factory
	 *      create telecommand components for the telecommand factory
	 *      load telecommands in the telecommand factory
     *
     *      retrieve the manoeuvre factory
	 *      create manoeuvre components for the manoeuvre factory
	 *      load manoeuvres in the manoeuvre factory
     *
	 *      return true;
     *    }
	 *   } </PRE>
     * Note that the dynamic factories are implemented as singletons that
     * are created and initialized by simply calling their <code>getInstance</code> method.
	 */
	virtual bool setUpTestCase(void);

     /**
      * All the items loaded in the factories in the <code>setUpTestCase</code>
      * method are marked as "not in use". The change in the "in use" status is
      * performed by calling their <code>setInUse</code> method with argument
      * NOT_IN_USE. This relieves
      * concrete subclasses of the need to releases components that they have
      * retrieved from a factory at the end of the test. Note that, if a concrete
      * test case also releases the factory components by calling their <code>setInUse</code>
      * method, this does not give rise to an error.
      * 
      */
	   virtual bool shutDownTestCase(void);
};
#endif

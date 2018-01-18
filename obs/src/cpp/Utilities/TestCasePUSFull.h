//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSFull.h
//
// Version	1.0
// Date		28.01.04
// Author	A. Pasetti
//
// Change Record:

#ifndef TestCasePUSFullH
#define TestCasePUSFullH

#include "../Utilities/TestCaseWithFactories.h"
#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/TestConstants.h"

/**
 * Base class for test cases that implement a PUS-related scenario.
 * The test set-up procedure creates and configures several PUS-related components:
 * <ul>
 * <li>Telecommand loader of type <code>DC_BasicPUSTcLoader</code></li>
 * <li>Telecommand manager</li>
 * <li>Telemetry manager</li>
 * <li>PUS Telemetry mode manager of type <code>DC_PUSTelemetryModeManager</code></li>
 * <li>Logger telemetry stream of type <code>DC_PUSTmLogger</code></li>
 * <li>PUS event repository of type <code>DC_PUSEventRepository</code></li>
 * <li>Manoeuvre manager</li>
 * <li>Dummy OBS Clock of type <code>DC_DummyObsClock</code></li>
 * </ul>
 * The event repository is loaded in the <code>CC_RootObject</code>
 * which is then unloaded in the shutdown procedure. 
 * All the above items are created as static instances and are accessible 
 * through getter methods defined by this class.
 * <p>
 * This class is especially useful for test cases that want to perform end-to-end
 * tests of PUS-related functionalities (many components they require are
 * already instantiated and configured) and generally for test cases that
 * exercise PUS-related functionalities.
 * <p>
 * In order to facilitate the task of the test developers, this class offers utility
 * methods to load the telecommand load area associated to the telecommand loader
 * with data representing instances of several types of telecommand packets.
 * The telecommand packet data are loaded in the command load area associated to the
 * telecommand loader managed by this class. This class is responsible for managing the
 * command load area. It updates its first byte that holds the number of telecommand packets
 * currently stored in the command area and it maintains a <i>command area position
 * index</i> that points to the location in the command area where the next telecommand packet
 * should be written. The position index is initialized to 1 and can be reset with method 
 * <code>resetCommandLoadArea</code>. The utility methods write both the header and the
 * application data part of the telecommand packet.  In general, except for the acknowledge 
 * field (which is specified by the caller), all other information in the telecommand packet 
 * header is given fixed default values. The header is written by method <code>writeTcHeader</code>.
 * <p>
 * If there is no space left in the command load area to store the telecommand packet specified
 * by the caller of this method, then the method returns a value of false. Otherwise, the
 * telecommand is written to the command load area and a value of true is returned.
 * @author A. Pasetti
 * @version 1.0
 * @ingroup TestCases
 */
class TestCasePUSFull : public TestCaseWithFactories {
 
  private:
     static bool firstActivation;

     static CC_TelemetryManager* pTmManager;
     static DC_PUSTelemetryModeManager* pTmModeMan;
     static CC_TelecommandManager* pTcManager;
     static CC_ManoeuvreManager* pManManager;
     static DC_PUSTmLogger* pTmLogger;
     static DC_BasicPUSTcLoader* pTcLoader;
     static DC_PUSEventRepository* pEvtRep;
     static DC_DummyObsClock* pObsClock;
     static unsigned char tcCommandArea[TC_COMMAND_AREA_MAX_N_TC*TC_COMMAND_AREA_MAX_TC_LEN];
     unsigned int tcCmdPos;
     DC_EventRepository* pOldEvtRep;

  protected:
	/**
	 * Helper method that writes a default telecommand packet header to the
     * telecommand load. 
     * This method is called by the methods that write telecommands packets
     * to the telecommand load area. 
     * @param length the "packet length" field of the telecommand packet
     * @param packetSeqControl the packet sequence control field of the telecommand packet
	 */
	void writeTcHeader(unsigned short length, unsigned short packetSeqControl);

  public:
	/**
	 * Set the identifier and the name of the test case.
	 * @param testId the test identifier
	 * @param testName the name of the test
	 */
	TestCasePUSFull(int testId,char *testName);

	/**
	 * Call the test setup service of the super class and then create
     * and configure the components listed in the class comment. 
     * Component creation and configuration of some parameters is only performed the first
     * time this method is executed. Configuration parameters that can updated 
     * once are instead set at every activation. This ensures that all derived test cases
     * can rely on the same initial configuration. The values of
     * the configuration parameters are constants that are defined in file <code>TestConstants.h</code>.
     * This method also loads the PUS event repository in <code>CC_RootObject</code>.
	 */
	virtual bool setUpTestCase(void);

     /**
      * Restore the old event repository that was loaded at the time this
      * test case was started.
      * 
      */
	virtual bool shutDownTestCase(void);

     /**
      * Return the telecommand manager created by the initialization
      * procedure of this test case.
      * @return the telecommmand manager
      */
	CC_TelecommandManager* getTelecommandManager(void) const;

     /**
      * Return the telemetry manager created by the initialization
      * procedure of this test case.
      * @return the telemetry manager
      */
	CC_TelemetryManager* getTelemetryManager(void) const;

     /**
      * Return the telemetry mode manager created by the initialization
      * procedure of this test case.
      * @return the telemetry mode manager
      */
	DC_PUSTelemetryModeManager* getTelemetryModeManager(void) const;

     /**
      * Return the manoeuvre manager created by the initialization
      * procedure of this test case.
      * @return the manoeuvre manager
      */
	CC_ManoeuvreManager* getManoeuvreManager(void) const;

     /**
      * Return the telecommand loader created by the initialization
      * procedure of this test case.
      * @return the telecommand loader
      */
	DC_BasicPUSTcLoader* getTcLoader(void) const;

     /**
      * Return the telemetry stream created by the initialization
      * procedure of this test case.
      * @return the telemetry stream
      */
	DC_PUSTmLogger* getTmStream(void) const;

     /**
      * Return the OBS clock created by the initialization
      * procedure of this test case.
      * @return the OBS clock
      */
	DC_DummyObsClock* getObsClock(void) const;

     /**
      * Return the PUS Event Repository created by the initialization
      * procedure of this test case.
      * @return the PUS event repository
      */
	DC_PUSEventRepository* getEventRepository(void) const;

     /**
      * Load the <i>command load area</i> with data representing a <code>DC_TestPUSTelecommand</code> 
      * telecommand packet.
      * @see DC_TestPUSTelecommand
      * @param ackField the acknowledge field of the telecommand 
      * @param execCounter the execution counter value
      * @param execCheckVal the execution check value
      * @param valCheckVal the validity check value
      * @param execCheckCode the execution check code
      * @param valCheckCode the validity check code
      * @param execOutcome the outcome of the execution check 
      * @param packetSeqControl the packet sequence control field
      * @return true if the telecommand packet could be successfully written, false otherwise
      */
     bool writeTestPUSTelecommand(unsigned char ackField, unsigned int execCounter, bool execCheckVal,
                       bool valCheckVal, TD_CheckCode execCheckCode,
                       TD_CheckCode valCheckCode, bool execOutcome, unsigned short packetSeqControl);

     /**
      * Load the <i>command load area</i> with data representing a <code>DC_PUSDefineDataReporting</code> 
      * telecommand packet.
      * A simple instance of the telecommand is written that includes only one parameter to be 
      * sample at every collection interval.
      * @see DC_PUSDefineDataReporting
      * @param ackField the acknowledge field of the telecommand 
      * @param collectionInterval the collection interval
      * @param sid the SID of the packet being defined
      * @param par the parameter to be sampled 
      * @param packetSeqControl the packet sequence control field
      * @param tcSubType the subtype of the telecommand packet 
      * @return true if the telecommand packet could be successfully written, false otherwise
      */
     bool writePUSDefineDataReporting(unsigned char ackField, TD_PUSCollectionInterval collectionInterval, 
                                                TD_SID sid, TD_DataPoolId par, unsigned short packetSeqControl,
                                                TD_TelecommandSubType tcSubType);

     /**
      * Load the <i>command load area</i> with data representing either a <code>DC_PUSControlDataReporting</code>,
      * or a <code>DC_PUSClearDataReporting</code>, or a <code>DC_PUSRequestDataReporting</code>
      * telecommand packet.
      * The telecommand content is specified by its subtype and by an array that holds the SIDs of 
      * data reporting telecommands that must be controlled, cleared, or requested.
      * @see DC_PUSDefineDataReporting
      * @param ackField the acknowledge field of the telecommand 
      * @param NSID the number of SIDs in the telecommand
      * @param sid the array holding the SIDs
      * @param tcSubType the telecommand subtype
      * @param packetSeqControl the packet sequence control field
      * @return true if the telecommand packet could be successfully written, false otherwise
      */
     bool writePUSDataReportingControl(unsigned char ackField, unsigned char NSID, TD_SID* sid,
                                          TD_TelecommandSubType tcSubType, unsigned short packetSeqControl);

     /**
      * Clear the <i>command load area</i>. The command load area position index is reset to 
      * one and the first byte of the command load area is reset to zero.
      */
     void resetCommandLoadArea();

};
#endif

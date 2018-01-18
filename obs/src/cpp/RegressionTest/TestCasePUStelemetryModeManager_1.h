//
// Copyright 2003 P&amp;P Software GmbH (Konstanz, Germany) - All Rights Reserved
//
// TestCasePUSTelemetryModeManager_1.h
//
// Version	1.0
// Date		11.11.03
// Author	A. Pasetti (P&amp;P Software)

#ifndef TestCasePUSTelemetryModeManager_1H
#define TestCasePUSTelemetryModeManager_1H

#include "../Utilities/TestCasePUSFull.h"

/**
 * Check the functionality of the <code>DC_PUSTelemetryModeManager</code>
 * class. The test case is configured as follows:<ul>
 * <li>The telemetry packet factory is retrieved.</li>
 * <li>An instance of class <code>DC_PUSTelemetryModeManager</code> is created.</li>
 * <li>Two data reporting packet instances (instances of class
 * <code>DC_PUSDataReportingPacket</code>) are retrieved from the telemetry packet 
 * factory. The SIDs of the telemetry packets are SID_A and
 * SID_B. </li>
 * </ul>
 * The following specific tests are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the mode manager component is initially not configured.</li>
 * <li>The maximum number of packets N allowed by the mode manager is retrieved 
 * (recall that the telemetry mode manager is a 
 * singleton class whose single instance is configured in another test case)</li>
 * <li>It is checked that the mode manager component is now configured.</li>
 * <li>The two packets are loaded in the mode manager and it is checked that 
 * the number of loaded packets is correctly reported.</li>
 * <li>The SID_B packet is loaded N-2 times (N being the capacity of the 
 * telemetry mode manager) and it is checked that the component reports: 
 * "mode manager is full". </li>
 * <li>An attempt is made to load a further packet and it is checked that this
 * results in the correct event report being generated.</li>
 * <li>The iterator service is checked.</li>
 * <li>The mode manager is asked to verify whether a packet with SID other
 * than SID_A or SID_B is loaded and it is verified that the return value is: "false".</li>
 * <li>Packet SID_A is unloaded and the success of the unload operation is checked.</li>
 * <li>It is attempted to unload a non-existent packet and it is checked that 
 * the correct event is created.</li>
 * <li>The iterator service is checked again.</li>
 * <li>Packet SID_A loaded again and then packet SID_B is unloaded 
 * and the 
 * success of the load/unload operations is checked.</li>
 * <li>The iterator service is checked again.</li>
 * <li>Packet SID_B is unloaded (the mode manager should now be empty)
 * and the 
 * success of the unload operation is checked.</li>
 * <li>The iterator service is checked again.</li>
 * </ol>
 * Note that this test case uses the telemetry packet factory. It assumes that the structure
 * of the factory is such as to allow two packets of type <code>DC_PUSDataReportingPacket</code>
 * to be loaded in the factory.
 * @see DC_PUSTelemetryModeManager
 * @see CC_TelemetryPacketFactory
 * @author Alessandro Pasetti (P&amp;P Software GmbH)
 * @version 1.0
 */
class TestCasePUSTelemetryModeManager_1 : public TestCasePUSFull {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_PUSTELEMETRYMODEMANAGER*10+1 and "TestCasePUSTelemetryModeManager_1".
      */
     TestCasePUSTelemetryModeManager_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif

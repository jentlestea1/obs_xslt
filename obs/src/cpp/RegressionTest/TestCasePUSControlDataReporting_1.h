//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSControlDataReporting_1.h
//
// Version	1.0
// Date		11.11.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCasePUSControlDataReporting_1H
#define TestCasePUSControlDataReporting_1H

#include "../Utilities/TestCaseWithFactories.h"

/**
 * Check the functionality of the <code>DC_PUSControlDataReporting</code>
 * class under nominal conditions. The test case is configured as follows:<ul>
 * <li>The telemetry packet factory is retrieved.</li>
 * <li>Two data reporting packet instances are created and loaded
 * in the packet factory. The SIDs of the telemetry packets are SID_A and
 * SID_B. </li>
 * <li>One telecommand instance of type <code>DC_PUSControlDataReporting</code> is created.</li>
 * </ul>
 * The following specific tests are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the telecommand component is initially not configured.</li>
 * <li>The maximum number of SIDs in the telecommand component is set to 2 and the correctness of the
 * set operation is checked.</li>
 * <li>It is checked that the component is now configured.</li>
 * <li>The telecommand is loaded with raw data representing a request to enable the
 * telemetry packet with SID equal to SID_A. It is checked that the validity check of the
 * telecommand returns: "telecommand is valid".</li>
 * <li>The telecommand is executed and it is checked that telemetry packet SID_A has been
 * enabled and that the outcome code of the telecommand is ACTION_SUCCESS.</li>
 * <li>The telecommand is loaded with new raw data representing a request to disable the
 * telemetry packet with SID equal to SID_A. It is checked that the validity check of the
 * telecommand returns: "telecommand is valid".</li>
 * <li>The telecommand is executed and it is checked that telemetry packet SID_A has been
 * disabled and that the outcome code of the telecommand is ACTION_SUCCESS.</li>
 * <li>The telecommand is loaded with raw data representing a request to enable the
 * telemetry packets with SID equal to SID_A and SID_B. It is checked that the validity check of the
 * telecommand returns: "telecommand is valid" and the correct validity check code is returned.</li>
 * <li>The telecommand is executed and it is checked that both telemetry packets are 
 * enabled and that the outcome code of the telecommand is ACTION_SUCCESS.</li>
 * <li>Non-nominal behaviour check: the telecommand is loaded with raw data representing a request to enable three
 * telemetry packets. It is checked that the validity check of the
 * telecommand returns: "telecommand is not valid" and the correct validity check code is returned.</li>
 * <li>Non-nominal behaviour check: the telecommand is loaded with too many raw data 
 * and it is checked that the validity check of the
 * telecommand returns: "telecommand is valid". </li>
 * <li>Non-nominal behaviour check: the telecommand is loaded with inconsistent raw data 
 * and it is checked that the validity check of the
 * telecommand returns: "telecommand is valid". </li>
 * <li>The telecommand is loaded with raw data representing a request to enable two
 * telemetry packets with SID equal to SID_A and a non-existent SID. It is checked that the validity check of the
 * telecommand returns: "telecommand is valid".</li>
 * <li>The telecommand is executed and it is checked that the outcome code of the 
 * telecommand is ACTION_FAILURE.</li>
 * </ol>
 * Note that this test case uses the telemetry packet factory. It assumes that the structure
 * of the factory is such as to allow two packets of type <code>DC_PUSDataReportingPacket</code>
 * to be loaded in the factory.
 * @see DC_PUSControlDataReporting
 * @see CC_TelemetryPacketFactory
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCasePUSControlDataReporting_1 : public TestCaseWithFactories {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_PUSCONTROLDATAREPORTING*10+1 and "TestCasePUSControlDataReporting_1".
      */
     TestCasePUSControlDataReporting_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif

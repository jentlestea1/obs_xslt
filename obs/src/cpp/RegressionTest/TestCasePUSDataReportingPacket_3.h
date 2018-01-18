//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSDataReportingPacket_3.h
//
// Version	1.0
// Date		11.12.03
// Author	A. Pasetti (P&P Software)

#ifndef TestCasePUSDataReportingPacket_3H
#define TestCasePUSDataReportingPacket_3H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check the functionality of the <code>DC_PUSDataReportingPacket</code>
 * class for the case of a packet that contains one set of parameters
 * sampled once per collection interval and two fixed-length
 * arrays of oversampled parameters. The test starts with the creation
 * of one data pool to serve as the source of the data to be collected.
 * This data pool is loaded into <code>CC_RootObject</code> as <i>system
 * data pool</i>.
 * Then, a data reporting packet instance is created and configured to
 * have a collection interval equal to 6, one parameter to be sampled once
 * per collection interval, one fixed-length array with
 * two parameters and repetition count equal to 2 (ie. two samples per
 * collection interval), and one fixed-length array with one parameter
 * and repetition count equal to 3.The data reporting packet is configured and
 * enabled and the following
 * specific checks are performed upon it:<ol>
 * <li>Five consecutive update requests are sent to the packet. Each is followed
 * by a data acquisition request. It is checked that in all cases, the data acquisition
 * service reports: "no telemetry data". </li>
 * <li>A sixth update request is executed followed by a data acquisition request.
 * The correctness of the data returned by the data acqusition service
 * is checked.</li>
 * <li>A new set of six update-acquisition requests is performed. The correctness
 * of the data returned by the data acqusition service
 * is then checked.</li>
 * <li>Non-nominal behaviour check: it is attempted to load a packet definition that will
 * cause the packet value buffer to overflow and it is checked
 * that the correct event is generated.</li>
 * </ol>
 * This test case uses the <code>DC_SampleFullDataPool</code> as system data pool. The
 * implementation of the test case assumes the following about this data pool:<ul>
 * <li>The data pool contains at least four data pool items with identifiers 1 and 2.</li>
 * <li>The data pool item with identifier equal to 1 is of type <code>TD_Integer</code>.</li>
 * <li>The data pool item with identifier equal to 2 is of type <code>TD_Float</code>.</li>
 * <li>The data pool item with identifier equal to 4 is of type <code>TD_Integer</code>.</li>
 * <li>The data pool item with identifier equal to 5 is of type <code>TD_Float</code>.</li>
 * </ul>
 * @see DC_PUSDataReportingPacket
 * @see DC_SampleFullDataPool
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCasePUSDataReportingPacket_3 : public TestCaseWithEvtCheck {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_PUSDATAREPORTINGPACKET*10+3 and "TestCasePUSDataReportingPacket_3".
      */
     TestCasePUSDataReportingPacket_3(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif

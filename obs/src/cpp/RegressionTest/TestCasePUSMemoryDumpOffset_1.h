//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSMemoryDumpOffset_1.h
//
// Version	1.0
// Date		11.02.04
// Author	A. Pasetti (P&P Software)

#ifndef TestCasePUSMemoryDumpOffset_1H
#define TestCasePUSMemoryDumpOffset_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check the functionality of the <code>DC_PUSMemoryDumpOffset</code>
 * class. 
 * One telecommand instance of type <code>DC_PUSMemoryDumpOffset</code> is 
 * created and the following specific tests are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>The correctness of the type and subtype is checked.</li>
 * <li>It is checked that the telemetry packet component is initially not configured.</li>
 * <li>The maximum number of blocks in the telemetry packet component is set and 
 * the correctness of the
 * set operation is checked.</li>
 * <li>The size of the dump buffer is set and 
 * the correctness of the
 * set operation is checked.</li>
 * <li>It is checked that the component is now configured.</li>
 * <li>The base address is set and the correctness of the
 * set operation is checked.</li>
 * <li>The memory block identifier is set and the correctness of the
 * set operation is checked.</li>
 * <li>It is checked that the checksum flag is initially set to "false".</li>
 * <li>The memory dump blocks are defined and the correctness of the configuration operation
 * is checked.</li>
 * <li>It is checked that the fast acquisition service is available.</li>
 * <li>A data update operation is performed and is followed by a data acquisition operation.
 * The correctness of the acquired data is checked.</li>
 * <li>The number of bytes in the telemetry packet is read out and the correctness of the
 * read-out value is checked.</li>
 * <li>The checksum flag is changed to "true" (checksum field required) and the correctness of the
 * operation is checked.</li>
 * <li>One memory dump block is defined, a data update and a data acquisition are performed, 
 * and the correctness of the memory dump data (including the checksum filed) is checked.</li>
 * <li>Non-nominal behaviour check: an attempt is made to load too many memory blocks and
 * it is checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an attempt is made to configure a non-existent block
 * and it is checked that the correct event is generated.</li>
 * <li>Non-nominal behaviour check: an attempt is made to dump a set of blocks that overflow
 * the <i>dump buffer</i>
 * and it is checked that the correct event is generated.</li>
 * </ol>
 * @see DC_PUSMemoryLoadOffset
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCasePUSMemoryDumpOffset_1 : public TestCaseWithEvtCheck {

  public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_PUSMEMORYDUMPOFFSET*10+1 and "TestCasePUSMemoryDumpOffset_1".
      */
     TestCasePUSMemoryDumpOffset_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif

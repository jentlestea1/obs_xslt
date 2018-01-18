//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSMemoryLoadOffset_1.h
//
// Version	1.0
// Date		11.02.04
// Author	A. Pasetti (P&P Software)

#ifndef TestCasePUSMemoryLoadOffset_1H
#define TestCasePUSMemoryLoadOffset_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check the functionality of the <code>DC_PUSMemoryLoadOffset</code>
 * class for the case where no checksum checks are performed. 
 * One telecommand instance of type <code>DC_PUSMemoryLoadOffset</code> is 
 * created and the following specific tests are then performed:<ol>
 * <li>The correctness of the class identifier is checked.</li>
 * <li>It is checked that the telecommand component is initially not configured.</li>
 * <li>The maximum number of blocks in the telecommand component is set to 3 and 
 * the correctness of the
 * set operation is checked.</li>
 * <li>The maximum number of data in the telecommand component is set to 10 and 
 * the correctness of the
 * set operation is checked.</li>
 * <li>It is checked that the component is now configured.</li>
 * <li>The telecommand is loaded with raw data representing a memory load for one block
 * with two data. It is checked that the validity check of the
 * telecommand returns: "telecommand is valid".</li>
 * <li>The telecommand is executed and it is checked that the outcome code of 
 * the telecommand is ACTION_SUCCESS and that the memory load is correctly executed.</li>
 * <li>The telecommand is loaded with raw data representing a memory load for three blocks
 * with three data each. It is checked that the validity check of the
 * telecommand returns: "telecommand is valid".</li>
 * <li>The telecommand is executed and it is checked that the outcome code of 
 * the telecommand is ACTION_SUCCESS and that the memory load is correctly executed.</li>
 * <li>The telecommand is loaded with raw data representing a memory load for four blocks.
 * It is checked that the validity check of the
 * telecommand returns: "telecommand is not valid" and that the validity code is correct.</li>
 * <li>The telecommand is loaded with raw data representing a memory load for two blocks
 * with two data (first block) and nine data (second block).
 * It is checked that the validity check of the
 * telecommand returns: "telecommand is not valid" and that the validity code is correct.</li>
 * <li>The telecommand raw data service is called with an invalid number of bytes to 
 * be transfered.
 * It is checked that the validity check of the
 * telecommand returns: "telecommand is not valid" and that the validity code is correct.</li>
 * <li>The telecommand raw data service is called with an inconsistent number of bytes to 
 * be transfered.
 * It is checked that the validity check of the
 * telecommand returns: "telecommand is not valid" and that the validity code is correct.</li>
 * </ol>
 * @see DC_PUSMemoryLoadOffset
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCasePUSMemoryLoadOffset_1 : public TestCaseWithEvtCheck {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_PUSMEMORYLOADOFFSET*10+1 and "TestCasePUSMemoryLoadOffset_1".
      */
     TestCasePUSMemoryLoadOffset_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif

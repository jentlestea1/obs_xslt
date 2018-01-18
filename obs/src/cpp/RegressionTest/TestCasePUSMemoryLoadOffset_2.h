//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCasePUSMemoryLoadOffset_2.h
//
// Version	1.0
// Date		11.02.04
// Author	A. Pasetti (P&P Software)

#ifndef TestCasePUSMemoryLoadOffset_2H
#define TestCasePUSMemoryLoadOffset_2H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check the checksum-related functionalities of the <code>DC_PUSMemoryLoadOffset</code>
 * class. 
 * One telecommand instance of type <code>DC_PUSMemoryLoadOffset</code> is 
 * created. The image of a telecommand packet consisting of one block with four data 
 * is set up. The following specific tests are then performed:<ol>
 * <li>The telecommand is loaded with a valid checksum and it is then executed. It is 
 * checked that the outcome code of 
 * the telecommand is ACTION_SUCCESS and that the memory load is correctly executed.</li>
 * <li>The telecommand is loaded with a invalid checksum and it is then executed. It is 
 * checked that the correctness of the outcome code and that the memory load is 
 * not performed.</li>
 * </ol>
 * This test case assumes the type <code>TD_PUSMemData</code> to be defined as
 * <code>unsigned char</code>.
 * @see DC_PUSMemoryLoadOffset
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCasePUSMemoryLoadOffset_2 : public TestCaseWithEvtCheck {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_PUSMEMORYLOADOFFSET*10+2 and "TestCasePUSMemoryLoadOffset_2".
      */
     TestCasePUSMemoryLoadOffset_2(void);

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase(void);
};

#endif

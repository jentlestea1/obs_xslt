//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseDataItem16TmWord_1.h
//
// Version	1.1
// Date		08.12.02 (Version 1.0)
//          04.03.03 (Version 1.1)
// Author	A. Pasetti (P&P Software)
//
// Change Record:
//   Version 1.1: comment update

#ifndef TestCaseDataItem16TmWord_1H
#define TestCaseDataItem16TmWord_1H

#include "../Utilities/TestCaseGenericSetUp.h"

/**
 * Verify the structured telemetry packet services as implemented
 * by class <code>DC_DataItem16TmWord</code>.
 * An instance of this class is created and the following specific
 * tests are performed: <ol>
 * <li>The correctness of the class identifier is verified.</li>
 * <li>It is verified that the configuration check service of the object
 * initially reports "object not configured".</li>
 * <li>A data item object is loaded into the <code>DC_DataItem16TmWord</code>
 * and it is verified that the configuration check service now reports
 * "object configured".</li>
 * <li>It is verified that the <code>getNumberOfBytes</code> on
 * <code>DC_DataItem16TmWord</code> reports the correct result.</li>
 * <li>It is verified that the <i>validity service</i> on
 * <code>DC_DataItem16TmWord</code> reports "data valid".</li>
 * <li>An <i>update request</i> is made to the <code>DC_DataItem16TmWord</code>.
 * This is followed by a <i>data acquisition request</i>. This is implemented
 * first through the <code>getUnsignedShort</code> and then through the
 * <code>getUnsignedByte</code> services and it is verified that in
 * both cases the correct values are returned.</li>
 * </ol>
 * @see DC_DataItem16TmWord
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.1
 */
class TestCaseDataItem16TmWord_1 : public TestCaseGenericSetUp {

public :

     /**
      * Set the identifier and the name of the test case to, respectively,
      * ID_DATAITEM16TMWORD*10+1 and "TestCaseDataItem16TmWord_1".
      */
     TestCaseDataItem16TmWord_1(void);

     /**
      * Execute the test case. See class comment for details.
      */
      virtual void runTestCase(void);
};

#endif

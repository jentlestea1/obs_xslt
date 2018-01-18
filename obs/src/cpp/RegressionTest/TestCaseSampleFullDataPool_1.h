  
  
//
// Copyright 2003 P&P Software GmbH - All Rights Reserved
//
// TestCaseSampleFullDataPool_1.h
//
// This is an automatically generated file

#ifndef TestCaseSampleFullDataPool_1H
#define TestCaseSampleFullDataPool_1H

#include "../Utilities/TestCaseWithEvtCheck.h"

/**
 * Check the functionalities implemented by the
 * <code>DC_SampleFullDataPool</code> component.
 * An instance of the component is created and the following
 * specific checks are performed upon it: <ol>
 * <li>It is verified that the class ID of the component has the correct value.</li> 
 * <li>It is verified that, after instantiation, the configuration service
 * of the component reports "not configured".</li>
 * <li>The data pool is configured and it is verified that the configuration service
 * reports "configured".</li> 
 * <li>It is verified that the default value of the validity status is "valid".</li>
 * <li>A float value is set and then read and it is verified that the value that is read
 * back is the same as the value that was written.</li>
 * <li>An integer value is set and then read and it is verified that the value that is read
 * back is the same as the value that was written.</li>
 * <li>A float value is set and then its pointer is read and it is verified that the value that
 * was written can be correctly read from the pointer.</li>
 * <li>An integer value is set and then its pointer is read and it is verified that the value that
 * was written can be correctly read from the pointer.</li> 
 * <li>An OBS Clock is loaded into the data pool and the correctness of the load operation
 * is checked.</li> 
 * <li>The time stamp of a newly set data pool item is checked.</li> 
 * <li>The validity status of a data pool item is changed and it is checked that this
 * change is reflected in the validity status read back from the data pool.</li> 
 * <li>Non-nominal behaviour check: an attempt is made to set the validity status of a 
 * non-existent data pool item and it is checked that the correct event is generated.</li> 
 * <li>A call to method <code>reset</code> is performed and it is verified that 
 * a validity status previously set to "not valid" is reset to "valid".</li> 
 * <li>The validity status of a data pool item is switched to "not valid", its value is set and
 * then read back and it is verified that the value that is read back is the "back up value" (i.e. the
 * value of the data pool item before its validity status was changed. 
 * The data pool item value is read back both through the value getter method and through the
 * data item associated to the data pool item. </li> 
 * <li>The validity status of the data pool item is switched back to "valid", its value is set and
 * then read back and it is verified that the value that is read back is the "primary value" (i.e. the
 * last value of the data pool item to be set with the setter method.</li> 
 * The data pool item value is read back both through the value getter method and through the
 * data item associated to the data pool item. </li> 
 * <li>The type checking service is checked both for real-valued and for integer-valued
 * data pool items.</li> 
 * <li>A monitoring profile attribute is set and then read back and it is checked that the read-back
 * value is correct.</li> 
 * <li>A recovery action attribute is set and then read back and it is checked that the read-back
 * value is correct.</li> 
 * <li>Non-nominal behaviour check: it is checked that a call to a setter method with an illegal
 * data pool item identifier results in the generation of an "illegal datapool access" event 
 * report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a setter method with an illegal
 * data pool item type results in the generation of an "illegal datapool access" event 
 * report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a pointer getter method with an illegal
 * parameter identifier results in the generation of an "illegal data pool access" event 
 * report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a pointer getter method with an illegal
 * parameter type results in the generation of an "illegal data pool access" event 
 * report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a setter method for a
 * monitoring profile with an illegal parameter identifier results in the generation of an 
 * "illegal data pool access" event report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a setter method for a
 * recovery action with an illegal parameter identifier results in the generation of an 
 * "illegal data pool access" event report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a type checking method with an illegal
 * parameter identifier results in the generation of "illegal data pool access" event 
 * report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a getter method with an illegal
 * parameter identifier results in the generation of "illegal data pool access" event 
 * report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a data item getter method with an 
 * illegal parameter identifier results in the generation of an "illegal data pool access" event 
 * report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a time stamp getter method with an 
 * illegal parameter identifier results in the generation of an "illegal data pool access" event 
 * report. </li>
 * <li>Non-nominal behaviour check: it is checked that a call to a validity status getter method with an 
 * illegal parameter identifier results in the generation of an "illegal data pool access" event 
 * report. </li>
 * </ol>
 * The code for this test class - like the code for the component it checks -
 * is automatically generated by an XSLT program. The XSLT program takes as an input an
 * XML file (the 'Data Pool Descriptor File') that describes the structure
 * of the data pool in the component being tested.
 * @see DC_SampleFullDataPool
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class TestCaseSampleFullDataPool_1 : public TestCaseWithEvtCheck {

  public :

     /**
      * Set the identifier and the name of the test case to: 
      * ID_SAMPLEFULLDATAPOOL*10+1 and "TestCaseSampleFullDataPool_1".
      */
     TestCaseSampleFullDataPool_1();

     /**
      * Execute the test case. See class comment for details.
      */
     virtual void runTestCase();
};

#endif

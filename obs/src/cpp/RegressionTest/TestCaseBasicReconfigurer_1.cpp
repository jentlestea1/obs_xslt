//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TestCaseBasicReconfigurer_1.cpp
//
// Version	1.0
// Date		04.06.03
// Author	R. Totaro

#include "TestCaseBasicReconfigurer_1.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Base/DC_BasicReconfigurer.h"

TestCaseBasicReconfigurer_1::TestCaseBasicReconfigurer_1(void) :
	TestCaseWithEvtCheck(ID_BASICRECONFIGURER*10+1,"TestCaseBasicReconfigurer_1") {
	return;
}

void TestCaseBasicReconfigurer_1::runTestCase(void) {
	const TD_Config       nConf=16;
    unsigned int          nEvt =getNumberOfEvents();
	DC_BasicReconfigurer *pBR  =new DC_BasicReconfigurer();

	// Verify correctness of the class identifier
	if (pBR->getClassId()!=ID_BASICRECONFIGURER) {
		setTestResult(TEST_FAILURE,"Wrong class identifier");
		return;
	}

	// A newly created reconfigurer shall not be configured...
	if (pBR->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Newly created reconfigurer is configured");
		return;
	}

	// ...but it should be enabled!
	if (!pBR->isEnabled()) {
		setTestResult(TEST_FAILURE,"Newly created reconfigurer is not enabled");
		return;
	}

	// Let's see if we can change the enable status
	pBR->setEnabled(false);
	if (pBR->isEnabled()) {
		setTestResult(TEST_FAILURE,"Can't chenge enable status");
		return;
	}

	// We now set the number of possible configurations
	pBR->setNumberOfConfigurations(nConf);

	// The reconfigurer should now be configured
	if (!pBR->isObjectConfigured()) {
		setTestResult(TEST_FAILURE,"Reconfigurer not configured");
		return;
	}

	// Let's verify that the number of configuration is properly set,
	// that all the newly created configurations are healthy, and that
	// the active configuration is set to 0.
	if (pBR->getNumberOfConfigurations()!=nConf) {
		setTestResult(TEST_FAILURE,"Wrong number of configurations");
		return;
	}

	for (TD_Config i=0;i<nConf;i++) {
		if (!pBR->isConfigurationHealthy(i)) {
			setTestResult(TEST_FAILURE,"Unexpected unhealthy configuration found");
			return;
		}
	}

	if (pBR->getActive()!=0) {
		setTestResult(TEST_FAILURE,"Wrong active configuration");
		return;
	}

	// We now test DC_BasicReconfigurer::setActive().
	// First we try to set an out-of-range configuration
	// and verify the event reporting.
    if (isNonNominalCheckAllowed()) {
	    pBR->setActive(nConf);
        if (!verifyLatestEvent(nEvt+1,EVT_ILLEGAL_CONFIG))
		    return;
        nEvt++;
    }

	// Now we set the active configuration to a legal one and
	// verify the correctness of the active configuration value
	// and, once again, the event reporting.
	pBR->setActive(nConf-1);

	if (pBR->getActive()!=nConf-1) {
		setTestResult(TEST_FAILURE,"Wrong active configuration");
		return;
	}

	if (!verifyLatestEvent(nEvt+1,EVT_RECONFIG))
		return;
    nEvt++;

	// We now test DC_BasicReconfigurer::setHealthStatus().
	// Once again, we start by verify the error reporting, then
	// we check the nominal functionality.
    if (isNonNominalCheckAllowed()) {
    	pBR->setHealthStatus(nConf,NOT_HEALTHY);
        if (!verifyLatestEvent(nEvt+1,EVT_ILLEGAL_CONFIG))
            return;
        nEvt++;
    }

	pBR->setHealthStatus(0,NOT_HEALTHY);
	if (pBR->isConfigurationHealthy(0)) {
		setTestResult(TEST_FAILURE,"Wrong configuration health status");
		return;
	}

	// We call reconfigure(). The call should fail (the reconfigurer
	// is still disabled).
	pBR->reconfigure();
	if (!verifyLatestEvent(nEvt+1,EVT_RECONFIG_DISABLED))
		return;
    nEvt++;

	// We now enable it and try again. We also verify that the old
	// active configuration is set to NOT_HEALTHY and that the new
	// one is HEALTHY.
	pBR->setEnabled(true);
	pBR->reconfigure();

	if (!verifyLatestEvent(nEvt+1,EVT_RECONFIG))
		return;
    nEvt++;

	if (pBR->isConfigurationHealthy(nConf-1)) {
		setTestResult(TEST_FAILURE,"Wrong configuration health status");
		return;
	}

	if (!pBR->isConfigurationHealthy(pBR->getActive())) {
		setTestResult(TEST_FAILURE,"Unhealthy active configuration");
		return;
	}

	// Let's set all the configurations to NOT_HEALTHY and verify that
	// reconfigure properly reports the error
	for (TD_Config i=0;i<nConf;i++)
		pBR->setHealthStatus(i,NOT_HEALTHY);

	pBR->reconfigure();

	if (!verifyLatestEvent(nEvt+1,EVT_RECONFIG_NO_HEALTHY))
		return;
    nEvt++;

	// We now verify the behaviour of DC_BasicReconfigurer::reset().
	// The reconfigurer is disabled and reset() is called.
	pBR->setEnabled(false);
	pBR->reset();

	// All the configurations should now be healhty, the active should be
	// the first and the reconfigurer should be enabled.
	if (!pBR->isEnabled()) {
		setTestResult(TEST_FAILURE,"Reset failed to enable reconfigurer");
		return;
	}

	if (pBR->getActive()!=0) {
		setTestResult(TEST_FAILURE,"Reset failed to set active configuration");
		return;
	}

	for (TD_Config i=0;i<nConf;i++) {
		if (!pBR->isConfigurationHealthy(i)) {
			setTestResult(TEST_FAILURE,"Reset failed to set the configuration status");
			return;
		}
	}

	setTestResult(TEST_SUCCESS,"Test Successful");
	return;
}

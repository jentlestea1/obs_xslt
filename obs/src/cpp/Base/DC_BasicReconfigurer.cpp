//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicReconfigurer.cpp
//
// Version	1.0
// Date		13.05.03 (Version 1.1)
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "DC_BasicReconfigurer.h"

DC_BasicReconfigurer::DC_BasicReconfigurer(void) {
   setClassId(ID_BASICRECONFIGURER);
   numberOfConfig = 0;
   active = 0;
   enableStatus = ENABLED;
   isHealthy = pNULL;
}

void DC_BasicReconfigurer::setActive(TD_Config activeConfig) {
	assert( isObjectConfigured() );
    assert( activeConfig < numberOfConfig);

	if ( activeConfig >= numberOfConfig ) {
		CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CONFIG);
	} else if ( active != activeConfig ) {
		active = activeConfig;
		CC_RootObject::getEventRepository()->create(this,EVT_RECONFIG);
	}
}

void DC_BasicReconfigurer::reconfigure(void) {
	assert( isObjectConfigured() );

	if ( isEnabled() ) {
		for (TD_Config i=0; i<numberOfConfig; i++) {
			if ( (i!=active) && (isConfigurationHealthy(i)) ) {
				setHealthStatus(active,NOT_HEALTHY);
				active = i;
				CC_RootObject::getEventRepository()->create(this,EVT_RECONFIG);
				return;
			}
		}

		CC_RootObject::getEventRepository()->create(this,EVT_RECONFIG_NO_HEALTHY);
	}
	else
		CC_RootObject::getEventRepository()->create(this,EVT_RECONFIG_DISABLED);
}

void DC_BasicReconfigurer::setNumberOfConfigurations(TD_Config nOfConfig) {
   assert(numberOfConfig == 0);  // should be called only once
   assert(nOfConfig > 0);

   numberOfConfig = nOfConfig;
   isHealthy = new bool[numberOfConfig];

   active = 0;
   for (TD_Config i=0; i<numberOfConfig; i++)
       isHealthy[i] = HEALTHY;
}

void DC_BasicReconfigurer::setHealthStatus(TD_Config i, bool healthStatus) {
	assert( isObjectConfigured() );
    assert( i<numberOfConfig );

	if ( i<numberOfConfig )
		isHealthy[i] = healthStatus;
	else
		CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CONFIG);
}

bool DC_BasicReconfigurer::isConfigurationHealthy(TD_Config i) const {
    assert( isHealthy!=pNULL );
    assert( i<numberOfConfig );

    return isHealthy[i];
}

void DC_BasicReconfigurer::setEnabled(bool enabled) {
    enableStatus = enabled;
}

bool DC_BasicReconfigurer::isEnabled(void) const {
    return enableStatus;
}

TD_Config DC_BasicReconfigurer::getActive(void) const {
    return active;
}

TD_Config DC_BasicReconfigurer::getNumberOfConfigurations(void) const {
    return numberOfConfig;
}

void DC_BasicReconfigurer::reset(void) {
    assert( isObjectConfigured() );

    active = 0;
    enableStatus = ENABLED;
    for (TD_Config i=0; i<numberOfConfig; i++)
        isHealthy[i] = HEALTHY;
}

bool DC_BasicReconfigurer::isObjectConfigured(void) {
   return (CC_RootObject::isObjectConfigured() && numberOfConfig>0);
}


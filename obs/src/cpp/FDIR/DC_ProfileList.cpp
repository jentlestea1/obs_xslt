//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ProfileList.cpp
//
// Version	1.3
// Date		15.08.03 (Version 1.0)
//          01.10.03 (Version 1.1)
//          08.10.03 (Version 1.2)
//          21.10.03 (Version 1.3)
// Author	R. Totaro
//
// Change Record:
//   Version 1.1: Replaced double and int with TD_Float and TD_Integer
//   Version 1.2: Fixed isObjectConfigured() it did not check that all the
//                profiles were loaded.
//   Version 1.3: loadMonitoringProfile() renamed setMonitoringProfile()

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "DC_ProfileList.h"

DC_ProfileList::DC_ProfileList(void) {
	setClassId(ID_PROFILELIST);
	listSize=0;
	pList=pNULL;
}

void DC_ProfileList::setListSize(unsigned int listSize) {
    assert(this->listSize==0 && listSize!=0);

    this->listSize=listSize;
    pList=new MonitoringProfile*[listSize];

    for (unsigned int i=0;i<listSize;i++)
        pList[i]=pNULL;
}

unsigned int DC_ProfileList::getListSize(void) const {
	return listSize;
}

void DC_ProfileList::setMonitoringProfile(unsigned int i,MonitoringProfile *item) {
    // Note that, being i unsigned, if i<listSize, then listSize must be >0!
	assert(i<listSize && item!=pNULL);

	if (i<listSize)
		pList[i]=item;
	else
		CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_MP);
}

MonitoringProfile *DC_ProfileList::getMonitoringProfile(unsigned int i) const {
    // Note that, being i unsigned, if i<listSize, then listSize must be >0!
	assert(i<listSize);

    return pList[i];
}

bool DC_ProfileList::doProfileCheck(TD_Integer value) {
	assert(isObjectConfigured());

	bool retVal=false;

	for (unsigned int i=0;i<listSize;i++) {
		if (pList[i]->deviatesFromProfile(value))
			retVal=true;
	}

	return retVal;
}

bool DC_ProfileList::doProfileCheck(TD_Float value) {
	assert(isObjectConfigured());

	bool retVal=false;

	for (unsigned int i=0;i<listSize;i++) {
		if (pList[i]->deviatesFromProfile(value))
			retVal=true;
	}

	return retVal;
}

bool DC_ProfileList::isObjectConfigured(void) {
    if (!MonitoringProfile::isObjectConfigured() || listSize==0)
        return NOT_CONFIGURED;

    for (unsigned int i=0;i<listSize;i++) {
        if (pList[i]==pNULL)
            return NOT_CONFIGURED;
    }

    return CONFIGURED;
}

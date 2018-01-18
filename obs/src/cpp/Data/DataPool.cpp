//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DataPool.cpp
//
// Version	1.0
// Date		10.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../FDIR/DC_NullProfile.h"
#include "../FDIR/DC_NullRecoveryAction.h"
#include "DC_DataItem.h"
#include "DataPool.h"

DataPool::DataPool(void) {
    dummyInt = 0;
    pNullRecoveryAction = new DC_NullRecoveryAction();
    pNullProfile = new DC_NullProfile();
    pDummyDataItem = new DC_DataItem(&dummyInt);
}

DC_DataItem* DataPool::getDataItem(TD_DataPoolId id) {
    return pDummyDataItem;
}

TD_ObsTime DataPool::getTimeStamp(TD_DataPoolId id) {
   return (TD_ObsTime)0;
}

bool DataPool::isValid(TD_DataPoolId id) {
    return true;
}

void DataPool::setValidityStatus(TD_DataPoolId id, bool newValidityStatus) {
    return;
}

MonitoringProfile* DataPool::getMonitoringProfile(TD_DataPoolId id) {
    return pNullProfile;
}

RecoveryAction* DataPool::getRecoveryAction(TD_DataPoolId id) {
    return pNullRecoveryAction;
}

TD_DataPoolId DataPool::firstIdentifier(void) {
    return 0;
}

TD_DataPoolId DataPool::nextIdentifier(void) {
    return 0;
}

bool DataPool::isLastIdentifier(void) {
    return true;
}

bool DataPool::isFloat(TD_DataPoolId id) {
    return true;
}

bool DataPool::isInteger(TD_DataPoolId id) {
    return true;
}

void DataPool::reset(void) {
    return;
}

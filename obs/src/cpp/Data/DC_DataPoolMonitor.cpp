//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DataPoolMonitor.cpp
//
// Version	1.0
// Date		11.10.03
// Author	R. Totaro

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../FDIR/MonitoringProfile.h"
#include "../FDIR/RecoveryAction.h"
#include "DataPool.h"
#include "DC_DataPoolMonitor.h"

DC_DataPoolMonitor::DC_DataPoolMonitor(void) {
    setClassId(ID_DATAPOOLMONITOR);
}

bool DC_DataPoolMonitor::canExecute(void) {
    return true;
}

TD_ActionOutcome DC_DataPoolMonitor::doConditionalAction(void) {
    assert(isObjectConfigured());

    DataPool     *pDataPool=getDataPool();
    TD_DataPoolId i        =pDataPool->firstIdentifier();

    do {
        MonitoringProfile *pMP    =pDataPool->getMonitoringProfile(i);
        bool               invalid=(pDataPool->isFloat(i)?
                                    pMP->deviatesFromProfile(pDataPool->getFloatValue(i)):
                                    pMP->deviatesFromProfile(pDataPool->getIntegerValue(i)));

        if (invalid) {
            pDataPool->setValidityStatus(i,NOT_VALID);
            pDataPool->getRecoveryAction(i)->execute();
        }

        i=pDataPool->nextIdentifier();
    } while (!pDataPool->isLastIdentifier());

    return ACTION_SUCCESS;
}


//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// SampleApplication.cpp
//
// Version	1.0
// Author   A. Pasetti (P&P Software)

#include "CC_ComponentFactory.h"
#include "CC_ComponentFactory_inc.h"
#include "../FSM/CC_FSM.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"
#include "../Telecommand/CC_TelecommandManager.h"
#include "../Telemetry/CC_TelemetryManager.h"
#include "../Data/DC_ControlAction.h"
#include "../GeneralInclude/TestCompilerSwitches.h"
#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/Constants.h"

int main(int argc, char* argv[]) {

    CC_ComponentFactory* pCompFct;

    pCompFct = CC_ComponentFactory::getInstance();
    pCompFct->configureApplication();

    // Perform ten ativation cycles
    for (unsigned int i=0; i<10; i++) {
        pCompFct->getFSM(CI_Nominal_FSM)->activate();
        pCompFct->getFSM(CI_SM_FSM)->activate();
        pCompFct->getFSM(CI_FDIR_FSM)->activate();
        pCompFct->getControlAction(CI_contAction_1)->execute();
        pCompFct->getControlAction(CI_contAction_2)->execute();
        pCompFct->getControlAction(CI_contAction_3)->execute();
        pCompFct->getControlAction(CI_contAction_4)->execute();
        pCompFct->getManoeuvreManager(CI_manMan)->activate();
        pCompFct->getTelecommandManager(CI_tcMan)->activate();
        pCompFct->getTelemetryManager(CI_tmMan)->activate();
    }

    return 0;

}


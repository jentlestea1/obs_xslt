//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ControlList.cpp
//
// Version	1.0
// Date		08.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/Constants.h"
#include "../GeneralInclude/ClassId.h"
#include "../Base/CC_RootObject.h"
#include "DC_ControlList.h"

DC_ControlList::DC_ControlList(void) {
    listSize        =0;
    controlBlockList=pNULL;
    setClassId(ID_CONTROLLIST);
}

void DC_ControlList::setListSize(unsigned int listSize) {
    assert(listSize!=0 && this->listSize==0);

    this->listSize=listSize;
    controlBlockList=new ControlBlock*[listSize];

    for (unsigned int i=0;i<listSize;i++)
        controlBlockList[i]=pNULL;
}

unsigned int DC_ControlList::getListSize(void) const {
	return listSize;
}

void DC_ControlList::setControlBlock(unsigned int i,ControlBlock *item) {
	assert(item!=pNULL && i<listSize);

	if (i<listSize)
		controlBlockList[i]=item;
	else
		CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_CL);
}

ControlBlock *DC_ControlList::getControlBlock(unsigned int i) const {
	assert(i<listSize);

    return controlBlockList[i];
}

TD_ActionOutcome DC_ControlList::doConditionalAction(void) {
    assert(isObjectConfigured());

    for (unsigned int i=0;i<listSize;i++)
        controlBlockList[i]->propagate();

    return ACTION_SUCCESS;
}

bool DC_ControlList::canExecute(void) {
    assert(isObjectConfigured());

    return true;
}

void DC_ControlList::reset(void) {
    assert(isObjectConfigured());

    for (unsigned int i=0;i<listSize;i++)
        controlBlockList[i]->reset();
}

bool DC_ControlList::isObjectConfigured(void) {
    if (!ConditionalPunctualAction::isObjectConfigured() || listSize==0)
        return NOT_CONFIGURED;

    for (unsigned int i=0;i<listSize;i++)
        if (controlBlockList[i]==pNULL)
            return NOT_CONFIGURED;

    return CONFIGURED;
}

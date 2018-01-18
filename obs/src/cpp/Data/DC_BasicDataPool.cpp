//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicDataPool.cpp
//
// Version	1.0
// Date		10.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "../Data/DC_BasicDataPool.h"

DC_BasicDataPool::DC_BasicDataPool(void) {
    setClassId(ID_BASICDATAPOOL);
    value=pNULL;
    size=0;
}

void DC_BasicDataPool::setDataPoolSize(TD_DataPoolId size) {
    assert(value==pNULL && size>0);

    this->size=size;
    value=(unsigned char*)(new double[(size/sizeof(double))+1]);

    for (TD_DataPoolId i=0; i<size; i++)
        value[i]=0;
}

TD_DataPoolId DC_BasicDataPool::getDataPoolSize(void) {
    return size;
}

void DC_BasicDataPool::setValue(TD_DataPoolId id,TD_Float newValue) {
    assert(value!=pNULL && id<=(size-(TD_DataPoolId)sizeof(TD_Float)));

    *(TD_Float *)(value+id)=newValue;
}

void DC_BasicDataPool::setValue(TD_DataPoolId id,TD_Integer newValue) {
    assert(value!=pNULL && id<=(size-(TD_DataPoolId)sizeof(TD_Integer)));

    *(TD_Integer *)(value+id)=newValue;
}

TD_Float DC_BasicDataPool::getFloatValue(TD_DataPoolId id) {
    assert(value!=pNULL && id<=(size-(TD_DataPoolId)sizeof(TD_Float)));

    return *(TD_Float *)(value+id);
}

TD_Integer DC_BasicDataPool::getIntegerValue(TD_DataPoolId id) {
    assert(value!= pNULL && id<=(size-(TD_DataPoolId)sizeof(TD_Integer)));

    return *(TD_Integer *)(value+id);
}

TD_Float* DC_BasicDataPool::getPointerFloatValue(TD_DataPoolId id) {
    assert(value!=pNULL && id<=(size-(TD_DataPoolId)sizeof(TD_Float)));

    return (TD_Float *)(value+id);
}

TD_Integer* DC_BasicDataPool::getPointerIntegerValue(TD_DataPoolId id) {
    assert(value!=pNULL  && id<=(size-(TD_DataPoolId)sizeof(TD_Integer)));

    return (TD_Integer *)(value+id);
}

bool DC_BasicDataPool::isObjectConfigured(void) {
    return (CC_RootObject::isObjectConfigured() && value!=pNULL);
}

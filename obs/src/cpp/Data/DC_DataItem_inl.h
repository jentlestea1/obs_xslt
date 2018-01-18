//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DataItem_inl.h
//
// Version	1.0
// Date		11.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro

#ifndef DC_DataItem_INL
#define DC_DataItem_INL

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"

inline void DC_DataItem::initDataItem(void *data,TD_DataItemType type) {
	assert(data);
	pVar=data;

#ifndef NDEBUG
	varType=type;
#endif
}

inline DC_DataItem::DC_DataItem(TD_Float* d) {
	initDataItem(d,DI_FLOAT);
}

inline DC_DataItem::DC_DataItem(TD_Integer* d) {
	initDataItem(d,DI_INT);
}

inline TD_Float DC_DataItem::getFloatValue() const {
	assert(varType==DI_FLOAT);
	return *(TD_Float *)pVar;
}

inline TD_Integer DC_DataItem::getIntegerValue() const {
	assert(varType==DI_INT);
	return *(TD_Integer *)pVar;
}

inline void DC_DataItem::setValue(TD_Float newValue) {
	assert(varType==DI_FLOAT);
	*(TD_Float *)pVar=newValue;
}

inline void DC_DataItem::setValue(TD_Integer newValue) {
	assert(varType==DI_INT);
	*(TD_Integer *)pVar=newValue;
}


#endif

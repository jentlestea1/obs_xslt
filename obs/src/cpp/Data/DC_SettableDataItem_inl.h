//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_RawDataItem_inl.h
//
// Version	1.0
// Date		11.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro

#ifndef DC_SettableDataItem_INL
#define DC_SettableDataItem_INL

#include "DC_DataItem.h"

inline DC_SettableDataItem::DC_SettableDataItem(TD_Integer *d):DC_DataItem(d) {
}

inline DC_SettableDataItem::DC_SettableDataItem(TD_Float *d):DC_DataItem(d) {
}

inline void DC_SettableDataItem::setVariable(TD_Integer* pNewVar) {
	pVar = pNewVar;
}

inline void DC_SettableDataItem::setVariable(TD_Float* pNewVar) {
	pVar = pNewVar;
}

#endif

//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_RawDataItem_inl.h
//
// Version	1.0
// Date		11.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro

#ifndef DC_RawDataItem_INL
#define DC_RawDataItem_INL

#include "../GeneralInclude/CompilerSwitches.h"
#include "DC_RawDataItem.h"

inline DC_RawDataItem::DC_RawDataItem(void *d):DC_DataItem((TD_Integer*)d) {
}

inline char DC_RawDataItem::getChar() const {
	return *(char *)pVar;
}

inline unsigned char DC_RawDataItem::getUnsignedChar() const {
	return *(unsigned char *)pVar;
}

inline short DC_RawDataItem::getShort() const {
	return *(short *)pVar;
}

inline unsigned short DC_RawDataItem::getUnsignedShort() const {
	return *(unsigned short *)pVar;
}

inline int DC_RawDataItem::getInt() const {
	return *(int *)pVar;
}

inline unsigned int DC_RawDataItem::getUnsignedInt() const {
	return *(unsigned int *)pVar;
}

inline float DC_RawDataItem::getFloat() const {
	return *(float *)pVar;
}

inline double DC_RawDataItem::getDouble() const {
	return *(double *)pVar;
}

inline void DC_RawDataItem::setChar(char newValue) {
	*(char *)pVar=newValue;
}

inline void DC_RawDataItem::setUnsignedChar(unsigned char newValue) {
	*(unsigned char *)pVar=newValue;
}

inline void DC_RawDataItem::setShort(short newValue) {
	*(short *)pVar=newValue;
}

inline void DC_RawDataItem::setUnsignedShort(unsigned short newValue) {
	*(unsigned short *)pVar=newValue;
}

inline void DC_RawDataItem::setInt(int newValue) {
	*(int *)pVar=newValue;
}

inline void DC_RawDataItem::setUnsignedInt(unsigned int newValue) {
	*(unsigned int *)pVar=newValue;
}

inline void DC_RawDataItem::setFloat(float newValue) {
	*(float *)pVar=newValue;
}

inline void DC_RawDataItem::setDouble(double newValue) {
	*(double *)pVar=newValue;
}

#endif

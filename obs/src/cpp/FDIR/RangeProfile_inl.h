//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// RangeProfile_inl.h
//
// Version	1.1
// Date		17.01.03 (Version 1.0)
//          01.10.03 (Version 1.1)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer

#ifndef RangeProfile_INL
#define RangeProfile_INL

inline TD_Float RangeProfile::getLowerBound(void) const {
	return lowerBound;
}

inline TD_Float RangeProfile::getUpperBound(void) const {
	return upperBound;
}

#endif

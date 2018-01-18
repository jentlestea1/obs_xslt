//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// MonitoringProfile_inl.h
//
// Version	1.0
// Date		4.01.03
// Author	A. Pasetti (P&P Software)

#ifndef MonitoringProfile_INL
#define MonitoringProfile_INL

inline void MonitoringProfile::setEnabled(bool enableStatus) {
    this->enableStatus = enableStatus;
}

inline bool MonitoringProfile::isEnabled(void) {
    return enableStatus;
}

#endif

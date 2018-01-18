//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TelecommandLoader_inl.h
//
// Version	1.0
// Date		06.12.02
// Author	A. Pasetti (P&P Software)

#ifndef TelecommandLoaderINL
#define TelecommandLoaderINL


inline void TelecommandLoader::setTelecommandManager(CC_TelecommandManager* pTcManager) {
    pTelecommandManager = pTcManager;
}

inline CC_TelecommandManager* TelecommandLoader::getTelecommandManager(void) {
    assert( pTelecommandManager != pNULL );
    return pTelecommandManager;
}

#endif

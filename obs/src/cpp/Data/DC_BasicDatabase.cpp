//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicDatabase.cpp
//
// Version	1.0
// Date		12.10.02
// Author	A. Pasetti (P&P Software)

#include "../GeneralInclude/CompilerSwitches.h"
#include "../GeneralInclude/DebugSupport.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ClassId.h"
#include "../GeneralInclude/Constants.h"
#include "DC_BasicDatabase.h"

DC_BasicDatabase::DC_BasicDatabase(void) {
   setClassId(ID_BASICDATABASE);
   pDefaultTable = pNULL;
   pOperationalTable = pNULL;
   resetWasCalled = false;
   tableLength = 0;
}

void DC_BasicDatabase::reset(void) {
   assert( (pDefaultTable != pNULL) && (pOperationalTable != pNULL) );
   assert( tableLength > 0 );
   for (TD_DatabaseId i=0; i<tableLength; i++)
      pOperationalTable[i] = pDefaultTable[i];
   resetWasCalled = true;
}

void DC_BasicDatabase::setTableLength(TD_DatabaseId length) {
   assert( length > 0 );
   tableLength = length;
}

TD_DatabaseId DC_BasicDatabase::getTableLength(void) {
   return tableLength;
}

void DC_BasicDatabase::setDefaultTable(char* pDefTable) {
   assert( pDefTable != pNULL );
   pDefaultTable = pDefTable;
}

void DC_BasicDatabase::setOperationalTable(char* pOperTable) {
   assert( pOperTable != pNULL );
   pOperationalTable = pOperTable;
}

bool DC_BasicDatabase::isObjectConfigured(void) {
   return (CC_RootObject::isObjectConfigured() && tableLength>0 &&
           pDefaultTable!=pNULL && pOperationalTable!=pNULL && resetWasCalled);
}

// -------------------------------------------------------------------------

void DC_BasicDatabase::setParameter(TD_DatabaseId parId, unsigned int newValue) {
   assert( pOperationalTable != pNULL );
   *( (unsigned int*)(pOperationalTable+parId) ) = newValue;
}

void DC_BasicDatabase::setParameter(TD_DatabaseId parId, int newValue) {
   assert( pOperationalTable != pNULL );
   *( (int*)(pOperationalTable+parId) ) = newValue;
}

void DC_BasicDatabase::setParameter(TD_DatabaseId parId, unsigned short newValue) {
   assert( pOperationalTable != pNULL );
   *( (unsigned short*)(pOperationalTable+parId) ) = newValue;
}

void DC_BasicDatabase::setParameter(TD_DatabaseId parId, short newValue) {
   assert( pOperationalTable != pNULL );
   *( (short*)(pOperationalTable+parId) ) = newValue;
}

void DC_BasicDatabase::setParameter(TD_DatabaseId parId, bool newValue) {
   assert( pOperationalTable != pNULL );
   *( (bool*)(pOperationalTable+parId) ) = newValue;
}

void DC_BasicDatabase::setParameter(TD_DatabaseId parId, char newValue) {
   assert( pOperationalTable != pNULL );
   *( (char*)(pOperationalTable+parId) ) = newValue;
}

void DC_BasicDatabase::setParameter(TD_DatabaseId parId, unsigned char newValue) {
   assert( pOperationalTable != pNULL );
   *( (unsigned char*)(pOperationalTable+parId) ) = newValue;
}

void DC_BasicDatabase::setParameter(TD_DatabaseId parId, float newValue) {
   assert( pOperationalTable != pNULL );
   *( (float*)(pOperationalTable+parId) ) = newValue;
}

void DC_BasicDatabase::setParameter(TD_DatabaseId parId, double newValue) {
   assert( pOperationalTable != pNULL );
   *( (double*)(pOperationalTable+parId) ) = newValue;
}

// -------------------------------------------------------------------------

unsigned int DC_BasicDatabase::getParameterUnsignedInt(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return *(unsigned int*)(pOperationalTable+parId);
}

int DC_BasicDatabase::getParameterInt(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return *(int*)(pOperationalTable+parId);
}

unsigned short DC_BasicDatabase::getParameterUnsignedShort(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return *(unsigned short*)(pOperationalTable+parId);
}

short DC_BasicDatabase::getParameterShort(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return *(short*)(pOperationalTable+parId);
}

unsigned char DC_BasicDatabase::getParameterUnsignedChar(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return *(unsigned char*)(pOperationalTable+parId);
}

char DC_BasicDatabase::getParameterChar(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return *(char*)(pOperationalTable+parId);
}

bool DC_BasicDatabase::getParameterBool(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return *(bool*)(pOperationalTable+parId);
}

float DC_BasicDatabase::getParameterFloat(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return *(float*)(pOperationalTable+parId);
}

double DC_BasicDatabase::getParameterDouble(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return *(double*)(pOperationalTable+parId);
}

// -------------------------------------------------------------------------

unsigned int* DC_BasicDatabase::getParameterPointerUnsignedInt(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return (unsigned int*)(pOperationalTable+parId);
}

int* DC_BasicDatabase::getParameterPointerInt(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return (int*)(pOperationalTable+parId);
}

unsigned short* DC_BasicDatabase::getParameterPointerUnsignedShort(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return (unsigned short*)(pOperationalTable+parId);
}

short* DC_BasicDatabase::getParameterPointerShort(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return (short*)(pOperationalTable+parId);
}

unsigned char* DC_BasicDatabase::getParameterPointerUnsignedChar(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return (unsigned char*)(pOperationalTable+parId);
}

char* DC_BasicDatabase::getParameterPointerChar(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return (char*)(pOperationalTable+parId);
}

bool* DC_BasicDatabase::getParameterPointerBool(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return (bool*)(pOperationalTable+parId);
}

float* DC_BasicDatabase::getParameterPointerFloat(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return (float*)(pOperationalTable+parId);
}

double* DC_BasicDatabase::getParameterPointerDouble(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   return (double*)(pOperationalTable+parId);
}

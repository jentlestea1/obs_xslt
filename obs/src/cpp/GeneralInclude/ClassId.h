//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ClassId.h
//
// Version	1.0
// Date		12.09.02
// Author	A. Pasetti (P&P Software)

/**
 * @file ClassId.h 
 * This file defines the class identifiers for all the classes defined by the OBS
 * Framework. Class identifiers are associated to all the classes that are
 * derived from class <code>CC_RootObject</code>. The name of the identifier is 
 * formed by the prefix "ID_" followed by the name of the class.
 * <p>
 * One "fictitious" class identifier is added for module <code>Checksum</code>. 
 * Although this module is not implemented as a class, a class identifier is still
 * required because a test case is devoted to this class (class <code>TestcaseChecksum_1</code>)
 * and a class identifier is required to construct the test case identifier.
 * @see CC_RootObject
 */

#ifndef ClassIdH
#define ClassIdH

#include "BasicTypes.h"

const TD_ClassId ID_ROOTOBJECT                      = 1;   //@- Class Identifier
const TD_ClassId ID_EVENT                           = 2;   //@- Class Identifier
const TD_ClassId ID_EVENTREPOSITORY                 = 3;   //@- Class Identifier
const TD_ClassId ID_PUSEVENTREPOSITORY              = 4;   //@- Class Identifier

const TD_ClassId ID_DUMMYOBSCLOCK                   = 10;  //@- Class Identifier

const TD_ClassId ID_DATAITEM                        = 20;  //@- Class Identifier
const TD_ClassId ID_RAWDATAITEM                     = 21;  //@- Class Identifier

const TD_ClassId ID_DUMMYTRACER                     = 30;  //@- Class Identifier
const TD_ClassId ID_TESTTRACER                      = 31;  //@- Class Identifier

const TD_ClassId ID_DUMMYPUNCTUALACTION             = 40;  //@- Class Identifier
const TD_ClassId ID_DUMMYCONDITIONALPUNCTUALACTION  = 41;  //@- Class Identifier
const TD_ClassId ID_SIMPLEPUNCTUALACTIONMODEMANAGER = 42;  //@- Class Identifier
const TD_ClassId ID_PUNCTUALACTIONMANAGER           = 43;  //@- Class Identifier
const TD_ClassId ID_CYCLINGPUNCTUALACTIONMODEMANAGER= 44;  //@- Class Identifier

const TD_ClassId ID_FSMEVENT                        = 50;  //@- Class Identifier
const TD_ClassId ID_FROMFSMEVENT                    = 51;  //@- Class Identifier
const TD_ClassId ID_DUMMYFSMSTATE                   = 52;  //@- Class Identifier
const TD_ClassId ID_FSM                             = 53;  //@- Class Identifier
const TD_ClassId ID_DUMMYCONFIGURABLEFSMSTATE       = 54;  //@- Class Identifier
const TD_ClassId ID_NESTEDFSMACTIVATOR              = 55;  //@- Class Identifier
const TD_ClassId ID_NESTEDFSMACTIVATORWITHENDSTATE  = 56;  //@- Class Identifier
const TD_ClassId ID_NESTEDFSMACTIVATORWITHEXITCHECK = 57;  //@- Class Identifier
const TD_ClassId ID_UNSTABLEFSMSTATE                = 58;  //@- Class Identifier

const TD_ClassId ID_BASICDATABASE                   = 60;  //@- Class Identifier
const TD_ClassId ID_SAMPLER1DATABASE                = 61;  //@- Class Identifier
const TD_ClassId ID_SAMPLER2DATABASE                = 62;  //@- Class Identifier
const TD_ClassId ID_SAMPLER3DATABASE                = 63;  //@- Class Identifier
const TD_ClassId ID_DUMMYDATABASE                   = 64;  //@- Class Identifier

const TD_ClassId ID_DUMMYTELECOMMAND                = 80;  //@- Class Identifier
const TD_ClassId ID_DUMMYTELECOMMANDLOADER          = 81;  //@- Class Identifier
const TD_ClassId ID_TELECOMMANDMANAGER              = 82;  //@- Class Identifier
const TD_ClassId ID_DUMMYCRITICALTELECOMMAND        = 83;  //@- Class Identifier
const TD_ClassId ID_DUMMYPUSTELECOMMAND             = 84;  //@- Class Identifier
const TD_ClassId ID_BASICPUSTCLOADER                = 85;  //@- Class Identifier

const TD_ClassId ID_SIMPLECHANGEPROFILE             = 90;  //@- Class Identifier
const TD_ClassId ID_STUCKDATAPROFILE                = 91;  //@- Class Identifier
const TD_ClassId ID_DELTAPROFILE                    = 92;  //@- Class Identifier
const TD_ClassId ID_FORBIDDENVALUEPROFILE           = 93;  //@- Class Identifier
const TD_ClassId ID_INRANGEPROFILE                  = 94;  //@- Class Identifier
const TD_ClassId ID_OUTOFRANGEPROFILE               = 95;  //@- Class Identifier
const TD_ClassId ID_NULLPROFILE                     = 96;  //@- Class Identifier
const TD_ClassId ID_PROFILELIST                     = 97;  //@- Class Identifier

const TD_ClassId ID_DUMMYMODEMANAGER                = 100; //@- Class Identifier

const TD_ClassId ID_DUMMYMANOEUVRE                  = 110; //@- Class Identifier
const TD_ClassId ID_DUMMYCONFIGURABLEMANOEUVRE      = 111; //@- Class Identifier
const TD_ClassId ID_TESTPUSCONFIGURABLEMANOEUVRE    = 112; //@- Class Identifier
const TD_ClassId ID_MANOEUVREMANAGER                = 113; //@- Class Identifier
const TD_ClassId ID_MANOEUVREPUNCTUALACTION         = 114; //@- Class Identifier

const TD_ClassId ID_DUMMYCOPYCONTROLBLOCK           = 120; //@- Class Identifier
const TD_ClassId ID_DUMMYPOINTERCONTROLBLOCK        = 121; //@- Class Identifier
const TD_ClassId ID_DUMMYDATAITEMCONTROLBLOCK       = 122; //@- Class Identifier
const TD_ClassId ID_DUMMYDATAPOOLCONTROLBLOCK       = 123; //@- Class Identifier
const TD_ClassId ID_CONTROLACTION                   = 124; //@- Class Identifier
const TD_ClassId ID_CONTROLLIST                     = 125; //@- Class Identifier

const TD_ClassId ID_BASICRECONFIGURER               = 130; //@- Class Identifier

const TD_ClassId ID_MATLABCOPYPID                   = 140; //@- Class Identifier
const TD_ClassId ID_MATLABPOINTERPID                = 141; //@- Class Identifier
const TD_ClassId ID_MATLABDATAITEMPID               = 142; //@- Class Identifier
const TD_ClassId ID_MATLABDATAPOOLPID               = 143; //@- Class Identifier

const TD_ClassId ID_NULLRECOVERYACTION              = 150; //@- Class Identifier
const TD_ClassId ID_DUMMYRECOVERYACTION             = 151; //@- Class Identifier

const TD_ClassId ID_FDIRCHECK                       = 160; //@- Class Identifier

const TD_ClassId ID_ROOTOBJECTSTACK                 = 170; //@- Class Identifier
const TD_ClassId ID_INTSTACK                        = 171; //@- Class Identifier

const TD_ClassId ID_BASICDATAPOOL                   = 180; //@- Class Identifier
const TD_ClassId ID_SAMPLEFULLDATAPOOL              = 181; //@- Class Identifier
const TD_ClassId ID_SAMPLEMONITOREDDATAPOOL         = 182; //@- Class Identifier
const TD_ClassId ID_DATAPOOLMONITOR                 = 183; //@- Class Identifier
const TD_ClassId ID_DUMMYDATAPOOL                   = 184; //@- Class Identifier

const TD_ClassId ID_DUMMYTELEMETRYSTREAM            = 190; //@- Class Identifier
const TD_ClassId ID_PUSTMLOGGER                     = 191; //@- Class Identifier

const TD_ClassId ID_DUMMYPUSTCVERIFICATIONPACKET    = 200; //@- Class Identifier
const TD_ClassId ID_PUSDATAREPORTINGPACKET          = 201; //@- Class Identifier
const TD_ClassId ID_PUSDATAREPORTINGPACKETFACTORY   = 202; //@- Class Identifier
const TD_ClassId ID_PUSTCVERIFICATIONPACKET         = 203; //@- Class Identifier
const TD_ClassId ID_PUSMEMORYDUMPOFFSET             = 204; //@- Class Identifier
const TD_ClassId ID_PUSMEMORYDUMPABSOLUTE           = 205; //@- Class Identifier

const TD_ClassId ID_PUSCONTROLDATAREPORTING         = 220; //@- Class Identifier
const TD_ClassId ID_PUSCLEARDATAREPORTING           = 221; //@- Class Identifier
const TD_ClassId ID_PUSREQUESTDATAREPORTING         = 222; //@- Class Identifier
const TD_ClassId ID_PUSDEFINEDATAREPORTING          = 223; //@- Class Identifier
const TD_ClassId ID_PUSMEMORYLOADOFFSET             = 224; //@- Class Identifier
const TD_ClassId ID_PUSMEMORYLOADABSOLUTE           = 225; //@- Class Identifier
const TD_ClassId ID_PUSDUMPMEMORYOFFSET             = 226; //@- Class Identifier
const TD_ClassId ID_PUSDUMPMEMORYABSOLUTE           = 227; //@- Class Identifier
const TD_ClassId ID_TESTPUSTELECOMMAND              = 228; //@- Class Identifier

const TD_ClassId ID_TELEMETRYPACKETFACTORY          = 250; //@- Class Identifier
const TD_ClassId ID_TELECOMMANDFACTORY              = 251; //@- Class Identifier
const TD_ClassId ID_MANOEUVREFACTORY                = 252; //@- Class Identifier

const TD_ClassId ID_DATAITEM16TMWORD                = 260;  //@- Class Identifier
const TD_ClassId ID_CYCLEDATAITEM16TMSTREAM         = 261;  //@- Class Identifier
const TD_ClassId ID_SIMPLETELEMETRYMODEMANAGER      = 262;  //@- Class Identifier
const TD_ClassId ID_TELEMETRYMANAGER                = 263;  //@- Class Identifier
const TD_ClassId ID_FILETELEMETRYSTREAM             = 264;  //@- Class Identifier
const TD_ClassId ID_DUMMYTELEMETRYITEM              = 265;  //@- Class Identifier
const TD_ClassId ID_DUMMYPUSTELEMETRYPACKET         = 266;  //@- Class Identifier
const TD_ClassId ID_BYTEARRAYTELEMETRYSTREAM        = 267;  //@- Class Identifier
const TD_ClassId ID_CYCLINGTELEMETRYMODEMANAGER     = 268;  //@- Class Identifier
const TD_ClassId ID_PUSTELEMETRYMODEMANAGER         = 269;  //@- Class Identifier
const TD_ClassId ID_BASICPUSTMSTREAM                = 270;  //@- Class Identifier


const TD_ClassId ID_CHECKSUM                        = 400; //@- Class Identifier

#endif

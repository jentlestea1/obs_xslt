//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyDatabase.h
//
// Version	1.0
// Date		13.10.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_DummyDatabaseH
#define DC_DummyDatabaseH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "DC_BasicDatabase.h"

/**
 * Default component implementing a dummy parameter database.
 * A <i>dummy parameter database</i> is a parameter database with a length of
 * of one byte and with default and operational tables that coincide.
 * It is useful for testing purposes as a placeholder for a component of type
 * <code>ParameterDatabase</code>.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyDatabase : public DC_BasicDatabase {

  private:
    char table;

  public:
    /**
     * Instantiate a dummy database component. The class identifier is set.
     * The database size is set to one. An internal variable of type <code>char</code> is
     * used as default and operational table. The value of the single item it
     * contains is set to zero.
     */
    DC_DummyDatabase(void);

};

#endif

//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyDataPool.h
//
// Version	1.0
// Date		10.09.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#ifndef DC_DummyDataPoolH
#define DC_DummyDataPoolH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_BasicDataPool.h"

/**
 * Default component implementing a dummy data pool.
 * A dummy data pool is a <i>basic data pool</i> that can hold only one single integer-valued
 * data pool item. The value of 
 * this single data pool item is initialized to zero.
 * This data pool is useful for testing purposes as a placeholder for components of 
 * type <code>DataPool</code>.
 * @author Alessandro Pasetti (P&P Software)
 * @version 1.0
 */
class DC_DummyDataPool : public DC_BasicDataPool {

  public:
    /**
     * Instantiate a dummy data pool component. The class identifier is set.
     * The size of the data pool is set to the size of an instance of type <code>TD_Integer</code>
     * and the value of the single item in the data pool is initialized to zero.
     */
    DC_DummyDataPool(void);

};

#endif



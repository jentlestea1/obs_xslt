//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SettableDataItem.h
//
// Version	1.0
// Date		11.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#ifndef DC_SettableDataItemH
#define DC_SettableDataItemH

#include "../GeneralInclude/BasicTypes.h"
#include "DC_DataItem.h"

/**
 * This class encapsulates a settable data item.
 * A <i>settable data item</i> is a data item that allows the encapsulated variable
 * to be dynamically updated. Data items are used to set up permanent links between
 * a component A that needs some input data and a component B that provides the input 
 * data. In such a situation, component A can be passed a data item that encapsulates
 * access to the data from component B. Use of a settable data item (as opposed to an 
 * ordinary data item of the
 * kind that is directly instantiated from <code>DC_DataItem</code>) is useful when
 * it is desired to keep the option open of changing the input for component A.
 * This can be done by changing the variable that is encapsulated in the data item 
 * that A uses as the source for its input. 
 * @todo create a test case for this class
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_SettableDataItem : public DC_DataItem {

  public:
    /**
     * Instantiate a settable data item component that encapsulates an
     * integer-valued variable.
     * This constructor simply calls the constructor of the super class.
     * @param d reference to the variable encapsulated by the data item
     */
	inline DC_SettableDataItem(TD_Integer *d);

    /**
     * Instantiate a settable data item component that encapsulates a
     * real-valued variable.
     * This constructor simply calls the constructor of the super class.
     * @param d reference to the variable encapsulated by the data item
     */
	inline DC_SettableDataItem(TD_Float *d);

    /**
     * Set a new integer-valued variable as the variable that is encapsulated
     * by the data item.
     * @param pNewVar the new variable encapsulated in the data item
     */
    inline void setVariable(TD_Integer* pNewVar);

    /**
     * Set a new real-valued variable as the variable that is encapsulated
     * by the data item.
     * @param pNewVar the new variable encapsulated in the data item
     */
    inline void setVariable(TD_Float* pNewVar);

};

#include "DC_SettableDataItem_inl.h"

#endif




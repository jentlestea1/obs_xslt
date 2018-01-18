//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ControlList.h
//
// Version	1.0
// Date		08.10.03 (Version 1.0)
// Author	R. Totaro
//
// Change Record:

#ifndef DC_ControlListH
#define DC_ControlListH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ConditionalPunctualAction.h"
#include "ControlBlock.h"

/**
 * Encapsulation of list of <i>control blocks</i>. This control action can be
 * configured with a list of control blocks whose <code>propagate()</code> method
 * is invoked upon execution of the action. This class assumes that the target
 * control blocks are already fully configured.
 * <p>
 * Control lists offer a <i>reset service</i>. A call to the reset service
 * causes all the target control blocks to be reset.
 * <p>
 * This class implements a default <i>execution check</i> that always returns
 * "can execute". This means that, if the control action is enabled, then its
 * execution will always result in the target control blocks receiving a propagation
 * request. Subclasses can of course implement different execution checks.
 * @author Roberto Totaro
 * @version 1.0
 */

class DC_ControlList: public ConditionalPunctualAction {
private:
    unsigned int   listSize;
    ControlBlock **controlBlockList;

protected:
    /**
     * Encapsulate an <i>execution check</i> that always returns
     * "control action can execute".
     * @see ConditionalPunctualAction#doAction
     * @return always returns true.
     */
    virtual bool canExecute(void);

    /**
     * Send a propagate request to the target control block. This
     * method always returns: "ACTION_SUCCESS"
     * @see ConditionalPunctualAction#doAction
     * @return always returns ACTION_SUCCESS
     */
    virtual TD_ActionOutcome doConditionalAction(void);

public:
    /**
     * Instantiate a control list.
     * The class identifier is set, the size of the control block list
     * is initialized to 0 to signify that the component is not yet configured.
     */
    DC_ControlList(void);

    /**
     * Set the size of the list of control blocks.
     * The list size defines the maximum number of control blocks
     * that can be loaded into this component. A call to this method
     * causes memory for an internal data structure to be allocated.
     * This is an initialization method: it shall be called only
     * once, before the component is used for the first time. It is not legal
     * to set the repository size to 0. The entries in the list are initialized
     * to illegal values to signify that the component is not yet configured.
     * @param listSize the size of the control block list size
     */
    void setListSize(unsigned int listSize);

    /**
     * Return the size of the list of control blocks.
     * @see #setListSize
     * @return listSize the size of the control block list size
     */
    unsigned int getListSize(void) const;

    /**
     * Load the i-th entry in the list of control blocks.
     * Only non-null entries are legal. The index i must lie in the interval [0,N-1]
     * where N is the size of the control block list.
     * Use of illegal values results in the generation of an EVT_ILLEGAL_CL event report.
     * @see TD_EventId
     * @param i the index of the control block list
     * @param item the item to be added to the list at position i
     */
    void setControlBlock(unsigned int i,ControlBlock *item);

    /**
     * Get the i-th entry in the list of control blocks.
     * The index i should lie in the interval [0,N-1]
     * where N is the size of the control block list.
     * No checks are performed on the legality of the index.
     * @param i the index of the control block list
     * @return the item at position i of the control block list
     */
    ControlBlock *getControlBlock(unsigned int i) const;

    /**
     * Reset all the control blocks.
     */
    void reset(void);

    /**
     * Perform a class-specific configuration check on the control
     * list: verify that the size of the list of control blocks has
     * a value greater than zero and that all the entries in the list
     * have been loaded with control blocks.
     * @return true if the control list is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);
};

#endif

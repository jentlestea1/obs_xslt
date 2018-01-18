//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DataPoolMonitor.h
//
// Version	1.0
// Date		12.09.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_DataPoolMonitorH
#define DC_DataPoolMonitorH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/ConditionalPunctualAction.h"

/**
 * Component to perform a monitoring check on all items in the system
 * data pool. The system data pool that is subjected to monitoring 
 * is loaded from the <code>CC_RootObject</code> class.
 * The data pool monitor is implemented as a form of
 * <i>conditional punctual action</i>. When it is executed,
 * the component iterates over all
 * items in the data pool (using the <i>iteration service</i> offered by
 * the data pool). It retrieves the <i>monitoring profile</i> associated to
 * each item and it uses it to check the current value of the item. If a
 * monitoring violation is detected, the <i>validity status</i> of the item
 * is set to "not valid" and the <i>recovery action</i> associated to
 * the item is executed.
 * @todo change the specification and the implementation of the class to set the status
 * of a data pool item whose monitoring check reports "no deviation from profile" to
 * "valid". At present, the validity status can only go from "valid" to "not valid".
 * @see DataPool
 * @see CC_RootObject
 * @see MonitoringProfile
 * @see RecoveryAction
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DataPoolMonitor : public ConditionalPunctualAction {

  protected:
    /**
     * Encapsulate an <i>execution check</i> that always returns
     * "can execute".
     * @see ConditionalPunctualAction#doAction
     * @return always returns true.
     */
    virtual bool canExecute(void);

    /**
     * Perform the monitoring action on all the items in the data pool.
     * The data pool is loaded from the <code>CC_RootObject</code>.
     * A pseudo-code implementation of this method is as follows: <pre>
     *   pDataPool = CC_RootObject::getDataPool();
     *   for (all items p in pDataPool)
     *	 {  get the value v of p
     *	    get the monitoring profile m associated to p in pDataPool
	 *	    pass the value v through the monitoring profile m
     *	    if (monitoring violation detected)
     *      {    set the validity status of p to "not valid"
     *           get the recovery action r associated to p in pDataPool
     *           execute r
     *      }
     *    }	</pre>
     * This method always returns: "ACTION_SUCCESS"
     * @see ConditionalPunctualAction#doAction
     * @return the outcome code of the punctual action
     */
    virtual TD_ActionOutcome doConditionalAction(void);

  public:
    /**
     * Instantiate a data pool monitor component.
     * The value of the class identifier is set.
     */
    DC_DataPoolMonitor(void);
};

#endif

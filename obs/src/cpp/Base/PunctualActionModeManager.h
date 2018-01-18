//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PunctualActionModeManager.h
//
// Version	1.0
// Date		29.02.04 
// Author	A. Pasetti, R. Totaro
//
// Change Record:

#ifndef PunctualActionModeManagerH
#define PunctualActionModeManagerH

#include "ModeManager.h"
#include "PunctualAction.h"

/**
 * Base abstract class for mode manager components for the punctual
 * action manager.
 * A punctual action mode manager handles one single <i>strategy</i>, which
 * is represented by a set of <i>punctual action</i> components.
 * To every operational mode, the telemetry mode manager associates 
 * a set of punctual actions. 
 * Client access the items in this set through four
 * <i>iteration methods</i>: <code>first</code>, <code>next</code>,
 * <code>isIterationFinished</code>, and <code>getPunctualAction</code>.
 * <p>
 * This is an abstract class because it specifies neither the implementation
 * mechanism for the set of punctual actions nor the mode update mechanism.
 * @todo Create a class DC_FSMPunctualActionModeManager where the mode is driven
 * by an FSM. Same thing should be done for the TelemetryModeManager
 * @see CC_PunctualActionManager
 * @see PunctualAction
 * @author Alessandro Pasetti 
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup ModeManagement
 */
class PunctualActionModeManager : public ModeManager {
  
  public:
    /**
     * Instantiate a punctual action mode manager. This constructor returns
     * without taking any action.
     */
    PunctualActionModeManager(void);

    /**
     * Iteration method to iterate through the items in the set of
     * punctual actions applicable to the current operational mode. 
	 * This method should be used jointly with methods: <code>next</code>,
     * <code>isIterationFinished</code> and <code>getIterationPunctualAction</code>. 
	 * Taken together,
     * these methods allow all the items in the currently applicable set 
	 * of punctual actions to be scanned. 
	 * During an iteration cycle, an internal pointer, the <i>iteration
	 * pointer</i>, is made to scan over all the items in the currently applicable
	 * set of telemetry packets.
     * The item currently pointed at by the iteration counter can be retrieved
     * through method <code>getIterationPunctualAction</code>.
     * Thus, a typical iteration cycle might be organized as follows: <PRE>
     *      for (first(); !isIterationFinished(); next()) {
     *          pItem = getIterationPunctualAction();
     *          . . .    // process pItem
     *      }  </PRE>
     * @see #getIterationItem
     */
    virtual void first(void) = 0;

    /**
     * Iteration method to be used in conjunction with methods <code>first</code>
     * and <code>isIterationFinished</code>.
     * @see #first
     */
    virtual void next(void) = 0;

    /**
     * Iteration method to be used in conjunction with methods <code>first</code>
     * and <code>next</code>.
     * This method should only be used as part of an iteration cycle. The result
     * of calling it before ever calling <code>first</code>
     * is undefined.
     * @see #first
     * @return true if the end of the iteration has been reached, false otherwise
     */
    virtual bool isIterationFinished(void) = 0;

    /**
     * Return the punctual action item pointed at by the iterator.
     * This method is a type-safe wrapper for method <code>getIteratorItem</code>
     * in the superclass.
     * @see ListModeManager#getIterationItem
     * @return the punctual action item pointed at by the iterator
     */
    virtual PunctualAction* getIterationPunctualAction(void) = 0;
};

#endif

//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_ManoeuvreManager.h
//
// Version	1.0
// Date		16.04.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef CC_ManoeuvreManagerH
#define CC_ManoeuvreManagerH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "Manoeuvre.h"

/**
 * This class encapsulates a manoeuvre manager.
 * The manoeuvre manager is responsible for controlling the execution
 * of manoeuvres.
 * Manoeuvres are loaded into the manoeuvre manager and from
 * that moment onward their execution,
 * termination, and abortion remain under the control of the manoeuvre
 * manager.
 * The manoeuvre manager sees manoeuvres as instances of type
 * <CODE>Manoeuvre</CODE>.
 * <p>
 * The manoeuvre manager maintains a list of pending manoeuvres.
 * This is called the <i>pending manoeuvre list</i>.
 * The <i>pending manoeuvres</i> are the manouvres that are currently
 * loaded into the manoeuvre manager and that
 * are either executing or awaiting to start execution.
 * <p>
 * External entities typically performs three types of operations
 * upon a manoeuvre manager.
 * They can <i>load</i> a new manoeuvre in the manoeuvre manager.
 * They can <i>abort</i> execution of an already loaded manoeuvre.
 * They can <i>activate</i> the manoeuvre manager to advance the execution
 * of the pending manoeuvres.
 * <p>
 * The manoeuvre manager contributes to the management of the "in use" status of
 * manoeuvres. More precisely, before unloading a manoeuvre, the manoeuvre
 * manager marks if as "no longer in use".
 * <p>
 * The manoeuvre manager creates event reports to record the following
 * occurrences:<ul>
 * <li>Attempt to load a manoeuvre when the list of pending manoeuvres
 * is already full</li>
 * <li>A new manoeuvre is loaded</li>
 * <li>A manoeuvre is unloaded</li>
 * </ul>
 * In all cases, the <i>event originator</i> that is passed to the event creation
 * method is the manoeuvre that is being processed.
 * Note that the creation of event reports describing
 * changes of state of the manoeuvre are the responsibility of the
 * manoeuvres themselves.
 * @see Manoeuvre
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup FunctionalityManagers
 * @ingroup Manoeuvre
 */
class CC_ManoeuvreManager : public CC_RootObject {

  private:
    Manoeuvre** pManList;    // array of pointers -- pending manoeuvre list
    unsigned int manListSize;
    unsigned int manCounter;   // number of pending manoeuvres

  protected:

    /**
     * Unload a manoeuvre. The manoeuvre is removed from the list of
     * pending manoeuvres and will no longer be considered for execution.
     * The "inUse" status of the manoeuvre is changed to: "manoeuvre not in use".
     * <p>
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   . . .       // remove manoeuvre from list of pending manoeuvres
     *   pManoeuvre->inUse(false)   // mark manoeuvre as "not in use"
     *   createEventReport(EVT_MAN_UNLOADED);
     *   return; </PRE>
     * The <code>manId</code> parameter in the above pseudo-code is a manoeuvre
     * identifier. This class uses the class identifier of the manoeuvre
     * component as identifier.
     * @see TD_EventType
     * @param pManoeuvre the manoeuvre that is loaded
     */
    virtual void unload(Manoeuvre* pManoeuvre);

  public:

   /**
    * Instantiate a manoeuvre manager.
    * The size of the pending manoeuvre list is initialized to an illegal value
    * to signify that the manoeuvre manager is not yet configured. The class
    * identifier is set.
    */
   CC_ManoeuvreManager(void);

    /**
     * Unload all pending manoeuvres (aborting those that are executing).
     * A reset bring the telecommand manager
     * to the state where it was immediately after having being configured.
     */
    void reset(void);

    /**
     * Set the size of the pending manoeuvre list representing the maximum number
     * of pending manoeuvre that can be managed by the manoeuvre manager.
     * This method causes the memory for the pending manoeuvre list data structure
     * to be allocated and the data structure to be initialized. Only positive values
     * of the manoeuvre list size are legal.
     * <p>
     * This is an initialization method. It should be called before the
     * manoeuvre manager is used the first time and it should not be called more
     * than once.
     * @param listSize the maximum number of pending manoeuvres that can be
     * managed by the Manoeuvre Manager. This should be a positive number.
     */
    void setPendingManoeuvreListSize(const unsigned int listSize);

    /**
     * Get the size of the pending manoeuvre list.
     * @see #setPendingManoeuvreListSize
     * @return the maximum number of pending manoeuvres that can be
     * managed by the Manoeuvre Manager
     */
    unsigned int getPendingManoeuvreListSize(void);

    /**
     * Get the number of currently pending manoeuvres.
     * @see #setPendingManoeuvreListSize
     * @return the number of currently pending manoeuvres
     */
    unsigned int getPendingManoeuvres(void);

    /**
     * Load a manoeuvre. When a manoeuvre is loaded, it is inserted in the list
     * of pending manoeuvres and is then considered for execution by method
     * <code>activate</code>. The manoeuvre remains loaded until it has terminated
     * execution or is aborted.
     * <p>
     * If the list of pending manoeuvres is already full, no action is taken
     * other than the creation of an event report to record the attempted
     * manoeuvre load.
     * <p>
     * The manoeuvre manager creates an event whenever a new manoeuvre is loaded.
     * <p>
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   if (list of pending manoeuvres is full)    // the manoeuvre list is full
     *   {   createEventReport(EVT_MAN_LIST_FULL);
     *       return;
     *   }
     *   . . .       // insert manoeuvre in list of pending manoeuvres
     *   createEventReport(EVT_MAN_LOADED);
     *   return; </PRE>
     * The <code>manId</code> parameter in the above pseudo-code is a manoeuvre
     * identifier. This class uses the class identifier of the manoeuvre
     * component as its identifier.
     * @see TD_EventType
     * @param pManoeuvre the manoeuvre that is loaded
     */
    virtual void load(Manoeuvre* pManoeuvre);

    /**
     * Abort a manoeuvre.
     * An <CODE>abort()</CODE> request is sent to the manoeuvre and the
     * manoeuvre is then unloaded.
     * If the argument manoeuvre is not currently loaded, no action is taken.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   for (all manoeuvre m in the list of pending manoeuvres)
     *     if (m==pManoeuvre) {
     *          pManoeuvre->abort();
     *          pManoeuvre->setInUse(false);
     *          . . . // delete pManoeuvre from list of pending manoeuvres);
     *          createEventReport(EVT_MAN_UNLOADED);
     *      }
     *   return; </PRE>
     * @see TD_EventType
     * @see Manoeuvre#abort
     * @param pManoeuvre the manoeuvre to be aborted
     */
    virtual void abort(Manoeuvre* pManoeuvre);

    /**
     * Advance execution of pending manoeuvres.
     * When this method is called, the manoeuvre manager goes through the list
     * of pending manoeuvres and processes them in sequence.
     * This method would typically be called by an external scheduler.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   for (all manoeuvres m in the list of pending manoeuvres)
     *      if ( (!m->isExecuting()) && (m->canStart()) ) {
     *          m->initialize();
     *          m->doContinue();
     *      }
     *      else if ( (m->isExecuting()) && (m->canContinue()) )
     *          m->doContinue();
     *      else if ( (m->isExecuting()) && (!m->canContinue()) )
     *          m->abort();
     *
     *      if ( m->isFinished() )
     *          m->terminate();
     *          unload(m);
     *      } </PRE>
     */
    virtual void activate(void);

    /**
     * Perform a class-specific configuration check: verify that the size of the
     * pending manoeuvre list has a legal value.
     * @return true if the telecommand manager is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif

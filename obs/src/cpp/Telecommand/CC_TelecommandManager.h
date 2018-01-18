//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// CC_TelecommandManager.h
//
// Version	1.0
// Date		02.03.03 
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#ifndef CC_TelecommandManagerH
#define CC_TelecommandManagerH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "Telecommand.h"
#include "TelecommandLoader.h"

/**
 * This class encapsulates a telecommand manager.
 * The telecommand manager is the component that is responsible for controlling
 * execution of telecommands.
 * Telecommands are loaded into the telecommand manager (normally by the
 * telecommand loader) and from that
 * moment onward their execution remains under the control of the telecommand
 * manager.
 * The telecomand manager sees telecommands as objects of type
 * <CODE>Telecommand</CODE>.
 * <p>
 * The telecommand manager maintains a list of pending telecommand objects.
 * This is called the <i>pending telecommand list</i>.
 * The <i>pending telecommands</i> are the telecommand objects that are
 * currently loaded into the telecommand manager and that
 * are due for execution.
 * Execution can be immediate or it can be deferred to a certain time
 * (time-tagged telecommands).
 * Before a telecommand is executed, the <i>execution check</i> is performed
 * upon it.
 * In this way, the telecommand has a way of checking whether the conditions
 * for its execution are fulfilled.
 * If the execution check fails, the telecommand is aborted.
 * <p>
 * When a telecommand is loaded into the telecommand manager, the telecommand
 * manager performs a <i>validity check</i>
 * upon it.
 * If the validity check fails, the telecommand is immediately aborted.
 * <p>
 * After being executed, or after being aborted, a telecommand is <i>unloaded</i>.
 * This means that the telecommand is removed from the list of pending
 * telecommands and that the telecommand loader is notified that the
 * telecommand is no longer in use.
 * This allows the telecommand loader to release any resources that it had
 * allocated to the telecommand and to perform any other clean-up actions.
 * <p>
 * Telecommands can be <i>aborted</i>.
 * An abort operation consists in the unloading of a telecommand that has not
 * yet been executed.
 * <p>
 * The telecommand manager creates event reports to record the following
 * occurrences: a telecommand has been loaded; a telecommand has been
 * unloaded; a telecommand has been aborted; a telecommand could not be
 * loaded because it failed its validity check; a telecommand could
 * not be loaded because the list of telecommands was full; a
 * telecommand could not be executed because its execution check failed.
 * Note that execution of the telecommand is not recorded because
 * telecommands are punctual actions and
 * therefore their execution is automatically recorded as an event
 * by the services provided by the <code>PunctualAction</code> class.
 * <p>
 * The configuration procedure for a newly instantiated telecommand
 * manager is as follows: <ol>
 * <li>Load an OBS clock in the telecommand manager (method
 * <code>setObsClock</code>.</li>
 * <li>Load a telecommand loader in the telecommand manager (method
 * <code>setTelecommandLoader</code>.</li>
 * <li>Set the size of the pending telecommand list (method
 * <code>setPendingTelecommandListSize</code>).</li>
 * </ol>
 * The above operations can be execute in any order.
 * <p>
 * The telecommand manager is intended to be used "as is" and without
 * changes. However, the <code>load</code>, <code>abort</code> and
 * <code>activate</code> methods are marked virtual to
 * allow users to customize their logic.
 * @todo extend the test case for the telecommand manager to check the
 * generation of an event in case the telecommand execution is not successful
 * @todo the name of method setPendingTelecommandListSize is not consistent with
 * the name of the equivalent method in class ManoeuvreManager (which is simply
 * called setPendingListSize. The two names should perhaps be harmonized.
 * @see Telecommand
 * @see TelecommandLoader
 * @see PunctualAction
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup FunctionalityManagers
 * @ingroup Telecommand
 */
class CC_TelecommandManager : public CC_RootObject {

  private:
    Telecommand** pTcList;    // array of pointers -- pending telecommand list
    unsigned int tcListSize;
    unsigned int tcCounter;   // number of pending telecommands
    TelecommandLoader* pTcLoader;
    ObsClock* pObsClock;

  public:

    /**
     * Instantiate a telecommand manager.
     * The size of the pending telecommand list is initialized to an illegal
     * value to signify that the telecommand manager is not yet configured.
     * The class identifier is set.
     */
    CC_TelecommandManager(void);

    /**
     * Abort all pending telecommands. A reset bring the telecommand manager
     * to the state where it was immediately after having being configured.
     */
    void reset(void);

    /**
     * Set the size of the pending telecommand list representing the maximum
     * number of pending telecommands that can be managed by the telecommand
     * manager.
     * This method causes memory for the pending telecommand list data
     * structure to be allocated and the data structure to be
     * initialized. Only positive telecommand list sizes are legal.
     * <p>
     * This is an initialization method. It should be called before the
     * telecommand manager is used the first time and it should not be called more
     * than once.
     * @param listSize the maximum number of pending telecommands that can be
     * managed by the Telecommand Manager. This should be a positive number.
     */
    void setPendingTelecommandListSize(unsigned int listSize);

    /**
     * Get the size of the pending telecommand list.
     * @see #setPendingTelecommandListSize
     * @return the maximum number of pending telecommands that can be
     * managed by the Telecommand Manager
     */
    unsigned int getPendingTelecommandListSize(void);

    /**
     * Get the number of currently pending telecommands.
     * @see #setPendingTelecommandListSize
     * @return the number of currently pending telecommands
     */
    unsigned int getPendingTelecommands(void);

    /**
     * Get the i-th pending telecommand (only provided for testing purposes). 
     * This method returns the i-th entry in the list of pending telecommands.
     * The index i should be in the range [0,N-1] where N is the size of the telecommand
     * lending list. A null
     * pointer is returned if no telecommand is currently loaded at the i-th
     * position of the list. This method is only intended to be used for
     * testing purposes. It should not be used during normal operation.
     * @see #setPendingTelecommandListSize
     * @return the i-th pending telecommand or null if the i-the entry in the list is empty
     */
    Telecommand* getPendingTelecommand(unsigned int i);

    /**
     * Load a telecommand. When a telecommand is loaded, it is inserted in
     * the list of pending telecommands and will then be considered for execution.
     * Immediately after being loaded, a validity check is performed on the
     * telecommand.
     * If the validity check fails, an event is created to record the fact and
     * the telecommand is aborted.
     * The telecommand remains loaded until it has terminated execution or is
     * aborted.
     * The telecommand manager creates an event whenever a new telecommand is
     * loaded.
     * If the list of pending telecommands is already full, an event report
     * is created to record the attempted telecommand load and the telecommand
     * is aborted.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      if (telecommand is not valid)
     *      {   createEventReport(EVT_TC_NOT_VALID);
     *          pTcLoader->release(telecommand);  // notify telecommand loader
     *          return;
     *      }
     *      if (list of pending telecommand is full)
     *      {   createEventReport(EVT_TC_LIST_FULL);
     *          pTcLoader->release(telecommand);  // notify telecommand loader
     *          return;
     *      }
     *      createEventReport(EVT_TC_LOADED);
     *      . . .       // insert telecommand in list of pending telecommands
     *      return; </PRE>
     * The telecommand that is being loaded is passed as the
     * <i>event originator</i> to the event reporting method.
     * @param pTelecommand the telecommand that is loaded
     */
    virtual void load(Telecommand* pTelecommand);

    /**
     * Abort a telecommand.
     * The telecomand is unloaded without being executed.
     * The telecommand loader is notified that the telecommand has been unloaded.
     * If the argument telecommand is not currently loaded, no action is
     * taken.
     * An event report is created whenever a telecommand is aborted.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      for (all telecommands tc in pending telecommand list)
     *          if (tc eq pTelecommand)
     *          {   . . .   // delete tc from list of pending TC
     *              pTcLoader->release(tc);
     *              createEventReport(EVT_TC_ABORTED);
     *          }
     *      return; </PRE>
     * The telecommand that is being aborted is passed as the
     * <i>event originator</i> to the event reporting method.
     * @see TelecommandLoader#release
     * @param pTelecommand the telecommand to be aborted
     */
    virtual void abort(Telecommand* pTelecommand);

    /**
     * Abort a telecommand.
     * This method has the same semantics as the abort method that takes a
     * telecommand pointer as argument but it designates the telecommand to
     * be aborted by its identifier rather than through a pointer to the
     * object that encapsulates it. See the documentation of that method
     * for more information.
     * <p>
     * However, note that in this case, if a telecommand with a given id
     * appears more than once in the pending telecommand list (e.g. with two
     * different time tags), then all its instances will be aborted.
     * @see abort
     * @see TelecommandLoader#release
     * @param telecommandId the telecommand to be aborted
     */
    void abort(TD_TelecommandId telecommandId);

    /**
     * Load the telecommand loader as a plug-in component.
     * The telecommand manager needs access to the telecommand loader because
     * it must notify it when a telecommand is unloaded.
     * @see #activate
     * @see #abort
     * @param pTcLoader the telecommand loader
     */
    void setTelecommandLoader(TelecommandLoader* pTcLoader);

    /**
     * Getter method for the telecommand loader plug-in component.
     * @see #setTelecommandLoader
     * @return the telecommand loader
     */
    TelecommandLoader* getTelecommandLoader(void);

    /**
     * Load the OBS clock as a plug-in component.
     * The telecommand manager needs access to the on-board time because it
     * needs to check the telecommand time tag with the current time.
     * @see #activate
     * @param pObsClock the on-board clock
     */
    void setObsClock(ObsClock* pObsClock);

    /**
     * Getter method for the OBS clock plug-in component.
     * @see #setObsClock
     * @return the on-board clock
     */
    ObsClock* getObsClock(void);

    /**
     * Go through the list of pending telecommands and execute those that are
     * due for execution.
     * This method would typically be called by an external scheduler.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      for (all telecommands tc in the list of pending telecommands)
     *          if ( ( tc->getTimeTag() le currentTime ) OR ( tc->getTimeTag() eq 0 ) )
     *          {   if ( tc->canExecute() ) {
     *                  tcOutcome = tc->execute();
     *                  if (tcOutcome!=ACTION_SUCCESS)
     *                      createEventReport(EVT_TC_EXEC_FAIL);
     *                  else
     *                      createEventReport(EVT_TC_EXEC_SUCC);
     *              } else
     *                  createEventReport(EVT_TC_EXEC_CHECK_FAIL);
     *
     *              tcLoader->release(tc);
     *              . . .    // delete tc from list of pending telecommands
     *           }        </PRE>
     * The telecommand that is being processed is passed as the
     * <i>event originator</i> to the event reporting method.
    */
    virtual void activate(void);

    /**
     * Perform a class-specific configuration check on the telecommand
     * manager: verify that the pending telecommand list size has been set,
     * that the OBS clock has been loaded, and that the telecommand loader has
     * been loaded.
     * @return true if the telecommand manager is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif

//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PunctualActionListModeManager.h
//
// Version	1.0
// Date		24.01.04
// Author	A. Pasetti (P&P Software)

#ifndef PunctualActionListModeManagerH
#define PunctualActionListModeManagerH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualActionModeManager.h"

/**
 * Base abstract class for list-based punctual action mode managers.
 * A list-based punctual action mode manager handles the set of 
 * punctual action in a punctual action mode manager as a statically defined 
 * linear list. 
 * The mode manager maintains several such lists, one for each
 * operational mode.
 * <p>
 * At any given time, one list is the <i>current list</i> (or
 * <i>active list</i>).
 * The iteration methods specified in the super class are implemented
 * to iterate over the items in the list starting with the one with the 
 * lowest position and ending with the one with the highest position
 * in the list.
 * <p>
 * The lists are loaded, one item at a time, when the mode manager
 * is configured. The loading methods
 * are: <code>loadListLength</code> (to load the number
 * items in each list) and <code>loadItem</code>
 * (to load the individual items in each list).
 * <p>
 * This class is abstract because it does not define the update
 * mechanism for the mode manager. This must be defined by concrete
 * subclasses.
 * </p>
 * An initialization sequence for this class consists of the following
 * steps (to be performed in the order given): <ul>
 * <li>Set the number of modes through method <code>setNumberOfModes</code></li>
 * <li>Set the default mode <code>setDefaultMode</code></li>
 * <li>Set the lengths of the lists through method
 * <code>setListLength</code></li>
 * <li>Load the individual items through method <code>setListItem</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Base
 * @ingroup ModeManagement
 */
class PunctualActionListModeManager : public PunctualActionModeManager {

  private:

    PunctualAction*** list;    // list[i][j] is the j-th item in the i-th list

    unsigned int* listLength;   // listLength[i] is the length of the i-th list

    unsigned int iterationListIndex;  // the index of the iteration list
    unsigned int counter;             // iteration counter

  protected:

    /**
     * Allocate the memory for the lists. The newly allocated memory
     * is initialized with pNULL. Note that this method
     * cannot allocate all the memory required by a list mode manager because
     * this also depends on the number of items in each list. This number is loaded
     * with method: <code>setLength</code>.
     * <p>
     * This method is called by method <code>setNumberOfModes</code> in the
     * superclass <code>ModeManager</code>.
     * <p>
     * This is an initialization method. It should only be called once. The number
     * of modes should be greater than zero.
     * @see ModeManager#setNumberOfModes
     * @param numberOfModes the number of modes
     */
    virtual void allocateMemory(TD_Mode numberOfModes);

  public:

    /**
     * Retrieve the punctual action currently scanned by the iteration counter.
     * This method returns the counter-th item in the iteration list where
     * "counter" is the iteration counter.
     * This method should only be used within an iteration cycle. However, it is
     * guaranteed to return a reference to a list item at all times.
     * @see #first
     * @return the item currently scanned by the iteration counter
     */
    virtual PunctualAction* getIterationPunctualAction(void);

    /**
     * Load an item in a list. The item <code>pItem</code> is loaded in the pos-th
     * position of the n-th list. A check is performed on the legality of the
     * <code>n</code> and <code>pos</code> arguments. If they are found
     * to be out of range, the fact is reported as an event of type EVT_ILLEGAL_MM.
     * <p>
     * @param n the list index
     * @param pos the position within the list where the item is loaded
     * @param pItem the item to be loaded
     */
    void setListItem(unsigned int n, unsigned int pos, PunctualAction* pItem);

    /**
     * Instantiate a punctual action mode manager component. The internal data
     * variables are initialized to illegal values to signify that the component
     * is not yet configured.
     */
    PunctualActionListModeManager(void);

    /**
     * Set the size of the n-th list. The n-th list is the list that is active
     * in the n-th operational mode.
     * A call to this method causes memory to be allocated to store the items in
     * the n-th list. The newly allocated memory is initialized
     * to pNULL.
     * <p>
     * This is an initialization method. It should only be called once.
     * @param n the list index (should be in the range [0,N-1] where N is the
     * number of modes)
     * @param length the number of items in the list-th telemetry packet list (should
     * be greater than zero)
     */
    void setListLength(unsigned int n, unsigned int length);

    /**
     * Iteration method to iterate through the punctual actions in the current
     * list. This method should be used jointly with methods: <code>next</code>,
     * <code>isIterationFinished</code> and <code>getPunctualAction</code>. 
	 * Taken together,
     * these methods allow all the items in a list to be scanned. The list
     * that is thus iterated through is called the <i>iteration list</i>.
     * The iteration list is the current list at the time method <code>first</code>
     * is called. This list is
     * guaranteed to remain unchanged in between successive calls to
     * method <code>first</code>. Thus, even if the current mode changes
     * during the iteration (for instance, following a call to method
     * <code>update</code>), the iterators will continue processing the
     * list that was active when <code>first</code> was called.
     * <p>
     * This class internally maintains an <i>iteration
     * counter</i>. During an iteration cycle, the iteration counter is
     * incremented from zero to (N-1) where N is number of items in the
     * iteration list. Method <code>first</code> resets the iteration counter
     * to 0. A call to method <code>next</code> causes the iteration counter
     * to be incremented by 1 up to the value of (N-1). Method <code>isIterationFinished</code>
     * returns true when the counter has reached the value (N-1).
     * The item currently pointed at by the iteration counter can be retrieved
     * through method <code>getPunctualAction</code>.
     * <p>
     * Thus, a typical iteration cycle might be organized as follows: <PRE>
     *      for (first(); !isIterationFinished(); next()) {
     *          pItem = getIterationPunctualAction();
     *          . . .    // process pItem
     *      }  </PRE>
     */
    virtual void first(void);

    /**
     * Iteration method to be used in conjunction with methods <code>first</code>
     * and <code>isIterationFinished</code>.
     * @see #first
     */
    virtual void next(void);

    /**
     * Iteration method to be used in conjunction with methods <code>first</code>
     * and <code>next</code>.
     * This method should only be used as part of an iteration cycle. The result
     * of calling it before ever calling <code>first</code>
     * is undefined.
     * @see #first
     * @return true if the end of the iteration has been reached, false otherwise
     */
    virtual bool isIterationFinished(void);

	/**
     * Perform a class-specific configuration check on a punctual action mode
     * manager: verify that all the lists have been initialized
     * and that all the items have been loaded.
     * @return true if the list mode manager is configured, false
     * otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif

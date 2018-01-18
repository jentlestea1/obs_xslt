//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DataPool.h
//
// Version	1.0
// Date		12.09.03
// Author	A. Pasetti (P&P Software)

#ifndef DataPoolH
#define DataPoolH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all data pool classes are derived.
 * A <i>data pool</i> is a component that acts as a shared data area for data
 * that must be exchanged among other components. The data pool physically
 * contains the data to be exchanged. The producers of the data deposit them into
 * the data pool and the consumers of the data retrieve them from the data pool.
 * This class implements a data pool as a collection of items with the
 * following attributes: <ul>
 * <li>Each item in the data pool has a <i>value</i>.</li>
 * <li>Each item in the data pool has a <i>time stamp</i> that represents
 * the time when the value of the item was last updated.</li>
 * <li>Each item in the data pool has a <i>type</i> that represents
 * the syntactical type of the value of the item. This interface recognizes
 * two possible types: "float" and "integer" that, at syntactical level, correspond
 * to two types defined through <code>typedef</code> declarations (<code>TD_Float</code>
 * and <code>TD_Integer</code>).</li>
 * <li>Each item in the data pool is identified by a <i>data pool item identifier</i>.
 * Access to the value of the item is exclusively through its identifier.
 * Note that this class does not mandate any checks on the legality of the data
 * identifier used by a caller. This is not done because of the potential execution
 * and memory costs of such checks. Legality checks can however be introduced by
 * some implementations if needed.</li>
 * <li>Each item in the data pool has a <i>validity status</i> that
 * can have two values: "valid" and "not valid".</li>
 * <li>Each item in the data pool has an associated <i>monitoring profile</i>
 * that represents the legal time profile that the value of the data pool item
 * can take.</li>
 * <li>Each item in the data pool has an associated <i>recovery action</i> that represents
 * the recovery action that should be performed when the value of the item violates
 * its monitoring profile.</li>
 * </ul>
 * This is an abstract class because the internal organization of the
 * data pool is application-dependent. In particular, the data structure used to
 * represent the data pool and the implementation of the attributes defined above
 * is left undefined. Full
 * implementation of all the above attributes would
 * result in a very "heavy" class that would not be suitable for applications
 * with tight memory and CPU budgets. Most concrete data pool classes will
 * only provide meaningful implementations for only a subset of the
 * above attributes.
 * <p>
 * This class defines the following service: <ul>
 * <li>The <i>iteration service</i> that allows a client to
 * iterate over all the identifiers of the items contained in the data
 * pool.</li>
 * <li>The <i>type checking service</i> that allows a client to check the type
 * of an item as a function of its identifier. The type checking service
 * can also be used to check whether a certain integer is a legal identifier.</li>
 * <li>The <i>reset service</i> that resets the validity status of all data pool
 * items to the value they had at the time the data pool component was initialized.</li>
 * </ul>
 * The purpose of a data pool is to allow client components to link to it
 * to access data which they share with other components. This data pool
 * offers three types of linking mechanism to a client component:<ul>
 * <li><i>Copy Link</i>: the client component accesses the value of the
 * shared datum through data setter and getter methods. The shared datum
 * is copied to and from the data pool.</li>
 * <li><i>Pointer Link</i>: at configuration time, the client component
 * accesses the pointer of the shared datum and then uses this pointer
 * to access the value of the datum during the operational phase.</li>
 * <li><i>Data Item Link</i>: at configuration time, the client component
 * accesses the <i>data item</i> that encapsulates the shared datum and
 * accesses its value during during the operational phase using the services
 * defined by the <i>DC_DataItem</i> class.</li>
 * </ul>
 * A data pool is a low-level data structure whose implementation will
 * usually require use of pointers. Most implementations of this class
 * will therefore violate project specific coding rule PR3.1.
 * <p>
 * @todo This class defines the setter and getter methods to be virtual. This
 * is expensive in CPU time. Given that data pool implementations will often
 * be generated automatically by XSL programs, and given that an application
 * would normally only have one data pool component, it may be wiser to 
 * have the XSL program generate an implementation for class DataPool that 
 * is defined to have only non-virtual methods. The problem with this approach
 * is that it is not possible to have multiple implementations of a data pool
 * in a single delivery and that therefore it is not possible to have several
 * data pool test cases in the same delivery (this could be alleviated by
 * generating the test case for the data pool as well as the data pool 
 * implementation). 
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Data
 */
class DataPool : public CC_RootObject {

  private:
    DC_NullProfile* pNullProfile;
    DC_NullRecoveryAction* pNullRecoveryAction;
    TD_Integer dummyInt;
    DC_DataItem* pDummyDataItem;

  public:

    /**
     * Instantiate a data pool object.
     */
    DataPool(void);

    /**
     * Setter method for the value of a real-typed data pool item.
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
    virtual void setValue(TD_DataPoolId id, TD_Float newValue) = 0;

    /**
     * Setter method for the value of an integer-typed data pool item.
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
    virtual void setValue(TD_DataPoolId id, TD_Integer newValue) = 0;

    /**
     * Getter method for the value of a real-typed data pool item.
     * This method implements the <i>copy link</i>
     * mechanism for real-valued data.
     * @param id the data identifier of the data pool item to be read
     * @return the value of the data with identifier id
     */
    virtual TD_Float getFloatValue(TD_DataPoolId id) = 0;

    /**
     * Getter method for the value of an integer-typed data pool item.
     * This method implements the <i>copy link</i>
     * mechanism for integer-valued data.
     * @param id the data identifier of the data pool item to be read
     * @return the value of the data with identifier id
     */
    virtual TD_Integer getIntegerValue(TD_DataPoolId id) = 0;

    /**
     * Getter method for the pointer to a real-typed data pool item.
     * This method implements the <i>pointer link</i>
     * mechanism for real-typed data.
     * @param id the data identifier of the data pool item to be read
     * @return the pointer to the data with identifier id
     */
    virtual TD_Float* getPointerFloatValue(TD_DataPoolId id) = 0;

    /**
     * Getter method for the pointer to an integer-typed data pool item.
     * This method implements the <i>pointer link</i>
     * mechanism for integer-typed data.
     * @param id the data identifier of the data pool item to be read
     * @return the pointer to the data with identifier id
     */
    virtual TD_Integer* getPointerIntegerValue(TD_DataPoolId id) = 0;

    /**
     * Getter method for a <i>data item</i> that encapsulates a
     * data pool item. This method implements the <i>data item link</i>
     * mechanism.
     * This class provides a default implementation that returns
     * a data item that encapsulates an internal variable of type "unsigned
     * integer" and with a constant value of zero. This default
     * implementation is useful for
     * subclasses that do not wish to implement a <i>data item link</i>
     * mechanism.
     * @see DC_DataItem
     * @param id the data identifier of the data pool item to be read
     * @return the <code>DC_DataItem</code> item encapsulating the data
     * pool item with identifier id
     */
    virtual DC_DataItem* getDataItem(TD_DataPoolId id);

    /**
     * Return the time stamp of a data pool item.
     * The time stamp of a data pool item is normally set by the setter
     * method when the item value is updated.
     * This class provides a default implementation that always returns zero.
     * @param id the data identifier of the data whose time stamp is sought
     * @return the time stamp of the data with identifier id
     */
    virtual TD_ObsTime getTimeStamp(TD_DataPoolId id);

    /**
     * Return the validity status of a data pool item.
     * This class provides a default implementation that always returns "data valid".
     * @param id the data identifier of the data pool item
     * @return true if the data pool item is valid, false otherwise
     */
    virtual bool isValid(TD_DataPoolId id);

    /**
     * Set the validity status of a data pool item.
     * This class provides a default implementation that returns without taking any action.
     * @param id the data identifier of the data pool item
     * @param newValidityStatus the new validity status
     */
    virtual void setValidityStatus(TD_DataPoolId id, bool newValidityStatus);

    /**
     * Get the monitoring profile for a data pool item.
     * This class provides a default implementation that returns the same
     * dummy monitoring profile (an instance of <code>DC_NullMonitoringProfile</code>) for
     * all values of the parameter identifier.
     * Note that this class does not define any setter method for the monitoring
     * profile. This is because different implementations may have different policies
     * for defining the monitoring profiles. In a typical case, to each data pool
     * item a particular and fixed monitoring profile is associated. In this case, the data pool
     * class would offer a setter method for the monitoring profile. In another typical
     * case, the monitoring profiles are mode-dependent: the association between a
     * particular data pool item and its monitoring profile is a function of the
     * operational mode. In that case, the monitoring profiles are dynamically
     * loaded by a <i>mode manager</i> and the data pool class only exposes a
     * a setter method for this mode manager.
     * @param id the identifier of the data pool item
     * @return the monitoring profile
     */
    virtual MonitoringProfile* getMonitoringProfile(TD_DataPoolId id);

    /**
     * Get the recovery action for a data pool item.
     * This class provides a default implementation that returns the same
     * dummy recovery action (an instance of <code>DC_NullRecoveryAction</code>) for
     * all values of the parameter identifier.
     * Note that this class does not define any setter method for the recovery
     * action. This is because different implementations may have different policies
     * for defining the recovery actions. In a typical case, to each data pool
     * item a particular and fixed recovery action is associated. In this case, the data pool
     * class would offer a setter method for the recovery action. In another typical
     * case, the recovery actions are mode-dependent: the association between a
     * particular data pool item and its recovery action is a function of the
     * operational mode. In that case, the recovery actions are dynamically
     * loaded by a <i>mode manager</i> and the data pool class only exposes a
     * a setter method for this mode manager.
     * @param id the identifier of the data pool item
     * @return the recovery action
     */
    virtual RecoveryAction* getRecoveryAction(TD_DataPoolId id);

    /**
     * Iteration method that resets the iteration and returns the lowest
     * indentifier of the items in the data pool. This method is used in
     * conjunction with the other two iteration methods <code>nextIdentifier</code>
     * and <code>isLastIdentifier</code>. These three methods are typically
     * used in a for-loop as follows: <pre>
     *		for (unsigned int i=firstIdentifier(); !isLastIdentifier(); i=nextIdentifier())
     *			... // process i-th item in the data pool  </pre>
     * The conceptual model behind the iteration methods is as follows.
     * The data pool maintains an internal <i>iteration pointer</i>. During an
     * iteration, this pointer scans all the items in the data pool in sequence.
     * When method <code>firstIdentifier</code> is called, the pointer is reset
     * to point to the lowest valued identifier in the data pool. Each call to method
     * <code>nextIdentifier</code> causes this pointer to switch to the next
     * higher valid identifier in the data pool. Users can check the progress
     * of the iteration by calling method <code>isLastIdentifier</code> which
     * returns false if (and only if) the pointer is positioned on the highest
     * valued identifier in the data pool.
     * <p>
     * This class provides a default implementation that always returns zero.
     * Note that the value of zero is not a legal identifier. This default
     * implementation is useful for the case where a data pool is unable or
     * unwilling to provide a meaningful implementation for the iteration
     * services.
     * @see #nextIdentifier
     * @see #isLastIdentifier
     * @return the identifier of the first data pool item in the iteration
     */
    virtual TD_DataPoolId firstIdentifier(void);

    /**
     * Iteration method that returns the next identifier in an iteration.
     * This method is used in
     * conjunction with the other two iteration methods <code>firstIdentifier</code>
     * and <code>isLastIdentifier</code>.
     * This method should only be called after having called method
     * <code>firstIdentifier</code> and while method <code>isLastIdentifier</code>
     * returns false. If these conditions do not hold, the return value of this
     * method is undefined.
     * <p>
     * This class provides a default implementation that always returns zero.
     * Note that the value of zero is not a legal identifier. This default
     * implementation is useful for the case where a data pool is unable or
     * unwilling to provide a meaningful implementation for the iteration
     * services.
     * @see #firstIdentifier
     * @see #isLastIdentifier
     * @return the identifier of the next data pool item in the iteration
     */
    virtual TD_DataPoolId nextIdentifier(void);

    /**
     * Iteration method that checks whether an iteration is finished.
     * This method is used in
     * conjunction with the other two iteration methods <code>firstIdentifier</code>
     * and <code>isLastIdentifier</code>. It returns true when the iteration
     * is finished.
     * The iteration is finished if method <code>nextIdentifier</code> has been called
     * N times since the last time method <code>isFirstIdentifier</code> was called
     * where N is the number of items in the data pool
     * <p>
     * This class provides a default implementation that always returns true.
     * This default
     * implementation is useful for the case where a data pool is unable or
     * unwilling to provide a meaningful implementation for the iteration
     * services.
     * @see #nextIdentifier
     * @see #firstIdentifier
     * @return true if the iteration has completed, false otherwise
     */
    virtual bool isLastIdentifier(void);

    /**
     * Method implementing the type checking service to check whether a
     * data pool item is real-valued.
     * A real-value item is an item with a value whose syntactical type
     * is <code>TD_Float</code>.
     * This method returns true if the argument is the identifier of a
     * data pool item that is real-typed. The method returns false if the
     * identifier is either illegal (there is no item in the data pool
     * that takes it as its identifier) or if the identifier identifies a
     * an item that is integer-valued.
     * <p>
     * This method is often used during an iteration to verify whether the
     * data item being iterated upon is real-valued. This is important because
     * it allows the client to decide which getter method to use to retrieve
     * its value.
     * Note that this class also offers a method to check whether a data pool
     * item is integer-valued (method <code>isInteger</code>). Since a
     * data item must be either real-valued or integer-valued, these two
     * methods taken together allow a client to check whether to a particular
     * identifier value there corresponds a data item or not.
     * <p>
     * This class provides a default implementation that always returns true.
     * This default
     * implementation is useful for the case where a data pool is unable or
     * unwilling to distinguish between real-valued and integer-valued items.
     * @see #isInteger
     * @see id the identifier of the data pool item
     * @return true if the id is the identifier of a floating point data pool item,
     * false otherwise
     */
    virtual bool isFloat(TD_DataPoolId id);

    /**
     * Method implementing the type checking service to check whether a
     * data pool item is integer-typed.
     * This method is the counterpart of method <code>isFloat</code>.
     * This class provides a default implementation that always returns
     * true.
     * @see #isFloat
     * @see id the identifier of the data pool item
     * @return true if the id is the identifier of an integer data pool item,
     * false otherwise
     */
    virtual bool isInteger(TD_DataPoolId id);

    /**
     * Implement the data pool reset service.
     * The validity status of all data pool item is reset to the value it
     * had at the time the data pool component was created. This class
     * provides a default implementation that returns without doing anything.
     * @see #isValid
     */
    virtual void reset(void);

};

#endif

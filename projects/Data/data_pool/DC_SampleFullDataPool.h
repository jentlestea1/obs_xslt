  
//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_SampleFullDataPool.h
//
// The code in this file was automatically generated 

#ifndef DC_SampleFullDataPoolH
#define DC_SampleFullDataPoolH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DataPool.h"
#include "../Data/DC_SampleFullDataPool_inc.h"

/**
 * Sample data pool with full functionality..
 * The code for this class was automatically generated by an XSL program
 * using as input an XML-based description of the data pool. This class
 * fully defines the structure of the data pool: its constructor allocates memory
 * for all internal data structures and it initializes them to reflect the
 * data pool layout defined in the XML-based data pool descriptor file.
 * <p>
 * This data pool has the following characteristics: <ul>
 * <li>Time stamp attached to each data pool item. 
 * Its value is updated to 
 * the current time every time the setter method for the data pool item is called.
 * The current time is read from a plug-in <code>ObsClock</code> component</li>
 * <li>High level of robustness to use of illegal
 * identifier values in method calls: legality of the identifier value
 * is always checked in assertions and in run-time checks. Detection
 * of an illegal value results in the generation of an event report of type 
 * EVT_ILLEGAL_DP_ACCESS</li>. 
 * <li>Validity status flag attached to 
 * each data pool item. </li>
 * <li>Back-up value attached to each data pool item.
 * When the validity status of the data pool item
 * is equal to "valid", then the back-up value is kept identical to the primary value.
 * When the validity status of the data pool item
 * changes from "valid" to "not valid", then the primary value is no longer updated and
 * the getter method and getDataItem method for the data pool item will return the back-up
 * value. Note that the back-up mechanism is only effective for clients that link to the
 * data pool items through the <i>copy link</i> or the <i>data item link</i>
 * mechanism. It is not
 * effective for clients that use the <i>pointer link</i> mechanism.</li> 
 * <li>Data item (instance of class <code>DC_DataItem</code>) attached to each
 * data pool item. </li>
 * <li>Monitoring profile
 * (instance of class <code>MonitoringProfile</code>) attached to each data pool
 * item. </li>
 * <li>Recovery action
 * (instance of class <code>RecoveryAction</code>) attached to each data pool
 * item. </li>
 * <li>Type checking service fully implemented. </li>
 * </ul>
 * Note that an include file (<code>DC_SampleFullDataPool_inc.h</code>) 
 * is also automatically generated that defines symbolic names to access the items in the data pool. 
 * @author Automatically Generated
 * @version 1.0
 */
class DC_SampleFullDataPool : public DataPool {

  private:
      TD_Float* pDefaultFloat;
      TD_Integer* pDefaultInt;
      unsigned char* value;
      unsigned char** pValue;
      TD_DataPoolId size;
      TD_DataPoolId maxParId;
      TD_DataPoolId iterationCounter; 
      unsigned char** pBackUpValue;      
      unsigned char* backUpValue;
 
      ObsClock* pObsClock;
      TD_ObsTime* timeStamp;        
      bool* valid;   
      DC_SettableDataItem** pDataItem;    
      MonitoringProfile** pMonitoringProfile;       
      RecoveryAction** pRecoveryAction;       
      char* type;                 

  public:
    /**
     * Instantiate a data pool component. The class identifier is set.
     * All internal data structures are allocated and initialized.
     * The data pool is internally implemented as a linear array. In order
     * to avoid alignment problems, this array is forced to be aligned with
     * an 8-byte word boundary (more specifically, it is aligned with a 
     * location that can store a value of type <code>double</code>).
     * The time stamp of all data pool items is initialized to zero.
     * The validity status of all data pool items is initialized to "valid". 
     * The plug-in OBS Clock component is initialized to an illegal value to signify that the
     * data pool component is not yet configured.   
     */
    DC_SampleFullDataPool(void);

    /**
     * Load the OBS Clock component. The data pool needs access to
     * this component in order to time-stamp new values of data pool items.
     * @param pObsClock the OBS Clock component.
     */
    void setObsClock(ObsClock* pObsClock);

    /**
     * Return the OBS Clock component.
     * @see #setObsClock
     * @return the OBS Clock component.
     */
    ObsClock* getObsClock(void) const;
 
    /**
     * Setter method for the value of a real-typed data pool item. 
     * When this method is called on a data pool item, its time stamp is
     * automatically updated.       
     * If the validity status of the data pool item is "valid", then its
     * back up value is also updated.
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
    virtual void setValue(TD_DataPoolId id, TD_Float newValue);

    /**
     * Setter method for the value of an integer-typed data pool item.  
     * When this method is called on a data pool item, its time stamp is
     * automatically updated.       
     * If the validity status of the data pool item is "valid", then its
     * back up value is also updated.
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
    virtual void setValue(TD_DataPoolId id, TD_Integer newValue);

    /**
     * Getter method for the value of a real-typed data pool item.
     * This method implements the <i>copy link</i>
     * mechanism for real-valued data. 
     * If the validity status of the data pool item is "not valid", then the
     * back up value of the data pool item is returned.
     * @param id the data identifier of the data pool item to be read
     * @return the value of the data with identifier id
     */
    virtual TD_Float getFloatValue(TD_DataPoolId id);

    /**
     * Getter method for the value of an integer-typed data pool item.
     * This method implements the <i>copy link</i>
     * mechanism for integer-valued data.   
     * If the validity status of the data pool item is "not valid", then the
     * back up value of the data pool item is returned.
     * @param id the data identifier of the data pool item to be read
     * @return the value of the data with identifier id
     */
    virtual TD_Integer getIntegerValue(TD_DataPoolId id);

    /**
     * Getter method for the pointer to a real-typed data pool item.
     * This method implements the <i>pointer link</i>
     * mechanism for real-typed data. 
     * @param id the data identifier of the data pool item to be read
     * @return the pointer to the data with identifier id
     */
    virtual TD_Float* getPointerFloatValue(TD_DataPoolId id);

    /**
     * Getter method for the pointer to an integer-typed data pool item.
     * This method implements the <i>pointer link</i>
     * mechanism for integer-typed data.
     * @param id the data identifier of the data pool item to be read
     * @return the pointer to the data with identifier id
     */
    virtual TD_Integer* getPointerIntegerValue(TD_DataPoolId id);

    /**
     * Getter method for a <i>data item</i> that encapsulates a
     * data pool item. This method implements the <i>data item link</i>
     * mechanism.
     * If the validity status of the data pool item is "not valid", then the
     * data item returned by this method is dynamically reconfigured to point to
     * back up value of the data pool item.
     * @see DC_DataItem
     * @param id the data identifier of the data pool item to be read
     * @return the <code>DC_DataItem</code> item encapsulating the data
     * pool item with identifier id
     */
    virtual DC_DataItem* getDataItem(TD_DataPoolId id);

    /**
     * Return the time stamp of a data pool item.
     * The time stamp of a data pool item is set by the setter
     * method when the item value is updated. Note that it the data pool item is
     * accessed using its pointer or its data item, then the time stamp is not
     * updated.
     * @param id the data identifier of the data whose time stamp is sought
     * @return the time stamp of the data with identifier id
     */
    virtual TD_ObsTime getTimeStamp(TD_DataPoolId id);

    /**
     * Return the validity status of a data pool item.
     * The value that is returned is the value that is set with method
     * <code>setValidityStatus</code>. 
     * @see #setValidityStatus
     * @param id the data identifier of the data pool item
     * @return true if the data pool item is valid, false otherwise
     */
    virtual bool isValid(TD_DataPoolId id);

    /**
     * Set the validity status of a data pool item.
     * If the data pool item identifier has an out-of-range value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS. 
     * @param id the data identifier of the data pool item
     * @param newValidityStatus the new validity status
     */
    virtual void setValidityStatus(TD_DataPoolId id, bool newValidityStatus);

    /**
     * Get the monitoring profile for a data pool item.
     * The component that is returned by this method is the component that is set loaded
     * with method <code>setMonitoringProfile</code>.
     * @see #setMonitoringProfile
     * @param id the identifier of the data pool item
     * @return the monitoring profile
     */
    virtual MonitoringProfile* getMonitoringProfile(TD_DataPoolId id);

    /**
     * Set the monitoring profile for a data pool item.
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  
     * @see #getMonitoringProfile
     * @param id the identifier of the data pool item
     * @param pMonitoringProfile the monitoring profile
     */
    virtual void setMonitoringProfile(TD_DataPoolId id, MonitoringProfile* pMonitoringProfile);

    /**
     * Get the recovery action for a data pool item.
     * The component that is returned by this method is the component that is set loaded
     * with method <code>setRecoveryAction</code>.
     * @see #setRecoveryAction
     * @param id the identifier of the data pool item
     * @return the monitoring profile
     */
    virtual RecoveryAction* getRecoveryAction(TD_DataPoolId id);

    /**
     * Set the recovery action for a data pool item.
     * If the data pool item identifier has an illegal value, then no action is taken other
     * than generating an event of type EVT_ILLEGAL_DP_ACCESS.  
     * @see #getRecoveryAction
     * @param id the identifier of the data pool item
     * @param pRcoveryAction the recovery action
     */
    virtual void setRecoveryAction(TD_DataPoolId id, RecoveryAction* pRcoveryAction);

    /**
     * Iteration method that resets the iteration and returns the lowest
     * indentifier of the items in the data pool.
     * @see DataPool#firstIdentifier
     * @return the identifier of the first data pool item in the iteration
     */
    virtual TD_DataPoolId firstIdentifier(void);

    /**
     * Iteration method that returns the next identifier in an iteration.
     * @see DataPool#firstIdentifier
     * @return the identifier of the next data pool item in the iteration
     */
    virtual TD_DataPoolId nextIdentifier(void);

    /**
     * Iteration method that returns the next identifier in an iteration.
     * @see DataPool#firstIdentifier
     * @return true if the iteration has completed, false otherwise
     */
    virtual bool isLastIdentifier(void);

    /**
     * Method implementing the type checking service to check whether a
     * data pool item is real-typed.
     * @see DataPool#isFloat
     * @see id the identifier of the data pool item
     * @return true if the id is the identifier of a real-valued data item,
     * false otherwise
     */
    virtual bool isFloat(TD_DataPoolId id);

    /**
     * Method implementing the type checking service to check whether a
     * data pool item is integer-typed.
     * @see DataPool#isInteger
     * @see id the identifier of the data pool item
     * @return true if the id is the identifier of a real-valued data item,
     * false otherwise
     */
    virtual bool isInteger(TD_DataPoolId id);

    /**
     * Implement the data pool reset service.
     * The validity status of all data pool item is reset to the value it
     * had at the time the data pool component was created.
     * @see #isValid
     */
    virtual void reset(void);

    /**
     * Perform a class-specific configuration check. The following checks are performed: <ul>
     * <li>All monitoring profiles have been loaded</li>
     * <li>All recovery actions have been loaded</li>
     * <li>The OBS Clock plug-in component has been loaded</li>
     * </ul>
     * @return true if the data pool object is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);


};

#endif

    
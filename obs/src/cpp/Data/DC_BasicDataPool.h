//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicDataPool.h
//
// Version	1.0
// Date		10.09.03 (Version 1.0)
// Author	A. Pasetti (P&P Software)
//

#ifndef DC_BasicDataPoolH
#define DC_BasicDataPoolH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DataPool.h"

/**
 * Default component implementing a data pool with basic functionality.
 * The data pool is implemented as a linear array whose index is the identifier
 * of the data pool item. Of all the attributes for data pool items defined in 
 * the base class, the only ones to have a non-dummy implementation are the value
 * and the identifier. For all other attributes, the default implementation inherited
 * from the base class is kept. Note in particular that there are no checks on the
 * legality of the identifier values used when accessing data pool items.
 * This results in a very efficient implementation both in terms of memory
 * and run-time overheads but it also results in a low level of robustness.
 * <p>
 * This class defines one single configuration method to set the size of the data pool.
 * <p>
 * The getter and setter methods are implemented to be fast and efficient but this
 * makes them vulnerable to alignement problems on some processors. For instance,
 * the setter methods for integer-valued variables is implemened as follows:<code>
 *  void DC_BasicDataPool::setValue(TD_DataPoolId id,TD_Integer newValue) {
 *   *(TD_Integer *)(value+id)=newValue;
 *   } </code>
 * On some processors, the assignment will fail if location <code>(value+id)</code> does not
 * correspond to a longword (4 bytes) boundary. There is no check to ensure that this
 * is the case and it is the responsibility of the user to ensure that the setter
 * method is called with the correct parameter values. The same applies to other
 * setter and getter methods. A more robust (but possibly slower) implementation
 * might use the <code>memcpy</code> library function to transfer the values of the
 * data between the data pool locations and the method variables.
 * @author Alessandro Pasetti (P&P Software)
 * @version 1.0
 */
class DC_BasicDataPool : public DataPool {

  private:
      unsigned char* value;                  
      TD_DataPoolId size;                   
 
  public:
    /**
     * Instantiate a data pool component. The class identifier is set.
     * The internal data structures are left uninitialized to signify that the
     * component is not yet configured.
     */
    DC_BasicDataPool(void);

    /**
     * Set the size of the internal array where the data pool items are stored.
     * After this method is called, the internal data structures for the data 
     * pool component are allocated and initialized to zero. 
     * <p>
     * The data pool is internally implemented as a linear array. In order to 
     * avoid alignment problems (see class comment), the array is forced to 
     * start at an 8-byte word boundary.
     * <p>
     * Only data pool size greater than zero are legal.
     * <p>
     * This is an initialization method. It should only be called once. If it is
     * called more than once, internal memory will be allocated multiple times. 
     * The memory allocated in previous calls is never reclaimed.
     * <p>
     * @param size the size of the data pool in number of bytes
     */
    void setDataPoolSize(TD_DataPoolId size);

    /**
     * Get the size of the data pool.
     * @see #setDataPoolSize
     * @return size of the data pool in number of bytes
     */
    TD_DataPoolId getDataPoolSize(void);

    /**
     * Setter method for the value of a real-typed data pool item. 
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
    virtual void setValue(TD_DataPoolId id, TD_Float newValue);

    /**
     * Setter method for the value of an integer-typed data pool item.  
     * @param id the data identifier of the data pool item to be set
     * @param newValue the new value to be set
     */
    virtual void setValue(TD_DataPoolId id, TD_Integer newValue);

    /**
     * Getter method for the value of a real-typed data pool item. 
     * This method implements the <i>copy link</i>
     * mechanism for real-valued data. 
     * @param id the data identifier of the data pool item to be read
     * @return the value of the data with identifier id
     */
    virtual TD_Float getFloatValue(TD_DataPoolId id);

    /**
     * Getter method for the value of an integer-typed data pool item. 
     * This method implements the <i>copy link</i>
     * mechanism for integer-valued data.   
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
     * Perform a class-specific configuration check on a data pool component:
     * verify that the size of the data pool has been set.
     * @see #reset
     * @return true if the database object is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);

};

#endif



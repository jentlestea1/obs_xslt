//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_BasicDatabase.h
//
// Version	1.0
// Date		13.10.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_BasicDatabaseH
#define DC_BasicDatabaseH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "ParameterDatabase.h"

/**
 * Default component implementing a basic parameter database.
 * The basic database implements the <i>Default Table</i> and the
 * <i>Operational Table</i> as linear arrays. The identifier of a parameter
 * is the index in the array at which the parameter is stored.
 * Syntactically, the elements of the table arrays are of char type but the
 * tables can hold elements of any type (the getter and setter operations defined
 * in this class will perform the necessary casting operations to convert
 * the raw bytes in the table arrays to the type required by the operation).
 * <p>
 * The default and operational tables are <i>not</i> defined by this class.
 * This class loads the tables using methods <code>setDefaultTable</code>
 * and <code>setOperationalTable</code>.
 * <p>
 * The configuration procedure for an instance of this class is as follows: <ol>
 * <li>Load the default table (method <code>setDefaultTable</code>)  </li>
 * <li>Load the operational table (method <code>setOperationalTable</code>)  </li>
 * <li>Set the length of the table (method <code>setTableLength</code>)  </li>
 * <li>Reset the component instance (method <code>reset</code>)  </li>
 * </ol>
 * This class is designed for efficiency. It does not perform any
 * legality checks on the access to the database. It therefore assumes that
 * the client components is using correct parameter identifiers.
 * <p>
 * The getter and setter methods are implemented to be fast and efficient but this
 * makes them vulnerable to alignement problems on some processors. For instance,
 * the setter methods for integer-valued parameters is implemened as follows:<code>
 * void DC_BasicDatabase::setParameter(TD_DatabaseId parId, int newValue) {
 *  *( (int*)(pOperationalTable+parId) ) = newValue;
 * }</code>
 * On some processors, the assignment will fail if location <code>(pOperationalTable+parId)</code> does not
 * correspond to a longword (4 bytes) boundary. There is no check to ensure that this
 * is the case and it is the responsibility of the user to ensure that the setter
 * method is called with the correct parameter values. The same applies to other
 * setter and getter methods. A more robust (but possibly slower) implementation
 * might use the <code>memcpy</code> library function to transfer the values of the
 * data between the database locations and the method variables.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_BasicDatabase : public ParameterDatabase {

  private:
      char* pDefaultTable;          // array of chars
      char* pOperationalTable;      // array of chars
      bool resetWasCalled;
      TD_DatabaseId tableLength;   // table length in bytes

  public:

    /**
     * Instantiate a basic database component.
     * The default and operational table arrays are initialized to illegal
     * values to signify that the component is not yet configured.
     * values. The class identifier is set.
     */
    DC_BasicDatabase(void);

    /**
     * Copy the default table array onto the operational table array.
     */
    virtual void reset(void);

    /**
     * Set the length of the default and operational table in number of
     * bytes. Only non-negative values of the length are legal.
     * <p>
     * This is an initialization method.
     * @param length the number of char elements in the default and in the
     * operational table
     */
    void setTableLength(TD_DatabaseId length);

    /**
     * Get the length of the default and operational table in number of
     * bytes.
     * @see #setTableLength
     * @return the number of char elements in the default and in the
     * operational table
     */
    TD_DatabaseId getTableLength(void);

    /**
     * Load the default table. This method assumes that the default table has
     * been defined and initialized by the caller. The method does not perform
     * any action on the table. It simply loads its address and will use it
     * for accessing the table entries.
     * <p>
     * This is an initialization method.
     * @param pDefTable the starting address of the default table
     */
    void setDefaultTable(char* pDefTable);

    /**
     * Load the operational table. This method assumes that the operational table has
     * been defined and initialized by the caller. The method does not perform
     * any action on the table. It simply loads its address and will use it
     * for accessing the table entries.
     * <p>
     * This is an initialization method.
     * @param pOperTable the starting address of the default table
     */
    void setOperationalTable(char* pOperTable);

    /**
     * Set the current value of a parameter interpreted as an unsigned integer.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, unsigned int newValue);

    /**
     * Set the current value of a parameter interpreted as an integer.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, int newValue);

    /**
     * Set the current value of a parameter interpreted as an unsigned short.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, unsigned short newValue);

    /**
     * Set the current value of a parameter interpreted as an short.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, short newValue);

    /**
     * Set the current value of a parameter interpreted as a boolean.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, bool newValue);

    /**
     * Set the current value of a parameter interpreted as a char.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, char newValue);

    /**
     * Set the current value of a parameter interpreted as an unsigned char.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, unsigned char newValue);

    /**
     * Set the current value of a parameter interpreted as a float.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, float newValue);

    /**
     * Set the current value of a parameter interpreted as a double.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, double newValue);

    /**
     * Get the current value of a parameter interpreted as an unsigned integer.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual unsigned int getParameterUnsignedInt(TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as an integer.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual int getParameterInt(TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as an unsigned short.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual unsigned short getParameterUnsignedShort(TD_DatabaseId parId); 

    /**
     * Get the current value of a parameter interpreted as a short.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual short getParameterShort(TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a boolean.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual bool getParameterBool(TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as an unsigned char.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual unsigned char getParameterUnsignedChar(TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a char.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual char getParameterChar(TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a float.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual float getParameterFloat(TD_DatabaseId parId);

    /**
     * Get the current value of a parameter interpreted as a double.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual double getParameterDouble(TD_DatabaseId parId);

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>unsigned int</code>.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual unsigned int* getParameterPointerUnsignedInt(TD_DatabaseId parId);

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>int</code>.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual int* getParameterPointerInt(TD_DatabaseId parId);

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>unsigned short</code>.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual unsigned short* getParameterPointerUnsignedShort(TD_DatabaseId parId);

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>short</code>.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual short* getParameterPointerShort(TD_DatabaseId parId);

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>unsigned char</code>.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual unsigned char* getParameterPointerUnsignedChar(TD_DatabaseId parId);

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>char</code>.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual char* getParameterPointerChar(TD_DatabaseId parId);

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>bool</code>.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual bool* getParameterPointerBool(TD_DatabaseId parId);

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>float</code>.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual float* getParameterPointerFloat(TD_DatabaseId parId);

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>double</code>.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual double* getParameterPointerDouble(TD_DatabaseId parId);

    /**
     * Perform a class-specific configuration check on a basic database object:
     * verify that the default and operational tables have been loaded, that
     * method <code>reset</code> has been called, and that the table length
     * is greater than zero.
     * @see #reset
     * @return true if the database object is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);

};

#endif

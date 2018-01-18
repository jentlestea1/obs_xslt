//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// ParameterDatabase.h
//
// Version	1.0
// Date		12.10.02
// Author	A. Pasetti (P&P Software)

#ifndef ParameterDatabaseH
#define ParameterDatabaseH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all parameter database classes are derived.
 * A parameter database object encapsulates a set of parameter values.
 * Each parameter can have two values: the <i>default value</i> and the
 * <i>current value</i>.
 * The default value is the value of the parameters immediately after the
 * database object is created or reset.
 * The current values are initialized with the default values at the time the
 * database object is created or
 * reset and they can subsequently be modified.
 * <p>
 * Parameters are identified by a <i>parameter identifier</i>.
 * Syntactically, this is a positive integer.
 * Each application instantiated from the framework would have its own set of
 * parameter identifiers.
 * <p>
 * In order to properly use the parameter database abstraction, it is
 * necessary to understand the conceptual implementation model that is
 * behind the interface defined in this class.
 * Parameter database information is stored in two tables: the <i>Default Table</i>
 * and the <i>Operational Table</i>. Each table stores a sequence of pairs.
 * The pairs have the form: (parameter value, parameter identifier).
 * Each entry in the table, in other words, contains the value of a parameter
 * and its identifier.
 * The two tables store values for the same set of parameters.
 * They differ only because the values stored in the default table are
 * intended to remain fixed whereas the values stored in the operational table
 * can be dynamically updated.
 * The operational table is initialized with a copy of the default table (this
 * is done using the <code>reset</code> operation).
 * <p>
 * In many implementations, the default table will be stored in ROM and the
 * operational table will be stored in RAM.
 * <p>
 * No methods are defined to set the default parameter values. This is because,
 * in most cases, these are defined outside the parameter database class
 * (they may, for instance, be burnt in PROM).
 * <p>
 * A parameter database is a low-level data structure whose implementation will
 * usually require use of pointers. Most implementations of this class
 * will therefore violate project specific coding rule PR3.1.
 * <p>
 * Client components can access the parameters in two ways. They can either
 * get their values using the getter methods defined in this interface. Or
 * they can <i>link</i> to the parameters using the <code>getParameterPointer</code>
 * method. This method returns a pointer to a specific parameter (as identified
 * by its identifier) which the client component can then store internally and
 * use to directly access the parameter value.
 * <p>
 * Parameters have a type.
 * The type of the parameter defines how the raw parameter value is
 * interpreted and how it is returned to the
 * external user of the database.
 * The possible types for the parameters are: unsigned int, int, unsigned short,
 * unsigned char, char, float, double.
 * For each paramete type, there is a dedicated parameter getter method.
 * Note that this interface does not mandate any protection against attempts to
 * access parameters with the wrong type.
 * Thus, for instance, if the parameter identified by identifier ID is
 * intended to represent an integer,
 * attempts to retrieve it as if it were of float type (using method
 * <CODE>getFloatParameter(ID)</CODE>) will not necessarily result
 * in an error and may produce a meaningless result.
 * Avoiding this type of errors is the responsibility of the user.
 * Subclasses, however, are free to introduce some run-time check to catch
 * this kind of error.
 * <p>
 * For similar reasons, the interface defined by this class does not mandate
 * any checks on the legality of the value of the parameter identifier in the
 * method calls. Such checks can again be added by subclasses.
 * <p>
 * The methods declared by this class allow an application component to
 * establish a link between their internal variables and the database parameters.
 * The process whereby this link is established is called <i>database linking</i>.
 * Two types of database linking are allowed by this class: <i>copy link</i>
 * and <i>pointer link</i>.
 * <p>
 * In a <i>copy link</i>, the application component holds a reference to
 * the parameter database and to the identifier of the target parameter
 * and periodically updates the value of its internal variable by copying
 * the value of the target database parameter.
 * <p>
 * In a <i>pointer link</i>, the application component internally defines
 * a pointer which is then initialized to point to the target database
 * parameter. The application component effectively uses the target database
 * parameter as its internal variable.
 * <p>
 * This is an abstract class because the internal organization of the
 * parameter database is application-dependent.
 * All the class methods are declared abstract.
 * In particular, the data structure used to represent the parameter tables
 * and the way parameters and their identifiers are associated is
 * application dependent.
 * <p>
 * @todo This class defines the setter and getter methods to be virtual. This
 * is expensive in CPU time. Given that database implementations will often
 * be generated automatically by XSL programs, and given that an application
 * would normally only have one database component, it may be wiser to 
 * have the XSL program generate an implementation for class ParameterDatabase that 
 * is defined to have only non-virtual methods. The problem with this approach
 * is that it is not possible to have multiple implementations of a database
 * in a single delivery and that therefore it is not possible to have several
 * database test cases in the same delivery (this could be alleviated by
 * generating the test case for the database as well as the database
 * implementation). 
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Data
 */
class ParameterDatabase : public CC_RootObject {

  public:

    /**
     * Instantiate a parameter database object.
     * This method returns without taking any actions.
     */
    ParameterDatabase(void);

    /**
     * Load the current values of the parameters with their default values.
     */
    virtual void reset(void) = 0;

    /**
     * Set the current value of a parameter interpreted as an unsigned integer.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, unsigned int newValue) = 0;

    /**
     * Set the current value of a parameter interpreted as an integer.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, int newValue) = 0;

    /**
     * Set the current value of a parameter interpreted as an unsigned short.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, unsigned short newValue) = 0;

    /**
     * Set the current value of a parameter interpreted as an short.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, short newValue) = 0;

    /**
     * Set the current value of a parameter interpreted as a boolean.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, bool newValue) = 0;

    /**
     * Set the current value of a parameter interpreted as a char.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, char newValue) = 0;

    /**
     * Set the current value of a parameter interpreted as an unsigned char.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, unsigned char newValue) = 0;

    /**
     * Set the current value of a parameter interpreted as a float.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, float newValue) = 0;

    /**
     * Set the current value of a parameter interpreted as a double.
     * @param parId the identifier of the parameter to be set
     * @param newValue the new current value of the parameter
     */
    virtual void setParameter(TD_DatabaseId parId, double newValue) = 0;

    /**
     * Get the current value of a parameter interpreted as an unsigned integer.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual unsigned int getParameterUnsignedInt(TD_DatabaseId parId) = 0;

    /**
     * Get the current value of a parameter interpreted as an integer.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual int getParameterInt(TD_DatabaseId parId) = 0;

    /**
     * Get the current value of a parameter interpreted as an unsigned short.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual unsigned short getParameterUnsignedShort(TD_DatabaseId parId) = 0;

    /**
     * Get the current value of a parameter interpreted as a short.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual short getParameterShort(TD_DatabaseId parId) = 0;

    /**
     * Get the current value of a parameter interpreted as a boolean.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual bool getParameterBool(TD_DatabaseId parId) = 0;

    /**
     * Get the current value of a parameter interpreted as an unsigned char.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual unsigned char getParameterUnsignedChar(TD_DatabaseId parId) = 0;

    /**
     * Get the current value of a parameter interpreted as a char.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual char getParameterChar(TD_DatabaseId parId) = 0;

    /**
     * Get the current value of a parameter interpreted as a float.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual float getParameterFloat(TD_DatabaseId parId) = 0;

    /**
     * Get the current value of a parameter interpreted as a double.
     * @param parId the identifier of the parameter to be set
     * @return the current value of the parameter
     */
    virtual double getParameterDouble(TD_DatabaseId parId) = 0;

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>unsigned int</code>.
     * <p>
     * This and other methods returing pointers to parameters are typically
     * used to set up a <i>pointer link</i> between a
     * target database parameter and the internal variable of an application
     * component. This can be done as follows. Consider an application component
     * instantiated from class <code>Comp</code> which defines an internal
     * variable <code>var</code>. Suppose that it is desired to link this
     * variable to the parameter characterized by identifier <code>PAR_ID</code>
     * in the database <code>pDatabase</code>. The <code>Comp</code> class
     * should expose a <i>database linker method</i>:<PRE>
     *      class Comp {
     *          unsigned int* par;
     *          . . .
     *          void linkParToDatabase(TD_DatabaseId parId, ParameterDatabase* pDB) {
     *              par = pDB->getParameterPointerUnsignedInt(parId);
     *          }
     *          . . .  </PRE>
     * The application component must then be configured as follows:<PRE>
     *      Comp* comp;                 // the application component
     *      ParameterDatabase* pDB;     // the parameter database
     *      TD_DatabaseId PAR_ID;       // the parameter identifier
     *      . . .
     *      comp->linkParToDatabase(PAR_ID,pDB); </PRE>
     * The last statement sets up a permanent link between the internal
     * application component variable and the database parameter.
     * Note that use of this mechanism entails a violation of coding
     * rule PR3.1. This is inevitable if the database linking is to be
     * performed in an efficient manner.
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual unsigned int* getParameterPointerUnsignedInt(TD_DatabaseId parId) = 0;

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>int</code>.
     * @see #getParameterPointerUnsignedInt
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual int* getParameterPointerInt(TD_DatabaseId parId) = 0;

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>unsigned short</code>.
     * @see #getParameterPointerUnsignedInt
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual unsigned short* getParameterPointerUnsignedShort(TD_DatabaseId parId) = 0;

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>short</code>.
     * @see #getParameterPointerUnsignedInt
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual short* getParameterPointerShort(TD_DatabaseId parId) = 0;

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>unsigned char</code>.
     * @see #getParameterPointerUnsignedInt
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual unsigned char* getParameterPointerUnsignedChar(TD_DatabaseId parId) = 0;

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>char</code>.
     * @see #getParameterPointerUnsignedInt
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual char* getParameterPointerChar(TD_DatabaseId parId) = 0;

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>bool</code>.
     * @see #getParameterPointerUnsignedInt
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual bool* getParameterPointerBool(TD_DatabaseId parId) = 0;

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>float</code>.
     * @see #getParameterPointerUnsignedInt
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual float* getParameterPointerFloat(TD_DatabaseId parId) = 0;

    /**
     * Return the pointer to the variable in the operational table storing the
     * parameter identified by <code>parId</code>. The variable is interpreted
     * as of type <code>double</code>.
     * @see #getParameterPointerUnsignedInt
     * @return the parameter pointer
     * @param parId the parameter identifier
     */
    virtual double* getParameterPointerDouble(TD_DatabaseId parId) = 0;

};

#endif

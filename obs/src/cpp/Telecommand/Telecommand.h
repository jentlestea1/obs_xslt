//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// Telecommand.h
//
// Version	1.0
// Date		15.10.03 (version 1.0)
// Author	A. Pasetti (P&P Software)
//
// Change Record:

#ifndef TelecommandH
#define TelecommandH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"

/**
 * Base class from which all telecommand classes are derived.
 * This is an abstract class. Concrete telecommands are obtained by deriving
 * this class.
 * <p>
 * A telecommand is a form of <i>punctual action</i>.
 * Telecommands add to the following attributes to those they inherit
 * from their superclass:<ul>
 * <li>A <i>time tag</i>: the time when the telecommand should be executed.
 * If the time tag is equal to zero, then the telecommand should be executed
 * immediately. Negative values of the time tag indicate a non-configured or
 * or otherwise invalid telecommand.</li>
 * <li>A <i>telecommand identifier</i>: an integer that uniquely identifies the
 * telecommand. </li>
 * <li>A <i>telecommand source</i>: an integer that uniquely identifies the
 * sender of the telecommand. </li>
 * <li>A <i>telecommand type</i>: an integer that identifies the type of
 * telecommand. </li>
 * <li>A <i>telecommand subtype</i>: an integer that identifies the subtype of
 * telecommand. This attribute is useful when the type attribute does not provide
 * sufficient granularity to represent the various categories of telecommands.</li>
 * <li>A <i>validity check code</i>: a read-only integer that conveys information about
 * the failure of the validity check (see below). </li>
 * <li>An <i>execution check code</i>: a read-only integer that conveys information about
 * the failure of the execution check (see below). </li>
 * <li>An <i>acknowledge level</i>: an integer that defines the level of acknowledgement
 * that the telecommand sender requires for the telecommand (e.g. acknowledgement upon
 * acceptance of the telecommand, acknowledgement upon execution start, acknowledgement
 * upon execution termination, etc).</li>
 * <li>An <i>in use flag</i>: a toggle attribute that can have two values:
 * "telecommand is in use" and "telecommand is not in use". This attribute
 * can be useful because telecommand components
 * are normally created dynamically and therefore their resources must be
 * managed dynamically. The "in use" attribute can then be used to discriminate
 * between telecommands that are being used (and whose resources are therefore
 * to be considered allocated) and telecommands that are not being used (and
 * whose resources can therefore be reclaimed and used to construct other
 * telecommand components). In the OBS Framework, the "in use" attribute
 * would typically be used by the <i>telecommand loader</i>.</li>
 * </ul>
 * With the exception of the "in use flag", all telecommand attributes are
 * conceptually read-only
 * attributes. However, since telecommand objects may have to be dynamically
 * configured by the <i>telecommand loader</i>, setter methods are provided
 * to dynamically set their values.
 * <p>
 * Telecommands implement the <i>raw data load service</i>. This is
 * intended to facilitate the configuration
 * of a telecommand by the <i>telecommand loader</i>. The usage scenario
 * for this service is a situation where the telecommand loader receives
 * the raw telecommand as a list of bytes. The list of bytes contain
 * the configuration data for the telecommand component. The raw data
 * load service allows the telecommand loader to load these bytes into the
 * telecommand loader in an "anonymous manner" without having to know
 * anything about their meaning for the telecommand component.
 * The raw data load service is an optional service that only some
 * concrete telecommand components will choose to implement. The choice to
 * implement it depends on the mutual relationship between the concrete
 * telecommand loader and the concrete telecommand components.
 * Two alternative implementations for the raw data load service are
 * defined. The first one is efficient but potentially unsafe (it does
 * not comply with project-specific coding rule PR3.3). The second one is
 * safe (it complies with all coding rules) but less efficient (it requires
 * a virtual method call for each byte that is loaded in the telecommand
 * component).
 * <p>
 * Telecommands can perform two checks: a <i>validity check</i> and an
 * <i>execution check</i>.
 * The validity check checks the internal validity of the telecommand
 * attributes.
 * It should normally be executed immediately after the telecommand is loaded to
 * verify its formal correctness.
 * The execution check should be performed just before the telecommand is
 * executed and should
 * verify whether conditions for the safe execution of the telecommand are
 * satisfied.
 * <p>
 * This class provides a general interface that can model telecommand concepts
 * of varying complexity but it only provides a minimal implementation.
 * Thus, of the attributes it defines, only the time tag and the "in use" flag
 * are implemented as true read/write attributes. The other attributes are
 * implemented as fixed constants. Applications are free to provide
 * subclasses that implement a larger subset of the attributes
 * defined in this class.
 * <p>
 * @todo The possibility should be considered of making Telecommand a subclass
 * of ConditionalPunctualAction. This would make sense because the Telecommand
 * class contains a conditional execution check. However, this change would
 * require delicate changes to the CC_TelecommandManager and CriticalTelecommand
 * classes (at the least). For the time being, it seems wiser to leave things
 * as they are. The advantage of the current solution is that it gives greater
 * control to the telecommand manager over the execution of the telecommand
 * and it makes it easier to implement "special" types of telecommands (such
 * as, for instance, critical telecommands).
 * @todo should new versions of method setRawData that take as argument unsigned short
 * and unsigned int be added? This would speed up execution when a large number of data have
 * to be loaded but it might make implementation of the methods in concrete subclasses
 * more complex.
 * @see TelecommandLoader
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Telecommand
 */
class Telecommand : public PunctualAction {

  private:
    TD_ObsTime timeTag;
    bool inUse;

  public:

    /**
     * Instantiate a telecommand.
     * The telecommand attributes are set. The "in use" flag is set to
     * "telecommand is not in use" and the time tag is initialized to an
     * illegal value to signify that the component is not yet configured.
     */
    Telecommand(void);

    /**
     * Execute the validity check on the telecommand.
     * This class provides a default implementation that returns "telecommand is
     * valid".
     * Subclasses may introduce more complex validity checks (e.g. checksum checks).
     * @see CC_TelecommandManager#activate
     * @return true if the telecommand is valid, false otherwise
     */
    virtual bool isValid(void);

    /**
     * Return the validity check code for the telecommand.
     * The validity check code allows a telecommand to make information available about
     * the reasons for the failure of the validity check. The return value of this
     * method is only valid if the validity check has returned "telecommand not
     * valid" (ie. if method <code>isValid</code> has returned false). This class
     * provides a default implementation that returns zero.
     * @see #isValid
     * @return the validity check code
     */
    virtual TD_CheckCode getValidityCheckCode(void) const;

    /**
     * Perform the execution check on the telecommand.
     * This class provides a default implementation that always return "telecommand
     * can execute".
     * @see CC_TelecommandManager#activate
     * @return true if the telecommand can safely execute, false otherwise
     */
    virtual bool canExecute(void);

    /**
     * Return the execution check code for the telecommand.
     * The execution check code allows a telecommand to make information available about
     * the reasons for the failure of the execution check. The return value of this
     * method is only valid if the execution check has returned "telecommand cannot
     * execute" (ie. if method <code>canExecute</code> has returned false). This class
     * provides a default implementation that returns zero.
     * @see #isValid
     * @return the validity check code
     */
    virtual TD_CheckCode getExecutionCheckCode(void) const;

    /**
     * Getter method for the telecommand identifier. This class implements the
     * the telecommand identifier to coincide with the instance identifier.
     * Note that this assumes that the type of the instance identifier
     * (TD_InstanceId) is assignment-compatible with the type of the 
     * telecommand identifier (TD_TelecommandId).
     * A pseudo-code implementation of this method therefore is:<pre>
     *      return getInstanceId();</pre>
     * @return the telecommand identifier
     */
    virtual TD_TelecommandId getTelecommandId(void) const;

    /**
     * Setter method for the telecommand identifier. Since this class
     * identifies the telecommand identifier with the instance identifier
     * (see <code>CC_RootObject</code>), this method is implemented as
     * a dummy method that returns without taking any action.
     * @see #getTelecommandId
     * @param tcIdentifier the telecommand identifier
     */
    virtual void setTelecommandId(TD_TelecommandId tcIdentifier);

    /**
     * Getter method for the telecommand type. This class implements 
     * the telecommand type to coincide with the least significant
     * byte of the class identifier.
     * A pseudo-code implementation of this method therefore is:<pre>
     *      return (TD_TelecommandType)(getClassId() mod 256);</pre>
     * @return the telecommand type
     */
    virtual TD_TelecommandType getType(void) const;

    /**
     * Setter method for the telecommand type. Since this class
     * identifies the telecommand type with the class identifier
     * (see <code>CC_RootObject</code>), this method is implemented as
     * a dummy method that returns without taking any action.
     * @see #getType
     * @param tcType the telecommand type
     */
    virtual void setType(TD_TelecommandType tcType);

    /**
     * Getter method for the telecommand sub-type. This class does not model
     * the telecommand sub-type. This method always returns zero.
     * @return the telecommand sub-type
     */
    virtual TD_TelecommandSubType getSubType(void) const;

    /**
     * Setter method for the telecommand sub-type. Since this class
     * does not model the telecommand sub-type, this method is implemented as
     * a dummy method that returns without taking any action.
     * @see #getTelecommandsubType
     * @param tcSubType the telecommand sub-type
     */
    virtual void setSubType(TD_TelecommandSubType tcSubType);

    /**
     * Getter method for the telecommand source. This class does not model
     * the telecommand source. This method always returns zero.
     * @return the telecommand source
     */
    virtual TD_TelecommandSource getSource(void) const;

    /**
     * Setter method for the telecommand source. Since this class
     * does not model the telecommand source, this method is implemented as
     * a dummy method that returns without taking any action.
     * @see #getSource
     * @param tcSource the telecommand source
     */
    virtual void setSource(TD_TelecommandSource tcSource);

    /**
     * Getter method for the telecommand time tag.
     * @return the telecommand time tag
     */
    TD_ObsTime getTimeTag(void) const;

    /**
     * Setter method for the telecommand time tag.
     * @see TelecommandLoader
     * @param timeTag the telecommand time tag
     */
    void setTimeTag(TD_ObsTime timeTag);

    /**
     * Implementation of the raw data load service. This method would normally
     * be called by a telecommand loader to load the i-th byte into the
     * telecommand component. The telecommand component uses the data that it
     * receives from the telecommand loader to configure its internal data
     * structures. The index i should lie in an interval [0,N-1] where N is
     * the return value of method <code>getNumberOfRawData</code>.
     * This implementation of the raw data load service is safe (unlike
     * its alternative <code>setRawData(unsigned char*, unsigned int)</code>,
     * it does not give access to the internal data of the
     * caller) but can be inefficient because it requires the caller to pass
     * the telecommand configuration bytes one by one through dedicated calls
     * to a virtual method.
     * <p>
     * This class provides a default implementation that does nothing and
     * should never be called.
     * @see getNumberOfRawData
     * @param i the index of the raw telecommand data
     * @param d the raw data
     */
    virtual void setRawData(unsigned int i, unsigned char d);

    /**
     * Return the number of raw data bytes that can be loaded with the
     * raw telecommand data load service <code>setRawData(unsigned int, 
     * unsigned char)</code>.
     * This class provides a default implementation that returns zero.
     * @see #setRawData
     * @return the number of raw data bytes to be loaded with the raw
     * data load service
     */
    virtual unsigned int getNumberOfRawData(void) const;

    /**
     * Implementation of the raw data load service. This method would normally
     * be called by a telecommand loader to load the configuration data for the
     * telecommand as s single array of bytes. The telecommand component uses the 
     * data in the array to configure its internal data
     * structures. 
     * This implementation of the raw data load service is efficient (unlike
     * its alternative <code>setRawData(unsigned int, unsigned char)</code>)
     * but is unsafe because it forces the caller to give access to its interal
     * data structures to the telecommand component.
     * <p>
     * This class provides a default implementation that does nothing and
     * should never be called.
     * @param i the number data in the d array
     * @param d the array holding the raw data
     */
    virtual void setRawData(unsigned char* d, unsigned int i);

    /**
     * Set the value of the "in use" attribute.
     * @see #isInUse
     * @param newInUse the new value of the in use attribute
     */
    void setInUse(bool newInUse);

    /**
     * Return the value of the "in use" attribute. If the method returns true, then
     * the telecommand is in use, otherwise it is not in use.
     * @see #setInUse
     * @return the value of the "in use" attribute.
     */
    bool isInUse(void) const;

    /**
     * Set the value of the acknowledge level for this telecommand.
     * This class does not implement the acknowledge level and
     * this method therefore returns without taking any action.
     * @see #getAcknowledgeLevel
     * @param ackLevel the new value of the acknowledge level attribute
     */
    virtual void setAcknowledgeLevel(TD_TelecommandAck ackLevel);

    /**
     * Return the value of the acknowledge level.
     * This class does not implement the acknowledge level and
     * this method always returns a default and fixed value of zero.
     * @see #setAcknowledgeLevel
     * @return the value of the acknowledge level attribute
     */
    virtual TD_TelecommandAck getAcknowledgeLevel(void) const;

    /**
     * Perform a class-specific configuration check on the telecommand:
     * verify that the time tag has a legal value.
     * @return true if the component is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif

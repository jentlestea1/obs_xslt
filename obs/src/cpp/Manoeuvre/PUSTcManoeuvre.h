//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSTcManoeuvre.h
//
// Version	1.0
// Date		10.11.03
// Author	A. Pasetti (P&P Software)

#ifndef PUSTcManoeuvreH
#define PUSTcManoeuvreH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Manoeuvre/Manoeuvre.h"

/**
 * Base class for classes encapsulating a <i>PUS telecommand manoeuvre</i>.
 * A PUS telecommand manoeuvre models the manoeuvre-like actions associated
 * to a PUS telecommand.
 * The OBS Framework implements a telecommand as a form of <i>punctual action</i>
 * that is executed in one-shot mode (i.e. its execution terminates in the same cycle
 * in which it begins). The Packet Utilization Standard (PUS) instead
 * allows for actions to be associated to a telecommand that must be executed over
 * an interval of time. This class models this type of actions as a form of
 * <i>manoeuvre</i>. A manoeuvre of this type would normally be launched by
 * a PUS telecommand.
 * <p>
 * This class adds to its base class the following attributes that
 * describe the telecommand that launches the manoeuvre: <ul>
 * <li>The <i>telecommand identifier attribute</i> of the PUS telecommand that triggered
 * execution of the manoeuvre. In a PUS telecommand, this attribute is identical to the
 * packet sequence control attribute.</li>
 * <li>The <i>execution start acknowledge flag</i> of the PUS telecommand that triggered
 * execution of the manoeuvre. </li>
 * <li>The <i>progress acknowledge flag</i> of the PUS telecommand that triggered
 * execution of the manoeuvre. </li>
 * <li>The <i>completion acknowledge flag</i> of the PUS telecommand that triggered
 * execution of the manoeuvre. </li>
 * </ul>
 * Additionally, this class provides a <i>progress event generation service</i>. This
 * service can be called by concrete subclasses to generate an event marking the
 * advancement of the execution of the PUS telecommand mananoeuvre.
 * <p>
 * A PUS telecommand manoeuvre is normally loaded into the manoeuvre manager by
 * a PUS telecommand. The PUS telecommand should configured the PUS manoeuvre as follows:<ul>
 * <li>It should set its telecommand identifier attribute</li>
 * <li>It should set its execution start acknowledge flag</li>
 * <li>It should set its progress acknowledge flag</li>
 * <li>It should set its completion acknowledge flag</li>
 * </ul>
 * The above configuration actions can be performed in any order.
 * @see PUSTelecommand
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup PUS
 * @ingroup Manoeuvre
 */
class PUSTcManoeuvre: public Manoeuvre {

  private:
    bool startAck;
    bool progressAck;
    bool completionAck;
    TD_TelecommandId tcId;

  protected:

    /**
     * This method generates an event of type EVT_MAN_PROGRESS (manoeuvre progress event report). 
     * Some applications require that telemetry packets be generated to
     * mark the advancement of the execution of the actions associated to a PUS telecommand.
     * This method is intended as a facility to be called by concrete subclasses at points
     * where generation of an execution progress report is required. It would typically be
     * called from inside the implementation of method <code>doInternalContinue</code>.
     * A pseudo-code implementation for this method is as follows:<pre>
     *          createEventReport(this, EVT_MAN_PROGRESS); </pre>
     * @see #isProgressAckRequired
     */
    virtual void generateProgressEvent(void);

  public:

   /**
    * Instantiate a PUS telecommand manoeuvre component.
    * The acknoweldge flags are set to false ("no acknowledge is required") and the telecommand
    * identifier is set to an illegal value to signify that the component is not yet configured.
    */
    PUSTcManoeuvre(void);

    /**
     * Return true if acknowledgement of manoeuvre execution start is
     * required. This flag should normally have the same value as the execution start 
     * acknowledgement flag of the telecommand that triggered the execution of this
     * manoeuvre.
     * @see #setStartAckFlag
     * @return the value of the execution start acknowledge flag
     */
    bool isStartAckRequired(void) const;

    /**
     * Return true if acknowledgement of manoeuvre execution progress is
     * required. This flag should normally have the same value as the progress
     * acknowledgement flag of the telecommand that triggered the execution of this
     * manoeuvre.
     * @see #setProgressAckFlag
     * @return the value of the progress acknowledge flag
     */
    bool isProgressAckRequired(void) const;

    /**
     * Return the true if acknowledgement of manoeuvre execution completion is
     * required. This flag should normally have the same value as the completion
     * acknowledgement flag of the telecommand that triggered the execution of this
     * manoeuvre.
     * @see #setCompletionAckFlag
     * @return the value of the completion acknowledge flag
     */
    bool isCompletionAckRequired(void) const;

    /**
     * Set the value of the start acknowledge flag.
     * @see #isStartAckRequired
     * @param startAckFlag the value of the execution start acknowledge flag
     */
    void setStartAckFlag(bool startAckFlag);

    /**
     * Set the value of the completion acknowledge flag.
     * @see #isCompletionAckRequired
     * @param completionAckFlag the value of the completion acknowledge flag
     */
    void setCompletionAckFlag(bool completionAckFlag);

    /**
     * Set the value of the progress acknowledge flag.
     * @see #isCompletionAckRequired
     * @param progressAckFlag the value of the progress acknowledge flag
     */
    void setProgressAckFlag(bool progressAckFlag);

    /**
     * Getter method for the identifier of the telecommand that launched this
     * manoeuvre.
     * @see #setTelecommandId
     * @return the telecommand identifier
     */
    virtual TD_TelecommandId getTelecommandId(void) const;

    /**
     * Setter method for the identifier of the telecommand that launched this
     * manoeuvre.
     * @see #getTelecommandId
     * @param tcIdentifier the telecommand identifier
     */
    virtual void setTelecommandId(TD_TelecommandId tcIdentifier);

};

#endif


//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// MonitoringProfile.h
//
// Version	1.0
// Date	    30.09.03 
// Author	A. Pasetti, R. Totaro
//
// Change Record:

#ifndef MonitoringProfileH
#define MonitoringProfileH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all monitoring profile classes are derived.
 * A monitoring profile encapsulates a profile against which the value
 * of a monitored variable must be checked (<i>monitoring check</i>).
 * Two versions of the monitoring check are offered by this class,
 * one for monitored variables of <code>TD_Float</code> type and one for monitored
 * variables of <code>TD_Integer</code> type.
 * <p>
 * Monitoring profiles can be enabled or disabled.
 * A monitoring profile that is disabled will always report:
 * "no deviation from profile".
 * <p>
 * Monitoring profiles can be linked in sequential
 * chains. The client only sees one single monitoring profile (the one
 * at the head of the chain) but its execution can lead to all profiles 
 * in the chain being executed in sequence. This class defines a <i>next monitoring
 * profile</i> attribute that holds the pointer to the next monitoring profile in the
 * chain. A monitoring profile reports "no profile violation detected" only if
 * neither itself nor any of the monitoring profiles downstream in the chain of
 * linked profiles report "no profile violation detected".
 * <p>
 * A violation of a monitoring profile is reported as an event.
 * <p>
 * This class is abstract because the implementation of the monitoring
 * profile is class-specific and must be defined in the derived classes
 * that implement concrete profiles.
 * The management of the enable status and the reporting of profile
 * violation as events is however performed in this base class.
 * @todo Add an internal variable that to record the reason for the violation
 * and that concrete monitoring profiles can set to indicate how the profile
 * was violated (e.g. violation of upper boundary of a range interval). Clients
 * can then inspect the value of this variable to know the exact reason of the
 * profile violation.
 * @todo Add a test case to cover the "next monitoring profile" functionality.
 * This could be obtained by modifying the test case of DC_ProfileList.
 * @todo Monitoring profiles use parameters that are implemented as internal variables.
 * In practice, these parameters will often have to come from the parameter database.
 * Two solutions are possible: generators are used to parameterize the concrete 
 * monitoring profiles classes with respect to the mode of implementation of the
 * profile parameters. Or aspect programs are used modify the monitoring profile class
 * as follows: code to set the link to the parameter database is inserted, and 
 * code to update the value of the internal parameter with the value read from the
 * parameter database is added at the beginning of method doProfileCheck.
 * @author Alessandro Pasetti 
 * @author Roberto Totaro
 * @version 1.0
 * @ingroup FDIR
 */
class MonitoringProfile: public CC_RootObject {
private:
    bool enableStatus;
    MonitoringProfile* pNext;

protected:
    /**
     * Encapsulate the check of the monitored variable value against the
     * monitoring profile.
     * This method is called by method <CODE>deviatesFromProfile()</CODE>
     * in this same class.
     * User of monitoring profiles do not see <CODE>method doProfileCheck()</CODE>,
     * they only see method
     * <CODE>deviatesFromProfile()</CODE>.
     * @see #deviatesFromProfile
     * @param value the value of the monitored variable
     * @return true if the monitored variable deviates from the monitoring profile, false otherwise
     */
    virtual bool doProfileCheck(TD_Float value) = 0;

    /**
     * Version of method <CODE>doProfileCheck()</CODE> for monitored variables
     * of integer type.
     * @see #doProfileCheck
     */
    virtual bool doProfileCheck(TD_Integer value) = 0;

public:
    /**
     * Instantiate a monitoring profile.
     * The enabled status of the profile is initialized to "enabled".
     * The "next monitoring profile" attribute is set to NULL.
     */
    MonitoringProfile(void);

    /**
     * Check whether the value of the monitored variable - passed as an argument
     * to the method - is within
     * the profile encapsulated by the monitoring profile object.
     * The check is only done if the monitoring profile object is enabled.
     * If it is disabled, the method returns true indicating that there is no
     * deviation from the profile.
     * After performing the monitoring check encapsulated by this class, 
     * it is verified whether there are any linked monitoring checks and, if
     * so, the check value is passed on to them. A return value of "deviation
     * detected" may indicate either that this check has detected a violation
     * or that a violation has been detected by the next monitoring profile 
     * in the chain.
     * <p>
     * A pseudo-code implementation for this method is as follows: <PRE>
     *   bool outcome = NO_MON_PROFILE_DEVIATION;
     *   if ( isEnabled() )
     *   { if (doProfileCheck(value))
     *     { createEventReport(EVT_MON_PROFILE_VIOLATION);
     *       outcome = MON_PROFILE_DEVIATION;
     *     }
     *   }
     *   if ( pNext!=pNULL )     // there is a next monitoring profile 
     *      if ( next->deviatesFromProfile(value) )
     *          outcome = MON_PROFILE_DEVIATION;
     *   return outcome; </PRE>
     * The <CODE>doProfileCheck()</CODE> method is abstract and encapsulates
     * the implementation of the profile check.
     * Thus, this class enforces the management of the enabled status and 
     * of the "next monitoring profile" but delegates implementation of the
     * monitoring profile check to derived classes implementing concrete profiles.
     * An event is created when deviations from the profile are detected.
     * The event parameter is the class identifier of the monitoring profile
     * object itself.
     * @param value the value of the monitored variable
     * @return true if the monitored variable deviates from the monitoring profile,
     * false otherwise
     */
    bool deviatesFromProfile(TD_Float value);

    /**
     * Version of method <CODE>deviatesFromProfile()</CODE> for monitored
     * variables of integer type.
     * @see #deviatesFromProfile
     */
    bool deviatesFromProfile(TD_Integer value);

    /**
     * Set the enable status of the monitoring profile.
     * When the profile is disabled, a call to method <CODE>deviatesFromProfile()</CODE>
     * always returns "no deviation from profile".
     * @param enableStatus if true, then the profile is enabled; if false, then
     * the profile is disabled
     */
    inline void setEnabled(bool enableStatus);

    /**
     * Check the enable status of the monitoring profile.
     * @return true if the profile is enabled, false otherwise
     */
    inline bool isEnabled(void);

	/**
	 * Set the next monitoring profile.
	 * @see #deviatesFromProfile
	 * @param pNextMonitoringProfile the next monitoring profile
	 */
	void setNextMonitoringProfile(MonitoringProfile* pNextMonitoringProfile);

	/**
	 * Get the next monitoring profile. If no monitoring profile has been chained
     * to this one, then a value of pNULL is returned.
	 * @see #deviatesFromProfile
	 * @return the next monitoring profile
	 */
	MonitoringProfile* getNextMonitoringProfile();

    /**
     * Reset the internal state of the monitoring profile to the value it had
     * immediately after instantiation.
     * Some monitoring profiles need to keep track of past values of the monitored
     * variable and therefore have
     * an internal state.
     * This method allows this internal state to be reset.
     * This class offers a default implementation of this method that does not
     * do anything.
     * Subclasses may need to override this default implementation.
     */
    virtual void reset(void);
};

#include "MonitoringProfile_inl.h"

#endif

//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ProfileList.h
//
// Version	1.2
// Date		31.08.03 (Version 1.0)
//          01.10.03 (Version 1.1)
//          21.10.03 (Version 1.2)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:
//   Version 1.1: replaced double and int with TD_Float and TD_Integer
//   Version 1.2: loadMonitoringProfile() renamed setMonitoringProfile()

#ifndef DC_ProfileListH
#define DC_ProfileListH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "MonitoringProfile.h"

/**
 * Monitoring profile that encapsulates a list of monitoring profiles.
 * This monitoring profile reports a "deviation from profile" if any of the
 * monitoring profiles in the list report "deviation from profile".
 * This component is useful when there is a need to subject a variable
 * to a sequence of monitoring actions. Use of this component allows the
 * client (the component that is responsible for performing the monitoring
 * action) to be shielded from the knowledge of which and how many monitoring
 * profiles are being used.
 * <p>
 * The size of the list of monitoring profiles is set as an initialization
 * parameter.
 * <p>
 * <i>Note:</i> This class has effectively become redundant after class 
 * <code>MonitoringProfile</code> was modified to handle chains of linked 
 * monitoring profiles. 
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 1.2
 */
class DC_ProfileList: public MonitoringProfile {
private:
    /**
     * Array of pointers to the monitoring profiles
     */
    MonitoringProfile **pList;

    /**
     * Size of the monitoring profile list
     */
    unsigned int listSize;

protected:
  /**
  * Version of method <CODE>doProfileCheck()</CODE> for monitored variables
  * of type TD_Integer. The logic of this method is the same as for the version
  * that takes a <code>TD_Float</code> argument.
  * @see #doProfileCheck
  */
  virtual bool doProfileCheck(TD_Integer value);

  /**
  * Pass the monitored value through all the monitoring profiles in the
  * list and report "devation from profile" if any of the profiles in
  * the list report "deviation from profile".
  * A pseudo-code implementation for this method is as follows: <PRE>
  *   flag = NO_MON_PROFILE_DEVIATION;
  *   for (all monitoring profiles p in the list)
  *   {  if ( p->deviatesFromProfile(value) )
  *         flag = MON_PROFILE_DEVIATION;
  *   }
  *   return flag; </PRE>
  * Note that the monitored value is always passed through all
  * monitoring profiles in the list.
  * @param value the value of the monitored variable
  * @return true if the monitored variable deviates from the profile,
  * false otherwise
  */
  virtual bool doProfileCheck(TD_Float value);

public:

  /**
  * Instantiate a monitoring profile list.
  * The class identifier is set, the size of the monitoring profile list
  * is initialized to 0 to
  * signify that the component is not yet configured.
  */
  DC_ProfileList(void);

  /**
  * Set the size of the list of monitoring profiles.
  * The list size defines the maximum number of monitoring profiles
  * that can be loaded into this component. A call to this method
  * causes memory for an internal data structure to be allocated.
  * This is an initialization method: it shall be called only
  * once, before the component is used for the first time.
  * It is not legal to set the repository size to 0.
  * The entries in the list are initialized to pNULL.
  * @param listSize the size of the monitoring list size
  */
  void setListSize(unsigned int listSize);

  /**
  * Return the size of the list of monitoring profiles.
  * @see #setListSize
  * @return listSize the size of the monitoring list size
  */
  unsigned int getListSize(void) const;

  /**
  * Set the i-th entry in the list of monitoring profiles.
  * Only non-null entries are legal. The index i must lie in the range [0,N-1]
  * where N is size of the monitoring profile list.
  * Use of illegal values result in the generation of the
  * EVT_ILLEGAL_MP event report.
  * @see TD_EventId
  * @param i the index of the monitoring list
  * @param item the item to be added to the list at position i
  */
  void setMonitoringProfile(unsigned int i, MonitoringProfile* item);

  /**
  * Get the i-th entry in the list of monitoring profiles.
  * If the i-th entry has not yet been loaded, a null value is returned.
  * The index i should lie in the range [0,N-1]
  * where N is size of the monitoring profile list.
  * @param i the index of the monitoring list
  * @return the item at position i of the monitoring profile list
  */
  MonitoringProfile* getMonitoringProfile(unsigned int i) const;

  /**
  * Perform a class-specific configuration check on the monitoring
  * profile: verify that the size of the list of monitoring profiles has
  * a value greater than zero and that all the entries in the list
  * have been loaded with monitoring profiles.
  * @return true if the monitoring profile is configured, false otherwise.
  */
  virtual bool isObjectConfigured(void);
};

#endif

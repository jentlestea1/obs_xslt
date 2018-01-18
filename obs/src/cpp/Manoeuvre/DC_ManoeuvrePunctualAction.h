//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_ManoeuvrePunctualAction.h
//
// Version	1.0
// Date		18.05.03 (version 1.0)
// Author	A. Pasetti (P&P Software)

#ifndef DC_ManoeuvrePunctualActionH
#define DC_ManoeuvrePunctualActionH

#include "../GeneralInclude/BasicTypes.h"
#include "../Base/PunctualAction.h"
#include "../Manoeuvre/CC_ManoeuvreManager.h"

/**
 * Punctual action that launches a manoeuvre.
 * The action associated to this punctual action consists in loading
 * manoeuvre in the manoeuvre manager. The manoeuvre to be loaded
 * is a configuration parameter.
 * This punctual action is useful to model an action that consists
 * in triggering other actions that extend over time and which
 * therefore cannot be directly executed by the punctual action
 * component itself. In such a case, the actions that extend over a
 * time interval can be encoded in a manoeuvre component.
 * @see Manoeuvre
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_ManoeuvrePunctualAction : public PunctualAction {

  private:
   CC_ManoeuvreManager* pManoeuvreManager;
   Manoeuvre* pManoeuvre;

  public:

    /**
     * Instantiate a punctual action. The call identifier is set. The
     * manoeuvre manager and the manoeuvre are initialized to illegal
     * values to signify that the component is not yet configured.
     */
    DC_ManoeuvrePunctualAction(void);

    /**
     * Setter method for the manoeuvre manager into which the target
     * manoeuvre is to be loaded.
     * @see #doAction
     * @param pManMan the manoeuvre manager
     */
    void setManoeuvreManager(CC_ManoeuvreManager* pManMan);

    /**
     * Getter method for the manoeuvre manager.
     * @see #setManoeuvreManager
     * @return pManMan the manoeuvre manager
     */
    CC_ManoeuvreManager* getManoeuvreManager(void) const;

    /**
     * Setter method for the manoeuvre to be loaded into the manoeuvre
     * manager.
     * @see #doAction
     * @param pMan the manoeuvre
     */
    void setManoeuvre(Manoeuvre* pMan);

    /**
     * Getter method for the manoeuvre.
     * @see #doAction
     * @return pManMan the manoeuvre manager
     */
    Manoeuvre* getManoeuvre(void) const;

    /**
     * Perform a class-specific configuration check: verify that the manoeuvre
     * and manoeuvre manager have been loaded.
     * @return true if the object is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);

  protected:

    /**
     * Load the manoeuvre in the manoeuvre manager. This method always
     * return "action successfully executed". Note that reporting of
     * possible failures
     * related to the loading or execution of the manoeuvre should be
     * the responsibility of the manoeuvre manager.
     * @see PunctualAction#execute
     * @see TD_ActionOutcome
     * @return always returns ACTION_SUCCESS
     */
    virtual TD_ActionOutcome doAction(void);

};

#endif

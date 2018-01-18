//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// TelecommandLoader.h
//
// Version	1.0
// Date		05.12.02
// Author	A. Pasetti (P&P Software)

#ifndef TelecommandLoaderH
#define TelecommandLoaderH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all telecommand loaders are derived.
 * A telecommand loader is an object that is responsible for receiving
 * telecommands, decoding them and for
 * constructing the objects of type <CODE>Telecommand</CODE> that represent
 * the telecommand inside the application software.
 * <p>
 * Telecommand loaders must load a telecommand object in the telecommand
 * manager after having constructed it.
 * For this reason, they have the telecommand manager as a plug-in component
 * and this class declares the corresponding method to load the telecommand
 * manager.
 * <p>
 * During the process of constructing a telecommand object, the telecommand
 * loader may need to allocate
 * resources (typically memory to hold the telecommand object).
 * These resources must be released after the telecommand has been executed.
 * For this reason, this class declares a <CODE>release</CODE> method
 * that must be called by the
 * telecommand manager after it has executed a telecommand and that triggers
 * the release of the resources associated to the telecommand object.
 * <p>
 * Telecommand loaders are <i>activated</i> when a new telecommand has
 * (potentially) been received.
 * Depending on the implementation, this activation could be in response to
 * the arrival of an interrupt
 * signaling the actual reception of a new telecommand or it could be done
 * periodically to direct the
 * telecommand loader to check whether a new telecommand has arrived.
 * <p>
 * This is an abstract class. Concrete telecommand loaders are obtained by
 * deriving this class.
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 * @ingroup Telecommand
*/
class TelecommandLoader : public CC_RootObject {

  private:
    CC_TelecommandManager* pTelecommandManager;

  public:

    /**
     * Instantiate a telecommand loader. This constructor initializes the
     * telecommand manager plug-in component to point to pNULL to signify that
     * the component has not yet been configured.
     */
    TelecommandLoader(void);

    /**
     * Check whether a telecommand has been received and, if so, construct
     * the <CODE>Telecommand</CODE> object to represent
     * it and load it in the telecommand manager.
     * This is an abstract method because the way in which telecommands are
     * received and the way in which the
     * corresponding objects are constructed is application-specific.
     */
    virtual void activate(void) = 0;

    /**
     * Release the resources that the telecommand loader had allocated to the
     * argument telecommand.
     * This method should be called after the argument telecommand object has
     * been executed to allow the
     * telecommand loader to release any resources that it had allocated to
     * the telecommand object when it created it.
     * This method would normally be called by the telecommand manager.
     * @see CC_TelecommandManager#activate
     * @param pTelecommand the telecommand whose resources must be released
     */
    virtual void release(Telecommand* pTelecommand) = 0;

    /**
     * Load the telecommand manager as a plug-in component.
     * A telecommand loader needs access to the telecommand manager because
     * it must load newly created
     * telecommand objects in the telecommand manager.
     * @param pTcManager the telecommand manager
     */
    inline void setTelecommandManager(CC_TelecommandManager* pTcManager);

    /**
     * Getter method for the telecommand manager plug-in component.
     * @see #setTelecommandManager
     * @return the telecommand manager
     */
    inline CC_TelecommandManager* getTelecommandManager(void);

    /**
     * Perform a class-specific configuration check on the telecommand
     * loader: verify that the telecommand manager has been loaded.
     * @return true if the telecommand loader is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);
};

#include "TelecommandLoader_inl.h"


#endif

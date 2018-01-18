//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_DummyTelecommandLoader.h
//
// Version	1.0
// Date		11.12.02
// Author	A. Pasetti (P&P Software)

#ifndef DC_DummyTelecommandLoaderH
#define DC_DummyTelecommandLoaderH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"
#include "TelecommandLoader.h"

/**
 * Dummy telecommand loader that is useful for testing purposes.
 * This telecommand loader can be used to help test the functionalities
 * of the <code>TelecommandLoader</code> class and of the telecommand
 * manager component.
 * The dummy telecommand loader manages three <i>sample telecommands</i>.
 * These telecommands must be loaded when the dummy telecommand loader is
 * configured. When the telecommand loader is <i>activated</i>, it loads
 * one sample telecommand. The telecommand loader maintains an
 * <i>allocation counter</i> that records the number of telecommands that
 * are currently loaded in the telecommand manager associated to the
 * telecommand loader. The allocation counter is incremented by one
 * every time a telecommand is loaded into the telecommand manager and
 * it is decremented by one every time the telecommand manager sends a
 * <i>release</i> request to the telecommand loader.
 * @see DC_DummyTelecommand
 * @see CC_TelecommandManager
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_DummyTelecommandLoader : public TelecommandLoader {

  private:
    unsigned int N_SAMPLE_TC;              // number of sample telecommands
    Telecommand** pSampleTelecommand;     // array holding sample telecommands
    unsigned int allocationCounter;

  public:

    /**
     * Instantiate a dummy telecommand loader. This constructor initializes the
     * sample telecommands to pNULL and the allocation counter to zero.
     */
    DC_DummyTelecommandLoader(void);

    /**
     * Load a sample telecommand in the telecommand manager.
     * A pseudo-code implementation for this method is as follows: <PRE>
     *      i = allocationCounter MOD 3;
     *      load i-th sample telecommand in telecommand manager;
     *      allocationCounter++;  </PRE>
     * Thus, each activation causes one sample telecommand to be loaded. The
     * three sample telecommands are loaded in a cyclical sequence.
     */
    virtual void activate(void);

    /**
     * Decrement the allocation counter by 1.
     * @param pTelecommand the telecommand whose resources must be released
     */
    virtual void release(Telecommand* pTelecommand);

    /**
     * Load the i-th sample telecommand. The maximum number of sample
     * telecommands that can be loaded is 3. The index i must lie in the
     * interval [0,2]. No check is performed on the value of the index i
     * at run time.
     * @param i the sample telecommand index
     * @param pSampleTc the sample telecommand to be loaded in the i-th position
     */
    void setSampleTelecommand(unsigned int i, Telecommand* pSampleTc);

    /**
     * Getter method for allocation counter.
     * @return the allocation counter
     */
    unsigned int getAllocationCounter(void);

    /**
     * Perform a class-specific configuration check on the dummy telecommand
     * loader: verify that the sample telecommands have been loaded.
     * @return true if the telecommand loader is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);
};

#endif

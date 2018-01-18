//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSTelemetryModeManager.h
//
// Version	1.0
// Date		23.01.04
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSTelemetryModeManagerH
#define DC_PUSTelemetryModeManagerH

#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/ForwardDeclarations.h"
#include "TelemetryModeManager.h"

/**
 * PUS telemetry mode manager.
 * This telemetry mode manager has one single mode to which there 
 * corresponds a set of PUS data reporting telemetry packets 
 * (instances of class <code>PUSDataReportingPacket</code>).
 * The telemetry packets can be loaded and unloaded dynamically. 
 * The iteration methods iterate through all the currently loaded 
 * telemetry packets (the order of the iteration is undefined).
 * The mode manager is configured with the maximum number of 
 * telemetry packets that it can hold (method <code>setMaxNumberOfPackets</code>).
 * </p>
 * An initialization sequence for this class consists of the following
 * steps (to be performed in the order given): <ul>
 * <li>Set the maximum number of loadable packets with method <code>setMaxNumberOfPackets</code></li>
 * <li>Reset the component by calling method <code>reset</code></li>
 * </ul>
 * @ingroup PUS
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSTelemetryModeManager : public TelemetryModeManager {

  private:

    DC_PUSDataReportingPacket** list;    
    unsigned int listLength;   
    unsigned int iterationCounter;   
    unsigned int counter;             // number of items in list

  protected:

    /**
     * This method returns without taking any action.
     * This method is unnecessary in this class because no mode-dependent
     * memory data structures need to be allocated.
     * @see #setNumberOfModes
     * @param numberOfModes the number of modes
     */
    virtual void allocateMemory(TD_Mode numberOfModes);

  public:

    /**
     * Instantiate a PUS telemetry mode manager. The class identifier is set.
	 * The number of modes is initialized to 1. The single mode is declared to 
     * be the default mode.
	 * The size of the set of telemetry packet is initialized with illegal values
	 * to signify that the component is not yet configured.
     */
    DC_PUSTelemetryModeManager(void);

    /**
     * This method return without taking any action. This mode manager
	 * has only one mode and therefore the <i>update</i> operation is
	 * implemented to return without taking any action.
     * @see ModeManager#update
     */
    virtual void update(void);

    /**
     * Retrieve the telemetry packet currently scanned by the iteration counter.
     * This method should only be used within an iteration cycle. This method
     * should only be used within an iteration cycle (i.e. while 
     * <code>isIterationFinished</code> reports <code>false</code>).
     * @see TelemetryModeManager#first
     * @return the item currently scanned by the iteration counter
     */
    virtual TelemetryPacket* getIterationTelemetryPacket(void);

    /**
     * Load a telemetry packet in the set of packets managed by this
	 * mode manager. If the set is already full, then an event of 
	 * type EVT_ILLEGAL_MM is generated. Before calling this method, clients 
	 * should call method
	 * <code>isFull</code> to check whether there is space available.
     * @param pItem the item to be loaded
     */
    void loadPacket(DC_PUSDataReportingPacket* pItem);

    /**
     * Unload the PUS telemetry packet identified by the argument SID.
	 * If none of the currently loaded packets matches the given SID (or
	 * if the set is currently empty),
	 * no action is taken other than generating an event report of type
	 * EVT_SID_NOT_FOUND. Method <code>isSIDLoaded</code> can be used 
	 * to check whether a packet with a certain SID is currently loaded.
     * @param sid the SID of the packet to be unloaded
     */
    void unloadPacket(TD_SID sid);

    /**
     * Check whether the mode manager is full. 
	 * @see #loadPacket
     * @return true if no packets are currently loaded
     */
    bool isFull() const;

    /**
     * Return the number of packets that are currently loaded.
     * @return number of packets currently loaded
     */
    unsigned int getNumberOfPackets() const;

    /**
     * Check whether the packet with the argument SID is currently loaded.
	 * @see #unloadPacket
     * @param sid the SID 
     * @return true if a packet with the argument SID is currently loaded
     */
    bool isSIDLoaded(TD_SID sid) const;

    /**
     * Set the maximum number of packets that can be loaded. 
     * This is an initialization method. It should only be called once.
     * Only positive values for the maximum number of packets are legal.
     * @param n the maximum number of packets
     */
    void setMaxNumberOfPackets(unsigned int n);

    /**
     * Return the maximum number of packets that can be loaded.
     * @return maximum number of packets that can be loaded
     */
    unsigned int getMaxNumberOfPackets() const;

    /**
     * Iteration method to iterate through the currently loaded telemetry 
	 * packets. This method should be used jointly with methods: <code>next</code>,
     * <code>isIterationFinished</code> and <code>getIterationTelemetryPacket</code>. 
	 * Taken together,
     * these methods allow all the currently loaded items to be scanned. 
     * The item currently scanned can be retrieved
     * through method <code>getIterationTelemetryPacket</code>.
     * Thus, a typical iteration cycle might be organized as follows: <PRE>
     *      for (first(); !isIterationFinished(); next()) {
     *          pItem = getIterationTelemetryPacket();
     *          . . .    // process pItem
     *      }  </PRE>
     */
    virtual void first(void);

    /**
     * Iteration method to be used in conjunction with methods <code>first</code>
     * and <code>isIterationFinished</code>.
     * This method should only be called as part of an iteration cycle.
     * @see #first
     */
    virtual void next(void);

    /**
     * Iteration method to be used in conjunction with methods <code>first</code>
     * and <code>next</code>.
     * This method should only be used as part of an iteration cycle. The result
     * of calling it before ever calling <code>first</code>
     * is undefined.
     * @see #first
     * @return true if the end of the iteration has been reached, false otherwise
     */
    virtual bool isIterationFinished(void);

	/**
     * Perform a class-specific configuration check on a telemetry mode
     * manager: verify that the maximum number of telemetry packets that can
	 * be loaded has been set
     * @return true if the mode manager is configured, false
     * otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif

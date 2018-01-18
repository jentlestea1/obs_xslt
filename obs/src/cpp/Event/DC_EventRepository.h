//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_EventRepository.h
//
// Version	1.0
// Date	    13.09.03 (version 1.0)
//          03.12.03 (version 1.1)
// Author	A. Pasetti, R. Totaro
//

#ifndef DC_EventRepositoryH
#define DC_EventRepositoryH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../Base/CC_RootObject.h"

/**
 * Base class from which all event repository classes are derived.
 * An event repository is a generic container for <i>event reports</i>.
 * An event report is intended to record an occurrence of relevance
 * to an application.
 * The event reports are stored in instances of an <i>event class</i>.
 * To each event repository class is associated an event class. The event class
 * associated to the <code>DC_EventRepository</code> class is DC_Event.
 * <p>
 * Event repositories are characterized by one attribute and three services.
 * The attribute is the <i>repository size</i>. The repository size defines the
 * maximum number of event reports that can be stored in the repository. In a
 * typical implementation, event reports might be stored in a circular buffer and
 * only the S most recent reports are kept where S is the repository size.
 * <p>
 * The three services are the <i>event creation service</i>, the <i>repository
 * iteration service</i> and the <i>event enable service</i>.
 * <p>
 * The <i>event creation service</i> allows a client to make a new entry in
 * the event repository. Normally, to each type of event, some data that describe
 * the circumstances that led to its creation are associated. The transfer of
 * this information from the event creating component to the event repository
 * component follows a mixed "push-pull" model. The component that creates the event
 * passes an <i>event type identifier</i> to the event repository ("information push").
 * Additionally, it passes a reference to itself that allows the event repository
 * to collect additional information about the event ("information pull"). This
 * model makes it easy for designers to change the type and amount of information that
 * is associated to each event since this is defined only in the event repository,
 * not in the event creating component.
 * <p>
 * The <i>repository iteration service</i> allows clients to inspect all
 * event reports currently stored in the
 * repository in sequence starting with the most recently stored event report.
 * The event repository maintains an <i>event pointer</i> that points to one
 * of the event reports currently stored in the repository.
 * This pointer can be made to iterate through the event reports in the repository
 * using the <CODE>latest</CODE>,
 * <CODE>previous</CODE> and <CODE>isIterationFinished</CODE> methods.
 * The attributes of the event report pointed at by the event pointer can be
 * retrieved by using getter methods that are defined by the repository itself.
 * <p>
 * The <i>event enable service</i> allows creation of new event reports to be enabled and
 * disabled. This can be done either globally by disabling the creation of all
 * new event or selectively by disabling only some events.
 * <p>
 * This class offers a basic implementation of an event repository.
 * Applications which need more specialized types of event reports or different
 * implementation of the event report services, or additional services,
 * should extend this class and, if necessary, the associated event class.
 * <p>
 * This class implements the event creation service in a single method called
 * <code>create</code>. This method takes as its input the pointer to the "event
 * originator" and the event type. The originator of the event is seen as a
 * generic component of type <code>CC_RootObject</code>. Normally, the event originator
 * is the component that is calling the <code>create</code> method.
 * <p>
 * Subclasses can offer multiple
 * implementations of method <code>create</code> that
 * differ on the basis of the type of the "event originator" (for instance,
 * one could have a <code>create</code> method for event originators of type <code>Telecommand</code>
 * that intercepts event reports originating from telecommands, another <code>create</code> method
 * for event originators of type <code>Manouvre</code> that intercepts
 * event reports for manoeuvres, etc). Each
 * <code>create</code> method would gather type-specific information from its
 * event originator and create the appropriate event report.
 * @see DC_Event
 * @author Alessandro Pasetti (P&P Software)
 * @author Roberto Totaro
 * @version 1.1
 */
class DC_EventRepository : public CC_RootObject {
private:
    bool         globalEnabled;
    bool         selectiveEnabled[LAST_EVENT_TYPE+1];
    ObsClock    *pObsClock;
    unsigned int counter;	        // number of events inserted in repository
    unsigned int listSize;			// size of 'pList' event array
    unsigned int iterationCounter;

protected:
    /**
     * Array of pointers to the events in the repository. Event repository
     * classes differ, among other things, in the type of event reports they
     * store. Individual event reports are stored in objects of type
     * <code>DC_Event</code>. In general, to a subclass of <code>DC_EventRepository</code>
     * there should correspond a subclass of <code>DC_Event</code>.
     * In order to allow the implementation provided by this class to be
     * as far as possible reused by its subclasses, the manipulation of the
     * event reports is done through pointers to objects of type <code>DC_Event</code>.
     */
    DC_Event **pList;

    /**
     * Event pointer. This variable is updated by the iterator methods.
     * @see #latest
     */
    unsigned int eventPointer;

    /**
     * Create the data structure holding the event instances in the repository.
     * This implementation creates a data structure for events of type
     * <code>DC_Event</code>. Repository subclasses that must hold different
     * kinds of events should override this method to create a data structure
     * appropriate to their type of events.
     * @see #setRepositorySize
     */
    virtual void createEventDataStructure(void);

public:
    /**
     * Instantiate an event repository.
     * The global enable status of the repository is initialized to "enabled".
     * The selective enable status is initialized to "enabled" for all event types.
     * The repository size is initialized with an illegal value to signify
     * that the repository is not yet configured.
     */
    DC_EventRepository(void);

    /**
     * Setter method for the repository size.
     * The repository size defines the maximum number of event reports that can be
     * stored by the repository. A call to this method causes the internal data
     * structure where event reports are stored to be created and initialized.
     * This class offers a default implementation as follows:  <PRE>
     *    pList = new DC_Event*[repositorySize];
     *    createEventDataStructure(repositorySize);</PRE>
     * The method thus creates and initializes the data structure that
     * holds the pointers to the events in the repository but creation of the data
     * structure where the event themselves are held is delegated to the (protected)
     * method <code>createEventDataStructure</code>. Subclasses
     * must re-implement this latter method to instantiate a data structure to
     * hold events as instances of the appropriate subclass of
     * <code>DC_Event</code> (recall that to each event repository class,
     * an event class is associated). Method <code>setRepositorySize</code> can
     * instead be re-used unchanged since it is independent of the concrete
     * type of events that are stored in the repository.
     * <p>
     * This is an initialization method. It should be called before the
     * event repository is used for the first time and it should not be called more
     * than once. It is not legal to set the repository size to 0.
     * @see #createEventDataStructure
     * @see #pList
     * @param repositorySize the maximum number of events that can be stored
     * in the event repository
     */
    void setRepositorySize(unsigned int repositorySize);

    /**
     * Implement the event creation service.
     * A call to this method causes a new event report to be stored in the
     * repository if event creation is enabled.
     * Event creation can be disabled either globally (through method
     * <code>setEnable(boolean)</code>) or selectively (through
     * method <code>setSelectiveEnableMask(int)</code>).
     * Clients that call this method in order to report an event should pass to it a
     * reference to the originator of the event and the event type identifier.
     * The <i>originator</i> is the component that detected or triggered the event.
     * The <i>event type identifier</i> is an enumeration value that identifies the type
     * of event.
     * An event repository can use the pointer to the event originator to acquire
     * additional information about the event. This implementation however does not
     * use it. It takes the event type identifier, adds a time stamp to it and
     * stores it in a circular FIFO buffer.
     * If the buffer is already full, the oldest event report is overwritten.
     * The pseudo-code for this method is as follows:  <PRE>
     *    if (isEnabled())
     *         return;
     *    if (isEnabled(eventId))
     *         . . .  // add timestamp to event and store in repository
     *    else
     *         return; </PRE>
     * @see #setEnabled
     * @param originator the originator of the event
     * @param eventId the event type identifier
     */
    void virtual create(CC_RootObject *originator,TD_EventType eventId);

    /**
     * Set the global enable status of the repository.
     * When the repository is disabled, a call to method <CODE>create</CODE>
     * has no effect.
     * @param isEnabled if true, then the repository is enabled; if false,
     * then the repository is disabled
     */
    inline void setEnabled(bool isEnabled);

    /**
     * Set the selective enable status of the repository.
     * This method can be used to enabled or disable creation of events of
     * type <code>eventType</code>.
     * When creation of events of a certain type is disabled, a call
     * to method <CODE>create</CODE> for
     * an event of that type has no effect.
     * @param eventType the event type
     * @param isEnabled the new enable status for events of the specified type
     */
    inline void setEnabled(TD_EventType eventType,bool isEnabled);

    /**
     * Check the global enable status of the repository.
     * @return true if the repository is enabled, false otherwise
     */
    inline bool isEnabled(void) const;

    /**
     * Check the enable status for events of type <code>eventType</code>.
     * @return true if the generation of events of type <code>eventType</code>
     * is enabled, false otherwise
     */
    inline bool isEnabled(TD_EventType eventType) const;

    /**
     * Iteration method to position the <i>event pointer</i> on the  most recently
     * stored event.
     * The iteration methods are typically used in a loop like the following:
     * <PRE>
     *    for (latest(); !isIterationFinished(); previous())
     *         . . .  // process event pointed to by event pointer </PRE>
     * If the repository is empty, the event pointer is set to the first
     * (non-configured) event in the repository.
     * The attributes of the event report pointed to by the event pointer can be
     * retrieved with the <CODE>getEventId</CODE> and
     * <CODE>getTimeStamp</CODE> methods.
     * The effect of this and the other iterator methods is simply to update the
     * value of the event pointer variable. The event pointer is declared as a
     * <code>protected</code> variable and can therefore be accessed by subclasses.
     * Subclasses can therefore re-use the iteration services declared by this
     * class.
     * <p>
     * Calling this method also has the effect of resetting an on-going iteration.
     * <p>
     * The implementation of this method is robust to calls of method <code>create</code>
     * during an on-going iteration. The effect of doing this is that the iterators
     * may skip one event but the internal state of the repository remains consistent.
     * @see #eventPointer
     * @see DC_Event#getEventType
     * @see DC_Event#getTimeStamp
     */
    void latest(void);

    /**
     * Iteration method to advance the event pointer to the next oldest
     * event.
     * If the repository is empty or if the oldest event in the repository
     * has already been reached, then this methods has no effect.
     * @see #latest
     */
    void previous(void);

    /**
     * Iteration method to return true if the iteration is finished.
     * The iteration is finished if method <code>previous</code> has been called
     * N times since the last time method <code>latest</code> was called
     * where N is either the size of the repository (if the repository is
     * is full) of the number of items in the repository (if it is not
     * full).
     * <p>
     * If the repository is empty, this method returns true.
     * @see #latest
     * @return true if the iteration is finished
     */
    inline bool isIterationFinished(void) const;

    /**
     * Return the event identifier of the event currently pointed to by the
     * event pointer.
     * This method is typically used in conjunctions with the iteration
     * methods.
     * @see #latest
     * @return event identifier of the event currently pointed to by the
     * event pointer
     */
    inline TD_EventType getEventType(void) const;

    /**
     * Return the time stamp of the event currently pointed to by the event
     * pointer.
     * This method is typically used in conjunctions with the iteration
     * methods.
     * @see #latest
     * @return time stamp of the event currently pointed to by the event
     * pointer
     */
    inline TD_ObsTime getTimeStamp(void) const;

    /**
     * Return the number of events that have been stored in the repository
     * since it was created (including events that have been overwritten).
     * The event counter is stored in an <code>unsigned int</code> variable.
     * For reasons of run-time efficiency, there is no overflow check and
     * this class will generate an exception when the number of events exceeds
     * the capacity of the counter.
     * @return number of events created in the repostory since repository
     * creation.
     */
    inline unsigned int getCounter(void) const;

    /**
     * Return the size of the event repository.
     * @return the size of the event repository
     */
    inline unsigned int getRepositorySize(void) const;

    /**
     * Load the OBS Clock component. The event repository needs access to
     * this component in order to time-stamp events as they are created.
     * @param pObsClock the OBS Clock component.
     */
    inline void setObsClock(ObsClock *pObsClock);

    /**
     * Return the OBS Clock component.
     * @see #setObsClock
     * @return the OBS Clock component.
     */
    inline ObsClock *getObsClock(void) const;

    /**
     * Reset the repository.
     * When a repository is reset, all its event entries are cleared and the
     * event pointer is reset to point to the first (non-configured) entry
     * in the repository. Note that the event counter and the enable flags
     * are not affected by a call to this method.
     */
    void reset(void);

    /**
     * Perform a class-specific configuration check on a repository object:
     * verify that the repository size
     * has a legal value and that the OBS clock component has been loaded.
     * @return true if the object is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);
};

#include "DC_EventRepository_inl.h"


#endif



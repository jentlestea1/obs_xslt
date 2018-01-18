//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_PUSDataReportingPacket.h
//
// Version	1.0
// Date		01.11.03
// Author	A. Pasetti (P&P Software)

#ifndef DC_PUSDataReportingPacketH
#define DC_PUSDataReportingPacketH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "../GeneralInclude/Constants.h"
#include "../Telemetry/PUSTelemetryPacket.h"

/**
 * PUS telemetry data reporting packet with no filtering.
 * A <i>PUS data reporting packet</i> is used to hold the data associated
 * to a housekeeping and diagnostic data reporting definition (PUS service type 3).
 * This class assumes that no filtering is performed on the reported data.
 * The following types of service reports of the housekeeping
 * and diagnostic data reporting service are modelled:<ul>
 * <li>The housekeeping parameter report (PUS service subtype 25)</li>
 * <li>The diagnostic parameter report (PUS service subtype 26)</li>
 * </ul>
 * A data reporting packet is characterized by the following attributes: <ul>
 * <li>A structure identification or SID</li>
 * <li>A collection interval</li>
 * <li>A set of parameter identifiers</li>
 * <li>A set of fixed length arrays</li>
 * <li>A mode flag</li>
 * <li>An enabled flag</li>
 * </ul>
 * The <i>SID</i> is an integer that uniquely identifies the data reporting packet.
 * <p>
 * The <i>collection interval</i> defines the interval between successive
 * dispatches of the packet content to the telemetry stream. The collection interval
 * is expressed as a positive integer representing a number of activations
 * of the <i>data update service</i> (see method <code>update</code> in the base
 * class <code>TelemetryPacket</code>). Thus, for instance, a collection interval of 3
 * indicates that the data in the reporting packets are made available for dispatch
 * to the telemetry stream every third activation of the <i>data update service</i>.
 * <p>
 * The <i>parameter identifiers</i> identify the parameters whose values have to
 * be included in the reporting packet. Only parameters in the <i>system data pool</i>
 * can be included in a data reporting
 * packet. As parameter identifier, the <i>data pool item identifier</i> must be used
 * (see class <code>DataPool</code>).
 * <p>
 * A <i>fixed length array</i> identifies a set of parameters that must be sampled with the
 * frequency. The fixed length array specifies the sampling frequency through the
 * the <i>repetition count</i>, namely the number of times that the parameters must be sampled in a
 * collection interval. If C is the collection interval for the data reporting packet
 * and NREP is the repetition count, then C must be a multiple of NREP. The value of
 * the parameters is acquired every C/NREP activations of the <i>data update service</i>.
 * <p>
 * The <i>mode flag</i> determines whether the "mode" field should be included
 * in the generated packet. If it is to be included, its value is always zero.
 * The mode flag is a static attribute that is defined as a constant PUS_DATA_REP_MODE
 * in file <code>Constants.h</code>.
 * <p>
 * The <i>enabled flag</i> determines whether the data reporting packet is enabled
 * or disabled. If a data reporting
 * packet is disabled, then its <i>update service</i> takes no action and its
 * <i>data acquisition service</i> reports: "no telemetry data to be acquired".
 * <p>
 * An instance of this class is first configured after being created by performing the
 * following operations: <ul>
 * <li>The maximum size of the packet definition buffer is set (method
 * <code>setDefinitionBufferSize</code>). </li>
 * <li>The maximum size of the packet value buffer is set (method
 * <code>setValueBufferSize</code>). </li>
 * <li>The maximum number of fixed-length array is set (method <code>setMaxNumberFA</code>). </li>
 * </ul>
 * The <i>packet definition buffer</i> is an internal buffer that holds a copy of the
 * application data of the PUS telecommand that defined the housekeeping or diagnostic packet
 * report.
 * The <i>packet value buffer</i> is an internal buffer that holds an image of
 * telemetry data associated to this telemetry packet. In particular, it hols
 * the values of the
 * parameters as they are acquired in a collection interval.
 * <p>
 * Instances of this class will normally undergo a second configuration process
 * at run time when the housekeeping or diagnostic report definition is loaded.
 * This configuration procedure is performed by loading the packet definition buffer
 * byte by byte using method <code>setDefinitionBuffer</code>.
 * <p>
 * The PUS specifies that the SID, the collection interval, the number of parameters, the number
 * of repetitions, and the number of fixed-length arrays, should be of "unsigned integer" type but it
 * does not specify the implementation of this type. This class uses <code>typedef</code> type definitions
 * for the SID, the collection interval, and the number of parameters and it implements the number
 * of repetitions and the number of fixed length arrays as "unsigned char".
 * Similarly, the PUS specifies that the mode of packet generation should be of "enumerated" type but
 * it does not elaborate on the exact nature of this type. This class implements the mode indicator
 * as an "unsigned char".
 * <p>
 * This class retrieves the data to be stored in the PUS reporting packet from the system
 * data pool. In order to copy them to the packet, information about the type of the data
 * is required. This information is retrieved by using the <i>type checking</i> service of
 * the data pool (see methods <code>isFloat</code> and <code>isInteger</code> in class
 * <code>DataPool</code>). This class therefore assumes that the type checking service is fully
 * implemented by the system data pool.
 * <p>
 * This class implements the <i>fast version of the data acquisition service</i>. This is 
 * useful when the amount of telemetry data is very large.
 * <p>
 * <b>Description of Internal Data Structures</b>
 * The internal data structures of this class do not differentiate between the paramaters that
 * are sampled only once per collection interval and the fixed-length arrays that describe
 * oversampled paramaters. To the parameters that are sampled only once per collection interval,
 * a fictitious fixed-length array is associated with a repetition count of 1.
 * <p>
 * The internal array F holds the descriptors of the fixed length arrays. Element F[0] describes
 * the parameters that are to be sampled only once per collection interval. Element F[i] with i>0
 * describes the i-th fixed length array.
 * <p>
 * The definition of the PUS packet is kept in the <i>packet definition buffer</i> that is a byte-by-byte
 * copy of the application data in the PUS telecommand defining the housekeeping or diagnostic
 * parameter report. This buffer is loaded byte by byte and it is interpreted as it is loaded.
 * The objective of the interpretation is to set up a "map" of the buffer. This map consists
 * of variables that point to locations in the buffer where certain information is held. Thus,
 * for instance, internal variable <code>indNFA</code> points to the location in the buffer where
 * the NFA field is stored. The most important mapping variable is the array <code>indFA</code>.
 * Element <code>indFA[i]</code> with i>0 holds the location of the NREP value of the i-th fixed-length
 * array.
 * <p>
 * The <i>packet value buffer</i> is organized as an array of unsigned char. Its first locations
 * hold the SID and, depending on the value of flag PUS_DATA_REP_MODE, the reporting mode.
 * Successive locations hold the collected parameter
 * values stored in consecutive locations.
 * @see DataPool
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class DC_PUSDataReportingPacket : public PUSTelemetryPacket {

  private:
    bool enabled;

    unsigned char* defBuffer;
    unsigned int defBufferSize;
    unsigned int defBufferCounter;  // number of bytes loaded in the packet definition buffer

    unsigned char* valBuffer;
    unsigned int valBufferSize;

    unsigned int indSID;
    unsigned int indCollectionInterval;
    unsigned int indNPAR1;
    unsigned int indNFA;

    struct FaDescType {
        unsigned char nrep;   // repetition count (number of frames to be collected in one interval)
        TD_PUSNumberOfParameters npar;
        unsigned int size;    // number of bytes required to store one set of samples (one frame)
        TD_PUSCollectionInterval counter;       // after a call to update(): the number of remaining
                                                // update cycles before a data collection
        unsigned int rep;     // after a call to update(): the number of frames already collected
                              // in this collection interval
        unsigned int ind;     // index of defBuffer where the first byte of the first FA parameter is stored
        unsigned int val;     // index of valBuffer where the first byte of the FA values is stored
    };
    FaDescType* F;
    unsigned int faDescSize;
    unsigned int FAcounter;   // number of FA in the packet

  protected:
    /**
     * Get the parameter id of the parPos-th parameter in the faIndex-th fixed length array.
     * The parameter id is read from the packet definition buffer. The value of <code>faIndex</code>
     * should lie in the interval [0,N] where N is the number of fixed length arrays in the
     * packet. A value of <code>faIndex</code> equal to zero is taken to refer to the
     * paramaters that are sampled only once per collection interval. The value of <code>parPos</code>
     * should lie in the interval [0,M-1] where M is the total number of parameters in
     * the fixed-length array (or the total number of parameters to be sampled only once per
     * collection interval).
     * @param faIndex the fixed length array index
     * @param parPos the position of the parameter in the fixed length array
     * @return the paramater identifier
     */
    TD_DataPoolId  getParameterId(unsigned int faIndex, unsigned int parPos);

  public:
    /**
     * Instantiate a PUS data report packet.
     * The size of the internal buffers are set to illegal values to signify
     * that the data report packet is not yet configured. The class identifier is set.
     * The packet type is set to: PUS_TYPE_DATA_REP.
     * The enable status is set to "disabled". The "in use" status is set to:
     * "packet not in use".
     * @see PUS_TYPE_DATA_REP
     */
    DC_PUSDataReportingPacket(void);

    /**
     * Set the enable status of the data reporting packet.
     * @param enabledStatus the new enabled status
     */
    void setEnabled(bool enabledStatus);

    /**
     * Return the enable status of the data reporting packet.
     * @return true if the data reporting packet is enabled, false otherwise
     */
    bool isEnabled() const;

    /**
     * Getter method for the collection interval.
     * @return the collection interval
     */
    TD_PUSCollectionInterval getCollectionInterval();

    /**
     * Getter method for the number of parameters to be sampled once per collection
     * interval.
     * @return the number of parameters
     */
    TD_PUSNumberOfParameters getNPAR1();

    /**
     * Getter method for the number of fixed-length arrays.
     * @return the number of fixed-length arrays
     */
    unsigned char getNFA();

    /**
     * Getter method for the structure identifier (SID) of the data reporting packet.
     * @return the SID of the packet
     */
    TD_SID getSID();

    /**
     * Load the i-the byte of the <i>packet definition buffer</i>. As the packet bytes
     * are loaded, they are interpreted and the internal map of the packet is constructed.
     * This method assumes that the bytes are loaded in sequence starting from the most significant
     * byte of the SID and ending with the least significant byte of the last parameter identifier
     * in the last fixed-length array of the packet.
     * <p>
     * The index i must lie in the interval [0,N-1] where N is the size of the
     * packet definition buffer. If this is not the case, then the method generates an event
     * report EVT_ILLEGAL_PUS_REP_PACKET and returns without taking any further action.
     * <p>
     * This method, among other things, maintains a counter that keeps track of the number of fixed
     * length arrays that have been loaded. If the number of fixed length arrays exceeds the
     * maximum value set with method <code>setMaxNumberFA</code>, then an event report
     * EVT_ILLEGAL_PUS_REP_PACKET is generated.
     * @see #setDefinitionBufferSize
     * @param i the byte to be loaded
     * @param val the value of the byte
     */
    void setDefinitionBuffer(unsigned int i, unsigned char val);

    /**
     * Return the i-th byte of the <i>packet definition buffer</i>. The values that are
     * returned are those that were set with the last set of consecutive calls to
     * method <code>setDefinitionBuffer</code>.
     * This method should be used in conjunction with method <code>getDefinitionBufferLength</code>.
     * The legal range of the index i is [0,N-1] where N is the return value of
     * <code>getDefinitionBufferLength</code>.
     * @see #getDefinitionBufferLength
     * @see #setDefinitionBuffer
     * @param i the index of the byte in the packet definition buffer to be returned
     * @return the value of the byte
     */
    unsigned char getDefinitionBuffer(unsigned int i);

    /**
     * Return the number of bytes in the <i>packet definition buffer</i> that were loaded with
     * the last set of consecutive calls to method <code>setDefinitionBuffer</code>.
     * @return the number of loaded bytes in the packet definition buffer
     */
    unsigned int getDefinitionBufferLength(void);

    /**
     * Implement the data update service. This class maintains a <i>main counter</i> and a
     * a set of <i>FA counters</i>, one for each fixed-length array. After a reset (call
     * to method <code>reset</code>). The main counter is initialized to the value of the
     * collection interval. The FA counters are initialized to the value of the
     * repetition count of their fixed-length array.
     * If the component is enabled, then every time this method is called, the counters are
     * decremented by one. When an FA counter reaches the value of zero, the following
     * actions are performed: <ul>
     * <li>The values of the parameters in the fixed-length array are acquired from the
     * system database and are stored in the parameter buffer</li>
     * <li>The FA counter is reset to its initial value</li>
     * </ul>
     * When the main counter reaches zero, then all the parameter values are acquired.
     * In all cases, the time attribute of the telemetry packet is set to the current
     * time.
     */
    virtual void update();

    /**
     * Reset the internal state of the data reporting packet. The main counter is
     * initialized to the value of the
     * collection interval. The FA counters are initialized to the value of the
     * repetition counter of their fixed-length array. The component is disabled.
     * @see #update
     */
    void reset();

    /**
     * Return the number of bytes that this data reporting packet will provide at
     * the next call of the data acquisition service.
     * If this method is called at a time other than the end of a collection interval,
     * then its return value is zero. The end of a collection interval is detected by
     * looking at the value of the main counter defined in method <code>update</code>.
     * At the end of a collection interval, this counter has value zero. A return
     * value of zero for this method indicates that the data reporting packet is not
     * providing any data for the telemetry stream. A PUS data reporting packet
     * is only intended to provide telemetry data at the end of its collection interval.
     * <p>
     * If this method is called at the end of a collection interval (i.e. at a time
     * when the main counter defined in method <code>updatey</code> is equal to zero), then
     * its return value is equal to the number of bytes in the data reporting packet. This
     * is computed as follows: <pre>
     *      n1 = sizeof(TD_SID);
     *      if (PUS_DATA_REP_MODE)
     *          n2 = 1;
     *      else
     *          n2 = 0;
     *      n3 = 0;
     *      for (all parameters p in the packet)
     *          if (p is of type TD_Float)
     *              n3 += (repetition count of p) * sizeof(TD_Float);
     *          else
     *              n3 += (repetition count of p) * sizeof(TD_Integer);
     *      return (n1+n2+n3); </pre>
     * The "repetition count" of a parameter is 1 for parameters that are collected only
     * once per cycle and it is as specified by the relevant fixed-length array for over-sampled
     * parameters.
     * <p>
     * If the packet is disabled, then this method returns zero to signify that a disabled
     * packet should not provide any telemetry data.
     * @see #update
     * @return the number of bytes in this data reporting packet at the end of
     * a collection interval or zero at other times
     */
    virtual unsigned int getNumberOfBytes (void);

    /**
     * Return the n-th byte of this data reporting packet. The image of this packet is stored
     * in the packet value buffer. This method therefore simply returns the value of the n-th element 
     * of the packet value buffer. 
     * Note that this method is independent of whether or not the packet is enabled.
     * @param n the byte to be returned
     */
    virtual unsigned char getUnsignedByte(unsigned int  n);

    /**
     * Return a pointer to start address of the packet value buffer. 
     * This method implements the fast version of the data acquisition service.
     * This may be useful (if potentially unsafe) in the case of large packets.
     * @return the start address of the packet value buffer
     */
    virtual unsigned char* getStartAddress(void);

    /**
     * Return <code>true</code> to signify that the fast version of the data acquisition
     * service is implemented. 
     * @see #getStartAddress
     * @return this method always returns <code>true</code> 
     */
    virtual bool isFastAcquisitionImplemented(void);

    /**
     * Set the maximum size of the <i>packet definition buffer</i>.
     * This is an initialization method. It should be called only once as part of the
     * component configuration during the application initialization phase.
     * The maximum size should be smaller than 0xFF.
     * @todo Clarify the reason for the 0xFF limit on the buffer size. This seems to be
     * obsolete.
     * @param size the size of the packet definition buffer
     */
    void setDefinitionBufferSize(unsigned int size);

    /**
     * Get the maximum size of the <i>packet definition buffer</i>.
     * @return the size of the packet definition buffer
     */
    unsigned int getDefinitionBufferSize();

    /**
     * Set the maximum number of fixed-length arrays that are allowed in a
     * data reporting packet.
     * This is an initialization method. It should be called only once as part of the
     * component configuration during the application initialization phase.
     * @param n the maximum number of fixed-length arrays
     */
    void setMaxNumberFA(unsigned int n);

    /**
     * Return the maximum number of fixed-length arrays that are allowed in a
     * data reporting packet.
     * @return the maximum number of Ffixed-length arrays
     */
    unsigned int getMaxNumberFA(void);

    /**
     * Set the maximum size of the <i>packet value buffer</i>.
     * This is an initialization method. It should be called only once as part of the
     * component configuration during the application initialization phase.
     * @param size the size of the packet definition buffer
     */
    void setValueBufferSize(unsigned int size);

    /**
     * Return the maximum size of the <i>packet value buffer</i>.
     * @return the size of the packet definition buffer
     */
    unsigned int getValueBufferSize(void);

    /**
     * Perform a class-specific configuration check on the telemetry packet:
     * verify that: <ul>
     * <li>The maximum size of the packet definition buffer has a legal value</li>
     * <li>The maximum size of the packet value buffer has a legal value</li>
     * <li>The maximum number of fixed-length arrays has a legal value</li>
     * </ul>
     * @return true if the component is configured, false otherwise.
     */
    virtual bool isObjectConfigured(void);

};

#endif

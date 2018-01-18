//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// PUSMemoryDump.h
//
// Version	1.0
// Date		05.12.03
// Author	A. Pasetti (P&P Software)

#ifndef PUSMemoryDumpH
#define PUSMemoryDumpH

#include "../GeneralInclude/ForwardDeclarations.h"
#include "../GeneralInclude/BasicTypes.h"
#include "PUSTelemetryPacket.h"

/**
 * Base class from which the classes implementing the memory dump telemetry packets 
 * (PUS service type 6, subtypes 4 and 6) can be derived.
 * This class defines an internal memory structure where the characteristics of the
 * memory blocks to be dumped (start address, length, and checksum) are stored.
 * Additionally, it defines <i>dump buffer</i> to be used to store the telemetry packet
 * image. The <i>data acqusition service</i>
 * (defined by the super class <code>TelemetryPacket</code>) is implemented to flush
 * this buffer. Since the amount of data in a memory packet may be large, this class
 * implements both the safe and fast versions of the data acquisition service.
 * Finally, this class defines a <i>checksum flag</i>) that can be set
 * to indicate whether checksum should be computed and included in the telemetry packet 
 * data. the checksum flag is defined as a static variable and is initialized to false.
 * The <i>data update service</i> depends on the data subtype and must therefore
 * be defined by the subclasses. All the internal data structures defined by this class
 * are declared <code>protected</code> to allow easy access to them by the subclasses
 * that implement the two forms of the memory dump service.
 * <p>
 * The initial configuration of this class is performed as follows:<ul>
 * <li>Method <code>setMaxNumberOfBlocks</code> must be called to set the maximum
 * number of memory blocks that can be managed by this telemetry packet</li>
 * <li>Method <code>setDumpBufferSize</code> must be called to set the maximum size of
 * the dump buffer.</li>
 * <li>The checksum flag is set with method <code>setChecksumFlag</code>. Note that 
 * this is a static method and that the checksum flag applies globally to all
 * memory dump telemetry blocks.</li>
 * </ul>
 * The dynamic configuration of the telemetry packet is performed as follows:<ul>
 * <li>The number of blocks to be dumped is set with method <code>setNumberOfBlocks</code>  </li>
 * <li>The blocks are defined with a sequence of calls to method <code>defineBlock</code>  </li>
 * </ul>
 * The PUS leaves some leeway in the definition of the structure of the application
 * data for memory load telecommands. This implementation makes the following 
 * assumptions: <ul>
 * <li>The memory ID is always present and is an integer of syntactical type <code>TD_PUSMemId</code>.</li>
 * <li>The number of memory blocks field is always present. The number of memory blocks is treated
 * as an integer of syntatical type <code>TD_PUSNumberMemBlocks</code>.</li>
 * <li>The memory data are treated as integers of syntactical type 
 * <code>TD_PUSMemData</code>. This type defines the single addressable unit (or SAU).</li>
 * <li>The offset of a memory block with respect to a base address is treated as an integer
 * of syntactic type <code>TD_PUSMemOffset</code>.</li>
 * <li>The length of a memory block is treated as an integer
 * of syntactic type <code>TD_PUSMemLength</code>.</li>
 * <li>The checksum field is always included (it is set to zero when no checksum is required).</li>
 * </ul>
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @version 1.0
 */
class PUSMemoryDump : public PUSTelemetryPacket {

  protected:

    /**
     * This structure describes one memory dump block. 
     */
    struct MemBlockType {

        /**
         * Start address of a memory dump block
         */ 
        TD_PUSMemData* startAddress;         

        /**
         * The number of SAUs to be loaded
         */ 
        TD_PUSMemLength length;              

        /**
         * The checksum of the block
         */ 
        unsigned short checksum;             
    };

    /**
     * The i-th item of this array holds the descriptor for the i-th memory block
     * to be dumped
     */
    MemBlockType* block;

    /**
     * The maximum number of memory dump blocks
     */
    TD_PUSNumberMemBlocks maxNumberBlocks;

    /**
     * The number of memory dump blocks that must be dumped by this telemetry packet.
     */
    TD_PUSNumberMemBlocks numberBlocks;

    /**
     * Dump buffer. 
     */
    unsigned char* data;

    /**
     * The size of the telemetry packet in number of bytes. 
     */
    unsigned int tmPacketSize;

    /**
     * The size of the dump buffer.
     */
    unsigned int maxNumberData;
    
    /**
     * Flag indicating whether checksum data are required.
     */
    static bool isChecksumRequired;

    /**
     * Identifier of the memory block.
     */
    TD_PUSMemId memId;

  public:

    /**
     * Instantiate a PUS memory dump telemetry packet.
     * The values of the internal data structures that are used to hold the telecommand
     * application data are initialized to illegal values to signify that the telecommand
     * is not yet configured. 
     * The checksum flag is set to <code>false</code> (no checksum data required).
     * The memory identifier is initialized to zero.
     */
    PUSMemoryDump(void);

    /**
     * Set the maximum number of memory blocks that can be managed by this telemetry packet.
     * This is an initialization method that should only be called once.
     * A call to this method causes the internal data structures where the blocks are
     * held to be allocated and initialized. Only positive values of the method argument
     * are legal.
     * @param max the maximum number of blocks
     */
    void setMaxNumberBlocks(TD_PUSNumberMemBlocks max);

    /**
     * Get the maximum number of memory blocks that can be managed by this telemetry packet.
     * @see #setMaxNumberBlocks
     * @return the maximum number of blocks
     */
    TD_PUSNumberMemBlocks getMaxNumberBlocks() const;

    /**
     * Set the number of memory blocks that must be managed by this telemetry packet.
     * This method is normally called when the telemetry packet is dynamically configured.
     * The value of the argument N must lie in the range [1,N] where N is the maximum number of
     * blocks set with method <code>setmaxNumberBlocks</code>. If this is not the case, the number
     * of blocks is set to N and event report EVT_PUS_TOO_MANY_DUMP_BLOCKS. Only positive values are legal for the number
     * of blocks.
     * @param max the maximum number of blocks
     */
    void setNumberBlocks(TD_PUSNumberMemBlocks max);

    /**
     * Get the number of memory blocks that are managed by this telemetry packet.
     * @see #setNumberBlocks
     * @return the number of blocks
     */
    TD_PUSNumberMemBlocks getNumberBlocks() const;

    /**
     * Set the size (in number of bytes) of the dump buffer. 
     * This is an initialization method that should only be called once.
     * A call to this method causes the memory for the dump buffer to be 
     * allocated and initialized. Only positive values of the method argument
     * are legal.
     * @param max the size of the dump buffer
     */
    void setDumpBufferSize(unsigned int max);

    /**
     * Get the size (in number of bytes) of the dump buffer.
     * @see #setDumpBufferSize
     * @return the size (in number of bytes) of the dump buffer.
     */
    unsigned int getDumpBufferSize() const;

    /**
     * Set the checksum flag. If this flag is set to true, then the checksum is computed
     * for each memory block to be dumped. Otherwise, the checksum field is set to zero.
     * Note that the checksum field is always included in the telemetry packet.
     * @param checksumFlag the value of the checksum flag
     */
    static void setChecksumFlag(bool checksumFlag);

    /**
     * Return the value of the checksum flag. 
     * @return the value of the checksum flag
     */
    static bool isChecksumFlagSet();

    /**
     * Define the characteristics of the i-th memory block to be dumped. This method
     * would normally be called as part of the dynamic telemetry packet configuration.
     * The index i must lie in the range [0,N-1] where N is the number of blocks
     * set with method <code>setNumberBlocks</code>). If this is not the case, 
     * the method generates event report EVT_PUS_ILLEGAL_BLOCK_INDEX and returns immediately.
     * The checksum value of the i-th block is initialized to zero.
     * @param i the memory dump index
     * @param start the start address of the i-th memory dump block
     * @param length the length of the i-th memory dump block
     */
    void defineBlock(TD_PUSNumberMemBlocks i, TD_PUSMemData* start, TD_PUSMemLength length);

    /**
     * Return the number of bytes in this telemetry packet.
     * This is the number of bytes of the application data part of the telemetry packet
     * holding the memory dump data. The number of bytes in the telemetry packet is computed
     * as part of the <i>data update service</i>. This method will only return a valid value
     * after method <code>update</code> has been called.
     * @return number of bytes in this telemetry packet
     */
    virtual unsigned int getNumberOfBytes(void);

    /**
     * Implement the  <i>data acquisition service</i> for the PUS telemetry memory dump
     * packet. This method assumes the telemetry packet data to be already loaded in the
     * <i>dump buffer</i>. A pseudo-code implementation for this method is as follows:<pre>
     *      return data[n]; </pre>
     * where <code>data</code> is the dump buffer (recall that its first element holds the 
     * length of the telemetry packet).
     * The argument n must lie in the range [0,N-1] where N is the length of the 
     * telemetry packet (the return value of method <code>getNumberOfBytes</code>)
     * If this is not the case, the return value of this method is undefined.
     * The dump buffer is loaded by method <code>update</code>.
     * @return value of n-th telemetry byte
     * @param n the telemetry byte to be returned (starting with byte 0)
     */
    virtual unsigned char getUnsignedByte(unsigned int n);

    /**
     * Implement the fast version of the <i>data acquisition service</i>.
     * This method returns the address of the first location of the dump buffer. 
     * @return the address of the first location of the dump buffer
     */
    virtual unsigned char* getStartAddress(void);

    /**
     * Return <code>true</code> to signify that the the fast version of the data acquisition
     * service is implemented. 
     * @see #getStartAddress
     * @return always return <code>true</code>
     */
    virtual bool isFastAcquisitionImplemented(void);

    /**
     * Get the start address of the i-th currently loaded block.
     * The block index i must lie in the interval [0,N-1] where N is the number
     * of currently loaded blocks (the value returned by method 
     * <code>getNumberBlocks</code>). If this condition is not satisfied,
     * the return value is unpredictable. This method is unsafe because it
     * returns a pointer. It is intended to be used only for testing purposes.
     * @param i the block index
     * @return the start address of the i-th currently loaded block
     */
    TD_PUSMemData* getStartAddress(TD_PUSNumberMemBlocks i) const;

    /**
     * Get the length of the i-th currently loaded block.
     * The block index i must lie in the interval [0,N-1] where N is the number
     * of currently loaded blocks (the value returned by method 
     * <code>getNumberBlocks</code>). If this condition is not satisfied,
     * the return value is unpredictable. 
     * @param i the block index
     * @return the length of the i-th currently loaded block
     */
    TD_PUSMemLength getLength(TD_PUSNumberMemBlocks i) const;

    /**
     * Get the value of the checksum field for the i-th currently loaded block.
     * The block index i must lie in the interval [0,N-1] where N is the number
     * of currently loaded blocks (the value returned by method 
     * <code>getNumberBlocks</code>). If this condition is not satisfied,
     * the return value is unpredictable.
     * @param i the block index
     * @return the length of the i-th currently loaded block
     */
    unsigned short getChecksum(TD_PUSNumberMemBlocks i) const;

    /**
     * Set the memory block identifier for the dump packet.
     * Only values greater than zero are legal.
     * @see #update
     * @param memId the memory block identifier
     */
    void setMemoryId(TD_PUSMemId memId);

    /**
     * Get the memory block identifier for the dump packet.
     * @see #setMemId
     * @return the memory block identifier
     */
    TD_PUSMemId getMemoryId();

    /**
     * Perform a class-specific configuration check on the telecommand:
     * check that the maximum number of blocks and the maximum number of data have been
     * defind.
     * @return true if the telecommand is configured, false otherwise
     */
    virtual bool isObjectConfigured(void);

};

#endif 

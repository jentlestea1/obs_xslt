//
// Copyright 2004 P&P Software GmbH - All Rights Reserved
//
// DC_RawDataItem.h
//
// Version	1.0
// Date		11.10.03 (Version 1.0)
// Author	A. Pasetti (P&P Software), R. Totaro
//
// Change Record:

#ifndef DC_RawDataItemH
#define DC_RawDataItemH

#include "../GeneralInclude/BasicTypes.h"
#include "../Data/DC_DataItem.h"

/**
 * This class encapsulates a raw data item.
 * A <i>raw data item</i> is a data item that encapsulates a "raw pointer",
 * namely a pointer that does not have a specific type and is defined simply 
 * as a "pointer to void". The raw data item offers accessors methods that allow
 * its underlying variable to be accessed as a variable of the following
 * types: <code>unsigned int</code>, <code>int</code>, <code>unsigned short</code>,
 * <code>short</code>, <code>unsigned char</code>, <code>char</code>,
 * <code>float</code>, and <code>double</code>. The raw data item therefore
 * essentially allows cast to be performed between types in a controlled manner.
 * This is useful when manipulating registers or other low-level variables. 
 * @author Alessandro Pasetti (P&P Software GmbH)
 * @author Roberto Totaro
 * @version 2.0
 */
class DC_RawDataItem : public DC_DataItem {

  public:
    /**
     * Instantiate a raw data item component.
     * This constructor simply calls the constructor of the super class and
     * passes its argument to it as shown in the following pseudocode:<pre>
     *      DC_DataItem((TD_Integer*)d);  </pre>
     * The cast to the type "pointer to TD_Integer" is arbitrary and only 
     * serves to select one of the two constructors defined in the superclass.
     * @param d reference to the variable encapsulated by the data item
     */
	inline DC_RawDataItem(void *d);

    /**
     * Return the value of the data item intepreted as a variable of
     * type <code>char</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>char</code>
     * and its dereferenced value is returned.
     * @return the value of the variable encapsulated in the data item
     */
    inline char getChar(void) const;

    /**
     * Set the value of the data item intepreted as a variable of
     * type <code>char</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>char</code>.
     * @param newValue the new value of the variable encapsulated in the data item
     */
    inline void setChar(char newValue);

    /**
     * Return the value of the data item intepreted as a variable of
     * type <code>unsigned char</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>unsigned char</code>
     * and its dereferenced value is returned.
     * @return the value of the variable encapsulated in the data item
     */
    inline unsigned char getUnsignedChar(void) const;

    /**
     * Set the value of the data item intepreted as a variable of
     * type <code>unsigned char</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>unsigned char</code>.
     * @param newValue the new value of the variable encapsulated in the data item
     */
    inline void setUnsignedChar(unsigned char newValue);

    /**
     * Return the value of the data item intepreted as a variable of
     * type <code>short</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>short</code>
     * and its dereferenced value is returned.
     * @return the value of the variable encapsulated in the data item
     */
    inline short getShort(void) const;

    /**
     * Set the value of the data item intepreted as a variable of
     * type <code>short</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>short</code>.
     * @param newValue the new value of the variable encapsulated in the data item
     */
    inline void setShort(short newValue);

    /**
     * Return the value of the data item intepreted as a variable of
     * type <code>unsigned short</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>unsigned short</code>
     * and its dereferenced value is returned.
     * @return the value of the variable encapsulated in the data item
     */
    inline unsigned short getUnsignedShort(void) const;

    /**
     * Set the value of the data item intepreted as a variable of
     * type <code>unsigned short</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>unsigned short</code>.
     * @param newValue the new value of the variable encapsulated in the data item
     */
    inline void setUnsignedShort(unsigned short newValue);

    /**
     * Return the value of the data item intepreted as a variable of
     * type <code>int</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>int</code>
     * and its dereferenced value is returned.
     * @return the value of the variable encapsulated in the data item
     */
    inline int getInt(void) const;

    /**
     * Set the value of the data item intepreted as a variable of
     * type <code>int</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>int</code>.
     * @param newValue the new value of the variable encapsulated in the data item
     */
    inline void setInt(int newValue);

    /**
     * Return the value of the data item intepreted as a variable of
     * type <code>unsigned int</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>unsigned int</code>
     * and its dereferenced value is returned.
     * @return the value of the variable encapsulated in the data item
     */
    inline unsigned int getUnsignedInt(void) const;

    /**
     * Set the value of the data item intepreted as a variable of
     * type <code>unsigned int</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>unsigned int</code>.
     * @param newValue the new value of the variable encapsulated in the data item
     */
    inline void setUnsignedInt(unsigned int newValue);

    /**
     * Return the value of the data item intepreted as a variable of
     * type <code>float</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>float</code>
     * and its dereferenced value is returned.
     * @return the value of the variable encapsulated in the data item
     */
    inline float getFloat(void) const;

    /**
     * Set the value of the data item intepreted as a variable of
     * type <code>float</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>float</code>.
     * @param newValue the new value of the variable encapsulated in the data item
     */
    inline void setFloat(float newValue);

    /**
     * Return the value of the data item intepreted as a variable of
     * type <code>double</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>double</code>
     * and its dereferenced value is returned.
     * @return the value of the variable encapsulated in the data item
     */
    inline double getDouble(void) const;

    /**
     * Set the value of the data item intepreted as a variable of
     * type <code>double</code>. The pointer that is encapsulated by the
     * data item is interpreted as a pointer to type <code>double</code>.
     * @param newValue the new value of the variable encapsulated in the data item
     */
    inline void setDouble(double newValue);
};

#endif

#include "DC_RawDataItem_inl.h"



<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for a stack container class for the OBS 
Framework.
A "stack container" is a container class that behaves like a FIFO
data structure. This code generator essentially allows the class to be
parameterized by the type of the items to be held in stack container.

This XSLT program generates the header file of the stack container class.

This XSLT program process an XML file that describes the target stack 
container. The XML file is assumed to have the following structure:
- A top-level element "StackContainerDescriptor" with a "name" attribute
  (the name of the stack container class) and "classId" attribute (the 
  class identifier). 
- A child element "Type" (the type of the objects to be held in the
  stack) with a "headerFile" attribute (the fully qualified name of the 
  header file where the type is defined. The file name must be relative to 
  the directory where the wrapper class will be stored). If the "headerFile"
  is not present, then the type of the items in the stack is a primitive type
- A child element "ObsFrameworkCodeDirPath" (the path of the OBS Framework
  code directory relative to the directory where the wrapper class will be
  stored. Header and body files are assumed to be placed in the same
  directory)
===================================================================-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.0"
    xmlns:lxslt="http://xml.apache.org/xslt"
    xmlns:redirect="org.apache.xalan.lib.Redirect"
    extension-element-prefixes="redirect">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--================================================================-->
<!-- Top-level rule                                                 -->
<!--================================================================-->

<xsl:template match="/StackContainerDescriptor">
  <xsl:call-template name="GenerateCode"/>
</xsl:template>

<!--================================================================-->
<!-- Code generationg                                               -->
<!--================================================================-->

<xsl:template name="GenerateCode">

  <!-- extract useful variables from XML file                       -->
  <xsl:variable name="ClassName" select="@name"/>
  <xsl:variable name="ClassId" select="@classId"/>
  <xsl:variable name="Type" select="Type"/>
  <xsl:variable name="HeaderFile" select="Type/@headerFile"/>
  <xsl:variable name="CodeDir" select="ObsFrameworkCodeDirPath"/>

  <!-- start code generation                                       -->
//
// Copyright 2003 P&amp;P Software GmbH  - All Rights Reserved
//
// <xsl:value-of select="$ClassName"/>.h
//
// Version	1.0
// Date		30.08.03 (Version 1.0)
// Author	A. Pasetti (P&amp;P Software)
//

#ifndef <xsl:value-of select="$ClassName"/>H
#define <xsl:value-of select="$ClassName"/>H

#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/ForwardDeclarations.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$CodeDir"/>Base/CC_RootObject.h"
<xsl:if test="Type/@headerFile">#include "<xsl:value-of select="Type/@headerFile"/>"</xsl:if>

/**
 * Stack-like container class for items of type: &lt;code&gt;<xsl:value-of select="$Type"/>&lt;/code&gt;. 
 * This class was automatically generated by an XSLT program.
 * It models a FIFO container with a fixed size. The items in the container are
 * handled as variables of type: &lt;code&gt;<xsl:value-of select="$Type"/>&lt;/code&gt;. This is 
 * a type-safe class that does not perform any type casting.
 * The size of the stack must be set by the user during the initialization phase
 * and cannot be changed afterwards. This class offers the two traditional &lt;i&gt;push&lt;/i&gt;
 * and &lt;i&gt;pop&lt;/i&gt; operations and a &lt;i&gt;reset&lt;/i&gt; operation that empties the stack.
 * Attempts to push a full stack or to pop an empty stack result in no action other
 * than the generation of an event report.
 * @author Alessandro Pasetti (P&amp;P Software)
 * @version 1.0
 */
class <xsl:value-of select="$ClassName"/> : public CC_RootObject {

  private:
    unsigned int size;		
    unsigned int stackPointer;	// index of next free location on stack		
    <xsl:value-of select="$Type"/>* pStack;     // Array of pointers to the items in the stack.

  public:

    /**
     * Instantiate a new stack container.
     * The stack is initially empty. Its size is set to an illegal value to 
     * signify that the stack is not yet configured.
     */
    <xsl:value-of select="$ClassName"/>();

    /**
     * Push an item onto the stack.
     * If the stack is already full, no action is taken but event report
     * EVT_STACK_FULL is generated to report the fact. Users should always check that the
     * stack is not full (using operation &lt;code&gt;isFull&lt;/code&gt;) before performing
     * a push operation. 
     * @see TD_EventType
     * @param newItem the new item to be added to the stack
     */
    void push(<xsl:value-of select="$Type"/> newItem);

    /**
     * Pop an item from the stack.
     * If the stack is empty, the value of NULL is returned and event report
     * EVT_STACK_FULL is generated to report the fact. Users should always check that the
     * stack is not empty (using operation &lt;code&gt;isEmpty&lt;/code&gt;) before performing
     * a pop operation. 
     * @see TD_EventType
     * @return the most recently item pushed onto the stack or NULL if the stack is 
     * empty
     */
    <xsl:value-of select="$Type"/> pop();

    /**
     * Set the size of the stack. The size of the stack is the maximum number of
     * items that can be held by the stack. A call to this method causes the internal 
     * FIFO data structure where the stack items are stored to be created and initialized.
     * &lt;p&gt;
     * This is an initialization method. It should be called before the
     * stack is used for the first time and it should not be called more
     * than once. Attempts to call it more than once will result in memory leaks.
     * It is not legal to set the repository size to 0.     
     * @param size the desired size of the stack
     */
    void setStackSize(unsigned int size);

    /**
     * Return the size of the stack.      
     * @see #setStackSize
     * @return the desired size of the stack
     */
    unsigned int getStackSize() const;

    /**
     * Return the number of items currently on the stack.      
     * @return the number of items currently on the stack
     */
    unsigned int getNumberOfItems() const;

    /**
     * Check whether the stack is emtpy
     * @return true if the stack is emtpy, false otherwise
     */
    bool isEmpty() const;

    /**
     * Check whether the stack is full
     * @return true if the stack is full, false otherwise
     */
    bool isFull() const;

    /**
     * Reset the stack.
     * The stack is brought back to the status it had after it was
     * configured but before it was ever used.
     */
    void reset();

    /**
     * Perform a class-specific configuration check on a stack object:
     * verify that the stack size
     * has a legal value.
     * @return true if the object is configured, false otherwise
     */
    virtual bool isObjectConfigured();

};

#endif


</xsl:template>

</xsl:stylesheet>

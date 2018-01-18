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

This XSLT program generates the body file of the stack container class.

This XSLT program process an XML file that describes the target Matlab
routine. See the comment to the XSLT program "GenerateStackContainerHeader.xsl"
for a description of the assumed format of the XML file.
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
  <xsl:variable name="CodeDir" select="ObsFrameworkCodeDirPath"/>

  <!-- start code generation                                       -->
//
// Copyright 2003 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$ClassName"/>.h
//
// Version	1.0
// Date		30.08.03 (Version 1.0)
// Author	A. Pasetti (P&amp;P Software)
//

#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/CompilerSwitches.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/DebugSupport.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/ClassId.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/Constants.h"
#include "<xsl:value-of select="$CodeDir"/>Base/CC_RootObject.h"
<xsl:if test="Type/@headerFile">#include "<xsl:value-of select="Type/@headerFile"/>"</xsl:if>
#include "<xsl:value-of select="$ClassName"/>.h"

<xsl:value-of select="$ClassName"/>::<xsl:value-of select="$ClassName"/>() {
    size = 0;
    stackPointer = 0;
    pStack = pNULL;
	setClassId(<xsl:value-of select="$ClassId"/>);
}

void <xsl:value-of select="$ClassName"/>::setStackSize(unsigned int size) {
   assert( this->size == 0);      // should not be called more than once
   assert( size > 0);             // stack size must be greater than zero

   pStack = new <xsl:value-of select="$Type"/>[size];
   assert( pStack!= pNULL );
   this->size = size;
   stackPointer = 0;
}

unsigned int <xsl:value-of select="$ClassName"/>::getStackSize() const {
   return size;
}

unsigned int <xsl:value-of select="$ClassName"/>::getNumberOfItems() const {
    return stackPointer;
}


void <xsl:value-of select="$ClassName"/>::push(<xsl:value-of select="$Type"/> newItem) {
   assert( (pStack != pNULL) );

   if ( isFull() )
       this->CC_RootObject::getEventRepository()->create(this,EVT_STACK_FULL);
   else {
       pStack[stackPointer]=newItem;
       stackPointer++;
   }
   assert( stackPointer &lt;= size );
}

<xsl:value-of select="$Type"/><xsl:text> </xsl:text><xsl:value-of select="$ClassName"/>::pop() {
   assert( (pStack != pNULL) );

   if ( isEmpty() ) {
       this->CC_RootObject::getEventRepository()->create(this,EVT_STACK_EMPTY);
       return pNULL;
   } else {
       stackPointer--;
       return pStack[stackPointer];
   }
}

bool <xsl:value-of select="$ClassName"/>::isFull() const {
   assert( (pStack != pNULL) );
   return (stackPointer==size);
}

bool <xsl:value-of select="$ClassName"/>::isEmpty() const {
   assert( (pStack != pNULL) );
   return (stackPointer==0);
}

void <xsl:value-of select="$ClassName"/>::reset() {
   assert( (pStack != pNULL) );
   stackPointer = 0;
}

bool <xsl:value-of select="$ClassName"/>::isObjectConfigured() {

   // Check configuration of super object
   if ( !CC_RootObject::isObjectConfigured() )
       return NOT_CONFIGURED;

   if ( (pStack == pNULL) )
       return NOT_CONFIGURED;
   return CONFIGURED;
}

</xsl:template>

</xsl:stylesheet>

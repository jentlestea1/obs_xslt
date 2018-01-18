<?xml version="1.0" encoding="UTF-8"?>
<!--
    Copyright 2004 P&P Software GmbH                                                                                 
-->
<!--
This is the code generator for the header and body files of a custom ControlBlock class.
This XSL program process the XML-based application model.
The XSL program searches the application model for all "ControlAction" elements
which have a "Custom" subelement that indicates that a custom control block
class must be created. For each such element a class header file and a class
body files are created.

NB: This program writes its outputs (the header and body files) to documents that are 
opened using the "xsl:document" instruction. The directory where these files
are written must apparently be specified through an absolute path names (this
seems to be in contrast with the documentation of xsl:document and may be a
bug in the XSLT provessor). This directory is hardcoded in variable
$TargetFile.

@todo: 
      - add treatment of default attributes
      - add setting of class identifier in the constructor body
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"  version="1.1"  xmlns:lxslt="http://xml.apache.org/xslt">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--
    Global Variables                                                                                                                      
-->
<xsl:variable name="codeDir" select="'../'"/>
<!--
       Include general utility rules
-->
<xsl:include href="WriteCommentBody.xsl"/>
<xsl:include href="ClassNameFromPath.xsl"/>
<!--
    Top-Level Rule (iterates over all FsmState elements with a Custom subelement)
-->
<xsl:template match="/ObsApplication">
      <!-- write warning about the location of the output file -->
       WARNING: this XSL program hardcodes the directory where output files are written in variable $TargetFile
            
      <xsl:for-each select="//ControlBlock[Custom]">
            <xsl:variable name="SuperClassNamePath">
                  <xsl:choose>
                        <xsl:when test="DataPoolLink">
                              <xsl:value-of select="'Data/DataPoolControlBlock'"/>
                        </xsl:when>
                        <xsl:when test="DataItemLink">
                              <xsl:value-of select="'Data/DataItemControlBlock'"/>
                        </xsl:when>
                        <xsl:when test="PointerLink">
                              <xsl:value-of select="'Data/PointerControlBlock'"/>
                        </xsl:when>
                        <xsl:when test="CopyLink">
                              <xsl:value-of select="'Data/CopyControlBlock'"/>
                        </xsl:when>
                  </xsl:choose>
            </xsl:variable>
            <xsl:variable name="SuperClassName">
                  <xsl:call-template name="ClassNameFromPath">
                        <xsl:with-param name="path" select="$SuperClassNamePath"/>
                  </xsl:call-template>
            </xsl:variable>
            <xsl:variable name="ClassName">
                  <xsl:call-template name="ClassNameFromPath">
                        <xsl:with-param name="path" select="Custom/@type"/>
                  </xsl:call-template>
            </xsl:variable>
            <xsl:variable name="TargetFile" select="concat('/Projects/ObsFramework/src/cpp/',Custom/@type)"/>     
            Generating code for class <xsl:value-of select="$ClassName"/> in files <xsl:value-of select="$TargetFile"/>.h/.cpp

            <!-- Check whether writing to an output file is possible -->
            <xsl:if test="not(element-available('xsl:document'))">
                  FATAL ERROR: the xsl:document element is not supported. Header files cannot be written! This element
                  is normally supported only in version 1.1 of XSL.
            </xsl:if>
            
            <!-- Construct variables holding the number of inputs, of parameters and of outputs -->
            <xsl:variable name="NumberOfInputs" select="count(Input)"/>
            <xsl:variable name="NumberOfOutputs" select="count(Output)"/>
            <xsl:variable name="NumberOfParameters" select="count(Parameter)"/>
            
            <!-- ===================================================================================
                   Create the header file  
                   ===================================================================================-->
             <xsl:document href="{$TargetFile}.h" omit-xml-declaration="yes" method="text">  
//
// Copyright 2004 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$ClassName"/>.h
//
// This file was automatically generated by an XSL program

#ifndef <xsl:value-of select="$ClassName"/>H
#define <xsl:value-of select="$ClassName"/>H

#include "<xsl:value-of select="$codeDir"/>GeneralInclude/ForwardDeclarations.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$codeDir"/><xsl:value-of select="$SuperClassNamePath"/>.h"

/**
<xsl:call-template name="WriteCommentBody">
         <xsl:with-param name="text" select="normalize-space(Custom/Description)"/>
         <xsl:with-param name="indent" select="' '"/>
</xsl:call-template>
 * &lt;p&gt;
 * This is a stub class. It provides dummy implementations for some of the virtual
 * methods of its superclass. 
 * This class was automatically generated by an XSL program that processes the
 * XML-based &lt;i&gt;target application model&lt;/i&gt;. The XSL program  
 * searches the application model for all "ControlBlock" elements
 * which have a "Custom" subelement that indicates that a custom control block
 * class must be created. For each such element a class header file is created.
 * @todo Modify the generator meta-component generateRecoveryAction to generate the code
 * that sets the class identifier and to treat the default attributes in the custom recovery action description.
 * @author Automatically Generated Class
 * @version 1.0
 */
class <xsl:value-of select="$ClassName"/> : public <xsl:value-of select="$SuperClassName"/> {

  public: 
  
    /**
     * Stub constructor that sets the number of inputs, of outputs, of states and of parameters.
     * The number of inputs is set to <xsl:value-of select="$NumberOfInputs"/>.
     * The number of outputs is set to <xsl:value-of select="$NumberOfOutputs"/>.
     * The number of parameters is set to <xsl:value-of select="$NumberOfParameters"/>.
     * The number of states is set to zero. Developers may have to change this value to reflect
     * their desired implementation of this class.
     */
    <xsl:value-of select="$ClassName"/>(void);
    
    /**
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that returns without doing anything.
     */
    virtual void propagateState(void);

    /**
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that returns without doing anything.
     */
    virtual void updateOutput(void);
 
    /**
     * This is a stub method that must be completed by the application developer.
     * This stub provides a default implementation that returns without doing anything.
     */
    virtual void reset(void);

};
            
#endif
             </xsl:document>
             
            <!-- ===================================================================================
                   Create the body file  
                   ===================================================================================-->
             <xsl:document href="{$TargetFile}.cpp" omit-xml-declaration="yes" method="text">  
//
// Copyright 2004 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$ClassName"/>.cpp
//
// This file was automatically generated by an XSL program

#include "<xsl:value-of select="$codeDir"/>GeneralInclude/CompilerSwitches.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/Constants.h"  <xsl:text/>
<xsl:choose>
      <xsl:when test="DataItemLink">
#include "<xsl:value-of select="$codeDir"/>Data/DC_DataItem.h" <xsl:text/>
      </xsl:when>
      <xsl:when test="DataPoolLink">
#include "<xsl:value-of select="$codeDir"/>Data/DataPool.h" <xsl:text/>
      </xsl:when>
</xsl:choose>
#include "<xsl:value-of select="$codeDir"/><xsl:value-of select="$SuperClassNamePath"/>.h"
#include "<xsl:value-of select="$codeDir"/><xsl:value-of select="Custom/@type"/>.h"

<xsl:value-of select="$ClassName"/>::<xsl:value-of select="$ClassName"/>(void) {
      setNumberOfInputs(<xsl:value-of select="$NumberOfInputs"/>);
      setNumberOfOutputs(<xsl:value-of select="$NumberOfOutputs"/>);
      setNumberOfParameters(<xsl:value-of select="$NumberOfParameters"/>);
      setNumberOfStates(0);
      // Update the number of states (if necessary) and insert any other application-specific code here
}
    
void <xsl:value-of select="$ClassName"/>::propagateState(void) {
      return;
      // remove previous statement and insert application-specific code here
}

void <xsl:value-of select="$ClassName"/>::updateOutput(void) {
<!--      <xsl:choose>
            <xsl:when test="DataPoolLink">
      DataPool *pDP=getDataPool();
      int n = 0;
      if (nInputs>nParameters)
            n = nParameters;
      else
            n = nInputs;
      for (int j=0; j&lt;nOutputs; j++) {
            TD_Float accumulator = 0;
            for (int i = 0; i&lt;n; i++) {
                  accumulator = accumulator + p[i]*pDP->getFloatValue(dpu[i]);
                  pDP->setValue(dpy[j],accumulator);
            }
      }                  
            </xsl:when>
            <xsl:when test="DataItemLink">
      DataPool *pDP=getDataPool();
      int n = 0;
      if (nInputs>nParameters)
            n = nParameters;
      else
            n = nInputs;
      for (int j=0; j&lt;nOutputs; j++) {
            TD_Float accumulator = 0;
            for (int i = 0; i&lt;n; i++) {
                  accumulator = accumulator + p[i]*pDIU[i]->getFloatValue();
                  pDIY[j]->setValue(accumulator);
            }
      }                  
            </xsl:when>
            <xsl:when test="PointerLink">
      int n = 0;
      if (nInputs>nParameters)
            n = nParameters;
      else
            n = nInputs;
      for (int j=0; j&lt;nOutputs; j++) {
            TD_Float accumulator = 0;
            for (int i = 0; i&lt;n; i++) {
                  accumulator = accumulator + p[i]*(*pU[i]);
                  *pY[j] = accumulator;
            }
      }                  
            </xsl:when>
            <xsl:when test="CopyLink">
      int n = 0;
      if (nInputs>nParameters)
            n = nParameters;
      else
            n = nInputs;
      for (int j=0; j&lt;nOutputs; j++) {
            TD_Float accumulator = 0;
            for (int i = 0; i&lt;n; i++) {
                  accumulator = accumulator + p[i]*u[i];
                  y[j] = accumulator;
            }
      }                  
            </xsl:when>
      </xsl:choose>   -->
      return;
      // remove previous statements and insert application-specific code here
}

void <xsl:value-of select="$ClassName"/>::reset(void) {
      return;
      // remove previous statement and insert application-specific code here
}
    

            </xsl:document>
      </xsl:for-each>
</xsl:template>




</xsl:stylesheet>
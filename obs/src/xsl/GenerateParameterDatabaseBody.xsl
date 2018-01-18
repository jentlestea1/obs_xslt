<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for a parameter database class for the OBS Framework.

This XSL program generates the body file of the parameter database
class.

This XSL program processes the XML-based application model.
===================================================================-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.1"
    xmlns:lxslt="http://xml.apache.org/xslt"
    xmlns:redirect="org.apache.xalan.lib.Redirect"
    extension-element-prefixes="redirect">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--===================================================================
       Include general utility rules
===================================================================-->
 <xsl:include href="ClassNameFromPath.xsl"/>
 <xsl:include href="ClassIdFromClassName.xsl"/>
<xsl:include href="WriteCommentBody.xsl"/>
<xsl:include href="MakeFirstLetterCap.xsl"/>
<!--===================================================================
      Top-level rule 
===================================================================-->
<xsl:template match="/ObsApplication/ParameterDatabase/IndexedDatabase">
<!--===================================================================
      Define general-purpose variables
 ===================================================================-->  
  <xsl:variable name="ClassName">
        <xsl:call-template name="ClassNameFromPath">
              <xsl:with-param name="path" select="@type"/>
        </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="ClassId">
        <xsl:call-template name="ClassIdFromClassName">
              <xsl:with-param name="className" select="$ClassName"/>
        </xsl:call-template>
  </xsl:variable>
  <xsl:variable name="CodeDir" select="'../'"/>
  <xsl:variable name="Level" select="RobustnessLevel/@value"/>

  <!-- compute and store the maximum parameter ID value           -->
  <xsl:variable name="maxParId">
    <xsl:call-template name="computeMaxParId">
       <xsl:with-param name="currentMax" select="0"/>
       <xsl:with-param name="currentPos" select="1"/>
    </xsl:call-template>
  </xsl:variable>

  <!-- start code generation                                       -->
  <xsl:variable name="TargetFile" select="concat('/home/wangshaobo/obs_xml_xsl/projects/',@type)"/>     
  Generating code for class <xsl:value-of select="$ClassName"/> in files <xsl:value-of select="$TargetFile"/>.cpp

  <!-- Check whether writing to an output file is possible -->
  <xsl:if test="not(element-available('xsl:document'))">
        FATAL ERROR: the xsl:document element is not supported. Header files cannot be written! This element
        is normally supported only in version 1.1 of XSL.
  </xsl:if>
            
  <!-- ===================================================================================
         Create the output file  
          ===================================================================================-->
  <xsl:document href="{$TargetFile}.cpp" omit-xml-declaration="yes" method="text">  
//
// Copyright 2003 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$ClassName"/>.cpp
//
// This file was automatically generated by an XSL program
//

#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/CompilerSwitches.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/DebugSupport.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/ClassId.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/Constants.h"
<xsl:if test="$Level!=1">#include "<xsl:value-of select="$CodeDir"/>Base/CC_RootObject.h"</xsl:if>
#include "<xsl:value-of select="$ClassName"/>.h"

static unsigned int const CharCode = 1;
static unsigned int const UnsignedCharCode = 2;
static unsigned int const ShortCode = 3;
static unsigned int const UnsignedShortCode = 4;
static unsigned int const IntCode = 5;
static unsigned int const UnsignedIntCode = 6;
static unsigned int const BoolCode = 7;
static unsigned int const FloatCode = 8;
static unsigned int const DoubleCode = 9;

<xsl:value-of select="$ClassName"/>::<xsl:value-of select="$ClassName"/>() {
   setClassId(<xsl:value-of select="$ClassId"/>);
   pDefaultTable = pNULL;
   pOperationalTable = pNULL;
   resetWasCalled = false;

   tableLength = <xsl:value-of select="Size/@value"/>;

   maxParId = <xsl:value-of select="$maxParId"/>;
   pPar = new char*[maxParId+1];
   parType = new char[maxParId+1];
   for (TD_DatabaseId i=0; i&lt;maxParId; i++)  {
       pPar[i] = pNULL;
       parType[i] = -1;
   }

}

void <xsl:value-of select="$ClassName"/>::reset() {
   assert( pDefaultTable != pNULL ) ;
   assert( pOperationalTable != pNULL );
   assert( tableLength > 0 );
   for (TD_DatabaseId i=0; i&lt;tableLength; i++)
      pOperationalTable[i] = pDefaultTable[i];
   resetWasCalled = true;

<xsl:for-each select="Parameter">
  <xsl:sort select="Id/@value" data-type="number"/>
   pPar[<xsl:value-of select="Id/@value"/>] = pOperationalTable+<xsl:value-of 
                                                        select="Offset/@value"/>;<xsl:text/>
  <xsl:variable name="type" select="Type/@value"/>
  <xsl:choose>
    <xsl:when test="$type='unsigned int'">
   parType[<xsl:value-of select="Id/@value"/>] = UnsignedIntCode;<xsl:text/>
    </xsl:when>
    <xsl:when test="$type='int'">
   parType[<xsl:value-of select="Id/@value"/>] = IntCode;<xsl:text/>
    </xsl:when>
    <xsl:when test="$type='unsigned short'">
   parType[<xsl:value-of select="Id/@value"/>] = UnsignedShortCode;<xsl:text/>
    </xsl:when>
    <xsl:when test="$type='short'">
   parType[<xsl:value-of select="Id/@value"/>] = ShortCode;<xsl:text/>
    </xsl:when>
    <xsl:when test="$type='unsigned char'">
   parType[<xsl:value-of select="Id/@value"/>] = UnsignedCharCode;<xsl:text/>
    </xsl:when>
    <xsl:when test="$type='char'">
   parType[<xsl:value-of select="Id/@value"/>] = CharCode;<xsl:text/>
    </xsl:when>
    <xsl:when test="$type='bool'">
   parType[<xsl:value-of select="Id/@value"/>] = BoolCode;<xsl:text/>
    </xsl:when>
    <xsl:when test="$type='double'">
   parType[<xsl:value-of select="Id/@value"/>] = DoubleCode;<xsl:text/>
    </xsl:when>
    <xsl:when test="$type='float'">
   parType[<xsl:value-of select="Id/@value"/>] = FloatCode;<xsl:text/>
    </xsl:when>
  </xsl:choose>
</xsl:for-each>
}

void <xsl:value-of select="$ClassName"/>::setDefaultTable(char* pDefTable) {
   assert( pDefTable != pNULL );
   pDefaultTable = pDefTable;
}

void <xsl:value-of select="$ClassName"/>::setOperationalTable(char* pOperTable) {
   assert( pOperTable != pNULL );
   pOperationalTable = pOperTable;
}

bool <xsl:value-of select="$ClassName"/>::isObjectConfigured() {

   // Check configuration of super object
   if ( !CC_RootObject::isObjectConfigured() )
       return NOT_CONFIGURED;

   if ( (tableLength &lt;= 0) ||
        (pDefaultTable == pNULL) ||
        (pOperationalTable == pNULL) ||
        (!resetWasCalled) )
       return NOT_CONFIGURED;
   return CONFIGURED;
}

<xsl:call-template name="setParameterMethod">
   <xsl:with-param name="type" select="'int'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>   
<xsl:call-template name="setParameterMethod">
   <xsl:with-param name="type" select="'unsigned int'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="setParameterMethod">
   <xsl:with-param name="type" select="'short'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="setParameterMethod">
   <xsl:with-param name="type" select="'unsigned short'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="setParameterMethod">
   <xsl:with-param name="type" select="'char'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="setParameterMethod">
   <xsl:with-param name="type" select="'unsigned char'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="setParameterMethod">
   <xsl:with-param name="type" select="'bool'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="setParameterMethod">
   <xsl:with-param name="type" select="'float'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="setParameterMethod">
   <xsl:with-param name="type" select="'double'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>

<xsl:call-template name="getParameterMethod">
   <xsl:with-param name="type" select="'int'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getParameterMethod">
   <xsl:with-param name="type" select="'unsigned int'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getParameterMethod">
   <xsl:with-param name="type" select="'short'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getParameterMethod">
   <xsl:with-param name="type" select="'unsigned short'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getParameterMethod">
   <xsl:with-param name="type" select="'char'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getParameterMethod">
   <xsl:with-param name="type" select="'unsigned char'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getParameterMethod">
   <xsl:with-param name="type" select="'bool'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getParameterMethod">
   <xsl:with-param name="type" select="'float'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getParameterMethod">
   <xsl:with-param name="type" select="'double'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>

<xsl:call-template name="getPointerMethod">
   <xsl:with-param name="type" select="'int'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getPointerMethod">
   <xsl:with-param name="type" select="'unsigned int'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getPointerMethod">
   <xsl:with-param name="type" select="'short'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getPointerMethod">
   <xsl:with-param name="type" select="'unsigned short'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getPointerMethod">
   <xsl:with-param name="type" select="'char'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getPointerMethod">
   <xsl:with-param name="type" select="'unsigned char'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getPointerMethod">
   <xsl:with-param name="type" select="'bool'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getPointerMethod">
   <xsl:with-param name="type" select="'float'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>
<xsl:call-template name="getPointerMethod">
   <xsl:with-param name="type" select="'double'"/>
   <xsl:with-param name="level" select="$Level"/>
   <xsl:with-param name="className" select="$ClassName"/>
</xsl:call-template>

</xsl:document>
</xsl:template>

<!--================================================================-->
<!-- Utility to compute the maximum value of the parId field on     -->
<!-- all the Parameter elements.                                    -->
<!-- When it is called the first time, the parameter 'currentMax'   -->
<!-- should be set to zero and the parameter 'currentPos' should be -->
<!-- set to 1.                                                      -->
<!--================================================================-->

<xsl:template name="computeMaxParId">
  <xsl:param name="currentMax"/>
  <xsl:param name="currentPos"/>
  <xsl:choose>
    <xsl:when test="$currentPos=count(//Parameter)">
      <xsl:value-of select="$currentMax"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:variable name="valOfNextParId" select="//Parameter[$currentPos+1]/Id/@value"/>
      <xsl:choose>
        <xsl:when test="$currentMax &lt; $valOfNextParId">
          <xsl:call-template name="computeMaxParId">
            <xsl:with-param name="currentMax" select="$valOfNextParId"/>
            <xsl:with-param name="currentPos" select="$currentPos+1"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <xsl:call-template name="computeMaxParId">
            <xsl:with-param name="currentMax" select="$currentMax"/>
            <xsl:with-param name="currentPos" select="$currentPos+1"/>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>

<!--================================================================-->
<!-- Utility to write out the definiton of a parameter setter       -->
<!-- method.                                                        -->
<!-- The first template parameter is the name of the type of the    -->
<!-- database parameter. The second template parameter is the       -->
<!-- robustness level of the database. The third template parameter -->
<!-- is the name of the class being generated.                      -->
<!--================================================================-->

<xsl:template name="setParameterMethod">
  <xsl:param name="type"/>
  <xsl:param name="level"/>
  <xsl:param name="className"/>
  <xsl:variable name="normalizedType">
      <xsl:call-template name="MakeFirstLetterCap">
        <xsl:with-param name="before" select="''"/>
        <xsl:with-param name="after" select="$type"/>
      </xsl:call-template>
   </xsl:variable>
void <xsl:value-of select="$className"/>::setParameter(TD_DatabaseId parId, <xsl:value-of select="$type"/> newValue) {
   assert( pOperationalTable != pNULL );
   assert( (parId &lt;= maxParId) &amp;&amp; (parType[parId]==<xsl:value-of select="$normalizedType"/>Code) );
   <xsl:if test="$level!='1'">
   if (parId > maxParId) {
       CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DB_ACCESS);
       return;
   }
   if (parType[parId]!=<xsl:value-of select="$normalizedType"/>Code) {
       CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DB_ACCESS);
       return;
   }
   </xsl:if>
   *( (<xsl:value-of select="$type"/>*)(pPar[parId]) ) = newValue;
}
</xsl:template>

<!--================================================================-->
<!-- Utility to write out the definiton of a parameter getter       -->
<!-- method.                                                        -->
<!-- The first template parameter is the name of the type of the    -->
<!-- database parameter. The second template parameter is the       -->
<!-- robustness level of the database. The third template parameter -->
<!-- is the name of the class being generated.                      -->
<!--================================================================-->

<xsl:template name="getParameterMethod">
  <xsl:param name="type"/>
  <xsl:param name="level"/>
  <xsl:param name="className"/>
  <xsl:variable name="normalizedType">
      <xsl:call-template name="MakeFirstLetterCap">
        <xsl:with-param name="before" select="''"/>
        <xsl:with-param name="after" select="$type"/>
      </xsl:call-template>
   </xsl:variable>
<xsl:value-of select="$type"/><xsl:text> </xsl:text><xsl:value-of 
    select="$className"/>::getParameter<xsl:value-of select="$normalizedType"/>(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   assert( (parId &lt;= maxParId) &amp;&amp; (parType[parId]==<xsl:value-of select="$normalizedType"/>Code) );
   <xsl:if test="$level='3'">
   if (parId > maxParId) {
       CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DB_ACCESS);
       return (<xsl:value-of select="$type"/>)0;
   }
   if (parType[parId]!=<xsl:value-of select="$normalizedType"/>Code) {
       CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DB_ACCESS);
       return (<xsl:value-of select="$type"/>)0;
   }
   </xsl:if>
   return *(<xsl:value-of select="$type"/>*)(pPar[parId]);
}
</xsl:template>

<!--================================================================-->
<!-- Utility to write out the definiton of a parameter pointer      -->
<!-- getter method.                                                 -->
<!-- The first template parameter is the name of the type of the    -->
<!-- database parameter. The second template parameter is the       -->
<!-- robustness level of the database. The third template parameter -->
<!-- is the name of the class being generated.                      -->
<!--================================================================-->

<xsl:template name="getPointerMethod">
  <xsl:param name="type"/>
  <xsl:param name="level"/>
  <xsl:param name="className"/>
  <xsl:variable name="normalizedType">
      <xsl:call-template name="MakeFirstLetterCap">
        <xsl:with-param name="before" select="''"/>
        <xsl:with-param name="after" select="$type"/>
      </xsl:call-template>
   </xsl:variable>
<xsl:value-of select="$type"/>* <xsl:value-of select="$className"/>::getParameterPointer<xsl:value-of 
        select="$normalizedType"/>(TD_DatabaseId parId) {
   assert( pOperationalTable != pNULL );
   assert( (parId &lt;= maxParId) &amp;&amp; (parType[parId]==<xsl:value-of select="$normalizedType"/>Code) );
   <xsl:if test="$level!='1'">
   if (parId > maxParId) {
       CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DB_ACCESS);
       return pNULL;
   }
   if (parType[parId]!=<xsl:value-of select="$normalizedType"/>Code) {
       CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DB_ACCESS);
       return pNULL;
   }
   </xsl:if>
   return (<xsl:value-of select="$type"/>*)(pPar[parId]);
}
</xsl:template>



</xsl:stylesheet>

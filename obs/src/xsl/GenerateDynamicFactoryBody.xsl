<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for a dynamic factory class for the OBS Framework.

This XSL program generates the body file of the dynamic factory class.

This XSL program process the XML-based application model.

NB: This program writes its outputs to documents that are 
opened using the "xsl:document" instruction. The directory where these files
are written must apparently be specified through an absolute path names (this
seems to be in contrast with the documentation of xsl:document and may be a
bug in the XSLT provessor). This directory is hardcoded in variable
$TargetFile. One output document is opened for each dynamic factory covered by
this XSL program.
===================================================================-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.1"  xmlns:lxslt="http://xml.apache.org/xslt">

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--
       Include general utility rules
-->
<xsl:include href="WriteCommentBody.xsl"/>
<xsl:include href="ClassNameFromPath.xsl"/>
<xsl:include href="TruncatedClassNameFromPath.xsl"/>
<xsl:include href="TypeNameFromPath.xsl"/>
<!--
      Define global variables
-->
<xsl:variable name="codeDir" select="'../'"/>
<!--
      Top-level rule 
-->
<xsl:template match="/ObsApplication">

      <!-- Extract the information reelvant to the generation of the manoeuvre dynamic factory and store it in a tree variable -->
      <xsl:if test="//Manoeuvre">
            <xsl:variable name="temp">
               <xsl:for-each select="//ManoeuvreManagement/Manoeuvre">
                  <xsl:element name="Manoeuvre">
                        <xsl:attribute name="type">
                              <xsl:value-of select=".//*[(@kind='component') and (@type)]/@type"/>
                        </xsl:attribute>
                        <xsl:for-each select=".//*[(@kind='property') and (@type='int') and (@name)]">  
                               <xsl:element name="Property"><xsl:value-of select="@name"/></xsl:element>
                        </xsl:for-each>
                  </xsl:element>
               </xsl:for-each>
            </xsl:variable>
            
            <xsl:variable name="sortedManoeuvres">
                  <xsl:for-each select="$temp/Manoeuvre">
                        <xsl:sort select="@type"/>
                        <xsl:copy-of select="."/>
                  </xsl:for-each>
            </xsl:variable>
            
            The following manoeuvre types with their configuration parameters are processed:
            <xsl:for-each select="$sortedManoeuvres/Manoeuvre">
                  TC Type: <xsl:value-of select="@type"/>
                     Config. Properties: <xsl:for-each select="Property"><xsl:value-of select="."/><xsl:text>  </xsl:text></xsl:for-each>
            </xsl:for-each>

            <xsl:variable name="TargetFile" select="'/Projects/ObsFramework/src/cpp/Manoeuvre/CC_ManoeuvreFactory'"/>     
            Generating code for class CC_ManoeuvreFactory in file <xsl:value-of select="$TargetFile"/>.cpp
            <xsl:document href="{$TargetFile}.cpp" omit-xml-declaration="yes" method="text">  
               <xsl:call-template name="GenerateCode">
                  <xsl:with-param name="className" select="'CC_ManoeuvreFactory'"/>
                  <xsl:with-param name="classId" select="'ID_MANOEUVREFACTORY'"/>
                  <xsl:with-param name="containedType" select="'Manoeuvre'"/>
                  <xsl:with-param name="nodes" select="$sortedManoeuvres/Manoeuvre"/>
               </xsl:call-template>
            </xsl:document>
      </xsl:if>

      <!-- Extract the information relevant to the generation of the telecommand dynamic factory and store it in a tree variable -->
      <xsl:if test="(//Telecommand) or (//PUSTelecommand)">
            <xsl:variable name="temp">
               <xsl:for-each select="//*[(@kind='interface') and ((@type='Telecommand/Telecommand') or (@type='Telecommand/PUSTelecommand'))]">
                  <xsl:element name="Telecommand">
                        <xsl:attribute name="type">
                              <xsl:value-of select=".//*[(@kind='component') and (@type)]/@type"/>
                        </xsl:attribute>
                        <xsl:for-each select=".//*[(@kind='property') and (@type='int') and (@name)]">  
                               <xsl:element name="Property"><xsl:value-of select="@name"/></xsl:element>
                        </xsl:for-each>
                  </xsl:element>
               </xsl:for-each>
            </xsl:variable>
            
            <xsl:variable name="sortedTelecommands">
                  <xsl:for-each select="$temp/Telecommand">
                        <xsl:sort select="@type"/>
                        <xsl:copy-of select="."/>
                  </xsl:for-each>
            </xsl:variable>
            
            The following telecommand types with their configuration parameters are processed:
            <xsl:for-each select="$sortedTelecommands/Telecommand">
                  TC Type: <xsl:value-of select="@type"/>
                     Config. Properties: <xsl:for-each select="Property"><xsl:value-of select="."/><xsl:text>  </xsl:text></xsl:for-each>
            </xsl:for-each>

            <xsl:variable name="TargetFile" select="'/Projects/ObsFramework/src/cpp/Telecommand/CC_TelecommandFactory'"/>     
            Generating code for class CC_TelecommandFactory in file <xsl:value-of select="$TargetFile"/>.cpp
            <xsl:document href="{$TargetFile}.cpp" omit-xml-declaration="yes" method="text">  
               <xsl:call-template name="GenerateCode">
                  <xsl:with-param name="className" select="'CC_TelecommandFactory'"/>
                  <xsl:with-param name="classId" select="'ID_TELECOMMANDFACTORY'"/>
                  <xsl:with-param name="containedType" select="'Telecommand'"/>
                  <xsl:with-param name="nodes" select="$sortedTelecommands/Telecommand"/>
               </xsl:call-template>
            </xsl:document>
      </xsl:if>

       <!-- Extract the information relevant to the generation of the telemetry packet dynamic factory and store it in a tree variable -->
      <xsl:if test="(//StandardTelemetryPacket) or (//PUSTelemetryPacket)">
            <xsl:variable name="temp">
               <xsl:for-each select="//*[(@kind='interface') and ((@type='Telemetry/StandardTelemetryPacket') or (@type='Telemetry/PUSTelemetryPacket'))]">
                  <xsl:element name="TelemetryPacket">
                        <xsl:attribute name="type">
                              <xsl:value-of select=".//*[(@kind='component') and (@type)]/@type"/>
                        </xsl:attribute>
                        <xsl:for-each select=".//*[(@kind='property') and (@type='int') and (@name)]">  
                               <xsl:element name="Property"><xsl:value-of select="@name"/></xsl:element>
                        </xsl:for-each>
                  </xsl:element>
               </xsl:for-each>
            </xsl:variable>
            
            <xsl:variable name="sortedTelemetryPackets">
                  <xsl:for-each select="$temp/TelemetryPacket">
                        <xsl:sort select="@type"/>
                        <xsl:copy-of select="."/>
                  </xsl:for-each>
            </xsl:variable>
            
            The following telemetry packet types with their configuration parameters are processed:
            <xsl:for-each select="$sortedTelemetryPackets/TelemetryPacket">
                  TC Type: <xsl:value-of select="@type"/>
                     Config. Properties: <xsl:for-each select="Property"><xsl:value-of select="."/><xsl:text>  </xsl:text></xsl:for-each>
            </xsl:for-each>
            
            <xsl:variable name="TargetFile" select="'/Projects/ObsFramework/src/cpp/Telemetry/CC_TelemetryPacketFactory'"/>     
            Generating code for class CC_TelemetryPacketFactory in file <xsl:value-of select="$TargetFile"/>.cpp
            <xsl:document href="{$TargetFile}.cpp" omit-xml-declaration="yes" method="text">  
               <xsl:call-template name="GenerateCode">
                  <xsl:with-param name="className" select="'CC_TelemetryPacketFactory'"/>
                  <xsl:with-param name="classId" select="'ID_TELECOMMANDFACTORY'"/>
                  <xsl:with-param name="containedType" select="'TelemetryPacket'"/>
                  <xsl:with-param name="nodes" select="$sortedTelemetryPackets/TelemetryPacket"/>
               </xsl:call-template>
            </xsl:document>
      </xsl:if>


</xsl:template>

<xsl:template name="GenerateCode">
  <xsl:param name="className"/>
  <xsl:param name="classId"/>
  <xsl:param name="containedType"/>
  <xsl:param name="nodes"/>
//
// Copyright 2003 P&amp;P Software GmbH - All Rights Reserved
//
// <xsl:value-of select="$className"/>.cpp
//
// This file was automatically generated by an XSL program
//

#include "<xsl:value-of select="$codeDir"/>GeneralInclude/CompilerSwitches.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/DebugSupport.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/ClassId.h"
#include "<xsl:value-of select="$codeDir"/>GeneralInclude/Constants.h"  <xsl:text/>
<xsl:for-each select="$nodes">
   <xsl:variable name="clsName" select="@type"/>
   <xsl:variable name="pos" select="position()"/>
   <xsl:if test="($pos=1) or ($nodes[position()=(($pos)-1)]/@type!=$clsName)">
#include "<xsl:value-of select="$codeDir"/><xsl:value-of select="$clsName"/>.h"  <xsl:text/>
    </xsl:if>
</xsl:for-each>
#include "<xsl:value-of select="$codeDir"/>Base/CC_RootObject.h"
#include "<xsl:value-of select="$className"/>.h"

<xsl:value-of select="$className"/>* <xsl:value-of select="$className"/>::pInstance = pNULL;

<xsl:value-of select="$className"/>::<xsl:value-of select="$className"/>(void) {
    setClassId(<xsl:value-of select="$classId"/>);

  <xsl:for-each select="$nodes">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClsName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                  <xsl:with-param  name="path" select="$clsName"/>
            </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
       <xsl:variable name="pos" select="position()"/>
      <xsl:if test="($pos=1) or ($nodes[position()=(($pos)-1)]/@type!=$clsName)">
    size<xsl:value-of select="$tClsName"/> = <xsl:value-of select="count($nodes[@type=$clsName])"/>;
    pool<xsl:value-of select="$tClsName"/> = new <xsl:value-of
        select="$uClsName"/>*[size<xsl:value-of select="$tClsName"/>];
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        pool<xsl:value-of select="$tClsName"/>[i] = pNULL;
      </xsl:if>
  </xsl:for-each>
}

bool <xsl:value-of select="$className"/>::isObjectConfigured(void) {

    if ( !CC_RootObject::isObjectConfigured() )
        return false;
  <xsl:for-each select="$nodes">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClsName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                  <xsl:with-param  name="path" select="$clsName"/>
            </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="pos" select="position()"/>
      <xsl:if test="($pos=1) or ($nodes[position()=(($pos)-1)]/@type!=$clsName)">
    if ( pool<xsl:value-of select="$tClsName"/>==pNULL )
        return false;

    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( pool<xsl:value-of select="$tClsName"/>[i]==pNULL )
            return false;
     </xsl:if>
  </xsl:for-each>

   return true;
}

<xsl:value-of select="$className"/>* <xsl:value-of select="$className"/>::getInstance(void) {
    if (pInstance==pNULL)
        pInstance = new <xsl:value-of select="$className"/>();
    return pInstance;
}

  <xsl:for-each select="$nodes">
      <xsl:variable name="clsName" select="@type"/>
      <xsl:variable name="tClsName">
            <xsl:call-template name="TruncatedClassNameFromPath">
                  <xsl:with-param  name="path" select="$clsName"/>
            </xsl:call-template>
      </xsl:variable>
      <xsl:variable name="uClsName">
         <xsl:call-template name="ClassNameFromPath">
               <xsl:with-param name="path" select="$clsName"/>
         </xsl:call-template>
      </xsl:variable>
    <xsl:variable name="pos" select="position()"/>
    <xsl:if test="($pos=1) or ($nodes[position()=(($pos)-1)]/@type!=$clsName)">
void <xsl:value-of select="$className"/>::set<xsl:value-of
                    select="$containedType"/>(unsigned int i, <xsl:value-of select="$uClsName"/>* pItem) {
    assert(i&lt;size<xsl:value-of select="$tClsName"/>);
    assert(pItem!=pNULL);
    pool<xsl:value-of select="$tClsName"/>[i] = pItem;
    pool<xsl:value-of select="$tClsName"/>[i]->setInUse(false);
}

unsigned int <xsl:value-of select="$className"/>::getNumber<xsl:value-of select="$tClsName"/>(void) {
    unsigned int counter = 0;
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( pool<xsl:value-of select="$tClsName"/>[i]->isInUse() )
            counter++;
    return counter;
}

unsigned int <xsl:value-of select="$className"/>::getCapacity<xsl:value-of select="$tClsName"/>(void) {
    return size<xsl:value-of select="$tClsName"/>;
}


<xsl:value-of select="$uClsName"/>* <xsl:value-of
                        select="$className"/>::allocate<xsl:value-of select="$tClsName"/>(<xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>) {
    assert( isObjectConfigured() );
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if (<xsl:for-each select="Property">pool<xsl:value-of select="$tClsName"/>[i]->get<xsl:value-of select="."/>()>=<xsl:value-of select="."/> &amp;&amp;
             </xsl:for-each>!pool<xsl:value-of select="$tClsName"/>[i]->isInUse() ) {
           pool<xsl:value-of select="$tClsName"/>[i]->setInUse(true);
           return pool<xsl:value-of select="$tClsName"/>[i];
        }
    return pNULL;
}

bool <xsl:value-of select="$className"/>::isFree<xsl:value-of select="$tClsName"/>(<xsl:for-each select="Property">unsigned int <xsl:if test="not(position()=last())">
          <xsl:value-of select="."/>, </xsl:if><xsl:if test="position()=last()"><xsl:value-of select="."/></xsl:if></xsl:for-each>) {
    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( <xsl:for-each select="Property">pool<xsl:value-of select="$tClsName"/>[i]->get<xsl:value-of select="."/>()>=<xsl:value-of select="."/> &amp;&amp;
             </xsl:for-each>!pool<xsl:value-of select="$tClsName"/>[i]->isInUse() )
           return true;

    return false;
}

      <!-- Handle special case of getPUSDataReportingPacket(sid) -->
            <xsl:if test="$uClsName='DC_PUSDataReportingPacket'">
<xsl:value-of select="$uClsName"/>* <xsl:value-of select="$className"/>::get<xsl:value-of
                                                                select="$tClsName"/>(TD_SID sid) {
    assert( isObjectConfigured() );
    assert( sid>0 );

    for (unsigned int i=0; i&lt;size<xsl:value-of select="$tClsName"/>; i++)
        if ( ( pool<xsl:value-of select="$tClsName"/>[i]->getSID() == sid ) &amp;&amp;
             ( pool<xsl:value-of select="$tClsName"/>[i]->isInUse() ) ) {
            return pool<xsl:value-of select="$tClsName"/>[i];
         }
    return pNULL;
}
            </xsl:if>

     </xsl:if>
   </xsl:for-each>

</xsl:template>

</xsl:stylesheet>

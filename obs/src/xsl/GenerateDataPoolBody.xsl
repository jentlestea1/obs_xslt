<?xml version="1.0" encoding="UTF-8"?>

<!--================================================================-->
<!-- Copyright 2003 P&P Software GmbH                               -->
<!--================================================================-->

<!--===================================================================
Generator meta-component for a data pool class for the OBS Framework.

This XSLT program generates the body file of the data pool class.

NB: This program writes its output to documents that are 
opened using the "xsl:document" instruction. The directory where these files
are written must apparently be specified through an absolute path names (this
seems to be in contrast with the documentation of xsl:document and may be a
bug in the XSLT processor). This directory is hardcoded in variable
$TargetFile.
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
<!--===================================================================
      Top-level rule 
===================================================================-->
<xsl:template match="/ObsApplication/DataPool/IndexedDataPool">
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

  <xsl:variable name="maxParId">
    <xsl:call-template name="computeMaxParId">
       <xsl:with-param name="currentMax" select="0"/>
       <xsl:with-param name="currentPos" select="1"/>
    </xsl:call-template>
  </xsl:variable>
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
// Automatically generated file

#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/CompilerSwitches.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/DebugSupport.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/BasicTypes.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/ClassId.h"
#include "<xsl:value-of select="$CodeDir"/>GeneralInclude/Constants.h"
#include "<xsl:value-of select="$CodeDir"/>Base/CC_RootObject.h"
#include "<xsl:value-of select="$CodeDir"/>System/ObsClock.h"
#include "<xsl:value-of select="$CodeDir"/>Data/DC_SettableDataItem.h"
#include "<xsl:value-of select="$ClassName"/>.h"

static unsigned int const TD_FloatCode = 1;
static unsigned int const TD_IntegerCode = 2;

<xsl:value-of select="$ClassName"/>::<xsl:value-of select="$ClassName"/>(void) {
   setClassId(<xsl:value-of select="$ClassId"/>);

   pDefaultFloat = new TD_Float();
   *pDefaultFloat = (TD_Float)0;
   pDefaultInt = new TD_Integer();
   *pDefaultInt = (TD_Integer)0;

   iterationCounter = 0;
   unsigned int const numberOfRealPar = <xsl:value-of select="count(//Type[@value='TD_Float'])"/>;
   unsigned int const numberOfIntPar = <xsl:value-of select="count(//Type[@value='TD_Integer'])"/>;
   size = numberOfRealPar*sizeof(TD_Float)+numberOfIntPar*sizeof(TD_Integer);
   maxParId = <xsl:value-of select="$maxParId"/>;
   value = (unsigned char*)(new double[(size/sizeof(double))+1]);
   pValue = new unsigned char*[maxParId+1];         <xsl:text/>
 <xsl:if test="BackUpValue">
   backUpValue = new unsigned char[size];
   pBackUpValue = new unsigned char*[maxParId+1]; <xsl:text/>
 </xsl:if>
 <xsl:if test="TimeStamp">
   pObsClock = pNULL;
   timeStamp = new TD_ObsTime[maxParId+1];<xsl:text/>
 </xsl:if>
 <xsl:if test="ValidityStatus">
   valid = new bool[maxParId+1];   <xsl:text/>
 </xsl:if>
 <xsl:if test="DataItem">
   pDataItem = new DC_SettableDataItem*[maxParId+1];    <xsl:text/>
 </xsl:if>
 <xsl:if test="MonitoringProfile">
   pMonitoringProfile = new MonitoringProfile*[maxParId+1];       <xsl:text/>
 </xsl:if>
 <xsl:if test="RecoveryAction">
   pRecoveryAction = new RecoveryAction*[maxParId+1];       <xsl:text/>
 </xsl:if>
 <xsl:if test="TypeChecking">
   type = new char[maxParId+1];                 <xsl:text/>
 </xsl:if>

   for (TD_DataPoolId i=0; i&lt;size; i++)  {
        value[i] = 0;  <xsl:text/>
 <xsl:if test="BackUpValue">
        backUpValue[i] = 0;          <xsl:text/>
 </xsl:if>
   }

   for (TD_DataPoolId i=0; i&lt;=maxParId; i++)  {
        pValue[i] = pNULL;         <xsl:text/>
 <xsl:if test="BackUpValue">
        pBackUpValue[i] = pNULL;          <xsl:text/>
 </xsl:if>
 <xsl:if test="TimeStamp">
        timeStamp[i] = 0;               <xsl:text/>
 </xsl:if>
 <xsl:if test="ValidityStatus">
        valid[i] = true;                <xsl:text/>
 </xsl:if>
 <xsl:if test="DataItem">
        pDataItem[i] = pNULL;   <xsl:text/>
 </xsl:if>
 <xsl:if test="MonitoringProfile">
        pMonitoringProfile[i] = pNULL;          <xsl:text/>
 </xsl:if>
 <xsl:if test="RecoveryAction">
        pRecoveryAction[i] = pNULL;             <xsl:text/>
 </xsl:if>
 <xsl:if test="TypeChecking">
        type[i] = -1;                           <xsl:text/>
 </xsl:if>
   }

 unsigned int offset = 0;           <xsl:text/>
<xsl:choose>
  <xsl:when test="//TypeChecking">
    <xsl:for-each select="DataPoolItem">
       <xsl:sort select="Id/@value" data-type="number"/>
       <xsl:choose>
         <xsl:when test="Type/@value='TD_Float'">
 type[<xsl:value-of select="Id/@value"/>] = TD_FloatCode;  <xsl:text/>        
         </xsl:when>
         <xsl:when test="Type/@value='TD_Integer'">
 type[<xsl:value-of select="Id/@value"/>] = TD_IntegerCode;  <xsl:text/>        
         </xsl:when>
       </xsl:choose>
    </xsl:for-each>
 // Store the TD_Float values in the first part of the array
 for (TD_DatabaseId i=0; i&lt;=maxParId; i++)  {
     if (type[i]==TD_FloatCode) {
        pValue[i] = value + offset;            <xsl:text/>
       <xsl:if test="//BackUpValue">                      
        pBackUpValue[i] = backUpValue + offset;         <xsl:text/>
       </xsl:if> 
       <xsl:if test="//DataItem">
        pDataItem[i] = new DC_SettableDataItem((TD_Float*)pValue[i]);     <xsl:text/>
       </xsl:if>
        offset = offset + sizeof(TD_Float);                     
     } 
 }

 // Now ensure that offset is aligned with a TD_Integer
 unsigned int temp = (offset/sizeof(TD_Integer));
 if (temp*sizeof(TD_Integer)&lt;offset)
    offset = (temp+1)*sizeof(TD_Integer);

 // Store the TD_Integer values in the second part of the array
 for (TD_DatabaseId i=0; i&lt;=maxParId; i++)  {
     if (type[i]==TD_IntegerCode) {
        pValue[i] = value + offset;            <xsl:text/>
       <xsl:if test="//BackUpValue">                      
        pBackUpValue[i] = backUpValue + offset;         <xsl:text/>
       </xsl:if> 
       <xsl:if test="//DataItem">
        pDataItem[i] = new DC_SettableDataItem((TD_Integer*)pValue[i]);     <xsl:text/>
       </xsl:if>
        offset = offset + sizeof(TD_Integer);                     
     } 
 }
       </xsl:when>
   <xsl:otherwise>
 // Store the TD_Float values in the first part of the array
     <xsl:for-each select="DataPoolItem[Type/@value='TD_Float']">
        <xsl:sort select="Id/@value" data-type="number"/>
 pValue[<xsl:value-of select="Id/@value"/>] = value + offset;               <xsl:text/>
        <xsl:if test="//BackUpValue">
 pBackUpValue[<xsl:value-of select="Id/@value"/>] = backUpValue + offset;   <xsl:text/>
        </xsl:if>
 offset = offset + sizeof(TD_Float);              <xsl:text/>
        <xsl:if test="//DataItem">
 pDataItem[<xsl:value-of select="Id/@value"/>] = new DC_SettableDataItem((TD_Float*)pValue[<xsl:value-of select="Id/@value"/>]); 
        </xsl:if>
     </xsl:for-each>
 // Now ensure that offset is aligned with a TD_Integer
 unsigned int temp = (offset/sizeof(TD_Integer));
 if (temp*sizeof(TD_Integer)&lt;offset)
    offset = (temp+1)*sizeof(TD_Integer);

 // Store the TD_Integer values in the second part of the array
     <xsl:for-each select="DataPoolItem[Type/@value='TD_Integer']">
        <xsl:sort select="Id/@value" data-type="number"/>
 pValue[<xsl:value-of select="Id/@value"/>] = value + offset;               <xsl:text/>
        <xsl:if test="//BackUpValue">
 pBackUpValue[<xsl:value-of select="Id/@value"/>] = backUpValue + offset;   <xsl:text/>
        </xsl:if>
 offset = offset + sizeof(TD_Integer);              <xsl:text/>
        <xsl:if test="//DataItem">
 pDataItem[<xsl:value-of select="Id/@value"/>] = new DC_SettableDataItem((TD_Integer*)pValue[<xsl:value-of select="Id/@value"/>]); 
        </xsl:if>
     </xsl:for-each>
   </xsl:otherwise>
</xsl:choose>

}
<!--=======================================================================================-->
 <xsl:if test="TimeStamp">
void <xsl:value-of select="$ClassName"/>::setObsClock(ObsClock* pObsClock) {
    assert( pObsClock != pNULL );               <xsl:text/>
    this->pObsClock = pObsClock;
}

ObsClock* <xsl:value-of select="$ClassName"/>::getObsClock(void) const {
    return pObsClock;
}
 </xsl:if>
<!--=======================================================================================-->
void <xsl:value-of select="$ClassName"/>::setValue(TD_DataPoolId id, TD_Float newValue) {
    assert( id &lt;= maxParId );               <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] == TD_FloatCode );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }<xsl:if test="TypeChecking">
    if ( type[id] != TD_FloatCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }</xsl:if>
 </xsl:if>
    (*(TD_Float*)pValue[id]) = newValue;        <xsl:text/>
 <xsl:if test="TimeStamp">
    timeStamp[id] = pObsClock->getTime();        <xsl:text/>
 </xsl:if>
 <xsl:if test="(BackUpValue) and (ValidityStatus)">
    if ( valid[id] )
        (*(TD_Float*)pBackUpValue[id]) = newValue;          <xsl:text/>
 </xsl:if>
}
<!--=======================================================================================-->
void <xsl:value-of select="$ClassName"/>::setValue(TD_DataPoolId id, TD_Integer newValue) {
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] == TD_IntegerCode );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }<xsl:if test="TypeChecking">
    if ( type[id] != TD_IntegerCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }</xsl:if>
 </xsl:if>
    (*(TD_Integer*)pValue[id]) = newValue;      <xsl:text/>
 <xsl:if test="TimeStamp">
    timeStamp[id] = pObsClock->getTime();        <xsl:text/>
 </xsl:if>
 <xsl:if test="(BackUpValue) and (ValidityStatus)">
    if ( valid[id] )
        (*(TD_Integer*)pBackUpValue[id]) = newValue;        <xsl:text/>
 </xsl:if>
}
<!--=======================================================================================-->
TD_Float <xsl:value-of select="$ClassName"/>::getFloatValue(TD_DataPoolId id) {
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] == TD_FloatCode );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return (TD_Float)0;
    }<xsl:if test="TypeChecking">
    if ( type[id] != TD_FloatCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return (TD_Float)0;
    }</xsl:if>
 </xsl:if>
 <xsl:choose>
   <xsl:when test="(BackUpValue) and (ValidityStatus)">
    if ( valid[id] )
        return (*(TD_Float*)pValue[id]);
    else
        return (*(TD_Float*)pBackUpValue[id]);
   </xsl:when>
   <xsl:otherwise>
    return (*(TD_Float*)pValue[id]);         <xsl:text/>
   </xsl:otherwise>
 </xsl:choose>
}
<!--=======================================================================================-->
TD_Integer <xsl:value-of select="$ClassName"/>::getIntegerValue(TD_DataPoolId id) {
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] == TD_IntegerCode );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return (TD_Integer)0;
    }<xsl:if test="TypeChecking">
    if ( type[id] != TD_IntegerCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return (TD_Integer)0;
    }</xsl:if>
 </xsl:if>
 <xsl:choose>
   <xsl:when test="(BackUpValue) and (ValidityStatus)">
    if ( valid[id] )
        return (*(TD_Integer*)pValue[id]);
    else
        return (*(TD_Integer*)pBackUpValue[id]);
   </xsl:when>
   <xsl:otherwise>
    return (*(TD_Integer*)pValue[id]);           <xsl:text/>
   </xsl:otherwise>
 </xsl:choose>
}
<!--=======================================================================================-->
TD_Float* <xsl:value-of select="$ClassName"/>::getPointerFloatValue(TD_DataPoolId id) {
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] == TD_FloatCode );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return pDefaultFloat;
    }<xsl:if test="TypeChecking">
    if ( type[id] != TD_FloatCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return pDefaultFloat;
     }</xsl:if>
 </xsl:if>
    return ((TD_Float*)pValue[id]);
}
<!--=======================================================================================-->
TD_Integer* <xsl:value-of select="$ClassName"/>::getPointerIntegerValue(TD_DataPoolId id) {
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] == TD_IntegerCode );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return pDefaultInt;
    }<xsl:if test="TypeChecking">
    if ( type[id] != TD_IntegerCode ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return pDefaultInt;
    }</xsl:if>
 </xsl:if>
    return ((TD_Integer*)pValue[id]);
}
<!--=======================================================================================-->
 <xsl:if test="DataItem">
DC_DataItem* <xsl:value-of select="$ClassName"/>::getDataItem(TD_DataPoolId id) {
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getDataItem(id);
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getDataItem(id);
    }</xsl:if>
 </xsl:if>
    return pDataItem[id];
}
 </xsl:if>
<!--=======================================================================================-->
 <xsl:if test="TimeStamp">
TD_ObsTime <xsl:value-of select="$ClassName"/>::getTimeStamp(TD_DataPoolId id) {
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getTimeStamp(id);
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getTimeStamp(id);
    }</xsl:if>
 </xsl:if>
    return timeStamp[id];
}
 </xsl:if>
<!--=======================================================================================-->
<xsl:if test="ValidityStatus">
bool <xsl:value-of select="$ClassName"/>::isValid(TD_DataPoolId id) {
    assert( id &lt;= maxParId );               <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isValid(id);
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isValid(id);
    }</xsl:if>
 </xsl:if>
    return valid[id];
}

void <xsl:value-of select="$ClassName"/>::setValidityStatus(TD_DataPoolId id, bool newValidityStatus) {
    assert( id &lt;= maxParId );       <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }
 <xsl:if test="(BackUpValue) and (DataItem)">
    if ( valid[id] &amp;&amp; !newValidityStatus)       // change from valid to not valid
        pDataItem[id]->setVariable((TD_Integer*)pBackUpValue[id]);   // make the data item point to the backup value
    if ( !valid[id] &amp;&amp; newValidityStatus)       // change from not valid to valid
        pDataItem[id]->setVariable((TD_Integer*)pValue[id]);         // make the data item point to the primary value
 </xsl:if>
    valid[id] = newValidityStatus;
}
</xsl:if>
<!--=======================================================================================-->
<xsl:if test="MonitoringProfile">
MonitoringProfile* <xsl:value-of select="$ClassName"/>::getMonitoringProfile(TD_DataPoolId id) {
    assert( id &lt;= maxParId );       <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getMonitoringProfile(id);
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getMonitoringProfile(id);
    }</xsl:if>
 </xsl:if>
    return pMonitoringProfile[id];
}

void <xsl:value-of select="$ClassName"/>::setMonitoringProfile(TD_DataPoolId id, MonitoringProfile* pMonProf) {
    assert( pMonProf != pNULL );
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }</xsl:if>
 </xsl:if>
    pMonitoringProfile[id] = pMonProf;
}
</xsl:if>
<!--=======================================================================================-->
<xsl:if test="RecoveryAction">
RecoveryAction* <xsl:value-of select="$ClassName"/>::getRecoveryAction(TD_DataPoolId id) {
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getRecoveryAction(id);
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::getRecoveryAction(id);
    }</xsl:if>
 </xsl:if>
    return pRecoveryAction[id];
}

void <xsl:value-of select="$ClassName"/>::setRecoveryAction(TD_DataPoolId id, RecoveryAction* pRecAct) {
    assert( pRecAct != pNULL );
    assert( id &lt;= maxParId );               <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
 <xsl:if test="not(RobustnessLevel/Low)">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return;
    }</xsl:if>
 </xsl:if>
    pRecoveryAction[id] = pRecAct;
}
</xsl:if>
<!--=======================================================================================-->
TD_DataPoolId <xsl:value-of select="$ClassName"/>::firstIdentifier(void) {
    assert( pValue != pNULL );
    iterationCounter = 0;
    while ( (pValue[iterationCounter]==pNULL) &amp;&amp; (iterationCounter&lt;maxParId) )
        iterationCounter++;
    return iterationCounter;
}

TD_DataPoolId <xsl:value-of select="$ClassName"/>::nextIdentifier(void) {
    assert( pValue != pNULL );
    iterationCounter++;
    while ( (pValue[iterationCounter]==pNULL) &amp;&amp; (iterationCounter&lt;maxParId) )
        iterationCounter++;
    return iterationCounter;
}

bool <xsl:value-of select="$ClassName"/>::isLastIdentifier(void) {
    assert( pValue != pNULL );
    return ( iterationCounter &gt; maxParId );
}
<!--=======================================================================================-->
<xsl:if test="TypeChecking">
bool <xsl:value-of select="$ClassName"/>::isFloat(TD_DataPoolId id) {
    assert( id &lt;= maxParId );           <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isFloat(id);
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isFloat(id);
    }</xsl:if>
 </xsl:if>
    return ( type[id] == TD_FloatCode );
}

bool <xsl:value-of select="$ClassName"/>::isInteger(TD_DataPoolId id) {
    assert( id &lt;= maxParId );       <xsl:text/>
 <xsl:if test="TypeChecking">
    assert( type[id] != -1 );
 </xsl:if>
 <xsl:if test="RobustnessLevel/High">
    if ( id > maxParId ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isInteger(id);
    }<xsl:if test="TypeChecking">
    if ( type[id] == -1 ) {
        CC_RootObject::getEventRepository()->create(this,EVT_ILLEGAL_DP_ACCESS);
        return DataPool::isInteger(id);
    }</xsl:if>
 </xsl:if>
    return ( type[id] == TD_IntegerCode );
}
</xsl:if>
<!--=======================================================================================-->
<xsl:if test="(MonitoringProfile) or (RecoveryAction) or (TimeStamp)">
bool <xsl:value-of select="$ClassName"/>::isObjectConfigured(void) {

   // Check configuration of super object
   if (!DataPool::isObjectConfigured()<xsl:if test="TimeStamp">||(pObsClock==pNULL)</xsl:if>)
       return NOT_CONFIGURED;

   for (TD_DataPoolId i=firstIdentifier(); !isLastIdentifier(); i=nextIdentifier())
        if ( (getMonitoringProfile(i)==pNULL) || (getRecoveryAction(i)==pNULL) )
            return false;

   return true;
}
</xsl:if>
<!--=======================================================================================-->
<xsl:if test="ValidityStatus">
void <xsl:value-of select="$ClassName"/>::reset(void) {
   for (TD_DataPoolId i=firstIdentifier(); !isLastIdentifier(); i=nextIdentifier())
        setValidityStatus(i, true);
}
</xsl:if>
</xsl:document>
</xsl:template>

<!--================================================================-->
<!-- Utility to compute the maximum value of the Id/@value field on -->
<!-- all the Attribute elements.                                    -->
<!-- When it is called the first time, the parameter 'currentMax'   -->
<!-- should be set to zero and the parameter 'currentPos' should be -->
<!-- set to 1.                                                      -->
<!--================================================================-->

<xsl:template name="computeMaxParId">
  <xsl:param name="currentMax"/>
  <xsl:param name="currentPos"/>
  <xsl:choose>
    <xsl:when test="$currentPos=count(//DataPoolItem/Id)">
      <xsl:value-of select="$currentMax"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:variable name="valOfNextParId" select="//DataPoolItem[$currentPos+1]/Id/@value"/>
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
<!-- Utility to compute the position of the first element among     -->
<!-- all //DataPoolItem/Type elements to have a "value" attribute   -->
<!-- equal to "$mask". If this value never occurs, then a value     -->
<!-- of zero is returned.                                           -->
<!-- The first time this template is called, the parameter          -->
<!-- "$currentPos" should have value one.                           -->
<!--================================================================-->

<xsl:template name="computeFirst">
  <xsl:param name="mask"/>
  <xsl:param name="currentPos"/>
  <xsl:choose>
    <xsl:when test="$currentPos=count(//DataPoolItem/Type)+1">
      <xsl:value-of select="'0'"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:variable name="val" select="//DataPoolItem[$currentPos]/Type/@value"/>
      <xsl:choose>
        <xsl:when test="$val = $mask">
          <xsl:value-of select="$currentPos"/>
        </xsl:when>
        <xsl:otherwise>
          <xsl:call-template name="computeFirst">
            <xsl:with-param name="mask" select="$mask"/>
            <xsl:with-param name="currentPos" select="$currentPos+1"/>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>



</xsl:stylesheet>

<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
    <xsl:import href="GeneralTags.xsl"/>      
    <xsl:output method="xml"/>
  
    <!-- ================================================================================================== -->
    <!-- This matches any node -->
    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>

    <!-- =========================================================== -->
    <xsl:template match="DomainDictionary">
        <html>
            <head>
                <link rel="stylesheet" type="text/css" href="css/main.css"/>
                <link rel="stylesheet" type="text/css" href="css/3col_leftNav.css"/>
            </head>
            <body>
                <div id="header">
                    <h1 id="siteName">OBS Framework </h1>
                    <div id="globalNav"> 
                         <a href="Home.html">Home</a> | <a href="General.html">General</a> | <a href="Implementation.html">Implementation</a> | <a href="doxygen/html/index.html" target="_blank">C++ Code Documentation</a> | <a href="http://www.pnp-software.com/ObsFramework/ObsFramework_0_8_3.zip">Download</a> | <a href="indexDisclaimer.html">Disclaimer</a>
                    </div> 
                    <h2 id="pageName">Implementation - Domain Dictionary</h2> 
                  </div>
                    <div id="navbar"> 
                      <div id="sectionLinks">                         
                        <ul> 
                          <li><a href="indexDomainDictionary.html">Domain Dictionary</a></li>
                          <li><a href="indexDesignPatterns.html">Design Patterns</a></li>
                          <li><a href="indexAbstractInterfaces.html">Abstract Interfaces</a></li>
                          <li><a href="indexConcreteComponents.html">Concrete Components</a></li>
                          <li><a href="indexGeneratorMeta-Components.html">Generator Meta-Components</a></li>
                          <li><a href="indexTransformerMeta-Components.html">Transformer Meta-Components</a></li>
                          <li><a href="indexRealTimeIssues.html">Real Time Issues</a></li>
                          <li><a href="indexImplementationIssues.html">Implementation Issues</a></li>
                          <li><a href="indexInstallationIssues.html">Installation Issues</a></li>
                          <li><a href="indexSourceCode.html">Source Code</a></li>
                          <li><a href="doxygen/html/index.html" target="_blank">C++ Code Documentation</a></li>
                        </ul> 
                      </div>                       
                    </div>
                <div id="subnavbar"> 
                      <li><a href="DomainDictionaryEntries.html">- ALL ENTRIES -</a></li>
                      <li><a href="domainDictionaryAbstractUnit.html">Abstract Unit</a></li>
                      <li><a href="domainDictionaryConditionalPunctualAction.html">Conditional Punctual Action</a></li>
                      <li><a href="domainDictionaryControlAction.html">Control Action</a></li> 
                      <li><a href="domainDictionaryControlBlock.html">Control Block</a></li> 
                      <li><a href="domainDictionaryControllerManager.html">Controller Manager</a></li> 
                      <li><a href="domainDictionaryCriticalTelecommand.html">Critical Telecommand</a></li> 
                      <li><a href="domainDictionaryDataItem.html">Data Item</a></li> 
                      <li><a href="domainDictionaryDataPool.html">Data Pool</a></li> 
                      <li><a href="domainDictionaryEvent.html">Event</a></li> 
                      <li><a href="domainDictionaryEventRepository.html">Event Repository</a></li> 
                      <li><a href="domainDictionaryFDIRCheck.html">FDIR Check</a></li> 
                      <li><a href="domainDictionaryFSM.html">FSM</a></li> 
                      <li><a href="domainDictionaryFsmEvent.html">FsmEvent</a></li> 
                      <li><a href="domainDictionaryFsmState.html">FsmState</a></li> 
                      <li><a href="domainDictionaryFunctionalityImplementer.html">Functionality Implementer</a></li> 
                      <li><a href="domainDictionaryFunctionalityManager.html">Functionality Manager</a></li> 
                      <li><a href="domainDictionaryManoeuvre.html">Manoeuvre</a></li> 
                      <li><a href="domainDictionaryManoeuvreManager.html">Manoeuvre Manager</a></li> 
                      <li><a href="domainDictionaryModeManager.html">Mode Manager</a></li> 
                      <li><a href="domainDictionaryMonitoringProfile.html">Monitoring Profile</a></li> 
                      <li><a href="domainDictionaryOperatingSystemInterface.html">Operating System Interface</a></li> 
                      <li><a href="domainDictionaryParameterDatabase.html">Parameter Database</a></li> 
                      <li><a href="domainDictionaryPunctualAction.html">Punctual Action</a></li> 
                      <li><a href="domainDictionaryReconfigurationManager.html">Reconfiguration Manager</a></li> 
                      <li><a href="domainDictionaryRecoveryAction.html">Recovery Action</a></li> 
                      <li><a href="domainDictionaryTelecommand.html">Telecommand</a></li> 
                      <li><a href="domainDictionaryTelecommandLoader.html">Telecommand Loader</a></li> 
                      <li><a href="domainDictionaryTelecommandManager.html">Telecommand Manager</a></li> 
                      <li><a href="domainDictionaryTelemeterable.html">Telemeterable</a></li> 
                      <li><a href="domainDictionaryTelemetryItem.html">Telemetry Item</a></li> 
                      <li><a href="domainDictionaryTelemetryManager.html">Telemetry Manager</a></li> 
                      <li><a href="domainDictionaryTelemetryStream.html">Telemetry Stream</a></li> 
                      <li><a href="domainDictionaryTracer.html">Tracer</a></li>          
                </div> 
                <div id="content">
                      <xsl:for-each select="Entry">
                         <xsl:apply-templates select="Name"/>
                         <xsl:apply-templates select="Definition"/>
                         <xsl:apply-templates select="DesignPattern"/>
                       </xsl:for-each>
                </div>
                <div id="siteInfo"><a href="mailto:pasetti@control.ee.ethz.ch, cechti@control.ee.ethz.ch">Contact Us</a> | The OBS Framework Project</div>                 
            </body>
        </html>           
    </xsl:template>

   <!-- =========================================================== -->
    <xsl:template match="Name">
        <a>
             <xsl:attribute name="name"><xsl:value-of select="translate(normalize-space(.),' ','')"/></xsl:attribute><b>
            <xsl:value-of select="."/>
        </b>
            </a>
        
    </xsl:template>

    <!-- =========================================================== -->
    <xsl:template match="Definition">
        <p class="links">
           <xsl:copy-of select="."/> 
        </p>   
    </xsl:template>
    
    <!-- =========================================================== -->
    <xsl:template match="DesignPattern">
        <p class="links">
            See the
            <a>
             <xsl:attribute name="HREF"><xsl:value-of select="./FileName"/>.html</xsl:attribute><xsl:value-of select="./Name"/>
            </a> design pattern.
        </p>     
    </xsl:template>
    
    </xsl:stylesheet>

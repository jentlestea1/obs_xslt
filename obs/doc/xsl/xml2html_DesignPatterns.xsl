<?xml version="1.0" encoding="UTF-8" ?>
<!--The objective of tthe transformation is to translate component descriptions to description models required by the GIE.-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
    <xsl:import href="GeneralTags.xsl"/>      
    <xsl:output method="xml"/>
  
    <!-- =========================================================== -->
    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>
    <!-- =========================================================== -->
    <xsl:template match="Chapter">
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
                    <h2 id="pageName">Implementation - Design Patterns</h2> 
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
                        <li><a href="DesignPatternTable.html">- CATALOGUE -</a></li>  
                        <li><a href="Connection.html">Connection</a></li>
                        <li><a href="ControlBlock.html">Control Block</a></li>
                        <li><a href="Event.html">Event</a></li>
                        <li><a href="FDIRCheck.html">FDIR Check</a></li>
                        <li><a href="FSM.html">FSM</a></li>
                        <li><a href="Manager.html">Manager</a></li>
                        <li><a href="ManoeuvreManagement.html">Manoeuvre Management</a></li>
                        <li><a href="ModeManagement.html">Mode Management</a></li>
                        <li><a href="OperatingSystemInterface.html">Operating System Interface</a></li>
                        <li><a href="ParameterDatabase.html">Parameter Database</a></li>
                        <li><a href="PunctualAction.html">Punctual Action</a></li>
                        <li><a href="RecoveryAction.html">Recovery Action</a></li>
                        <li><a href="ReconfigurationManagement.html">Reconfiguration Management</a></li>
                        <li><a href="SharedData.html">Shared Data</a></li>
                        <li><a href="TelecommandManagement.html">Telecommand Management</a></li>
                        <li><a href="Telemeterable.html">Telemeterable</a></li>
                        <li><a href="TelemetryManagement.html">Telemetry Management</a></li>
                        <li><a href="TelemetryStream.html">Telemetry Stream</a></li>
                        <li><a href="TelemetryItem.html">Telemetry Item</a></li>
                        <li><a href="Trace.html">Trace</a></li>
                        <li><a href="VariableMonitoring.html">Variable Monitoring</a></li>           
                </div> 
                <div id="content">
                   <xsl:call-template name="Introduction"/>
                </div> 
                <div id="siteInfo"><a href="mailto:pasetti@control.ee.ethz.ch, cechti@control.ee.ethz.ch">Contact Us</a> | The OBS Framework Project</div>                 
            </body>
        </html>        
    </xsl:template>

</xsl:stylesheet>

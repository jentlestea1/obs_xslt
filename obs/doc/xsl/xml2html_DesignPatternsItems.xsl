<?xml version="1.0" encoding="UTF-8" ?>
<!--The objective of tthe transformation is to translate component descriptions to description models required by the GIE.-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
    <xsl:import href="GeneralTags.xsl"/>      
    <xsl:output method="xml"/>
  
    <!-- =========================================================== -->
    <xsl:template match="/">
        <xsl:call-template name="Menu"/>
    </xsl:template>
    <!-- =========================================================== -->
    <xsl:template name="Menu">
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
                   <xsl:apply-templates select="DesignPattern"/>
                </div>
                <div id="siteInfo"><a href="mailto:pasetti@control.ee.ethz.ch, cechti@control.ee.ethz.ch">Contact Us</a> | The OBS Framework Project</div>                 
            </body>
        </html>                    
    </xsl:template>

    <!-- =========================================================== -->    
     <xsl:template match="DesignPattern">
         <xsl:apply-templates select="Name"/>
        <xsl:apply-templates select="Intent"/>
        <xsl:apply-templates select="BasedOn"/>
        <xsl:apply-templates select="Motivation"/>
        <H3>
        <b>Dictionary Entries</b>
        </H3><p>The following abstractions or domain-wide concepts are defined to support the
        implementation of this design pattern:</p><ul>
            <xsl:apply-templates select="DictionaryEntry"/>
        </ul>
        <xsl:apply-templates select="Structure"/>
        <xsl:apply-templates select="StructureFigure"/>
        <H3>
            <b>Participants</b>
        </H3>
        <ul>
            <xsl:apply-templates select="Participant"/>
        </ul>
        <xsl:apply-templates select="Collaborations"/>
        <H3>
            <b>Consequences</b>
        </H3>
        <ul>
            <xsl:apply-templates select="Consequence"/>
        </ul>
        <xsl:apply-templates select="Applicability"/>
        <H3>
            <b>Implementation Issues</b>
        </H3>
        <xsl:apply-templates select="ImplementationIssue"/>
        <H3>
            <b>OBS Framework Mapping</b>
        </H3><p>The implementation of this design pattern in the OBS Framework is supported by
        the following classes:</p><ul>
            <xsl:apply-templates select="FrameworkMapping"/>
        </ul>
        <xsl:apply-templates select="SampleCode"/>
        <xsl:apply-templates select="Remarks"/>
        <xsl:apply-templates select="Author"/>
        <xsl:apply-templates select="LastModified"/>         
     </xsl:template>     
    <!-- =========================================================== -->
    <xsl:template match="Name">
        <p>
        <H4>                
        <xsl:apply-templates/>
        Design Pattern
         </H4>    
        </p>
    </xsl:template>
    <!-- =========================================================== -->
    <xsl:template match="Intent">
        <p>
        <H3>
            <b>Intent</b>
        </H3>
        </p>
        <p>
        <xsl:apply-templates/>
        </p>
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="BasedOn">
        <p>
        <H3>
            <b>Based On</b>
        </H3>
        </p>
        <p>
        <xsl:apply-templates/>
        </p>
    </xsl:template>
    <!-- =========================================================== -->
    <xsl:template match="Motivation">
        <p>
        <H3>
            <b>Motivation</b>
        </H3>
        </p>
        <p>  
        <xsl:apply-templates/>
        </p>    
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="DictionaryEntry">
        <li>
            <i>
                <a>
                    <xsl:attribute name="HREF">domainDictionary<xsl:value-of select="translate(normalize-space(.),' ','')"/>.html</xsl:attribute>
                    <xsl:value-of select="."/>
                </a>
            </i>
        </li>
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="Structure">
        <p>
        <H3>
            <b>Structure</b>
        </H3>
        </p>
        <p>   
        <xsl:apply-templates/>
         </p>   
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="Participant">
        <li>
            <CODE>
                <xsl:value-of select="Name"/>
            </CODE>:&#160; <xsl:apply-templates select="Role"/>
        </li>
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="Collaborations">
        <p>
        <H3>
            <b>Collaborations</b>
        </H3>
        </p>
        <p>
        <xsl:apply-templates/>
        </p>    
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="Consequence">
        <li>
            <xsl:apply-templates/>
        </li>
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="Applicability">
        <p>
        <H3>
            <b>Applicability</b>
        </H3>
        </p>
        <p>
        <xsl:apply-templates/>
        </p>    
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="ImplementationIssue">
        <p>
            <xsl:apply-templates/>
        </p>
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="FrameworkMapping">
        <xsl:variable name="DPName" select="Name"/>
        <xsl:variable name="DPType" select="Type"/>
        <li>
            <i>
                <xsl:value-of select="$DPName"/>
            </i>
            <xsl:text/>
            <xsl:value-of select="$DPType"/> --&gt; <xsl:choose>
                <xsl:when test="FrameworkClass">
                    <xsl:for-each select="FrameworkClass">
                        <xsl:variable name="className" select="."/>
                        <xsl:variable name="correctedClassName">
                            <xsl:call-template name="doubleUnderscore">
                                <xsl:with-param name="string" select="$className"/>
                            </xsl:call-template>
                        </xsl:variable>
                        <CODE>
                            <a>
                                <xsl:attribute name="href">doxygen/html/class<xsl:value-of select="$correctedClassName"/>.html</xsl:attribute>
                                <xsl:value-of select="$className"/>
                            </a>
                        </CODE>
                        <xsl:if test="position()!=last()">, </xsl:if>
                    </xsl:for-each>
                </xsl:when>
                <xsl:otherwise>
                    <xsl:value-of select="Remark"/>
                </xsl:otherwise>
            </xsl:choose>
        </li>
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="SampleCode">
        <a>
            <xsl:attribute name="NAME">#SampleCode</xsl:attribute>    
            <p>
            <H3>
                <b>Sample Code</b>
            </H3>
            </p>    
        </a>
        <p>
        <xsl:apply-templates/>
        </p>    
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="Remarks">
        <p>
        <H3>
            <b>Remarks</b>
        </H3>
        </p>
        <p>
        <xsl:apply-templates/>
        </p>    
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="Author">
        <p>
        <H3>
            <b>Author</b>
        </H3>
        </p>
        <p>
        <xsl:apply-templates/>
        </p>    
    </xsl:template>
    <!-- =========================================================== -->    
    <xsl:template match="LastModified">
        <p>
        <H3>
            <b>Last Modified</b>
        </H3>
        </p>
        <p>
        <xsl:apply-templates/>
        </p>        
    </xsl:template>
    <!-- =========================================================== -->      
    <xsl:template match="Figure">
        <H1 ALIGN="center">
            <img>
                <xsl:attribute name="src">../figures/gif/<xsl:value-of select="."/>.gif</xsl:attribute>
            </img>
        </H1>
    </xsl:template>
    <!-- =========================================================== -->      
    <xsl:template match="ClassDiagram">
        <H1 ALIGN="center">
            <img>
                <xsl:attribute name="src">../figures/gif/<xsl:value-of select="."/>.gif</xsl:attribute>
            </img>
        </H1>
    </xsl:template>
    <!-- =========================================================== -->      
    <xsl:template match="*|@*|text()">
        <xsl:copy>
            <xsl:apply-templates select="*|@*|text()"/>
        </xsl:copy>
    </xsl:template>
    <!--==================================================================
Utility that takes one input string and returns the same string
transformed as follows:
- if the string does not contain any underscore, it is left unchanged
- it the string contains underscore characters, the first one is "doubled".
Thus, for instance, string "aaa_bb" is transformed into string "aaa__bb".
This utility is useful because Doxygen doubles the underscore when
creating the name of a file that holds the description of a class.
Thus, for instance, the class "CC_RootObject" is described in file
"classCC__RootObject.html".
======================================================================-->
    <xsl:template name="doubleUnderscore">
        <xsl:param name="string"/>
        <xsl:choose>
            <xsl:when test="contains($string,'_')">
                <xsl:variable name="before" select="substring-before($string,'_')"/>
                <xsl:variable name="after" select="substring-after($string,'_')"/>
                <xsl:value-of select="concat($before,'__',$after)"/>
            </xsl:when>
            <xsl:otherwise>
                <xsl:value-of select="$string"/>
            </xsl:otherwise>
        </xsl:choose>
    </xsl:template>
    
    <!-- =========================================================== -->    
    <xsl:template match="StructureFigure">
      
        <xsl:attribute name="name">
          <xsl:value-of select="normalize-space(.)"/><xsl:text/>
        </xsl:attribute>
        <p>
          <center>
            <img>
              <xsl:attribute name="src">../figures/gif/<xsl:value-of select="normalize-space(.)"/>.gif<xsl:text/>
              </xsl:attribute>
            </img>
          </center>
        </p> 
    </xsl:template>        
</xsl:stylesheet>

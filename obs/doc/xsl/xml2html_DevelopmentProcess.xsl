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
                    <h1 id="siteName">OBS Framework</h1>
                    <div id="globalNav"> 
                         <a href="Home.html">Home</a> | <a href="General.html">General</a> | <a href="Implementation.html">Implementation</a> | <a href="doxygen/html/index.html" target="_blank">C++ Code Documentation</a> | <a href="http://www.pnp-software.com/ObsFramework/ObsFramework_0_8_3.zip">Download</a> | <a href="indexDisclaimer.html">Disclaimer</a>
                    </div> 
                    <h2 id="pageName">General - Development Process</h2> 
                  </div>
                    <div id="navbar"> 
                      <div id="sectionLinks">                         
                        <ul> 
                            <li><a href="indexDevelopmentProcess.html" class="current">Development Process</a></li>
                            <li><a href="indexModellingApproach.html">Modelling Approach</a></li>                        
                            <li><a href="indexPUSCompatibility.html">PUS Compatibility</a></li>
                            <li><a href="indexQualificationApproach.html">Qualification Approach</a></li>
                        </ul> 
                      </div>                       
                    </div>
                <div id="subnavbar"> 
                        <li><a href="#FrameworkCreation">Framework Creation</a></li>
                        <li><a href="#FrameworkInstantiation">Framework Instantiation</a></li>                         
                </div>    
                <div id="content">
                   <xsl:call-template name="Introduction"/>
                </div>
                <div id="siteInfo"><a href="mailto:pasetti@control.ee.ethz.ch, cechti@control.ee.ethz.ch">Contact Us</a> | The OBS Framework Project</div>
            </body>
        </html>               
    </xsl:template>
    
</xsl:stylesheet>

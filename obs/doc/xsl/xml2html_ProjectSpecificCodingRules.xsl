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
    <xsl:template match="CodingRules">
        <html>
            <head>
                <link rel="stylesheet" type="text/css" href="css/main.css"/>
                <link rel="stylesheet" type="text/css" href="css/2col_leftNav.css"/>
            </head>
            <body>
                <div id="header">
                    <h1 id="siteName">OBS Framework </h1>
                    <div id="globalNav"> 
                         <a href="Home.html">Home</a> | <a href="General.html">General</a> | <a href="Implementation.html">Implementation</a> | <a href="doxygen/html/index.html" target="_blank">C++ Code Documentation</a> | <a href="http://www.pnp-software.com/ObsFramework/ObsFramework_0_8_3.zip">Download</a> | <a href="indexDisclaimer.html">Disclaimer</a>
                    </div> 
                    <h2 id="pageName">Implementation - Project Specific Coding Rules</h2> 
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
                <div id="content">
                 <p class="links">
                   This page defines and justifies the project-specific coding rules that were applied to the
                   implementation of the OBS Framework. These coding rules complement those
                   <a href="ComplianceWithEsaCodingStandard.html">taken over</a> from the "C and C++ Coding
                   Standard" prepared by the ESA Board for Software Standardisation and Control (BSSC).
                   The rules are grouped in categories of logically related rules.
                  </p>
                    
                    <xsl:for-each select="Rule">
                     <xsl:variable name="category" select="Category"/>
                     <xsl:variable name="precPos" select="position()-1"/>
                     <xsl:variable name="prec" select="../Rule[position()=$precPos]/Category"/>
                     <xsl:if test="($precPos=0) or (not ($prec=$category))">
                       <p><H3><b><xsl:value-of select="$category"/> Rules</b></H3></p>
                       <table WIDTH="90%" BORDER="1" ALIGN="center" CELLPADDING="5%">
                         <xsl:apply-templates select="../Rule[Category=$category]"/>
                       </table>
                     </xsl:if>
                   </xsl:for-each>
                </div>
                <div id="siteInfo"><a href="mailto:pasetti@control.ee.ethz.ch, cechti@control.ee.ethz.ch">Contact Us</a> | The OBS Framework Project</div>                 
            </body>
        </html>             
    </xsl:template>

<!-- =========================================================== -->

<xsl:template match="Rule">

  <a>
    <xsl:attribute name="NAME">Rule<xsl:value-of select="Id"/>
    </xsl:attribute>
  </a>
  <tr>
    <td>
      <b>PR<xsl:apply-templates select="Id"/></b>
    </td>
    <td>
      <b><xsl:apply-templates select="Description"/></b>
    </td>
  </tr>
  <tr>
    <td COLSPAN="2">
      <xsl:apply-templates select="Justification"/>
      <p></p>
    </td>
  </tr>

</xsl:template>

<!-- =========================================================== -->

<xsl:template match="*|@*|text()">
 <xsl:copy>
  <xsl:apply-templates select="*|@*|text()"/>
 </xsl:copy>
</xsl:template>
    
</xsl:stylesheet>

<?xml version="1.0" encoding="UTF-8" ?>
<!--The objective of tthe transformation is to translate component descriptions to description models required by the GIE.-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
    <xsl:output method="xml"/>
    <!-- =========================================================== -->
    <xsl:template match="/">
        <xsl:apply-templates/>
    </xsl:template>
    <!-- =========================================================== -->
    <xsl:template match="Chapter">
        <html>
            <head>
                <link rel="stylesheet" type="text/css" href="../css/obsstyle.css"/>
            </head>
            <body>
                <div id="header">
                    <h1>
                        <xsl:value-of select="normalize-space(Title)"/>
                    </h1>
                    <div id="navbar">
                        <a href="Home.html">Home</a>
                        <a href="Introduction.html">Introduction</a>                        
                        <a href="DevelopmentProcess.html">Development Process</a>
                        <a href="ModellingApproach.html">Modelling Approach</a>                        
                        <a href="DomainDictionary.html">Domain Dictionary</a>
                        <a href="AbstractInterfaces.html">Abstract Interfaces</a>
                        <a href="ConcreteComponents.html">Concrete Components</a>                        
                        <a href="GeneratorMeta-Components.html">Generator Meta-Components</a>
                        <a href="TransformerMeta-Components.html">Transformer Meta-Components</a>                                                
                        <a href="RealTimeIssues.html">Real Time Issues</a>
                        <a href="ImplementationIssues.html">Implementation Issues</a>
                        <a href="PUSCompatibility.html">PUS Compatibility</a>
                        <a href="QualificationApproach.html">Qualification Approach</a>
                        <a href="InstallationIssues.html">Installation Issues</a>                        
                        <a href="SourceCode.html">Source Code</a>
                        <a href="../../doc/doxygen/html/index.html">C++ Code Documentation</a>
                        <a href="Copyright.html">Copyright</a>
                        <a href="http://www.pnp-software.com/index.html">About Us</a>
                    </div>
                </div>
                <div id="maincontent">
                   <xsl:call-template name="Introduction"/>
                </div>
            </body>
        </html>
    </xsl:template>
   <!-- =========================================================== -->
    <xsl:template name="Introduction">
        <xsl:apply-templates/>      
    </xsl:template>

    <!-- =========================================================== -->
    <xsl:template match="p">
        <p class="links">
            <xsl:copy-of select="."/>
        </p>        
    </xsl:template>        

    <!-- =========================================================== -->
    <xsl:template match="ul">
        <p class="links">
            <xsl:copy-of select="."/>
        </p>    
    </xsl:template>        
   
    <!-- =========================================================== -->    
    <xsl:template match="Section">
      <h3>
        <a>
          <xsl:attribute name="name">
            <xsl:value-of select="translate(@Title,' ','')"/>
          </xsl:attribute>
          <xsl:value-of select="@Title"/>
        </a>
      </h3>
      <xsl:apply-templates/>
      
    </xsl:template>

    <!-- =========================================================== -->    
    <xsl:template match="table">
        <xsl:copy-of select="."/>
    </xsl:template>       
    
    <!-- =========================================================== -->    
    <xsl:template match="Figure">
      
        <xsl:attribute name="name">
          <xsl:value-of select="normalize-space(.)"/><xsl:text/>
        </xsl:attribute>
        <p>
          <center>
            <img>
              <xsl:attribute name="src">../../figures/gif/<xsl:value-of select="normalize-space(.)"/>.gif<xsl:text/>
              </xsl:attribute>
            </img>
          </center>
        </p>
      
    </xsl:template>    
    
    <!-- =========================================================== -->
    <xsl:template match="Title">
    
    </xsl:template>
    
     <!-- =========================================================== -->
    <xsl:template match="Name">
        
    </xsl:template>
    
    <!-- =========================================================== -->
    <xsl:template match="Author">
       
    </xsl:template>
    
    <!-- =========================================================== -->
    <xsl:template match="Affiliation">
        
    </xsl:template>
    
    <!-- =========================================================== -->
    <xsl:template match="EMail">
        
    </xsl:template> 
    
    <!-- =========================================================== -->
    <xsl:template match="LastModified">
        
    </xsl:template>         
    
</xsl:stylesheet>

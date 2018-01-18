<?xml version="1.0" encoding="UTF-8" ?>
<!--The objective of tthe transformation is to translate component descriptions to description models required by the GIE.-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.1">
    <xsl:output method="xml"/>     

    <!-- =========================================================== -->
    <xsl:template name="Introduction">
        <xsl:apply-templates/>      
    </xsl:template>

    <!-- =========================================================== -->
    <xsl:template match="p">
        <p class="links">
            <!--<xsl:copy-of select="."/>-->
            <xsl:apply-templates/> 
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
              <xsl:attribute name="src">../figures/gif/<xsl:value-of select="normalize-space(.)"/>.gif<xsl:text/>
              </xsl:attribute>
            </img>
          </center>
        </p> 
    </xsl:template>    
    
    <!-- =========================================================== -->
    <xsl:template match="*|@*|text()">
     <xsl:copy>
      <xsl:apply-templates select="*|@*|text()"/>
     </xsl:copy>
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

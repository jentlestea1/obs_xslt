<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
      <xsl:output method="xml"/>
      <!-- ================================================================================================== -->
      <!-- This matches any node -->
      <xsl:template match="/">
            <xsl:apply-templates select="*"/>
      </xsl:template>
      <!-- ================================================================================================== -->
      <xsl:template match="*">
            <xsl:variable name="fName" select="name()"/>
            <xsl:choose>
                  <xsl:when test="contains($fName,'_')">
                        <xsl:element name="{substring-before($fName,'_')}">
                              <xsl:apply-templates select="@*"/>
                              <xsl:if test="$fName='Description'">
                                    <xsl:value-of select="."/>
                              </xsl:if>
                              <xsl:apply-templates select="*"/>
                        </xsl:element>
                  </xsl:when>
                  <xsl:otherwise>
                        <xsl:element name="{$fName}">
                              <xsl:apply-templates select="@*"/>
                              <xsl:if test="$fName='Description'">
                                    <xsl:value-of select="."/>
                              </xsl:if>
                              <xsl:apply-templates select="*"/>
                        </xsl:element>
                  </xsl:otherwise>
            </xsl:choose>
      </xsl:template>
      <!-- ================================================================================================== -->
      <xsl:template match="@*">
            <xsl:copy/>
      </xsl:template>
</xsl:stylesheet>

<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<!--============================================================================
Project: OBS Environment
Author: A. Pasetti
Company: P&P Software
Description:
XSLT program to generate the list of domain dictionary entries with the
references to their definitions.
The output file is a text file consisting of a list of records.
Each record contains two fields:
- The first field is the name of a domain dictionary entry or of a basic
  operation associated to a domain dictionary entry.
- The second field is the name a URL pointing to the definition of the entry.
The URLs are referred to the directory where the domain dictionary is
stored.
=============================================================================-->

<xsl:strip-space elements="*"/>
<xsl:output omit-xml-declaration="yes" method="text"/>

<!--============================================================================
Define useful global variables
=============================================================================-->

<!-- Document holding the descritions of the core components                 -->
<xsl:variable name="CcBasicOp" select="document('../Components/CoreComponents.xml')/CoreComponents"/>

<!-- Document holding the descritions of the abstract interfaces             -->
<xsl:variable name="AiBasicOp" select="document('../AbstractInterfaces/AbstractInterfaces.xml')/AbstractInterfaces"/>

<!-- String separating the first and second fields                           -->
<xsl:variable name="Separator1" select="', '"/>

<!-- Double quote string                                                     -->
<xsl:variable name="Quote">"</xsl:variable>

<!-- String introducing a record representing a basic operation              -->
<xsl:variable name="BasicOpIntr" select="'  '"/>

<!-- URL of the domain dictionary file                                       -->
<xsl:variable name="DomainDictionaryFile" select="'DomainDictionary/DomainDictionary.html'"/>

<!-- URL of the abstract interface file                                      -->
<xsl:variable name="AbstractInterfaceFile" select="'AbstractInterfaces/AbstractInterfaces.html'"/>

<!-- URL of the core component file                                          -->
<xsl:variable name="CoreComponentsFile" select="'Components/CoreComponents.html'"/>

<!--============================================================================
Process the domain dictionary file
=============================================================================-->

<xsl:template match="DomainDictionary">

  <xsl:for-each select="Entry">
    <xsl:value-of select="$Quote"/>
    <xsl:value-of select="normalize-space(Name)"/>
    <xsl:value-of select="$Quote"/>
    <xsl:value-of select="$Separator1"/>
    <xsl:value-of select="$Quote"/>
    <xsl:value-of select="concat($DomainDictionaryFile,'#')"/>
    <xsl:value-of select="translate(normalize-space(Name),' ','')"/>
    <xsl:value-of select="$Quote"/><xsl:text>
</xsl:text>

    <xsl:choose>
      <xsl:when test="MappedTo/Type='Abstract Interface'">
        <xsl:call-template name="AiBasicOperations">
          <xsl:with-param name="name" select="MappedTo/Item"/>
        </xsl:call-template>
      </xsl:when>
      <xsl:when test="MappedTo/Type='Core Component'">
        <xsl:call-template name="CcBasicOperations">
          <xsl:with-param name="name" select="MappedTo/Item"/>
        </xsl:call-template>
      </xsl:when>
    </xsl:choose>
  </xsl:for-each>

</xsl:template>

<!--============================================================================
Write the basic operations associated to a domain dictionary entry
mapped to an abstract interface.
Parameter 1: the name of the dictionary entry
=============================================================================-->

<xsl:template name="AiBasicOperations">
  <xsl:param name="name"/>

  <xsl:for-each select="$AiBasicOp/AbstractInterface[Name=$name]/BasicOperation">
    <xsl:value-of select="$Quote"/>
    <xsl:value-of select="$BasicOpIntr"/>
    <xsl:value-of select="Name"/>
    <xsl:value-of select="$Quote"/>
    <xsl:value-of select="$Separator1"/>
    <xsl:value-of select="$Quote"/>
    <xsl:value-of select="concat($AbstractInterfaceFile,'#')"/>
    <xsl:value-of select="$name"/>
    <xsl:value-of select="translate(normalize-space(Name),' ','')"/>
    <xsl:value-of select="$Quote"/><xsl:text>
</xsl:text>
  </xsl:for-each>

</xsl:template>

<!--============================================================================
Write the basic operations associated to a domain dictionary entry
mapped to a core component.
Parameter 1: the name of the dictionary entry
=============================================================================-->

<xsl:template name="CcBasicOperations">
  <xsl:param name="name"/>

  <xsl:for-each select="$CcBasicOp/CoreComponent[Name=$name]/BasicOperation">
    <xsl:value-of select="$Quote"/>
    <xsl:value-of select="$BasicOpIntr"/>
    <xsl:value-of select="Name"/>
    <xsl:value-of select="$Quote"/>
    <xsl:value-of select="$Separator1"/>
    <xsl:value-of select="$Quote"/>
    <xsl:value-of select="concat($CoreComponentsFile,'#')"/>
    <xsl:value-of select="$name"/>
    <xsl:value-of select="translate(normalize-space(Name),' ','')"/>
    <xsl:value-of select="$Quote"/><xsl:text>
</xsl:text>
  </xsl:for-each>

</xsl:template>

</xsl:stylesheet>

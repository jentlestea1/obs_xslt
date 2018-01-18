<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.1" xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" exclude-result-prefixes="xsi">
    <xsl:output method="xml"/>
    <!-- ========================================================================= -->
    <!-- This matches any node -->
    <xsl:template match="/">
        <xsl:element name="FrameworkFeatureModel">
            <!-- select all the child nodes of the FrameworkFeatureModel tag in the main file -->
            <xsl:for-each select="FrameworkFeatureModel/child::Feature">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:apply-templates/>
        </xsl:element>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- This detects Macro element -->
    <xsl:template match="Macro">
        <xsl:variable name="mName" select="@nameOfMacro"/>
        <xsl:call-template name="OnlyFeature"/>
        <xsl:call-template name="Extension"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="OnlyFeature">
        <xsl:if test="Feature">
            <xsl:element name="Macro">
                <xsl:attribute name="nameOfMacro">
                    <xsl:value-of select="@nameOfMacro"/>
                </xsl:attribute>
                <xsl:call-template name="AddFeature"/>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Description">
        <xsl:if test="Description">
            <xsl:element name="Description">
                <xsl:attribute name="text">
                    <xsl:value-of select="Description/@text"/>
                </xsl:attribute>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="FeatureComment">
        <xsl:if test="FeatureComment">
            <xsl:element name="FeatureComment">
                <xsl:attribute name="text">
                    <xsl:value-of select="FeatureComment/@text"/>
                </xsl:attribute>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="FeatureCardinality">
        <xsl:element name="FeatureCardinality">
            <xsl:attribute name="FeatureCardMin">
                <xsl:value-of select="FeatureCardinality/@FeatureCardMin"/>
            </xsl:attribute>
            <xsl:if test="FeatureCardinality/@FeatureCardMax&gt;= 0">
                <xsl:attribute name="FeatureCardMax">
                    <xsl:value-of select="FeatureCardinality/@FeatureCardMax"/>
                </xsl:attribute>
            </xsl:if>
            <xsl:if test="FeatureCardinality/@FeatureCardMax = '*' ">
                <xsl:attribute name="FeatureCardMax">
                    <xsl:value-of select=" '*' "/>
                </xsl:attribute>
            </xsl:if>
            <xsl:if test="FeatureCardinality/@FeatureCardMax = '+' ">
                <xsl:attribute name="FeatureCardMax">
                    <xsl:value-of select=" '+' "/>
                </xsl:attribute>
            </xsl:if>
        </xsl:element>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Type">
        <xsl:element name="Type">
            <xsl:call-template name="Attribute"/>
            <xsl:call-template name="BuildingBlock"/>
            <xsl:call-template name="Composite"/>
        </xsl:element>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Attribute">
        <xsl:if test="Type/Attribute">
            <xsl:element name="Attribute">
                <xsl:call-template name="Property"/>
                <xsl:call-template name="IndexedProperty"/>
                <xsl:call-template name="Operation"/>
                <xsl:call-template name="ObjectList"/>
                <xsl:call-template name="EventListener"/>
                <xsl:call-template name="Functionality"/>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="BuildingBlock">
        <xsl:if test="Type/BuildingBlock">
            <xsl:element name="BuildingBlock">
                <xsl:call-template name="Aspect"/>
                <xsl:call-template name="Component"/>
                <xsl:call-template name="Interface"/>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Composite">
        <xsl:if test="Type/Composite">
            <xsl:element name="Composite"/>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Property">
        <xsl:if test="Type/Attribute/Property">
            <xsl:element name="Property">
                <xsl:attribute name="status">
                    <xsl:value-of select="Type/Attribute/Property/@status"/>
                </xsl:attribute>
                <xsl:if test="Type/Attribute/Property/@type">
                    <xsl:attribute name="type">
                        <xsl:value-of select="Type/Attribute/Property/@type"/>
                    </xsl:attribute>
                </xsl:if>
                <xsl:if test="Type/Attribute/Property/@name">
                    <xsl:attribute name="name">
                        <xsl:value-of select="Type/Attribute/Property/@name"/>
                    </xsl:attribute>
                </xsl:if>
                <xsl:if test="Type/Attribute/Property/@value">
                    <xsl:attribute name="value">
                        <xsl:value-of select="Type/Attribute/Property/@value"/>
                    </xsl:attribute>
                </xsl:if>
                <xsl:call-template name="Range"/>
                <xsl:call-template name="Enumeration"/>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Range">
        <xsl:if test="Type/Attribute/Property/Range">
            <xsl:element name="Range">
                <xsl:attribute name="minValue">
                    <xsl:value-of select="Type/Attribute/Property/Range/@minValue"/>
                </xsl:attribute>
                <xsl:attribute name="maxValue">
                    <xsl:value-of select="Type/Attribute/Property/Range/@maxValue"/>
                </xsl:attribute>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Enumeration">
        <xsl:if test="Type/Attribute/Property/Enumeration">
            <xsl:element name="Enumeration">
                <xsl:for-each select="Type/Attribute/Property/Enumeration/Item">
                    <xsl:call-template name="Item"/>
                </xsl:for-each>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Item">
        <xsl:element name="Item">
            <xsl:attribute name="value">
                <xsl:value-of select="@value"/>
            </xsl:attribute>
        </xsl:element>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="IndexedProperty">
        <xsl:if test="Type/Attribute/IndexedProperty">
            <xsl:element name="IndexedProperty">
                <xsl:attribute name="status">
                    <xsl:value-of select="Type/Attribute/IndexedProperty/@status"/>
                </xsl:attribute>
                <xsl:if test="Type/Attribute/IndexedProperty/@type">
                    <xsl:attribute name="type">
                        <xsl:value-of select="Type/Attribute/IndexedProperty/@type"/>
                    </xsl:attribute>
                </xsl:if>
                <xsl:if test="Type/Attribute/IndexedProperty/@name">
                    <xsl:attribute name="name">
                        <xsl:value-of select="Type/Attribute/IndexedProperty/@name"/>
                    </xsl:attribute>
                </xsl:if>
                <xsl:if test="Type/Attribute/IndexedProperty/@value">
                    <xsl:attribute name="value">
                        <xsl:value-of select="Type/Attribute/IndexedProperty/@value"/>
                    </xsl:attribute>
                </xsl:if>
                <xsl:if test="Type/Attribute/IndexedProperty/@index">
                    <xsl:attribute name="index">
                        <xsl:value-of select="Type/Attribute/IndexedProperty/@index"/>
                    </xsl:attribute>
                </xsl:if>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Operation">
        <xsl:if test="Type/Attribute/Operation">
            <xsl:element name="Operation">
                <xsl:attribute name="status">
                    <xsl:value-of select="Type/Attribute/Operation/@status"/>
                </xsl:attribute>
                <xsl:if test="Type/Attribute/Operation/@name">
                    <xsl:attribute name="name">
                        <xsl:value-of select="Type/Attribute/Operation/@name"/>
                    </xsl:attribute>
                </xsl:if>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="ObjectList">
        <xsl:if test="Type/Attribute/ObjectList">
            <xsl:element name="ObjectList">
                <xsl:attribute name="status">
                    <xsl:value-of select="Type/Attribute/ObjectList/@status"/>
                </xsl:attribute>
                <xsl:attribute name="type">
                    <xsl:value-of select="Type/Attribute/ObjectList/@type"/>
                </xsl:attribute>
                <xsl:if test="Type/Attribute/ObjectList/@name">
                    <xsl:attribute name="name">
                        <xsl:value-of select="Type/Attribute/ObjectList/@name"/>
                    </xsl:attribute>
                </xsl:if>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="EventListener">
        <xsl:if test="Type/Attribute/EventListener">
            <xsl:element name="EventListener">
                <xsl:attribute name="status">
                    <xsl:value-of select="Type/Attribute/EventListener/@status"/>
                </xsl:attribute>
                <xsl:attribute name="type">
                    <xsl:value-of select="Type/Attribute/EventListener/@type"/>
                </xsl:attribute>
                <xsl:if test="Type/Attribute/EventListener/@name">
                    <xsl:attribute name="name">
                        <xsl:value-of select="Type/Attribute/EventListener/@name"/>
                    </xsl:attribute>
                </xsl:if>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Functionality">
        <xsl:if test="Type/Attribute/Functionality">
            <xsl:element name="Functionality">
                <xsl:attribute name="status">
                    <xsl:value-of select="Type/Attribute/Functionality/@status"/>
                </xsl:attribute>
                <xsl:if test="Type/Attribute/Functionality/@name">
                    <xsl:attribute name="name">
                        <xsl:value-of select="Type/Attribute/Functionality/@name"/>
                    </xsl:attribute>
                </xsl:if>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Aspect">
        <xsl:if test="Type/BuildingBlock/Aspect">
            <xsl:element name="Aspect">
                <xsl:attribute name="status">
                    <xsl:value-of select="Type/BuildingBlock/Aspect/@status"/>
                </xsl:attribute>
                <xsl:attribute name="type">
                    <xsl:value-of select="Type/BuildingBlock/Aspect/@type"/>
                </xsl:attribute>
                <xsl:if test="Type/BuildingBlock/Aspect/@name">
                    <xsl:attribute name="name">
                        <xsl:value-of select="Type/BuildingBlock/Aspect/@name"/>
                    </xsl:attribute>
                </xsl:if>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Component">
        <xsl:if test="Type/BuildingBlock/Component">
            <xsl:element name="Component">
                <xsl:attribute name="status">
                    <xsl:value-of select="Type/BuildingBlock/Component/@status"/>
                </xsl:attribute>
                <xsl:if test="Type/BuildingBlock/Component/@type">
                    <xsl:attribute name="type">
                        <xsl:value-of select="Type/BuildingBlock/Component/@type"/>
                    </xsl:attribute>
                </xsl:if>
                <xsl:if test="Type/BuildingBlock/Component/@name">
                    <xsl:attribute name="name">
                        <xsl:value-of select="Type/BuildingBlock/Component/@name"/>
                    </xsl:attribute>
                </xsl:if>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Interface">
        <xsl:if test="Type/BuildingBlock/Interface">
            <xsl:element name="Interface">
                <xsl:attribute name="status">
                    <xsl:value-of select="Type/BuildingBlock/Interface/@status"/>
                </xsl:attribute>
                <xsl:attribute name="type">
                    <xsl:value-of select="Type/BuildingBlock/Interface/@type"/>
                </xsl:attribute>
                <xsl:if test="Type/BuildingBlock/Interface/@name">
                    <xsl:attribute name="name">
                        <xsl:value-of select="Type/BuildingBlock/Interface/@name"/>
                    </xsl:attribute>
                </xsl:if>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="GroupComment">
        <xsl:if test="GroupComment">
            <xsl:element name="GroupComment">
                <xsl:attribute name="text">
                    <xsl:value-of select="GroupComment/@text"/>
                </xsl:attribute>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="GroupCardinality">
        <xsl:element name="GroupCardinality">
            <xsl:attribute name="GroupCardMin">
                <xsl:value-of select="GroupCardinality/@GroupCardMin"/>
            </xsl:attribute>
            <xsl:attribute name="GroupCardMax">
                <xsl:value-of select="GroupCardinality/@GroupCardMax"/>
            </xsl:attribute>
        </xsl:element>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="AppendFeatureToGroup">
        <xsl:param name="targetGroup"/>
        <xsl:param name="feature"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="AppendGroupToFeature">
        <xsl:param name="targetFeature"/>
        <xsl:param name="group"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Feature">
        <xsl:param name="extension"/>
        <xsl:for-each select="Feature">
            <xsl:variable name="fName" select="@nameOfFeature"/>
            <xsl:element name="Feature">
                <xsl:attribute name="nameOfFeature">
                    <xsl:value-of select="@nameOfFeature"/>
                </xsl:attribute>
                <xsl:call-template name="Description"/>
                <xsl:call-template name="FeatureComment"/>
                <xsl:call-template name="FeatureCardinality"/>
                <xsl:call-template name="Type"/>
                <xsl:for-each select="$extension/AppendGroupToFeature">
                    <xsl:if test="@appendedFeatureName=$fName">
                        <xsl:call-template name="AddGroup"/>
                    </xsl:if>
                </xsl:for-each>
                <xsl:call-template name="Group">
                    <xsl:with-param name="extension" select="$extension"/>
                </xsl:call-template>
            </xsl:element>
        </xsl:for-each>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Group">
        <xsl:param name="extension"/>
        <xsl:for-each select="Group">
            <xsl:variable name="gName" select="@nameOfGroup"/>
            <xsl:element name="Group">
                <xsl:attribute name="nameOfGroup">
                    <xsl:value-of select="@nameOfGroup"/>
                </xsl:attribute>
                <xsl:call-template name="Description"/>
                <xsl:call-template name="GroupComment"/>
                <xsl:choose>
                    <xsl:when test="$extension/AppendFeatureToGroup/ModifyGroupCardinality">
                        <xsl:element name="GroupCardinality">
                            <xsl:attribute name="GroupCardMin">
                                <xsl:value-of select="$extension/AppendFeatureToGroup/ModifyGroupCardinality/@newMinCard"/>
                            </xsl:attribute>
                            <xsl:attribute name="GroupCardMax">
                                <xsl:value-of select="$extension/AppendFeatureToGroup/ModifyGroupCardinality/@newMaxCard"/>
                            </xsl:attribute>
                        </xsl:element>
                    </xsl:when>
                    <xsl:otherwise>
                        <xsl:call-template name="GroupCardinality"/>
                    </xsl:otherwise>
                </xsl:choose>
                <xsl:for-each select="$extension/AppendFeatureToGroup">
                    <xsl:if test="@appendedGroupName=$gName">
                        <xsl:call-template name="AddFeature"/>
                    </xsl:if>
                </xsl:for-each>
                <xsl:call-template name="Feature">
                    <xsl:with-param name="extension" select="$extension"/>
                </xsl:call-template>
                <xsl:call-template name="CallMacro"/>
            </xsl:element>
        </xsl:for-each>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="AddGroup">
        <xsl:for-each select="Group">
            <xsl:element name="Group">
                <xsl:attribute name="nameOfGroup">
                    <xsl:value-of select="@nameOfGroup"/>
                </xsl:attribute>
                <xsl:call-template name="Description"/>
                <xsl:call-template name="GroupComment"/>
                <xsl:call-template name="GroupCardinality"/>
                <xsl:call-template name="AddFeature"/>
                <xsl:call-template name="CallMacro"/>
            </xsl:element>
        </xsl:for-each>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="AddFeature">
        <xsl:for-each select="Feature">
            <xsl:variable name="fName" select="@nameOfFeature"/>
            <xsl:element name="Feature">
                <xsl:attribute name="nameOfFeature">
                    <xsl:value-of select="@nameOfFeature"/>
                </xsl:attribute>
                <xsl:call-template name="Description"/>
                <xsl:call-template name="FeatureComment"/>
                <xsl:call-template name="FeatureCardinality"/>
                <xsl:call-template name="Type"/>
                <xsl:call-template name="AddGroup"/>
            </xsl:element>
        </xsl:for-each>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- This detects Extension element -->
    <xsl:template name="Extension">
        <xsl:if test="Extension">
            <xsl:variable name="extensionTree" select="Extension"/>
            <xsl:element name="Macro">
                <xsl:attribute name="nameOfMacro">
                    <xsl:value-of select="@nameOfMacro"/>
                </xsl:attribute>
                <xsl:variable name="mName" select="Extension/@macroName"/>
                <xsl:for-each select="//Macro[@nameOfMacro=$mName]">
                    <xsl:call-template name="Feature">
                        <xsl:with-param name="extension" select="$extensionTree"/>
                    </xsl:call-template>
                </xsl:for-each>
            </xsl:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="CallMacro">
        <xsl:for-each select="CallMacro">
            <xsl:element name="CallMacro">
                <xsl:attribute name="nameOfCalledMacro">
                    <xsl:value-of select="@nameOfCalledMacro"/>
                </xsl:attribute>
                <xsl:call-template name="CallMacroComment"/>
            </xsl:element>
        </xsl:for-each>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="CallMacroComment">
        <xsl:if test="CallMacro/CallMacroComment">
            <xsl:element name="CallMacroComment">
                <xsl:attribute name="text">
                    <xsl:value-of select="CallMacro/CallMacroComment/@text"/>
                </xsl:attribute>
            </xsl:element>
        </xsl:if>
    </xsl:template>
</xsl:stylesheet>

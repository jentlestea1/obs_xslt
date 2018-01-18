<?xml version="1.0" encoding="UTF-8"?>
<!-- The task of this stylesheet is to transform a framework description made in XML into applicaction XML schema. -->
<!-- by Vaclav Cechticky (Automatic Control Laboratory ETH Zuerich) -->
<xsl:stylesheet version="1.1" xmlns:xs="http://www.w3.org/2001/XMLSchema"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" exclude-result-prefixes="xsi">
    <xsl:output method="xml"/>
    <!-- ========================================================================= -->
    <!-- The template matches any node. -->
    <xsl:template match="/">
        <xs:schema elementFormDefault="qualified" attributeFormDefault="unqualified">
            <xsl:apply-templates/>
            <xsl:call-template name="CreateDescriptionElement"/>
        </xs:schema>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template matches Feature element. -->
    <xsl:template match="Feature">
        <xsl:call-template name="ProcessFeature"/>
        <xsl:apply-templates/>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template matches Group element -->
    <xsl:template match="Group">
        <!-- create a new group -->
        <xs:group name="{@nameOfGroup}">
            <!-- ========================================================================= -->
            <!-- It processes a group cardinality in case that the minimal cardinality is 1 and maximal 1 -->
            <xsl:if test="(GroupCardinality/@GroupCardMin=1) and (GroupCardinality/@GroupCardMax=1)">
                <xsl:if test="count(child::Feature | child::CallMacro)=1">
                    <xsl:if test="(count(child::Feature)=1) and (count(child::CallMacro)=0)">
                        <xs:sequence>
                            <xsl:for-each select="Feature">
                                <xsl:call-template name="RefFeature"/>
                            </xsl:for-each>
                        </xs:sequence>
                    </xsl:if>
                    <xsl:if test="(count(child::Feature)=0) and (count(child::CallMacro)=1)">
                        <xs:sequence>
                            <xsl:for-each select="CallMacro">
                                <xsl:call-template name="RefCallMacro"/>
                            </xsl:for-each>
                        </xs:sequence>
                    </xsl:if>
                </xsl:if>
                <xsl:if test="count(child::Feature | child::CallMacro)&gt;1">
                    <xs:choice>
                        <xsl:for-each select="Feature">
                            <xsl:call-template name="RefFeature"/>
                        </xsl:for-each>
                        <xsl:for-each select="CallMacro">
                            <xsl:call-template name="RefCallMacro"/>
                        </xsl:for-each>
                    </xs:choice>
                </xsl:if>
            </xsl:if>
            <!-- ========================================================================= -->
            <!-- It processes a group cardinality in case that the minimal cardinality is 1 and maximal bigger than 1 -->
            <xsl:if test="(GroupCardinality/@GroupCardMin&gt;=1) and (GroupCardinality/@GroupCardMax&gt;1)">  
                <xs:choice>
                    <xsl:call-template name="ExpandGroupCardinality">
                        <xsl:with-param name="minCard" select="GroupCardinality/@GroupCardMin"/>
                        <xsl:with-param name="maxCard" select="GroupCardinality/@GroupCardMax"/>
                    </xsl:call-template>
                </xs:choice>
            </xsl:if>
            <!-- ========================================================================= -->
            <!-- It processes a group cardinality in case that the minimal cardinality is 0 and maximal equal or bigger than 1 -->
            <xsl:if test="(GroupCardinality/@GroupCardMin=0) and (GroupCardinality/@GroupCardMax&gt;=1)">
                <xs:choice>
                    <xsl:call-template name="ExpandGroupCardinality">
                        <xsl:with-param name="minCard" select="1"/>
                        <xsl:with-param name="maxCard" select="GroupCardinality/@GroupCardMax"/>
                    </xsl:call-template>
                </xs:choice>
            </xsl:if>
        </xs:group>
        <xsl:apply-templates/>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template makes all possible combinations of features defined in a group based on group cardinality. -->
    <xsl:template name="ExpandGroupCardinality">
        <!-- store minimal group cardinality -->
        <xsl:param name="minCard"/>
        <!-- store maximal group cardinality -->
        <xsl:param name="maxCard"/>
        <xsl:variable name="minCombinationLength" select="$minCard"/>
        <xsl:variable name="maxCombinationLength" select="$maxCard"/>
        <!-- the current length of the combination -->
        <xsl:variable name="currentLength" select="1"/>
        <!-- The loop makes combinations for each feature or callmacro that is direct child of the group element,
		the length of combinations is driven by minimal and maximal combination length. -->
        <xsl:for-each select="Feature | CallMacro">
            <xsl:if test="count(following-sibling::Feature | following-sibling::CallMacro)&gt;=($minCombinationLength+(-1))">
                <xs:sequence>
                    <xsl:if test="@nameOfFeature">
                        <xsl:call-template name="RefFeature"/>
                    </xsl:if>
                    <xsl:if test="@nameOfCalledMacro">
                        <xsl:call-template name="RefCallMacro"/>
                    </xsl:if>
                    <xsl:if test="count(following-sibling::Feature | following-sibling::CallMacro)&gt;=1">
                        <!-- it calls template where the combination are made by recursion -->
                        <xsl:call-template name="MakeCombinations">
                            <xsl:with-param name="list" select="following-sibling::Feature | following-sibling::CallMacro"/>
                            <xsl:with-param name="minCombinationLength" select="$minCombinationLength"/>
                            <xsl:with-param name="maxCombinationLength" select="$maxCombinationLength"/>
                            <xsl:with-param name="currentLength" select="$currentLength+1"/>
                        </xsl:call-template>
                    </xsl:if>
                </xs:sequence>
            </xsl:if>
        </xsl:for-each>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template MakeCombinations is called from ExpandGroupCardinality template. MakeCombination makes the combination by recursion. -->
    <xsl:template name="MakeCombinations">
        <xsl:param name="list"/>
        <xsl:param name="minCombinationLength"/>
        <xsl:param name="maxCombinationLength"/>
        <xsl:param name="currentLength"/>
        <xsl:if test="($minCombinationLength&gt;=$currentLength) and ($maxCombinationLength&gt;$currentLength) and count($list)&gt;=1">
            <xs:choice>
                <xsl:for-each select="$list">
                    <xsl:if test="(count(following-sibling::Feature | following-sibling::CallMacro)&gt;=($maxCombinationLength+(-$currentLength))) or (count(following-sibling::Feature | following-sibling::CallMacro)&gt;=($minCombinationLength+(-$currentLength)))">
                        <xs:sequence>
                            <xsl:if test="@nameOfFeature">
                                <xsl:call-template name="RefFeature"/>
                            </xsl:if>
                            <xsl:if test="@nameOfCalledMacro">
                                <xsl:call-template name="RefCallMacro"/>
                            </xsl:if>
                            <xsl:call-template name="MakeCombinations">
                                <xsl:with-param name="list" select="following-sibling::Feature | following-sibling::CallMacro"/>
                                <xsl:with-param name="minCombinationLength" select="$minCombinationLength"/>
                                <xsl:with-param name="maxCombinationLength" select="$maxCombinationLength"/>
                                <xsl:with-param name="currentLength" select="$currentLength+1"/>
                            </xsl:call-template>
                        </xs:sequence>
                    </xsl:if>
                </xsl:for-each>
            </xs:choice>            
        </xsl:if>    
        <xsl:if test="($minCombinationLength&lt;$currentLength) and ($maxCombinationLength&gt;$currentLength) and count($list)&gt;=1">
            <xs:choice minOccurs="0">
                <xsl:for-each select="$list">
                    <xsl:if test="(count(following-sibling::Feature | following-sibling::CallMacro)&gt;=($maxCombinationLength+(-$currentLength))) or (count(following-sibling::Feature | following-sibling::CallMacro)&gt;=($minCombinationLength+(-$currentLength)))">
                        <xs:sequence>
                            <xsl:if test="@nameOfFeature">
                                <xsl:call-template name="RefFeature"/>
                            </xsl:if>
                            <xsl:if test="@nameOfCalledMacro">
                                <xsl:call-template name="RefCallMacro"/>
                            </xsl:if>
                            <xsl:call-template name="MakeCombinations">
                                <xsl:with-param name="list" select="following-sibling::Feature | following-sibling::CallMacro"/>
                                <xsl:with-param name="minCombinationLength" select="$minCombinationLength"/>
                                <xsl:with-param name="maxCombinationLength" select="$maxCombinationLength"/>
                                <xsl:with-param name="currentLength" select="$currentLength+1"/>
                            </xsl:call-template>
                        </xs:sequence>
                    </xsl:if>
                </xsl:for-each>
            </xs:choice>
        </xsl:if>
        <xsl:if test="($currentLength=$maxCombinationLength) and ($minCombinationLength=$maxCombinationLength) and count($list)&gt;=1">
            <xs:choice>
                <xsl:for-each select="$list">
                    <xsl:if test="@nameOfFeature">
                        <xsl:call-template name="RefFeature"/>
                    </xsl:if>
                    <xsl:if test="@nameOfCalledMacro">
                        <xsl:call-template name="RefCallMacro"/>
                    </xsl:if>
                </xsl:for-each>
            </xs:choice>
        </xsl:if>        
        <xsl:if test="($currentLength=$maxCombinationLength) and ($minCombinationLength&lt;$maxCombinationLength) and count($list)&gt;=1">
            <xs:choice minOccurs="0">
                <xsl:for-each select="$list">
                    <xsl:if test="@nameOfFeature">
                        <xsl:call-template name="RefFeature"/>
                    </xsl:if>
                    <xsl:if test="@nameOfCalledMacro">
                        <xsl:call-template name="RefCallMacro"/>
                    </xsl:if>
                </xsl:for-each>
            </xs:choice>
        </xsl:if>        
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- ProcessFeature template processes the tag 'Feature'. -->
    <xsl:template name="ProcessFeature">
        <xs:element name="{@nameOfFeature}">
            <!-- process feature properties, description, group and type -->
            <xsl:call-template name="Description"/>
            <xs:complexType>
                <xs:sequence>
                    <!-- it makes a  reference to globally defined 'Description' element -->
                    <xs:element ref="Description" minOccurs="0"/>
                    <xsl:for-each select="Group">
                        <xsl:choose>
                            <xsl:when test="(GroupCardinality/@GroupCardMin=0) and (GroupCardinality/@GroupCardMax&gt;=1)">
                                <xs:group ref="{@nameOfGroup}" minOccurs="0"/>
                            </xsl:when>
                            <xsl:otherwise>
                                <!-- it makes a  reference to globally defined group element -->
                                <xs:group ref="{@nameOfGroup}"/>
                            </xsl:otherwise>
                        </xsl:choose>
                    </xsl:for-each>
                </xs:sequence>
                <!-- This calls 'Type' template that is further processing different subtypes. -->
                <xsl:call-template name="Type"/>
                <xs:attribute name="comment" use="optional" type="xs:string"/>
            </xs:complexType>
        </xs:element>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- RefFeature template processes the tag 'Feature'. -->
    <xsl:template name="RefFeature">
        <xsl:if test="(FeatureCardinality/@FeatureCardMax&gt;=1)">
            <xs:element ref="{@nameOfFeature}">
                <xsl:attribute name="minOccurs">
                    <xsl:value-of select="FeatureCardinality/@FeatureCardMin"/>
                </xsl:attribute>
                <xsl:attribute name="maxOccurs">
                    <xsl:value-of select="FeatureCardinality/@FeatureCardMax"/>
                </xsl:attribute>
            </xs:element>
        </xsl:if>
        <xsl:if test="(FeatureCardinality/@FeatureCardMax='+') or (FeatureCardinality/@FeatureCardMax='*')">
            <xs:element ref="{@nameOfFeature}">
                <xsl:attribute name="minOccurs">
                    <xsl:value-of select="FeatureCardinality/@FeatureCardMin"/>
                </xsl:attribute>
                <xsl:attribute name="maxOccurs">
                    <xsl:value-of select="'unbounded'"/>
                </xsl:attribute>
            </xs:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- RefFeatureMinZero template processes the tag 'Feature'. -->
    <xsl:template name="RefFeatureMinOccursZero">
        <xsl:if test="(FeatureCardinality/@FeatureCardMax&gt;=1)">
            <xs:element ref="{@nameOfFeature}">
                <xsl:attribute name="minOccurs">
                    <xsl:value-of select="0"/>
                </xsl:attribute>
                <xsl:attribute name="maxOccurs">
                    <xsl:value-of select="FeatureCardinality/@FeatureCardMax"/>
                </xsl:attribute>
            </xs:element>
        </xsl:if>
        <xsl:if test="(FeatureCardinality/@FeatureCardMax='+') or (FeatureCardinality/@FeatureCardMax='*')">
            <xs:element ref="{@nameOfFeature}">
                <xsl:attribute name="minOccurs">
                    <xsl:value-of select="0"/>
                </xsl:attribute>
                <xsl:attribute name="maxOccurs">
                    <xsl:value-of select="'unbounded'"/>
                </xsl:attribute>
            </xs:element>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- RefCallMacro template processes the tag 'CallMacro'. -->
    <xsl:template name="RefCallMacro">
        <xsl:variable name="mName" select="@nameOfCalledMacro"/>
        <xsl:for-each select="//Macro[@nameOfMacro=$mName]">
            <xsl:for-each select="Feature">
                <xsl:call-template name="RefFeature"/>
            </xsl:for-each>
        </xsl:for-each>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- RefCallMacroMinOccursZero template processes the tag 'CallMacro'. -->
    <xsl:template name="RefCallMacroMinOccursZero">
        <xsl:variable name="mName" select="@nameOfCalledMacro"/>
        <xsl:for-each select="//Macro[@nameOfMacro=$mName]">
            <xsl:for-each select="Feature">
                <xsl:call-template name="RefFeatureMinOccursZero"/>
            </xsl:for-each>
        </xsl:for-each>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Type">
        <xsl:if test="Type/Attribute">
            <xsl:call-template name="Attribute"/>
        </xsl:if>
        <xsl:if test="Type/BuildingBlock">
            <xsl:call-template name="BuildingBlock"/>
        </xsl:if>
        <xsl:if test="Type/Composite">
            <xsl:call-template name="Composite"/>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Attribute">
        <xsl:if test="Type/Attribute/Property">
            <xsl:call-template name="Property"/>
        </xsl:if>
        <xsl:if test="Type/Attribute/IndexedProperty">
            <xsl:call-template name="IndexedProperty"/>
        </xsl:if>
        <xsl:if test="Type/Attribute/Operation">
            <xsl:call-template name="Operation"/>
        </xsl:if>
        <xsl:if test="Type/Attribute/ObjectList">
            <xsl:call-template name="ObjectList"/>
        </xsl:if>
        <xsl:if test="Type/Attribute/EventListener">
            <xsl:call-template name="EventListener"/>
        </xsl:if>
        <xsl:if test="Type/Attribute/Functionality">
            <xsl:call-template name="Functionality"/>
        </xsl:if>        
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="BuildingBlock">
        <xsl:if test="Type/BuildingBlock/Aspect">
            <xsl:call-template name="Aspect"/>
        </xsl:if>
        <xsl:if test="Type/BuildingBlock/Component">
            <xsl:call-template name="Component"/>
        </xsl:if>
        <xsl:if test="Type/BuildingBlock/Interface">
            <xsl:call-template name="Interface"/>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Composite"/>
    <!-- ========================================================================= -->
    <xsl:template name="Property">
        <xs:attribute name="kind" use="required" fixed="property"/>
        <xsl:if test="Type/Attribute/Property/@status = 'provided' ">
            <xsl:choose>
                <xsl:when test="Type/Attribute/Property/@name">
                    <xs:attribute name="name" use="required" fixed="{Type/Attribute/Property/@name}"/>
                </xsl:when>
                <xsl:otherwise>
                    <xs:attribute name="name" use="optional"/>
                </xsl:otherwise>
            </xsl:choose>
            <xsl:choose>
                <xsl:when test="Type/Attribute/Property/@type">
                    <xs:attribute name="type" use="required" fixed="{Type/Attribute/Property/@type}"/>
                </xsl:when>
                <xsl:otherwise>
                    <xs:attribute name="type" use="required"/>
                </xsl:otherwise>
            </xsl:choose>
            <xsl:choose>
                <xsl:when test="Type/Attribute/Property/@value">
                    <xsl:if test="not(Type/Attribute/Property/Enumeration)">
                        <xs:attribute name="value" use="required" fixed="{Type/Attribute/Property/@value}"/>
                    </xsl:if>
                    <xsl:if test="Type/Attribute/Property/Enumeration">
                        <xs:attribute name="value" use="required">
                            <xs:simpleType>
                                <xs:restriction base="xs:string">
                                    <xsl:for-each select="Type/Attribute/Property/Enumeration/Item">
                                        <xs:enumeration value="{@value}"/>
                                    </xsl:for-each>
                                </xs:restriction>
                            </xs:simpleType>
                        </xs:attribute>
                    </xsl:if>
                </xsl:when>
                <xsl:otherwise>
                    <xs:attribute name="value" use="required"/>
                </xsl:otherwise>
            </xsl:choose>
        </xsl:if>
        <xsl:if test="Type/Attribute/Property/Range">
            <xs:attribute name="minValue" use="required" fixed="{Type/Attribute/Property/Range/@minValue}"/>
            <xs:attribute name="maxValue" use="required" fixed="{Type/Attribute/Property/Range/@maxValue}"/>
        </xsl:if>
        <xs:attribute name="status" use="required" fixed="{Type/Attribute/Property/@status}"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="IndexedProperty">
        <xs:attribute name="kind" use="required" fixed="indexed_property"/>
        <xsl:choose>
            <xsl:when test="Type/Attribute/IndexedProperty/@name">
                <xs:attribute name="name" use="required" fixed="{Type/Attribute/IndexedProperty/@name}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="name" use="optional"/>
            </xsl:otherwise>
        </xsl:choose>
        <xsl:choose>
            <xsl:when test="Type/Attribute/IndexedProperty/@type">
                <xs:attribute name="type" use="required" fixed="{Type/Attribute/IndexedProperty/@type}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="type" use="required"/>
            </xsl:otherwise>
        </xsl:choose>
        <xsl:choose>
            <xsl:when test="Type/Attribute/IndexedProperty/@value">
                <xs:attribute name="value" use="required" fixed="{Type/Attribute/IndexedProperty/@value}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="value" use="required"/>
            </xsl:otherwise>
        </xsl:choose>
        <xsl:choose>
            <xsl:when test="Type/Attribute/IndexedProperty/@index">
                <xs:attribute name="index" use="required" fixed="{Type/Attribute/IndexedProperty/@index}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="index" use="required"/>
            </xsl:otherwise>
        </xsl:choose>
        <xs:attribute name="status" use="required" fixed="{Type/Attribute/IndexedProperty/@status}"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Operation">
        <xs:attribute name="kind" use="required" fixed="operation"/>
        <xsl:choose>
            <xsl:when test="Type/Attribute/Operation/@name">
                <xs:attribute name="name" use="required" fixed="{Type/Attribute/Operation/@name}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="name" use="optional"/>
            </xsl:otherwise>
        </xsl:choose>
        <xs:attribute name="status" use="required" fixed="{Type/Attribute/Operation/@status}"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="ObjectList">
        <xs:attribute name="kind" use="required" fixed="object_list"/>
        <xsl:choose>
            <xsl:when test="Type/Attribute/ObjectList/@name">
                <xs:attribute name="name" use="required" fixed="{Type/Attribute/ObjectList/@name}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="name" use="optional"/>
            </xsl:otherwise>
        </xsl:choose>
        <xsl:choose>
            <xsl:when test="Type/Attribute/ObjectList/@type">
                <xs:attribute name="type" use="required" fixed="{Type/Attribute/ObjectList/@type}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="type" use="required"/>
            </xsl:otherwise>
        </xsl:choose>
        <xs:attribute name="status" use="required" fixed="{Type/Attribute/ObjectList/@status}"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="EventListener">
        <xs:attribute name="kind" use="required" fixed="event_listener"/>
        <xsl:choose>
            <xsl:when test="Type/Attribute/EventListener/@name">
                <xs:attribute name="name" use="required" fixed="{Type/Attribute/EventListener/@name}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="name" use="optional"/>
            </xsl:otherwise>
        </xsl:choose>
        <xsl:choose>
            <xsl:when test="Type/Attribute/EventListener/@type">
                <xs:attribute name="type" use="required" fixed="{Type/Attribute/EventListener/@type}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="type" use="required"/>
            </xsl:otherwise>
        </xsl:choose>
        <xs:attribute name="status" use="required" fixed="{Type/Attribute/EventListener/@status}"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Functionality">
        <xs:attribute name="kind" use="required" fixed="functionality"/>
        <xsl:choose>
            <xsl:when test="Type/Attribute/Functionality/@name">
                <xs:attribute name="name" use="required" fixed="{Type/Attribute/Functionality/@name}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="name" use="optional"/>
            </xsl:otherwise>
        </xsl:choose>
        <xs:attribute name="status" use="required" fixed="{Type/Attribute/Functionality/@status}"/>
    </xsl:template>    
    <!-- ========================================================================= -->
    <xsl:template name="Aspect">
        <xs:attribute name="kind" use="required" fixed="aspect"/>
        <xsl:choose>
            <xsl:when test="Type/BuildingBlock/Aspect/@name">
                <xs:attribute name="name" use="required" fixed="{Type/BuildingBlock/Aspect/@name}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="name" use="optional"/>
            </xsl:otherwise>
        </xsl:choose>
        <xs:attribute name="type" use="required" fixed="{Type/BuildingBlock/Aspect/@type}"/>
        <xs:attribute name="status" use="required" fixed="{Type/BuildingBlock/Aspect/@status}"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Component">
        <xs:attribute name="kind" use="required" fixed="component"/>
        <xsl:choose>
            <xsl:when test="Type/BuildingBlock/Component/@name">
                <xs:attribute name="name" use="required" fixed="{Type/BuildingBlock/Component/@name}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="name" use="optional"/>
            </xsl:otherwise>
        </xsl:choose>
        <xsl:choose>
            <xsl:when test="Type/BuildingBlock/Component/@type">
                <xs:attribute name="type" use="required" fixed="{Type/BuildingBlock/Component/@type}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="type" use="required"/>
            </xsl:otherwise>
        </xsl:choose>
        <xs:attribute name="status" use="required" fixed="{Type/BuildingBlock/Component/@status}"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <xsl:template name="Interface">
        <xs:attribute name="kind" use="required" fixed="interface"/>
        <xsl:choose>
            <xsl:when test="Type/BuildingBlock/Interface/@name">
                <xs:attribute name="name" use="required" fixed="{Type/BuildingBlock/Interface/@name}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="name" use="optional"/>
            </xsl:otherwise>
        </xsl:choose>
        <xsl:choose>
            <xsl:when test="Type/BuildingBlock/Interface/@type">
                <xs:attribute name="type" use="required" fixed="{Type/BuildingBlock/Interface/@type}"/>
            </xsl:when>
            <xsl:otherwise>
                <xs:attribute name="type" use="required"/>
            </xsl:otherwise>
        </xsl:choose>
        <xs:attribute name="status" use="required" fixed="{Type/BuildingBlock/Interface/@status}"/>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- Description template extracts information from feature types and write them into 'annotation' element. -->
    <xsl:template name="Description">
        <xs:annotation>
            <xs:documentation>
                <xsl:value-of select="Description/@text"/>
                <xsl:call-template name="PropertyDescription"/>
                <xsl:call-template name="PropertyEnumerationDescription"/>
                <xsl:call-template name="PropertyRangeDescription"/>
                <xsl:call-template name="OperationDescription"/>
                <xsl:call-template name="ObjectListDescription"/>
                <xsl:call-template name="EventListenerDescription"/>
                <xsl:call-template name="ComponentDescription"/>
                <xsl:call-template name="InterfaceDescription"/>
                <xsl:call-template name="AspectDescription"/>
            </xs:documentation>
        </xs:annotation>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template extracts information about a feature that is type property. This information usually becomes a part of more complex description. -->
    <xsl:template name="PropertyDescription">
        <xsl:if
            test="(Type/Attribute/Property) and (not(Type/Attribute/Property/Range)) and (not(Type/Attribute/Property/Enumeration))">
            The feature is type property. </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template extracts information about a feature that is type operation. This information usually becomes a part of more complex description. -->
    <xsl:template name="OperationDescription">
        <xsl:if test="Type/Attribute/Operation"> The feature is type operation.</xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template extracts information about a feature that is type object list. This information usually becomes a part of more complex description. -->
    <xsl:template name="ObjectListDescription">
        <xsl:if test="Type/Attribute/ObjectList"> The feature is type object list. </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template extracts information about a feature that is type event listener. This information usually becomes a part of more complex description. -->
    <xsl:template name="EventListenerDescription">
        <xsl:if test="Type/Attribute/EventListener"> The feature is type event listener. </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template extracts information about a feature that is type property range. This information usually becomes a part of more complex description. -->
    <xsl:template name="PropertyRangeDescription">
        <xsl:if
            test="(Type/Attribute/Property/Range/@minValue != '+') and          (Type/Attribute/Property/Range/@maxValue != '+')">
            The feature is type property range. The minimal inclusive range value is: <xsl:value-of
            select="Type/Attribute/Property/Range/@minValue"/> The maximal range value is:
                <xsl:value-of select="Type/Attribute/Property/Range/@maxValue"/>
        </xsl:if>
        <xsl:if
            test="(Type/Attribute/Property/Range/@minValue = '+') and          (Type/Attribute/Property/Range/@maxValue != '+')">
            The feature is type property range. The minimal inclusive range value is: -infinity The
            maximal range value is: <xsl:value-of select="Type/Attribute/Property/Range/@maxValue"/>
        </xsl:if>
        <xsl:if
            test="(Type/Attribute/Property/Range/@minValue != '+') and          (Type/Attribute/Property/Range/@maxValue = '+')">
            The feature is type property range. The minimal inclusive range value is: <xsl:value-of
            select="Type/Attribute/Property/Range/@minValue"/> The maximal range value is: infinity </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template extracts information about a feature that is type discrete. This information usually becomes a part of more complex description. -->
    <xsl:template name="PropertyEnumerationDescription">
        <xsl:if test="Type/Attribute/Property/Enumeration"> The feature is type property containing
            discrete values. The developer can select one of the following values: <xsl:for-each select="Type/Attribute/Property/Enumeration/Item">
                <xsl:value-of select="@value"/>, </xsl:for-each>
        </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template extracts information about a feature that is type component. This information usually becomes a part of more complex description. -->
    <xsl:template name="ComponentDescription">
        <xsl:if test="Type/BuildingBlock/Component/@status = 'provided' "> The feature is type component. The component already exists and its type is provided, the developer has to define the instance name. </xsl:if>
        <xsl:if
            test="(Type/BuildingBlock/Component/@status = 'generable') or     (Type/BuildingBlock/Component/@status = 'missing')"> The feature is type component. The component does not exist, the developer has to define the component type name and the instance name.</xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template extracts information about a feature that is type interface. This information usually becomes a part of more complex description. -->
    <xsl:template name="InterfaceDescription">
        <xsl:if test="Type/BuildingBlock/Interface/@status = 'provided' "> The feature is type interface. The interface already exists and its type is provided, the developer has to define the instance name. </xsl:if>
        <xsl:if
            test="(Type/BuildingBlock/Interface/@status = 'generable') or     (Type/BuildingBlock/Interface/@status = 'missing')"> The feature is type interface. The component does not exist, the developer has to define the component type name and the instance name. </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template extracts information about a feature that is type aspect. This information usually becomes a part of more complex description. -->
    <xsl:template name="AspectDescription">
        <xsl:if test="Type/BuildingBlock/Aspect/@status = 'provided' "> The feature is type aspect. The aspect already exists and its type is provided, the developer has to define the instance name. </xsl:if>
        <xsl:if
            test="(Type/BuildingBlock/Aspect/@status = 'generable') or     (Type/BuildingBlock/Aspect/@status = 'missing')"> The feature is type aspect. The component does not exist, the developer has to define the aspect type name and the instance name. </xsl:if>
    </xsl:template>
    <!-- ========================================================================= -->
    <!-- The template creates a global element called 'Description' where the developer of an application can write any commnets.  -->
    <xsl:template name="CreateDescriptionElement">
        <xs:element name="Description">
            <xs:complexType mixed="true">
                <xs:sequence>
                    <xs:any minOccurs="0" processContents="lax"/>
                </xs:sequence>
            </xs:complexType>
        </xs:element>
    </xsl:template>
</xsl:stylesheet>

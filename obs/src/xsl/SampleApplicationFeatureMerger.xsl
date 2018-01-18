<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml"/>
    
    <!--
          This program processes the feature models of  parts of the sample application for the OBS Framework and
          merges them together into a single file representing the sample application model
     -->
           
    <xsl:variable name="sampleFullDataPool" select="document('../xml/SampleFullDataPool.xml')"/>
    <xsl:variable name="sampleR2Database" select="document('../xml/SampleR2Database.xml')"/>
    <xsl:variable name="sampleFSM" select="document('../xml/SampleFSM.xml')"/>
    <xsl:variable name="sampleControlActions" select="document('../xml/SampleControlActions.xml')"/>
    <xsl:variable name="sampleObsClock" select="document('../xml/SampleObsClock.xml')"/>
    <xsl:variable name="sampleEventRepository" select="document('../xml/SampleEventRepository.xml')"/>
    <xsl:variable name="sampleTracer" select="document('../xml/SampleTracer.xml')"/>
    <xsl:variable name="sampleManoeuvres" select="document('../xml/SampleManoeuvres.xml')"/>
    <xsl:variable name="sampleTelecommands" select="document('../xml/SampleTelecommands.xml')"/>
    <xsl:variable name="sampleTelemetryPackets" select="document('../xml/SampleTelemetryPackets.xml')"/>

    <!-- ================================================================================================== -->

    <xsl:template match="/">
        <ObsApplication xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">

            <xsl:for-each select="$sampleFullDataPool/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>

            <xsl:for-each select="$sampleR2Database/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>

            <xsl:for-each select="$sampleFSM/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>

            <xsl:for-each select="$sampleControlActions/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>

            <xsl:for-each select="$sampleObsClock/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
        
            <xsl:for-each select="$sampleEventRepository/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
        
            <xsl:for-each select="$sampleTracer/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>

            <xsl:for-each select="$sampleManoeuvres/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>

            <xsl:for-each select="$sampleTelecommands/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>

            <xsl:for-each select="$sampleTelemetryPackets/ObsApplication/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>

        </ObsApplication>
    </xsl:template>
</xsl:stylesheet>

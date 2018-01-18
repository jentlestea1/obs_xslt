<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml"/>
    <!--load the merge file -->
    <xsl:variable name="extDoc1" select="document('../xml/FeatureObsApplication.xml')"/>
    <xsl:variable name="extDoc2" select="document('../xml/FeatureControllerManagement.xml')"/>
    <xsl:variable name="extDoc3" select="document('../xml/FeatureDataPool.xml')"/>
    <xsl:variable name="extDoc4" select="document('../xml/FeatureDefaultAttributes.xml')"/>
    <xsl:variable name="extDoc5" select="document('../xml/FeatureFSM.xml')"/>
    <xsl:variable name="extDoc6" select="document('../xml/FeatureFsmStates.xml')"/>
    <xsl:variable name="extDoc7" select="document('../xml/FeatureFsmEvents.xml')"/>
    <xsl:variable name="extDoc8" select="document('../xml/FeatureIndexedDatabase.xml')"/>
    <xsl:variable name="extDoc9" select="document('../xml/FeatureIndexedDataPool.xml')"/>
    <xsl:variable name="extDoc10" select="document('../xml/FeatureModeManager.xml')"/>
    <xsl:variable name="extDoc11" select="document('../xml/FeatureMonitoringProfiles.xml')"/>
    <xsl:variable name="extDoc12" select="document('../xml/FeatureControlActions.xml')"/>
    <xsl:variable name="extDoc13" select="document('../xml/FeatureParameterDatabase.xml')"/>
    <xsl:variable name="extDoc14" select="document('../xml/FeatureRecoveryActions.xml')"/>
    <xsl:variable name="extDoc15" select="document('../xml/FeatureDataItems.xml')"/>
    <xsl:variable name="extDoc16" select="document('../xml/FeatureManoeuvreManagement.xml')"/>
    <xsl:variable name="extDoc17" select="document('../xml/FeatureTelecommandManagement.xml')"/>
    <xsl:variable name="extDoc18" select="document('../xml/FeaturePUSTelecommands.xml')"/>
    <xsl:variable name="extDoc19" select="document('../xml/FeatureStandardTelecommands.xml')"/>
    <xsl:variable name="extDoc20" select="document('../xml/FeatureTelemetryManagement.xml')"/>
    <xsl:variable name="extDoc21" select="document('../xml/FeaturePUSTelemetryPackets.xml')"/>
    <xsl:variable name="extDoc22" select="document('../xml/FeatureStandardTelemetryPackets.xml')"/>
    <xsl:variable name="extDoc23" select="document('../xml/FeatureTelemetryStream.xml')"/>
    <xsl:variable name="extDoc24" select="document('../xml/FeaturePunctualActions.xml')"/>
    <xsl:variable name="extDoc25" select="document('../xml/FeatureObsClock.xml')"/>
    <xsl:variable name="extDoc26" select="document('../xml/FeatureFDIRManagement.xml')"/>
    <xsl:variable name="extDoc27" select="document('../xml/FeatureFDIRChecks.xml')"/>
    <xsl:variable name="extDoc28" select="document('../xml/FeatureEventRepository.xml')"/>
    <xsl:variable name="extDoc29" select="document('../xml/FeatureTracer.xml')"/>
    <!-- ================================================================================================== -->
    <!-- This matches any node -->
    <xsl:template match="/">
        <FrameworkFeatureModel>
            <xsl:for-each select="$extDoc1/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc2/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc3/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc4/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc5/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc6/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc7/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc8/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc9/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc10/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc11/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc12/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc13/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc14/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc15/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc16/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc17/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc18/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc19/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc20/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc21/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc22/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc23/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc24/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc25/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc26/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc27/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc28/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
            <xsl:for-each select="$extDoc29/FrameworkFeatureModel/child::*">
                <xsl:copy-of select="."/>
            </xsl:for-each>
        </FrameworkFeatureModel>
    </xsl:template>
</xsl:stylesheet>

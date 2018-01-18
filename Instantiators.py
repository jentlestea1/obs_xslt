# -*- coding: utf-8 -*-
import lxml.etree as ET

#先测试一部分，找思路
#------------------------------------------------------------------------------
#自动生成.h/.cpp文件，默认的代码生成地址为: /Projects/ObsFramework/src/cpp/

#xml model
#xml_filename = "/Users/yabo/ObsFramework_0_8_3/src/xml/MatlabCopyPID.xml" 
#xml_filename = "/Users/yabo/ObsFramework_0_8_3/models/xml/FeatureManoeuvreManagement.xml"


#xml_filename = "/Users/yabo/ObsFramework_0_8_3/src/xml/MatlabCopyPID.xml" 
#xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateMatlabWrapperBody.xsl"  


#xml_filename = "/Users/yabo/ObsFramework_0_8_3/src/xml/SampleFSM.xml"
#xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateFsmState.xsl"

#xml_filename = "/Users/yabo/ObsFramework_0_8_3/src/xml/SampleControlActions_n.xml"
#xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateControlBlock.xsl"


#xml_filename = "/Users/yabo/ObsFramework_0_8_3/src/xml/SampleApplicationModel.xml"
#xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateComponentFactoryHeader.xsl"

#scripts/buildSampleApplication.xml

#可以正常生成，但是要找到对应的xml和xsl


#数据池
#xml_filename = "/Users/yabo/ObsFramework_0_8_3/src/xml/SampleMonitoredDataPool.xml"
#xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateDataPoolBody.xsl"
#xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateComponentFactoryInclude.xsl"






#xsl programe
#xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateMatlabWrapperBody.xsl"  
#xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateComponentFactoryHeader.xsl"
#xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateComponentFactoryBody.xsl"

#wangshaobo 测试部分
#1#
#xml_filename = "./obs/src/xml/SampleApplicationModel.xml"
#xsl_filename = "./obs/src/xsl/GenerateParameterDatabaseHeader.xsl"
#xml_filename = "./obs/src/xml/SampleApplicationModel.xml"
##xsl_filename = "/Users/yabo/ObsFramework_0_8_3/src/xsl/GenerateParameterDatabaseHeader.xsl"

#第二次测试针对FSMState类的子类，对继承同一个父类的子类的模板
#xml_filename = "./xml/SampleFullDataPool.xml"
#xsl_filename = "./xsl/GenerateDataPoolHeader.xsl"
#xsl_filename = "./xsl/GenerateDataPoolBody.xsl"


##########具体查看类的继承关系，自己先写一个模板生成.c和.h文件

#3#xsl文件是一个模板，xml文件记录了4中Manager类，该xsl会被其他xsl引用
#xml_filename = "./xml/SampleTelecommands.xml"
#xsl_filename = "./xsl/ConfigureFunctionalityManagers.xsl"

#4#
#xml_filename = "/home/wangshaobo/obs/obs/src/xml/"
#xsl_filename = "/home/wangshaobo/obs/obs/src/xsl/GenerateParameterDatabaseTestCaseBody.xsl"


###########################################开始正式生成###################################################


#第一次SampleFSM.xml#
##GenerateFsmState.xsl
#xml_filename="./obs/src/xml/SampleFSM.xml"
#xsl_filename="./obs/src/xsl/GenerateFsmState.xsl"
##ConfigFSM.xsl
xml_filename="./obs/src/xml/SampleFSM.xml"
xsl_filename="./obs/src/xsl/ConfigureFSM.xsl"

#第二次#
##GenerateDataPoolHeader.xsl
#xml_filename="./obs/src/xml/SampleFullDataPool.xml"
#xsl_filename="./obs/src/xsl/GenerateDataPoolHeader.xsl"
##GenerateDataPoolBody.xsl
#xml_filename="./obs/src/xml/SampleFullDataPool.xml"
#xsl_filename="./obs/src/xsl/GenerateDataPoolBody.xsl"
##GenerateDataPoolInclude.xsl
#xml_filename="./obs/src/xml/SampleFullDataPool.xml"
#xsl_filename="./obs/src/xsl/GenerateDataPoolInclude.xsl"
##GenerateDataPoolTestCaseHeader.xsl
#xml_filename="./obs/src/xml/SampleFullDataPool.xml"
#xsl_filename="./obs/src/xsl/GenerateDataPoolTestCaseHeader.xsl"
##GenerateDataPoolTestCaseBody.xsl
#xml_filename="./obs/src/xml/SampleFullDataPool.xml"
#xsl_filename="./obs/src/xsl/GenerateDataPoolTestCaseBody.xsl"

#第三次#
##GenerateParameterDatabaseHeader.xsl
#xml_filename="./obs/src/xml/SampleR2Database.xml"
#xsl_filename="./obs/src/xsl/GenerateParameterDatabaseHeader.xsl"
##GenerateParameterDatabaseBody.xsl
#xml_filename="./obs/src/xml/SampleR2Database.xml"
#xsl_filename="./obs/src/xsl/GenerateParameterDatabaseBody.xsl"
##GenerateParameterDatabaseInclude.xsl
#xml_filename="./obs/src/xml/SampleR2Database.xml"
#xsl_filename="./obs/src/xsl/GenerateParameterDatabaseInclude.xsl"
##GenerateParameterDatabaseTestCaseBody.xsl
#xml_filename="./obs/src/xml/SampleR2Database.xml"
#xsl_filename="./obs/src/xsl/GenerateParameterDatabaseTestCaseBody.xsl"
##GenerateParameterDatabaseTestCaseHeader.xsl
#xml_filename="./obs/src/xml/SampleR2Database.xml"
#xsl_filename="./obs/src/xsl/GenerateParameterDatabaseTestCaseHeader.xsl"

#第四次#
##GenerateDynamicFactoryHeader.xsl
#####出错
#xml_filename="./obs/src/xml/SampleApplicationModel.xml"
#xsl_filename="./obs/src/xsl/GenerateDynamicFactoryHeader.xsl"

#第五次#
##GenerateComponentFactoryHeader.xsl
#xml_filename="./obs/src/xml/SampleApplicationModel.xml"
#xsl_filename="./obs/src/xsl/GenerateComponentFactoryHeader.xsl"

dom = ET.parse(xml_filename)
xslt = ET.parse(xsl_filename)
transform = ET.XSLT(xslt)
newdom = transform(dom)
print(ET.tostring(newdom, pretty_print=True))

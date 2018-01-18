# -*- coding: utf-8 -*-

#import os
#from validator import Validator

#validator = Validator("/Users/yabo/ObsFramework_0_8_3/models/xsd/ObsFrameworkAppModel.xsd")

from lxml import etree

#--------------------------------------------------------------------------------------

#XML_DIR = "/Users/yabo/ObsFramework_0_8_3/src/xml/"

XSD_FILE = "/Users/yabo/ObsFramework_0_8_3/models/xsd/ObsFrameworkAppModel.xsd" #Application XSD Schema,  application metamodel

#XML_FILE = "/Users/yabo/ObsFramework_0_8_3/src/xml/SampleApplicationModel.xml" #fail

XML_FILE = "/Users/yabo/ObsFramework_0_8_3/src/xml/SampleObsClock.xml" 

#--------------------------------------------------------------------------------------
# 验证framework特征模型的正确性

#XSD_FILE = "/Users/yabo/ObsFramework_0_8_3/doc/xsd/metamodel.xsd"   #Framework XSD Schema, Framework metamodel

#XML_FILE = "/Users/yabo/ObsFramework_0_8_3/models/xml/FeatureControlActions.xml"   #pass
#XML_FILE = "/Users/yabo/ObsFramework_0_8_3/models/xml/FeatureObsApplication.xml"    #pass
#XML_FILE = "/Users/yabo/ObsFramework_0_8_3/models/xml/FeatureTelemetryStream.xml"  #pass
#--------------------------------------------------------------------------------------



xml_doc = etree.parse(XML_FILE)
xsd_doc = etree.parse(XSD_FILE)

xmlschema = etree.XMLSchema(xsd_doc)

result = xmlschema.validate(xml_doc)

#result = xmlschema.assertValid(xml_doc)


if result:
     print('Valid! :)')
else:
     print('Not valid! :(')


# for file_name in os.listdir(XML_DIR):
#     print('{}: '.format(file_name), end='')

#     file_path = '{}/{}'.format(XML_DIR, file_name)

#     if validator.validate(file_path):
#         print('Valid! :)')
#     else:
#         print('Not valid! :(')
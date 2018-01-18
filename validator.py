from lxml import etree

class Validator:

    # def __init__(self, xsd_path: str):
    #     xmlschema_doc = etree.parse(xsd_path)
    #     self.xmlschema = etree.XMLSchema(xmlschema_doc)

    def validate(XML_FILE) -> bool:
        xml_doc = etree.parse(XML_FILE)
        result = self.xmlschema.validate(xml_doc)

        return result

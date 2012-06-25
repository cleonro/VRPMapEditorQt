#include "XmlDoc.h"
#include "rapidxml_print.hpp"

OXmlDoc::OXmlDoc()
{

}

OXmlDoc::~OXmlDoc()
{

}

void OXmlDoc::Clear()
{
	xml_doc_.clear();
}

std::string OXmlDoc::ToString()
{
	std::string str;
	rapidxml::print(std::back_inserter(str), xml_doc_, 0);
	return str;
}

void OXmlDoc::FromString(const std::string& xml_string)
{
	xml_doc_.parse<0>((char*)xml_string.c_str());
}


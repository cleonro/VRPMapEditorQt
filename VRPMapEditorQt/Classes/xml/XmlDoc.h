#pragma once

#include "rapidxml.hpp"
#include <string>
#include <sstream>

using namespace rapidxml;

class OXmlDoc
{
public:
	OXmlDoc();
	~OXmlDoc();

	void		Clear();
	std::string	ToString();
	void		FromString(const std::string& xml_string);

	template <typename T>
	void		AddSimpleNode(const char* node_name, const T& node_value);
	template <typename T>
	bool		GetSimpleNodeValue(const char* node_name, T& node_value);

protected:

	xml_document<>	xml_doc_;
};

template <typename T>
void OXmlDoc::AddSimpleNode(const char* node_name, const T& node_value)
{
	char* bname;
	char* bvalue;
	bname = xml_doc_.allocate_string(node_name, strlen(node_name) + 1);

	std::ostringstream buffer;
	buffer << node_value;

	bvalue = xml_doc_.allocate_string(buffer.str().c_str(), buffer.str().size() + 1);
	xml_node<>* xmln = xml_doc_.allocate_node(node_element, bname, bvalue);
	xml_doc_.append_node(xmln);
}

template <typename T>
bool OXmlDoc::GetSimpleNodeValue(const char* node_name, T& node_value)
{
	xml_node<>* xmln = xml_doc_.first_node(node_name);
	
	if(xmln == NULL) {
		//node name not found in xml_doc first level children
		return false;
	}

	//TODO: how to find if a xml node has children
// 	if(xmln->first_node() != NULL) {
// 		//not a simple node
// 		return false;
// 	}

	char* nodev = xmln->value();
	if(nodev == NULL) {
		//node doesn't have a value
		return false;
	}

	std::istringstream buffer(nodev);
	buffer >> node_value;

	return true;
}
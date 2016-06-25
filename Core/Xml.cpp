#include "Xml.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// XmlElement¿‡

XmlElement::XmlElement()
	: xml_node<>( rapidxml::node_document )
{

}

XmlElement::~XmlElement()
{
	
}

XmlElement* XmlElement::GetNode(const char *name /* = 0 */, std::size_t name_size /* = 0 */, bool case_sensitive /* = true */) const
{
	rapidxml::xml_node<>* pNode = first_node( name, name_size, case_sensitive );

	if ( NULL == pNode )
	{ return NULL; }

	return static_cast< XmlElement* >( pNode );
}

XmlElement* XmlElement::NextSibling( const char *name /* = 0 */, std::size_t name_size /* = 0 */, bool case_sensitive /* = true */ ) const
{
	rapidxml::xml_node<>* pNode = next_sibling( name, name_size, case_sensitive );

	if ( NULL == pNode )
	{ return NULL; }

	return static_cast< XmlElement* >( pNode );
}

const char* XmlElement::Attribute( const char* name ) const
{
	rapidxml::xml_attribute<>* pAttribute = first_attribute( name );
	if ( NULL == pAttribute )
	{ return NULL; }

	return pAttribute->value();
}

const char* XmlElement::Attribute( const char* name, int* iVal ) const
{
	rapidxml::xml_attribute<>* pAttribute = first_attribute( name );
	if ( NULL == pAttribute )
	{ return NULL; }

	if ( pAttribute )
	{
		sscanf( pAttribute->value(), "%d", iVal );
		return pAttribute->value();
	}
	return NULL;
}

const char* XmlElement::Attribute( const char* name, double* dVal ) const
{
	rapidxml::xml_attribute<>* pAttribute = first_attribute( name );
	if ( NULL == pAttribute )
	{ return NULL; }

	if ( pAttribute )
	{
		sscanf( pAttribute->value(), "%lf", dVal );
		return pAttribute->value();
	}
	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// XmlDocument¿‡

XmlDocument::XmlDocument()
{

}

XmlDocument::~XmlDocument()
{
	if ( NULL != pFile )
	{ delete pFile; }
}

void XmlDocument::LoadFile( const char* szFileName )
{
	pFile = new rapidxml::file<>( szFileName );

	parse< 0 >( pFile->data() );
}

XmlElement* XmlDocument::FirstChildElement( const char *name /* = 0 */, std::size_t name_size /* = 0 */, bool case_sensitive /* = true */ ) const
{
	rapidxml::xml_node<>* pNode = first_node( name, name_size, case_sensitive );
	
	if ( NULL == pNode )
	{ return NULL; }

	return static_cast< XmlElement* >( pNode );
}
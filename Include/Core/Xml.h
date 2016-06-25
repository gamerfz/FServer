/************************************************************************
*	@file		：	Xml.h
*	@brief		：	tinyxml封装
*	@author		：	fz
*	@date		：	16.1
************************************************************************/
#pragma once

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

enum XmlAttributeError
{
	XAE_Success,
	XAE_NameError,
	XAE_ValueError,
};

class XmlElement : public rapidxml::xml_node<>
{
public:
	XmlElement();
	~XmlElement();

	/*
	<Address Port="23001">127.0.0.1</Address>
	通过GetNode("Address")整个节点
	通过GetNode("Address")->value()获取127.0.0.1
	通过GetNode("Address")->Attribute("Port")获取23001
	*/
	// 获取节点
	XmlElement* GetNode( const char *name = 0, std::size_t name_size = 0, bool case_sensitive = true ) const;

	// name为空默认为下一个同级节点
	XmlElement* NextSibling(const char *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const;

	const char* Attribute( const char* name ) const;
	const char* Attribute( const char* name, int* iVal ) const;
	const char* Attribute( const char* name, double* dVal ) const;
};

class XmlDocument : public rapidxml::xml_document<>
{
public:
	XmlDocument();
	~XmlDocument();

	// 加载文件
	void LoadFile( const char* szFileName );

	// 查找元素
	XmlElement* FirstChildElement( const char *name = 0, std::size_t name_size = 0, bool case_sensitive = true ) const;

private:
	rapidxml::file<> * pFile;
};
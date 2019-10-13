#include "stdafx.h"
#include "XMLManipulation.h"
#include <string>
#include <iostream>

using std::string;
using std::cout;

void add_doc(pugi::xml_document &parent, pugi::xml_document &child)
{
	string name = child.first_child().name();
	for (auto &node : child.children())
	{
		pugi::xml_node c = parent.append_child(node.name());
		for (auto &cc : node.children())
		{
			add_node(c, cc);
		}
		for (auto &a : node.attributes())
		{
			pugi::xml_attribute att = c.append_attribute(a.name());
			att.set_value(a.value());
		}
	}
}

void add_node(pugi::xml_node &parent, pugi::xml_node &child)
{
	string name = child.name();
	pugi::xml_node childCopy = parent.append_child(name.c_str());
	for (auto &c : child.children())
	{
		add_node(childCopy, c);
	}
	for (auto &a : child.attributes())
	{
		if (a)
		{
			pugi::xml_attribute att = childCopy.append_attribute(a.name());
			att.set_value(a.value());
		}
	}
	//print_node(childCopy);
	
}

void add_child(pugi::xml_document &parent, pugi::xml_node &child)
{
	string name = child.first_child().name();
	pugi::xml_node childCopy = parent.first_child().append_child(name.c_str());

	for (auto &c : child.first_child().children())
	{
		add_node(childCopy, c);
	}
	for (auto &a : child.first_child().attributes())
	{
		pugi::xml_attribute att = childCopy.append_attribute(a.name());
		att.set_value(a.value());
	}
	//print_node(childCopy);
}


void print_doc(const pugi::xml_document &node)
{
	cout << "\n****Doc:" << node.name() << "**\n";

	for (auto a : node.attributes())
	{
		cout << "**Attribute:";
		cout << a.name();
		cout << "/" << a.value() << "\n";

	}
	for (auto &c : node.children())
	{ 
		cout << "**DocChildren:\n";
		print_node(c);
	}
	cout << "\n";
}


void print_node(const pugi::xml_node &node)
{
	cout << "Node:" << node.name() << "--\n";
	for (auto &a : node.attributes())
	{
		cout << "Attribute:";
		cout << a.name();
		cout << "/" << a.value() << "\n";

	}
	for (auto &c : node.children())
	{
		cout << "Children:";
		print_node(c);
	}
	cout << "\n";
}
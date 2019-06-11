#pragma once
#include <pugixml.hpp>

//For debugging purpose, prints infos on a given xml_node
void print_node(const pugi::xml_node &node);
//For debugging purpose, prints infos on a given xml_document
void print_doc(const pugi::xml_document &node);
//Adds a child node to a parent node
void add_node(pugi::xml_node &parent, pugi::xml_node &child);
//Adds a document to a parent document
void add_doc(pugi::xml_document &parent, pugi::xml_document &child);
//Adds child of child to child of parent node
void add_child(pugi::xml_document &parent, pugi::xml_node &child);
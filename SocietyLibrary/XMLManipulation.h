#pragma once
#include <pugixml.hpp>


void print_node(const pugi::xml_node &node);
void print_doc(const pugi::xml_document &node);
void add_node(pugi::xml_node &parent, pugi::xml_node &child);
void add_doc(pugi::xml_document &parent, pugi::xml_document &child);
void add_child(pugi::xml_document &parent, pugi::xml_node &child);
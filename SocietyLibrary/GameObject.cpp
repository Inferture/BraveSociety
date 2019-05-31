#include "stdafx.h"
#include "myMain.h"
#include "GameObject.h"
#include "XMLManipulation.h"

float GameObject::GetX() const
{
	return x;
}
float GameObject::GetY() const
{
	return y;
}
float GameObject::GetZ() const
{
	return z;
}


GameObject::GameObject() : x(0), y(0)
{
}
GameObject::GameObject(float x, float y, float z) : x(x), y(y), z(z)
{
}


void GameObject::SetPosition(float x, float y)
{
	this->x = x - (float)WINDOW_WIDTH / 2;
	this->y = -y + (float)WINDOW_HEIGHT / 2;
}


void GameObject::SetDepth(float z)
{
	this->z = z;
}


GameObject* GameObject::GetParent()
{
	return parent;
}
void GameObject::SetParent(GameObject* parent)
{
	this->parent = parent;
}
/*
std::vector<unique_ptr<GameObject>>  GameObject::GetChildren()
{
	return children;
}
void GameObject::AddChild(unique_ptr<GameObject> &go)
{
	go->SetParent(this);
	children.push_back(go);
}*/

bool operator<(const GameObject &go1, const GameObject& go2)
{
	return go1.GetZ() < go2.GetZ() || (go1.GetZ() == go2.GetZ() && go1.GetY() > go2.GetY());
}
bool GameObject::operator==(const GameObject &go)
{
	return this == &go;
}
bool sortZ(GameObject* c1, GameObject *c2)
{
	return c1->GetZ() < c2->GetZ() || (c1->GetZ() == c2->GetZ() && c1->GetY() > c2->GetY());
}

void GameObject::Translate(float x, float y)
{
	this->x += x;
	this->y -= y;
	/*
	for (auto &c : children)
	{
		c->Translate(x, y);
	}*/
}

bool SortZ(GameObject* c1, GameObject *c2)
{
	return c1->GetZ() < c2->GetZ() || (c1->GetZ() == c2->GetZ() && c1->GetY() > c2->GetY());
}


pugi::xml_document GameObject::SerializeRec() const
{
	pugi::xml_document doc = Serialize();
	/*
	for (auto &c : children)
	{
		pugi::xml_document child_doc = c->SerializeRec();
		add_child(doc, child_doc);
	}*/
	return doc;
}


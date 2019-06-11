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

void GameObject::Handle()
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
}

bool SortZ(GameObject* c1, GameObject *c2)
{
	return c1->GetZ() < c2->GetZ() || (c1->GetZ() == c2->GetZ() && c1->GetY() > c2->GetY());
}
bool SortZ(std::pair<int, unique_ptr<GameObject>> p1, std::pair<int, unique_ptr<GameObject>> p2)
{
	if (!p1.second.get() || !p2.second.get())
	{
		return false;
	}
	return p1.second.get()->GetZ() < p2.second.get()->GetZ() || 
		(p1.second.get()->GetZ() == p2.second.get()->GetZ() && p1.second.get()->GetY() > p1.second.get()->GetY());
}

pugi::xml_document GameObject::SerializeRec() const
{
	pugi::xml_document doc = Serialize();
	return doc;
}

void GameObject::Update()
{

}
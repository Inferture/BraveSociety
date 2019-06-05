#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include <pugixml.hpp>

using std::unique_ptr;
class GameObject
{



protected:
	/*x coordinate*/
	float x;
	/*y coordinate*/
	float y;
	/*z coordinate (the smaller the further down it will be drawn)*/
	float z;
	/*if a parent moves, the child follows*/
	GameObject* parent;
	//std::vector<unique_ptr<GameObject>> children;
	//std::vector<GameObject*> children;
	enum TeamStatus
	{
		RED,
		BLUE,
		NONE
	};

public:
	GameObject();
	GameObject(float x, float y, float z = 0);
	GameObject(pugi::xml_node node);

	float GetX() const;
	float GetY() const;
	float GetZ() const;

	void SetPosition(float x, float y);
	virtual void Translate(float x, float y);
	void SetDepth(float z);

	GameObject* GetParent();
	//std::vector<unique_ptr<GameObject>> GetChildren();

	//void AddChild(unique_ptr<GameObject> &go);
	void SetParent(GameObject* parent);

	virtual void Draw(sf::RenderWindow &window, float x, float y, bool selected = false) const = 0;


	virtual pugi::xml_document Serialize()const = 0;
	virtual pugi::xml_document SerializeRec()const;

	bool operator==(const GameObject &go);

	virtual bool IsTouched(float x_touch, float y_touch) const = 0;
	virtual void Scale(float scale)=0;
	/*Called every frame*/
	virtual void Update();
	//Display the info window
	virtual void Handle();
};
bool operator<(const GameObject &go1, const GameObject& go2);
bool SortZ(GameObject* c1, GameObject *c2);

/*
-Membre qui s'affiche
--Sprite hair & body
--Choix aléatoire
--Nom en dessous du personnage
-Membre qui se déplace

-Membre qui peut être sélectionné

-Affichage des infos sur le membre

-Possibilité de tuer le membre

-Membre qui interragit avec les autres

-Sauvegarde

*/
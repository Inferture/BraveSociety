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

	//Which team does the object belongs to ?
	enum TeamStatus
	{
		NONE,
		RED,
		BLUE
	};

public:
	GameObject();
	GameObject(float x, float y, float z = 0);
	GameObject(pugi::xml_node node);

	//returns the x coordinate
	float GetX() const;
	//returns the y coordinate
	float GetY() const;
	//returns the z coordinate (depth)
	float GetZ() const;

	//Sets position to (x,y)
	void SetPosition(float x, float y);
	//Translate position of (x,y)
	virtual void Translate(float x, float y);
	//Sets the depth (z coordinate)
	void SetDepth(float z);

	//Returns the parent object if any, null otherwise
	GameObject* GetParent();
	//To set the parent object
	void SetParent(GameObject* parent);
	//Displays the object on the window
	virtual void Draw(sf::RenderWindow &window, float x, float y, bool selected = false) const = 0;

	//Serialize the object with its attributes
	virtual pugi::xml_document Serialize()const = 0;
	//Serialize the object and its children
	virtual pugi::xml_document SerializeRec()const;

	bool operator==(const GameObject &go);

	//Does the coordinate (x_touch, y_touch) touches the object ?
	virtual bool IsTouched(float x_touch, float y_touch) const = 0;
	//To make an object bigger or smaller
	virtual void Scale(float scale)=0;
	//Called every frame
	virtual void Update();
	//Display the info window
	virtual void Handle();
};
bool operator<(const GameObject &go1, const GameObject& go2);

//Sorts by z axis, then by y axis if Zs are equals
bool SortZ(GameObject* c1, GameObject *c2);
//Sorts by z axis, then by y axis if Zs are equals
bool SortZ(std::pair<int, unique_ptr<GameObject>> p1, std::pair<int, unique_ptr<GameObject>> p2);

/*
todo

-Membre qui s'affiche
--Sprite hair & body
--Choix aléatoire						
--Nom en dessous du personnage		

-Membre qui se déplace


-Membre qui peut être sélectionné

-Affichage des infos sur le membre

-Possibilité de tuer le membre

-Membre qui interragit avec les autres

//roughly okay above

-Sauvegarde
--Demander nom sauvegarde

-Instruction en bas
--(S) Save
--(L) Load
--(B) Shop
---Gagner monnaie
---Dépenser et construire infrastructures
--(O) Option (ex:vitesse)

*/
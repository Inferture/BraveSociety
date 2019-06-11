#pragma once
#include "stdafx.h"
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Member.h"
#include <map>
#include <unordered_map>
#include "GameManager.h"



using std::unique_ptr;
enum infrastructureStatus
{
	USED,
	EMPTY
};
class GameManager;

class Infrastructure : public GameObject
{

private:
	//Maximum number of members inside the infrastructure
	int maxCapacity;
	
protected:
	//number of infrastructures
	static int nbInfrastructures;
	//speed at which the infrastructure disappears when dying
	float disappearSpeed;
	//name of the infrastructure
	std::string name;
	//bonus for membersInside's attack
	int bonusAttack;
	//bonus for membersInside's defense
	int bonusDefense;
	//Sprite of infrastructure
	sf::Sprite sprInfrastructure;
	//id of the infrastructure
	int id;
	//time the members stay inside the infrastructure
	float timeInside;
public:
	//members inside the infrastructure
	std::vector < std::pair<std::unique_ptr<Member>,float>> membersInside;

	Infrastructure(Infrastructure &);
	Infrastructure(float x, float y, float z, std::string name, int bonusDefense, int bonusAttack, int maxCapacity,
		sf::Sprite sprInfrastructure, float timeInside);
	Infrastructure(pugi::xml_node& node);
	
	//Displays the infrastructure on the window
	virtual void Draw(sf::RenderWindow &window, float x, float y, bool selected) const;
	//Does the coordinate (x_touch, y_touch) touches the infrastructure ?
	virtual bool IsTouched(float x_touch, float y_touch) const;
	//To make an infrastructure bigger or smaller
	virtual void Scale(float scale);
	//Displays a window with all the infos and interactions possible with an infrastructure
	virtual void Handle();
	//Called every frame
	virtual void Update();
	//Calculates the numbers of available places in the infrastructure
	int PlacesLeft();
	//Serializes the infrastructure in xml, for saving
	virtual pugi::xml_document Serialize() const;
	//Integrates the member with the id memberId into the infrastructure
	void Enters(int memberId);
	//Returns the id of the infrastructuer
	int GetId();
};


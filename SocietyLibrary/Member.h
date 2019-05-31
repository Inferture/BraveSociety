#pragma once


#include <string>
#include <SFML/Graphics.hpp>
#include "myMain.h"
#include "GameObject.h"



class Member : public GameObject
{
private:
	bool deathFlag;

protected:
	/* 0 - 1, inclination towards attacking others in case of conflict*/
	float aggressiveness;
	/* 0 - 1, inclination towards accepting others and avoiding conflict*/
	float tolerance;
	/* 0 - 1, affiliation towards the green clan*/
	float greenAffiliation;
	/* 0 - 1, affiliation towards the red clan*/
	float redAffiliation;
	/*can kill if attack > other's defense*/
	int attack;
	/*protected if defense >= other's attack*/
	int defense;

	/*Sprite of hair, with a given color*/
	sf::Sprite hair;
	/*Sprite of body, with a given color*/
	sf::Sprite body;
	
public:
	Member(float x, float y, float z, float aggressiveness, float tolerance, float greenAffiliation, float redAffiliation,
		sf::Sprite hair, sf::Sprite body, int attack=0, int defense=0);
	void Die();
	virtual void Draw(sf::RenderWindow &window, float x, float y, bool selected = false) const;
	virtual pugi::xml_document Serialize() const;
	//virtual pugi::xml_document SerializeRec() const;
	virtual bool IsTouched(float x_touch, float y_touch) const;
	virtual void Scale(float scale);
}; 
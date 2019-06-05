#pragma once
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObject.h"


enum MemberState
{
	IDLE,
	MOVING,
	WAITING,
	TALKING,
	FIGHTING,
	DYING,
};

enum RelationStatus
{
	PARENT,
	CHILD,
	SIBLING,
	FRIEND,
	BFF,
	ENEMY,
	KILLERSIBLING,
	KILLERPARENT,
	KILLERCHILD,
	KILLERFRIEND,
};



class Member : public GameObject
{

	struct Relationship
	{
		//-1-1, -1 is absolute hatred, 1 is absolute love, 0 is neutral
		float relation;
		//All statuses of the relation (sibling, friend...)
		std::vector<RelationStatus> statuses;
	};

private:
	float speed;
	float actionTimer;
	float actionTime;
	MemberState state;
	Member* targetMember;
protected:
	//speed at which the body disappears when dying
	float disappearSpeed;
	//name of the character
	std::string name;
	// 0 - 1, inclination towards attacking others in case of conflict
	float aggressiveness;
	// 0 - 1, inclination towards accepting others and avoiding conflict
	float tolerance;
	// 0 - 1, affiliation towards the blue clan
	float blueAffiliation;
	//0 - 1, affiliation towards the red clan
	float redAffiliation;
	//can kill if attack > other's defense
	int attack;
	//protected if defense >= other's attack
	int defense;
	//Sprite of hair, with a given color
	sf::Sprite hair;
	//Sprite of body, with a given color
	sf::Sprite body;
	//Sprite of stick, with a given color and which comes in front of the body and behind the hair
	sf::Sprite stick;
	//Sprite of clothes, with the "team" color
	sf::Sprite clothes;
	//Nametag, is displayed below the character
	sf::Text nametag;
	//Relationships with other members
	std::map<Member*, Relationship> relationships;
public:

	
	Member(float x, float y, float z, std::string name, float aggressiveness, float tolerance, float blueAffiliation, float redAffiliation,
		sf::Sprite hair, sf::Sprite body, sf::Sprite stick, sf::Sprite clothes, int attack=0, int defense=0);

	//Dies and sends the message of their death to their loved ones
	void Die(Member* killer=NULL);

	//Draws it on the window
	virtual void Draw(sf::RenderWindow &window, float x, float y, bool selected = false) const;

	//Serializes all its characteristics (but not its children)
	virtual pugi::xml_document Serialize() const;

	//virtual pugi::xml_document SerializeRec() const;
	virtual bool IsTouched(float x_touch, float y_touch) const;

	//Scales the characters by scale
	virtual void Scale(float scale);
	//Called every frame
	virtual void Update();
	//Tries to attack another member
	bool Attack(Member* target);

	//Add a status to the relation with target.
	//if relative, their relation jauge is added relation
	//else, it becomes relation
	void AddRelationStatus(Member* target, RelationStatus status, float relation = 0.0f, bool relative = true);

	//if relative, their relation jauge is added relation
	//else, it becomes relation
	void AddRelation(Member* target, float relation, bool relative = true);
	//Translates from (x,y)
	virtual void Translate(float x, float y);
	//Display the info window
	virtual void Handle();
	//checker si le personnage entre en territoire ennemi
	
}; 
bool IsFamily(RelationStatus status);
bool IsFriendly(RelationStatus status);
bool IsKiller(RelationStatus status);
void AddStatus(std::vector<RelationStatus> &statuses, RelationStatus status);
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
const std::vector<std::string> MemberStateStrings
{
	"IDLE",
	"MOVING",
	"WAITING",
	"TALKING",
	"FIGHTING",
	"DYING",
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

const std::vector<std::string> RelationStatusStrings{ 
	"PARENT",
	"CHILD",
	"SIBLING",
	"FRIEND",
	"BFF",
	"ENEMY",
	"KILLERSIBLING",
	"KILLERPARENT",
	"KILLERCHILD",
	"KILLERFRIEND",
};



class Member : public GameObject
{

	struct Relationship
	{
		//-1-1, -1 is absolute hatred, 1 is absolute love, 0 is neutral
		float relation;
		//All statuses of the relation (sibling, friend...)
		std::vector<RelationStatus> statuses;

		//Color the name will be displayed in
		sf::Color color;
		//Name of the other member
		std::string name;
	};

private:
	//speed at which the member moves
	float speed;
	//time spent since doing a particular action
	float actionTimer;
	//time until the end of the current action
	float actionTime;
	//State in which the member currently is (IDLE...)
	MemberState state;
	//Other member with which this is interacting (-1 if none) 
	int targetMemberId;
	//Infrastructure with which this is interacting (most likely goind to, -1 if none)
	int targetInfraId;

	//Which hairstyle (which hair image to load)
	int hairStyle;
	//Which body image to load
	int bodyStyle;
	//Which clothes image to load
	int clothesStyle;
	//Which stick image to load
	int stickStyle;
protected:
	//Total number of members in the party
	static int nbMember;
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
	//Relationships with other members
	std::map<int, Relationship> relationships;
	//Unique id of the member
	int id;
	//Name tag that appears below the character
	sf::Text nametag;
public:

	
	Member(float x, float y, float z, std::string name, float aggressiveness, float tolerance, float blueAffiliation, 
		float redAffiliation, sf::Sprite hair, sf::Sprite body, sf::Sprite stick, sf::Sprite clothes, int hairstyle, 
		int bodystyle, int clothesstyle, int stickstyle, int attack = 0, int defense = 0 );

	Member(pugi::xml_node& node);
	std::string GetName();
	//Dies and sends the message of their death to their loved ones
	void Die(int killerId=-1);

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
	bool Attack(int targetId);

	//Add a status to the relation with target.
	//if relative, their relation jauge is added relation
	//else, it becomes relation
	void AddRelationStatus(int targetId, RelationStatus status, float relation = 0.0f, bool relative = true);

	//if relative, their relation jauge is added relation
	//else, it becomes relation
	void AddRelation(int targetId, float relation, bool relative = true);
	//Translates from (x,y)
	virtual void Translate(float x, float y);
	//Display the info window
	virtual void Handle();
	//checker si le personnage entre en territoire ennemi

	//Returns the id
	int GetId();
	//Inits the tag with a given string (displayed below the player in blue)
	sf::Text InitTag(std::string);
	
	//Sets the target infrastructure (with id)
	void SetTargetInfra(int id);
	//Gets the target infrastructure's id
	int GetTargetInfra();
	//Sets the target member (with id)
	void SetTargetMember(int id);
	//Gets the target member's id
	int GetTargetMember();

	//Gets the hair color
	sf::Color GetHairColor();

	//Starts a new action which takes time
	void SetTimer(float time);
	//Sets the current state of the member
	void SetState(MemberState state);
}; 
//Is a given relationstatus a family status ?
bool IsFamily(RelationStatus status);
//Is a given relationstatus a friendly status ?
bool IsFriendly(RelationStatus status);
//Is a given relationstatus a killer status (used for revenge)
bool IsKiller(RelationStatus status);
//Add a status to a list of statuses (can delete other statuses if relevant, and avoids duplicates
void AddStatus(std::vector<RelationStatus> &statuses, RelationStatus status);
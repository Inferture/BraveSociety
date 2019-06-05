
#include <map>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Member.h"


enum infrastructureStatus
{
	USED,
	EMPTY,
	DYING,
};


class Infrastructure : public GameObject
{

private:
	float actionTimer;
	float actionTime;
	int maxCapacity;
	std::vector<Member *> membersInside;

protected:
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
	
public:

	Infrastructure(float x, float y, float z, std::string name, int bonusDefense, int bonusAttack, int maxCapacity,
	sf::Sprite sprInfrastructure ) {};

};


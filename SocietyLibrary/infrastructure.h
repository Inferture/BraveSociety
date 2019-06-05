#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Member.h"


enum infrastructureStatus
{
	USED,
	EMPTY
};


class Infrastructure : public GameObject
{

private:
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
	sf::Sprite sprInfrastructure ) : GameObject(x,y,z), name(name), bonusDefense(bonusDefense), bonusAttack(bonusAttack), maxCapacity(maxCapacity), sprInfrastructure(sprInfrastructure) {};

	virtual void Draw(sf::RenderWindow &window, float x, float y) const;
	virtual bool IsTouched(float x_touch, float y_touch) const;
	virtual void Scale(float scale);
	virtual pugi::xml_document Serialize() const;
};


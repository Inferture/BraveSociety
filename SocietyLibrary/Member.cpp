#include "stdafx.h"
#include "Member.h"
#include "ColorManipulation.h"


Member::Member(float x, float y, float z, float aggressiveness, float tolerance, float greenAffiliation, float redAffiliation,
	sf::Sprite hair, sf::Sprite body, int attack, int defense) :
	GameObject(x, y, z), aggressiveness(aggressiveness), tolerance(tolerance),
	greenAffiliation(greenAffiliation), redAffiliation(redAffiliation), hair(hair),
	body(body), attack(attack), defense(defense)
{
}

void Member::Die()
{
	deathFlag = true;
}

void Member::Draw(sf::RenderWindow &window, float x, float y, bool selected) const
{
	//hair.setPosition(sf::Vector2f(x, y));
	//body.setPosition(sf::Vector2f(x, y));

	window.draw(body);
	window.draw(hair);
}

pugi::xml_document Member::Serialize() const
{
	pugi::xml_document doc;
	doc.set_name("MemberDoc");

	pugi::xml_node node;
	node = doc.append_child("Member");


	pugi::xml_attribute attX = node.append_attribute("x");
	attX.set_value(x);

	pugi::xml_attribute attY = node.append_attribute("y");
	attY.set_value(y);

	pugi::xml_attribute attZ = node.append_attribute("z");
	attZ.set_value(z);


	pugi::xml_attribute attAggressiveness = node.append_attribute("aggressiveness");
	attAggressiveness.set_value(aggressiveness);

	pugi::xml_attribute attTolerance = node.append_attribute("tolerance");
	attTolerance.set_value(tolerance);

	pugi::xml_attribute attGreen = node.append_attribute("greenAffiliation");
	attGreen.set_value(greenAffiliation);

	pugi::xml_attribute attRed = node.append_attribute("redAffiliation");
	attRed.set_value(redAffiliation);

	pugi::xml_attribute attAttack = node.append_attribute("attack");
	attAttack.set_value(attack);

	pugi::xml_attribute attDefense = node.append_attribute("defense");
	attDefense.set_value(defense);

	pugi::xml_attribute attHairColor = node.append_attribute("hairColor");
	std::string hairColor = GetColorString(hair.getColor());
	attHairColor.set_value(hairColor.c_str());

	pugi::xml_attribute attBodyColor = node.append_attribute("bodyColor");
	std::string bodyColor = GetColorString(body.getColor());
	attBodyColor.set_value(bodyColor.c_str());

	return doc;
}

bool Member::IsTouched(float x_touch, float y_touch) const
{
	return false;
}
void Member::Scale(float scale)
{

}

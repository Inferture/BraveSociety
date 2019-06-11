#include "stdafx.h"
#include "Member.h"
#include "ColorManipulation.h"
#include "myMain.h"
#include <algorithm>
#include "GameManager.h"
#include <iostream>
#include <string>
#include <imgui.h>
#include <sfml-imgui/imgui-SFML.hpp>
#include "General.h"
#include "XMLManipulation.h"


using std::to_string;

Member::Member(float x, float y, float z, std::string name, float aggressiveness, float tolerance, float blueAffiliation, float redAffiliation,
	sf::Sprite hair, sf::Sprite body, sf::Sprite stick, sf::Sprite clothes, int hairstyle,
	int bodystyle, int clothesstyle, int stickstyle, int attack, int defense) :
	GameObject(x, y, z), name(name), aggressiveness(aggressiveness), tolerance(tolerance),
	blueAffiliation(blueAffiliation), redAffiliation(redAffiliation), hair(hair), speed(400),
	body(body), clothes(clothes), stick(stick), attack(attack), defense(defense), disappearSpeed(100),
	id(nbMember), nametag(InitTag(name)), targetMemberId(-1), targetInfraId(-1), hairStyle(hairstyle),
	bodyStyle(bodystyle), clothesStyle(clothesstyle), stickStyle(stickstyle)
{
	++nbMember;
	//this->body.setOrigin(this->body.getLocalBounds().width/2, this->body.getLocalBounds().height / 2);
	this->body.setPosition(x, y);
	//this->hair.setOrigin(this->hair.getLocalBounds().width / 2, this->hair.getLocalBounds().height / 2);
	this->hair.setPosition(x, y);

	this->clothes.setPosition(x, y);
	this->stick.setPosition(x, y);
}

void Member::Die(int killer)
{
	state = DYING;
	//Signal death to loved ones (parents, children, brothers/sisters)
	if (killer>=0 && GM.members[killer].get())
	{
		for (auto rel : relationships)
		{
			for (auto s : rel.second.statuses)
			{
				if (GM.members[rel.first].get())
				{
					if (s == BFF)
					{
						GM.members[rel.first].get()->AddRelationStatus(killer, KILLERFRIEND, -1.3f);
					}
					else if (s == FRIEND)
					{
						GM.members[rel.first].get()->AddRelationStatus(killer, KILLERFRIEND, -1.0f);
					}
					if (s == SIBLING)
					{
						GM.members[rel.first].get()->AddRelationStatus(killer, KILLERSIBLING, -1.3f);
					}
					if (s == PARENT)
					{
						GM.members[rel.first].get()->AddRelationStatus(killer, KILLERPARENT, -1.3f);
					}
					if (s == CHILD)
					{
						GM.members[rel.first].get()->AddRelationStatus(killer, KILLERCHILD, -1.3f);
					}
				}
			}
		}
	}
}

void Member::Draw(sf::RenderWindow &window, float x, float y, bool selected) const
{
	window.draw(nametag);
	window.draw(body);
	window.draw(stick);
	window.draw(clothes);
	window.draw(hair);
	if (state == TALKING)
	{
		sf::Sprite spriteBubble;
		spriteBubble.setTexture(texturesBubble[0]);
		spriteBubble.setOrigin(0,spriteBubble.getLocalBounds().height);
		if (GM.members.find(targetMemberId)!=GM.members.end() && GM.members[targetMemberId].get() && GM.members[targetMemberId].get()->x<x)
		{
			spriteBubble.setScale(-1, 1);
			spriteBubble.setOrigin(spriteBubble.getLocalBounds().width, spriteBubble.getLocalBounds().width);
			spriteBubble.setPosition(x , y - 10);
		}
		else
		{
			spriteBubble.setPosition(x + body.getLocalBounds().width / 2, y - 10);
		}
		
		window.draw(spriteBubble);
	}
}

Member::Member(pugi::xml_node& node): 
	GameObject(node.attribute("x").as_float(), node.attribute("y").as_float(), node.attribute("z").as_float()),
	name(node.attribute("name").as_string()), id(node.attribute("id").as_int()),
	aggressiveness(node.attribute("aggressiveness").as_float()), tolerance(node.attribute("tolerance").as_float()),
	blueAffiliation(node.attribute("blueAffiliation").as_float()), redAffiliation(node.attribute("redAffiliation").as_float()),
	attack(node.attribute("attack").as_int()), defense(node.attribute("defense").as_int()),
	speed(node.attribute("speed").as_float()), actionTimer(node.attribute("actionTimer").as_float()),
	actionTime(node.attribute("actionTime").as_float()), state((MemberState)node.attribute("state").as_int()),
	targetMemberId(node.attribute("targetMember").as_int()), targetInfraId(node.attribute("targetInfra").as_int()),
	disappearSpeed(node.attribute("disappearSpeed").as_float()), hairStyle(node.attribute("hairstyle").as_int()),
	bodyStyle(node.attribute("bodystyle").as_int()), stickStyle(node.attribute("stickstyle").as_int()),
	clothesStyle(node.attribute("clothesstyle").as_int()), nametag(InitTag(name))
{
	++nbMember;
	hair.setTexture(texturesHair[hairStyle]);
	hair.setColor(GetStringColor(node.attribute("hairColor").as_string()));

	body.setTexture(texturesBody[bodyStyle]);
	body.setColor(GetStringColor(node.attribute("bodyColor").as_string()));

	stick.setTexture(texturesStick[stickStyle]);
	stick.setColor(sf::Color::White);

	clothes.setTexture(texturesClothes[clothesStyle]);
	clothes.setColor(AttributeClothesColor(blueAffiliation,redAffiliation));


	this->body.setPosition(x, y);
	this->hair.setPosition(x, y);
	this->clothes.setPosition(x, y);
	this->stick.setPosition(x, y);
	nametag = InitTag(name);
	pugi::xml_node childNode(node.first_child());
	while (childNode)
	{
		int idRel(childNode.attribute("id").as_int());
		float relation(childNode.attribute("relation").as_float());
		std::string relName(childNode.attribute("name").as_string());
		std::string relColorString(childNode.attribute("color").as_string());
		sf::Color relColor(GetStringColor(relColorString));

		Relationship relationship;
		relationship.name = relName;
		relationship.color = relColor;
		relationship.relation = relation;
		
		pugi::xml_node statusNode(childNode.first_child());
		while (statusNode)
		{
			relationship.statuses.push_back((RelationStatus)statusNode.attribute("statusid").as_int());
			statusNode = statusNode.next_sibling();
		}

		relationships.insert({idRel,relationship});
		childNode = childNode.next_sibling();
	}

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

	pugi::xml_attribute attId = node.append_attribute("id");
	attId.set_value(id);

	pugi::xml_attribute attName = node.append_attribute("name");
	attName.set_value(name.c_str());

	pugi::xml_attribute attAggressiveness = node.append_attribute("aggressiveness");
	attAggressiveness.set_value(aggressiveness);

	pugi::xml_attribute attTolerance = node.append_attribute("tolerance");
	attTolerance.set_value(tolerance);

	pugi::xml_attribute attBlue = node.append_attribute("blueAffiliation");
	attBlue.set_value(blueAffiliation);

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

	pugi::xml_attribute attSpeed = node.append_attribute("speed");
	attSpeed.set_value(speed);

	pugi::xml_attribute attActionTimer = node.append_attribute("actionTimer");
	attActionTimer.set_value(actionTimer);

	pugi::xml_attribute attActionTime = node.append_attribute("actionTime");
	attActionTime.set_value(actionTime);

	pugi::xml_attribute attState = node.append_attribute("state");
	attState.set_value(state);

	pugi::xml_attribute attTargetMember = node.append_attribute("targetMember");
	attTargetMember.set_value(targetMemberId);

	pugi::xml_attribute attTargetInfra = node.append_attribute("targetInfra");
	attTargetInfra.set_value(targetInfraId);

	pugi::xml_attribute attDisappearSpeed = node.append_attribute("disappearSpeed");
	attDisappearSpeed.set_value(disappearSpeed);

	pugi::xml_attribute attHairStyle = node.append_attribute("hairstyle");
	attHairStyle.set_value(hairStyle);

	pugi::xml_attribute attBodyStyle = node.append_attribute("bodystyle");
	attBodyStyle.set_value(bodyStyle);

	pugi::xml_attribute attStickStyle = node.append_attribute("stickstyle");
	attStickStyle.set_value(stickStyle);

	pugi::xml_attribute attClothesStyle = node.append_attribute("clothesstyle");
	attClothesStyle.set_value(clothesStyle);

	for (auto r : relationships)
	{
		pugi::xml_node nodeRel = node.append_child("RelationShip");

		pugi::xml_attribute attRelId = nodeRel.append_attribute("id");
		attRelId.set_value(r.first);

		pugi::xml_attribute attRelation = nodeRel.append_attribute("relation");
		attRelation.set_value(r.second.relation);

		pugi::xml_attribute attRelColor = nodeRel.append_attribute("color");
		std::string relColor = GetColorString(r.second.color);
		attRelColor.set_value(relColor.c_str());
	
		pugi::xml_attribute attRelName= nodeRel.append_attribute("name");
		attRelName.set_value(r.second.name.c_str());

		for (auto s : r.second.statuses)
		{
			pugi::xml_node nodeStat = nodeRel.append_child("Status");
			pugi::xml_attribute attStatus = nodeStat.append_attribute("statusid");
			attStatus.set_value(s);
		}
	}

	return doc;
}
int Member::nbMember(0);
int Member::GetId()
{
	return id;
}
bool Member::IsTouched(float x_touch, float y_touch) const
{
	int x_px (int(x_touch- x));
	int y_px (int(y_touch-y));
	std::vector<sf::Sprite> sprites{ hair,body,clothes,stick };
	for (auto sprite : sprites)
	{
		auto image (sprite.getTexture()->copyToImage());
		auto vect(image.getSize());
		if (x_px>=0 && y_px>=0 && x_px< sprite.getLocalBounds().width && y_px < sprite.getLocalBounds().height)//x_px < vect.x && y_px < vect.y)//
		{
			return true;//temporary, would checking the pixel alpha take too much? should be implement special hitboxes ?
			if (true && image.getPixel(x_px, y_px).a > 10)//(sprite.getTexture()->copyToImage().getPixel(x_px, y_px).a > 10)
			{
				return true;
			}
		}
		
	}
	return false;
}
sf::Color Member::GetHairColor()
{
	return hair.getColor();
}
std::string Member::GetName()
{
	return name;
}
void Member::Scale(float scale)
{

}
void Member::Handle()
{
	ImGui::Begin(name.c_str());
	ImGui::Text(MemberStateStrings[state].c_str());


	std::string reda("Red affiliation:");
	reda += to_string((int)std::ceil(redAffiliation * 100)) + "/100";
	
	ImGui::TextColored(ImColor(255, 0, 0, 255), reda.c_str());
	std::string bluea("Blue affiliation:");
	bluea += to_string((int)std::ceil(blueAffiliation * 100)) + "/100";
	ImGui::TextColored(ImColor(0, 255, 0, 255), bluea.c_str());
	std::string tol("Tolerance:");
	tol += to_string((int)std::ceil(tolerance * 100)) + "/100";
	ImGui::Text(tol.c_str());
	std::string agg("Aggressiveness:");
	agg += to_string((int)std::ceil(aggressiveness * 100)) + "/100";
	ImGui::Text(agg.c_str());
	std::string att("Attack:");
	att += to_string(attack);
	ImGui::Text(att.c_str());
	std::string def("Defense:");
	def += to_string(defense);
	ImGui::Text(def.c_str());

	ImGui::Text("RELATIONS:");

	for (auto r : relationships)
	{
		std::string s(r.second.name);
		s += ": ";
		s+= to_string((int)std::floor(r.second.relation * 100));
		ImGui::TextColored(SfToImColor(r.second.color), s.c_str());
		for (auto s : r.second.statuses)
		{
			ImGui::BulletText(RelationStatusStrings[s].c_str());
		}
	}


	if (ImGui::Button("Kill"))
	{
		Die();
	}
	ImGui::End();
}
void Member::Update()
{
	float deltaTime(GM.GetDeltaTime());
	actionTimer += deltaTime;

	if (targetMemberId >= 0 && !GM.members[targetMemberId].get())
	{
		targetMemberId = -1;
	}

	if (state == DYING)
	{

		std::vector<sf::Sprite*> sprites{ &hair,&clothes,&body,&stick };
		for (auto sprite : sprites)
		{
			sf::Color sprColor(sprite->getColor());
			sprColor.a = std::max(0, sprColor.a-(int)std::ceil(disappearSpeed*deltaTime));
			sprite->setColor(sprColor);
		}
		sf::Color sprColor(nametag.getFillColor());
		sprColor.a = std::max(0, sprColor.a - (int)std::ceil(disappearSpeed*deltaTime));
		nametag.setFillColor(sprColor);
		if (sprColor.a <= 0)
		{
			GM.EraseMember(id);
		}
	}
	else if (state == MOVING)
	{
		if (targetInfraId >= 0)
		{
			float targetX(GM.infrastructures[targetInfraId].get()->GetX());
			float targetY(GM.infrastructures[targetInfraId].get()->GetY());

			float delta_x(targetX - x);
			float delta_y(targetY - y);

			if (delta_x*delta_x + delta_y * delta_y > body.getLocalBounds().width*body.getLocalBounds().width)
			{
				float dx(deltaTime*speed*delta_x / (std::abs(delta_x) + std::abs(delta_y)));
				float dy(deltaTime*speed*delta_y / (std::abs(delta_x) + std::abs(delta_y)));
				Translate(dx, -dy);
			}
			else
			{
				//alone and occupied
				if (targetMemberId < 0 && GM.infrastructures[targetInfraId].get()->PlacesLeft()<1)
				{
					state = IDLE;
					actionTime = ((float)rand() / (RAND_MAX)) * 1.0f + 1.0f;
					actionTimer = 0.0f;
				}
				//with someone, occupied
				else if(targetMemberId >= 0 && GM.infrastructures[targetInfraId].get()->PlacesLeft() <2)
				{
					state = TALKING;
					actionTime = ((float)rand() / (RAND_MAX)) * 5.0f + 1.0f;
					actionTimer = 0.0f;
				}
				else
				{
					targetMemberId = -1;
					GM.infrastructures[targetInfraId].get()->Enters(id);
				}
			}
		}
		else if (targetMemberId>=0 && GM.members[targetMemberId].get() && GM.members[targetMemberId].get()->state!=DYING)
		{
			float targetX(GM.members[targetMemberId].get()->GetX());
			float targetY(GM.members[targetMemberId].get()->GetY());
			
			float delta_x(targetX - x);
			float delta_y(targetY - y);
			//target still far
			if (delta_x*delta_x+delta_y*delta_y>body.getLocalBounds().width*body.getLocalBounds().width)
			{
				float dx(deltaTime*speed*delta_x / (std::abs(delta_x) + std::abs(delta_y)));
				float dy(deltaTime*speed*delta_y / (std::abs(delta_x) + std::abs(delta_y)));
				Translate(dx, -dy);
				
			}
			//Interaction
			else
			{
				float diff(std::abs(blueAffiliation - GM.members[targetMemberId].get()->blueAffiliation));
				diff += (std::abs(redAffiliation - GM.members[targetMemberId].get()->redAffiliation));
				
				double rConflict(((float)rand() / (RAND_MAX)));
				if (2* rConflict <diff-tolerance-GM.members[targetMemberId].get()->tolerance)
				{
					AddRelation(targetMemberId, -0.3f);
					GM.members[targetMemberId].get()->AddRelation(id, -0.3f);
					//Conflict
					double rAttack(((float)rand() / (RAND_MAX)));
					if (rAttack < aggressiveness)
					{
						state = FIGHTING;
						actionTime = ((float)rand() / (RAND_MAX)) * 5.0f + 1.0f;
						actionTimer = 0.0f;
					}
					else//no aggression, dispute
					{
						state = TALKING;
						actionTime = ((float)rand() / (RAND_MAX)) * 5.0f + 1.0f;
						actionTimer = 0.0f;
					}
					if(rAttack<GM.members[targetMemberId].get()->aggressiveness)//aggression
					{
						GM.members[targetMemberId].get()->state = FIGHTING;
						GM.members[targetMemberId].get()->actionTime = ((float)rand() / (RAND_MAX)) * 5.0f + 1.0f;
						GM.members[targetMemberId].get()->actionTimer = 0.0f;
					}
					else//no aggression
					{
						GM.members[targetMemberId].get()->state = TALKING;
						GM.members[targetMemberId].get()->actionTime = ((float)rand() / (RAND_MAX)) * 5.0f + 1.0f;
						GM.members[targetMemberId].get()->actionTimer = 0.0f;
					}

					if (GM.members[targetMemberId].get()->relationships[id].relation < -0.6f)
					{
						GM.members[targetMemberId].get()->AddRelationStatus(id, ENEMY);
					}
					if (relationships[targetMemberId].relation < -0.6f)
					{
						AddRelationStatus(targetMemberId, ENEMY);
					}
				}
				else
				{
					state = TALKING;
					actionTime = ((float)rand() / (RAND_MAX)) * 5.0f + 1.0f;
					actionTimer = 0.0f;
					GM.members[targetMemberId].get()->state = TALKING;
					GM.members[targetMemberId].get()->actionTime = actionTime;
					GM.members[targetMemberId].get()->actionTimer = 0.0f;
					AddRelation(targetMemberId, 0.3f);
					GM.members[targetMemberId].get()->AddRelation(id, 0.3f);
					if (GM.members[targetMemberId].get()->relationships[id].relation > 0.6f)
					{
						GM.members[targetMemberId].get()->AddRelationStatus(id, FRIEND);
					}
					if (relationships[targetMemberId].relation > 0.6f)
					{
						AddRelationStatus(targetMemberId, FRIEND);
					}
					if (GM.members[targetMemberId].get()->relationships[id].relation > 0.8f)
					{
						GM.members[targetMemberId].get()->AddRelationStatus(id, BFF);
					}
					if (relationships[targetMemberId].relation > 0.8f)
					{
						AddRelationStatus(targetMemberId, BFF);
					}
				}

			}
			
		}
		else
		{
			state = IDLE;
		}
	}
	else if (state == FIGHTING)
	{
		//\\draw fighting icon

		if (targetMemberId < 0)
		{
			state = IDLE;
		}
		else if (actionTimer > actionTime)
		{
			double rRipost(((double)rand() / (RAND_MAX)));
			//Attack target
			if (!Attack(targetMemberId) && GM.members[targetMemberId].get()->aggressiveness + 0.5f > rRipost)
			{
				//Target riposts
				GM.members[targetMemberId].get()->state = FIGHTING;
				GM.members[targetMemberId].get()->Attack(id);
				GM.members[targetMemberId].get()->state = IDLE;
				GM.members[targetMemberId].get()->actionTime = ((float)rand() / (RAND_MAX)) * 3 + 1;
				GM.members[targetMemberId].get()->actionTimer = 0;
			}
			state = IDLE;
			actionTime = ((float)rand() / (RAND_MAX)) * 3 + 1;
			actionTimer = 0;
		}
	}
	else if (state == TALKING)
	{
		if (targetMemberId < 0)
		{
			state = IDLE;
		}
		else
		{
			AddRelation(targetMemberId, 0.0f);
			GM.members[targetMemberId].get()->AddRelation(id, 0.0f);
			//\\draw talking icon

			if (actionTimer > actionTime)
			{
				double rHangout(((double)rand() / (RAND_MAX)));
				//Hangout target
				float r1(relationships[targetMemberId].relation);
				float r2(GM.members[targetMemberId].get()->relationships[id].relation);

				if (2 * rHangout < r1 + r2)
				{
					//\\Go somewhere
					AddRelation(targetMemberId, 0.3f);
					GM.members[targetMemberId].get()->AddRelation(id, 0.3f);
				}
				state = IDLE;
				actionTime = ((float)rand() / (RAND_MAX)) * 3 + 1;
				actionTimer = 0;
				targetMemberId = -1;
			}
			else if (GM.members[targetMemberId].get()->state != TALKING)
			{
				//???
			}
		}
		
	}
	else if (state == WAITING)
	{
		if (targetMemberId < 0)
		{
			state = IDLE;
		}
		else if (actionTime > actionTimer && targetMemberId>=0)
		{
			if (GM.members[targetMemberId].get()->state == MOVING && GM.members[targetMemberId].get()->targetMemberId == id)
			{
				if (dice(2) == 2)
				{
					state = MOVING;
				}
				actionTimer = 0;
				actionTime = ((float)rand() / (RAND_MAX)) * 2 + 1;
			}
			else
			{
				state = IDLE;
			}
		}
		
	}
	if (state == IDLE)
	{
		if (actionTimer > actionTime)
		{
			
			if ((double)rand() / (RAND_MAX) > 0.5f)
			{
				if (GM.members.size() + GM.infrastructures.size()>1)
				{
					int t(dice(GM.members.size() + GM.infrastructures.size()) - 1);

					if (t < GM.members.size())
					{
						if (GM.members.size() > 1)
						{
							auto it = GM.members.begin();
							std::advance(it, t);
							if (it->first == id)
							{
								t = (t + dice(GM.members.size() - 1)) % GM.members.size();

								it = GM.members.begin();
								std::advance(it, t);
							}
							targetMemberId = it->first;

							if (GM.members[targetMemberId].get()->state == IDLE)
							{

								state = MOVING;
								GM.members[targetMemberId].get()->state = WAITING;
								targetMemberId = it->first;
								GM.members[targetMemberId].get()->targetMemberId = id;
								GM.members[targetMemberId].get()->actionTime = ((float)rand() / (RAND_MAX)) * 2 + 1;
								GM.members[targetMemberId].get()->actionTimer = 0;
								actionTimer = 0;
							}
						}
						
					}
					else
					{
						t -= GM.members.size();
						auto it = GM.infrastructures.begin();
						std::advance(it, t);
						
						if (it->second.get()->PlacesLeft() >= 1)
						{
							state = MOVING;
							targetInfraId = it->first;
						}
					}
					
					
				}
			}
			else
			{
				actionTimer = 0;
				actionTime = ((float)rand() / (RAND_MAX)) * 7 + 1;
			}

		}
	}

	
}
void Member::Translate(float x, float y)
{
	this->x += x;
	this->y -= y;
	hair.setPosition(this->x, this->y);
	body.setPosition(this->x, this->y);
	stick.setPosition(this->x, this->y);
	clothes.setPosition(this->x, this->y);
	nametag.setPosition(this->x + body.getLocalBounds().width / 2, this->y + body.getLocalBounds().height);
}
void Member::SetTargetMember(int id)
{
	targetMemberId = id;
}
int Member::GetTargetMember()
{
	return targetMemberId;
}
MemberState Member::GetState()
{
	return state;
}
void Member::AddAttack(int a)
{
	attack+=a;
}
void Member::AddDefense(int d)
{
	defense+=d;
}
void Member::SetTargetInfra(int id)
{
	targetInfraId = id;
}
int Member::GetTargetInfra()
{
	return targetInfraId;
}
void Member::SetState(MemberState state)
{
	this->state = state;
}
void Member::SetTimer(float time)
{
	actionTimer=0;
	actionTime = time;
}


bool Member::Attack(int target)
{
	if (GM.members[target].get()->defense<attack)  
	{
		GM.members[target].get()->Die(id);
		return true;
	}
	return false;
}

void Member::AddRelation(int target, float relation, bool relative)
{
	std::map<int, Relationship>::iterator it = relationships.find(target);
	Relationship relationship;

	if (it==relationships.end())
	{
		relationship.name = GM.members[target].get()->name;
		relationship.color = GM.members[target].get()->hair.getColor();
		relationship.relation = relation;
		relationships.insert({ target, relationship });
	}
	else
	{
		if (relative)
		{
			it->second.relation += relation;
		}
		else
		{
			it->second.relation = relation;
		}
	}
}
sf::Text Member::InitTag(std::string name)
{
	sf::Text nameTag(name, tagfont);
	nameTag.setFillColor(sf::Color::Blue);
	nameTag.setOrigin(nameTag.getLocalBounds().width / 2, nameTag.getLocalBounds().height / 2);
	nameTag.setPosition(x + body.getLocalBounds().width / 2, y + body.getLocalBounds().height);
	return nameTag;
}
void Member::AddRelationStatus(int targetId ,RelationStatus status, float relation, bool relative)
{
	std::map<int, Relationship>::iterator it = relationships.find(targetId);
	Relationship relationship;

	if (it == relationships.end())
	{
		relationship.name = GM.members[targetId].get()->name;
		relationship.color = GM.members[targetId].get()->hair.getColor();
		relationship.relation = relation;
		AddStatus(relationship.statuses, status);
		
		relationships.insert({ targetId, relationship });
	}
	else
	{
		relationship.name = GM.members[targetId].get()->name;
		relationship.color = GM.members[targetId].get()->hair.getColor();
		AddStatus(it->second.statuses, status);
		if (relative)
		{
			it->second.relation += relation;
		}
		else
		{
			it->second.relation = relation;
		}
	
	}
	
}

void AddStatus(std::vector<RelationStatus> &statuses, RelationStatus status)
{
	if (Contains(statuses, status))
	{
		return;
	}
	if (IsKiller(status))
	{
		unsigned int i(0);
		while (i<statuses.size())
		{
			if (IsFriendly(statuses[i]))
			{
				statuses[i] = statuses[statuses.size() - 1];
				statuses.pop_back();
			}
			else
			{
				++i;
			}
		}
		statuses.push_back(status);
	}
	else if (IsFriendly(status))
	{
		unsigned int i(0);
		while (i < statuses.size())
		{
			if (IsKiller(statuses[i]))
			{
				statuses[i] = statuses[statuses.size() - 1];
				statuses.pop_back();
			}
			else
			{
				++i;
			}
		}
		statuses.push_back(status);
	}
	else
	{
		statuses.push_back(status);
	}
}

bool IsFamily(RelationStatus status)
{
	return status == SIBLING || status == CHILD || status == PARENT;
}
bool IsKiller(RelationStatus status)
{
	return status == KILLERCHILD || status == KILLERFRIEND || status == KILLERSIBLING 
		|| status == KILLERPARENT;
}
bool IsFriendly(RelationStatus status)
{
	return status == FRIEND || status == BFF;
}



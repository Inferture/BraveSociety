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

using std::to_string;
Member::Member(float x, float y, float z, std::string name, float aggressiveness, float tolerance, float blueAffiliation, float redAffiliation,
	sf::Sprite hair, sf::Sprite body, sf::Sprite stick, sf::Sprite clothes, int attack, int defense) :
	GameObject(x, y, z), name(name), aggressiveness(aggressiveness), tolerance(tolerance),
	blueAffiliation(blueAffiliation), redAffiliation(redAffiliation), hair(hair), speed(30),
	body(body), clothes(clothes), stick(stick), attack(attack), defense(defense), disappearSpeed(100),
	id(nbMember), nametag(InitTag(name))
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
	if (killer)
	{
		for (auto rel : relationships)
		{
			for (auto s : rel.second.statuses)
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

void Member::Draw(sf::RenderWindow &window, float x, float y, bool selected) const
{
	window.draw(nametag);
	window.draw(body);
	window.draw(stick);
	window.draw(clothes);
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
			return true;//
			if (true && image.getPixel(x_px, y_px).a > 10)//(sprite.getTexture()->copyToImage().getPixel(x_px, y_px).a > 10)
			{
				return true;
			}
		}
		
	}
	return false;
}
void Member::Scale(float scale)
{

}
void Member::Handle()
{
	ImGui::Begin(name.c_str());
	//ImGui::Begin("lel");
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
		std::string s(GM.members[r.first].get()->name);
		s += ": ";
		s+= to_string((int)std::floor(r.second.relation * 100));
		ImGui::Text(s.c_str());
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

	if (state == DYING)
	{
		std::cout << "DYING";
		std::vector<sf::Sprite*> sprites{ &hair,&clothes,&body,&stick };
		for (auto sprite : sprites)
		{
			sf::Color sprColor(sprite->getColor());
			sprColor.a = std::max(0, sprColor.a-(int)std::ceil(disappearSpeed*deltaTime));
			sprite->setColor(sprColor);
		}
		/*
		sf::Color hairColor(hair.getColor());
		hairColor.a = std::max(0,(int)std::ceil(disappearSpeed*deltaTime));

		sf::Color bodyColor(body.getColor());
		hair.setColor(hairColor);
		body.setColor(bodyColor);*/
	}
	else if (state == MOVING)
	{
		std::cout << "MOVING";
		if (targetMemberId>=0)
		{
			float targetX(GM.members[targetMemberId].get()->GetX());
			float targetY(GM.members[targetMemberId].get()->GetY());
			
			float delta_x(targetX - x);
			float delta_y(targetY - y);
			/*std::cout << "\nX"<<x;
			std::cout << "\nY"<<y;
			std::cout << "\ntargetX"<<targetX;
			std::cout << "\ntargetY"<<targetY;*/
			std::cout << "\nbodyW\n" << body.getLocalBounds().width;
			//target still far
			if (delta_x*delta_x+delta_y*delta_y>body.getLocalBounds().width*body.getLocalBounds().width)
			{
				float dx(deltaTime*speed*delta_x / (std::abs(delta_x) + std::abs(delta_y)));
				float dy(deltaTime*speed*delta_y / (std::abs(delta_x) + std::abs(delta_y)));
				std::cout << "\ndeltatime:" << deltaTime << "\nspeed:" << speed << "\ndelta_y" << delta_y;
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
	}
	else if (state == FIGHTING)
	{
		std::cout << "FIGHTING";
		//\\draw fighting icon


		if (actionTimer > actionTime)
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
		std::cout << "TALKING";
		AddRelation(targetMemberId, 0.0f);
		GM.members[targetMemberId].get()->AddRelation(id, 0.0f);
		//\\draw talking icon
		if (GM.members[targetMemberId].get()->state != TALKING)
		{
			//\\dead ?
		}
		else if (actionTimer > actionTime)
		{
			double rHangout(((double)rand() / (RAND_MAX)));
			//Hangout target
			float r1(relationships[targetMemberId].relation);
			float r2(GM.members[targetMemberId].get()->relationships[id].relation);
			
			if (2*rHangout<r1+r2)
			{
				//\\Go somewhere
				AddRelation(targetMemberId, 0.3f);
				GM.members[targetMemberId].get()->AddRelation(id, 0.3f);
			}
			state = IDLE;
			actionTime = ((float)rand() / (RAND_MAX)) * 3 + 1;
			actionTimer = 0;
		}
	}

	if (state == IDLE)
	{
		std::cout << "IDLE";
		if (actionTimer > actionTime)
		{
			actionTimer = 0;
			if ((double)rand() / (RAND_MAX) > 0.5f)
			{
				if (GM.members.size()>1)
				{
					state = MOVING;
					auto it = GM.members.begin();

					int t(dice(GM.members.size()) - 1);
					
					if (it->first == id)
					{
						t = (t + dice(GM.members.size() - 1)) % GM.members.size();

						it = GM.members.begin();
						std::advance(it, t);
					}
					
					targetMemberId = it->first;
				}
			}
			else
			{
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
		relationship.relation = relation;
		AddStatus(relationship.statuses, status);
		
		relationships.insert({ targetId, relationship });
	}
	else
	{
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



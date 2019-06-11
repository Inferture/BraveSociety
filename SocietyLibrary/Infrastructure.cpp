#include "stdafx.h"
#include "infrastructure.h"
#include "Member.h"
#include <string>
#include <vector>
#include <string>
#include <imgui.h>
#include <sfml-imgui/imgui-SFML.hpp>
#include "ColorManipulation.h"
#include "XMLManipulation.h"
#include "General.h"

extern std::vector<sf::Texture> texturesHouse;
extern GameManager  GM;

int Infrastructure::nbInfrastructures;

Infrastructure::Infrastructure(float x, float y, float z, std::string name, int bonusDefense, int bonusAttack, int maxCapacity,
	sf::Sprite sprInfrastructure, float timeInside) : GameObject(x, y, z), name(name), bonusDefense(bonusDefense),
	bonusAttack(bonusAttack), maxCapacity(maxCapacity), sprInfrastructure(sprInfrastructure),
	timeInside(timeInside), id(nbInfrastructures)
{
	++nbInfrastructures;
	this->sprInfrastructure.setPosition(x, y);
};


Infrastructure::Infrastructure(Infrastructure & infra) :
	GameObject(infra.x, infra.y, infra.z), name(infra.name), bonusDefense(infra.bonusDefense), bonusAttack(infra.bonusAttack),
	maxCapacity(infra.maxCapacity), sprInfrastructure(infra.sprInfrastructure), id(infra.id),
	timeInside(infra.timeInside), membersInside()
{
	++nbInfrastructures;
	for (int i = 0; i < infra.membersInside.size(); i++)
	{
		membersInside.push_back(std::make_pair(std::move(infra.membersInside[i].first), infra.membersInside[i].second));
	}
	this->sprInfrastructure.setPosition(x, y);

}
void Infrastructure::Draw(sf::RenderWindow &window, float x, float y, bool selected) const {
	window.draw(sprInfrastructure);
}
bool Infrastructure::IsTouched(float x_touch, float y_touch) const {
	int x_px(int(x_touch - x));
	int y_px(int(y_touch - y));
	
	return x_px >= 0 && y_px >= 0 && x_px < sprInfrastructure.getLocalBounds().width && y_px < sprInfrastructure.getLocalBounds().height;
	
}
void Infrastructure::Scale(float scale) {
	return;
}

Infrastructure::Infrastructure(pugi::xml_node& node):
	GameObject(node.attribute("x").as_float(), node.attribute("y").as_float(), node.attribute("z").as_float()),
	name(node.attribute("name").as_string()), id(node.attribute("id").as_int()),
	bonusAttack(node.attribute("bonusAttack").as_int()), bonusDefense(node.attribute("bonusDefense").as_int()),
	maxCapacity(node.attribute("maxCapacity").as_int()), timeInside(node.attribute("timeInside").as_float())	
{
	++nbInfrastructures;
	sprInfrastructure.setTexture(texturesHouse[0]);
	sprInfrastructure.setColor(GetStringColor(node.attribute("mainColor").as_string()));

	this->sprInfrastructure.setPosition(x, y);

	pugi::xml_node childNode(node.first_child());
	while (childNode)
	{
		Member mem(childNode);
		float timeStayedInside(childNode.attribute("timeStayedInside").as_float());
		membersInside.push_back({std::make_unique<Member>(mem), timeStayedInside});

		childNode = childNode.next_sibling();
	}

}


pugi::xml_document Infrastructure::Serialize() const {
	pugi::xml_document doc;
	doc.set_name("InfraDoc");

	pugi::xml_node node;
	node = doc.append_child("Infrastructure");

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

	pugi::xml_attribute attAttack = node.append_attribute("bonusAttack");
	attAttack.set_value(bonusAttack);

	pugi::xml_attribute attDefense = node.append_attribute("bonusDefense");
	attDefense.set_value(bonusDefense);

	pugi::xml_attribute attCapcacity = node.append_attribute("maxCapacity");
	attCapcacity.set_value(maxCapacity);

	pugi::xml_attribute attTimeInside = node.append_attribute("timeInside");
	attTimeInside.set_value(timeInside);
	pugi::xml_attribute attHairColor = node.append_attribute("mainColor");
	std::string mainColor = GetColorString(sprInfrastructure.getColor());
	attHairColor.set_value(mainColor.c_str());

	for (auto& mem : membersInside)
	{
		pugi::xml_document memberDoc = mem.first.get()->Serialize();
		pugi::xml_attribute attTimeStayedInside = memberDoc.first_child().append_attribute("timeStayedInside");
		attTimeStayedInside.set_value(mem.second);
		add_child(doc, memberDoc);
	}

	return doc;
}

int Infrastructure::GetId()
{
	return id;
}
int Infrastructure::PlacesLeft()
{
	return maxCapacity - membersInside.size();
}

void Infrastructure::Enters(int memberid)
{
	membersInside.push_back({std::move(GM.members[memberid]),0 });
	GM.EraseMember(memberid);
}
void Infrastructure::Update()
{
	
	float deltatime(GM.GetDeltaTime());
	int i(0);
	while (i < membersInside.size())
	{
		auto& v(membersInside[i]);
		v.second += deltatime;
		int idmem = v.first.get()->GetId();
		if (v.second > timeInside)
		{

			
			GM.members.insert({idmem, std::move(v.first)});

			membersInside[i] = std::make_pair(std::move(membersInside[membersInside.size() - 1].first), membersInside[membersInside.size() - 1].second);
			membersInside.pop_back();
			GM.members[idmem].get()->SetTargetInfra(-1);
			GM.members[idmem].get()->SetState(IDLE);
			GM.members[idmem].get()->SetTimer(5);
			
			GM.members[idmem].get()->AddAttack(bonusAttack);
			GM.members[idmem].get()->AddDefense(bonusDefense);
		}
		else
		{
			i++;
		}
	
	}
}
void Infrastructure::Handle()
{
	ImGui::Begin(name.c_str());
	
	if (bonusDefense != 0)
	{
		std::string s("Defense:");
		if (bonusDefense > 0)
		{
			s += "+";
		}
		s += std::to_string(bonusDefense);
		ImGui::Text(s.c_str());
	}
	if (bonusAttack != 0)
	{
		std::string s("Attack:");
		if (bonusAttack > 0)
		{
			s += "+";
		}
		s += std::to_string(bonusAttack);
		ImGui::Text(s.c_str());
	}
	std::string sCap("Capacity:");
	sCap += std::to_string(membersInside.size());
	sCap += "/";
	sCap += std::to_string(maxCapacity);
	if (membersInside.size() >= maxCapacity)
	{
		ImGui::TextColored(ImColor(1,0,0), sCap.c_str());
	}
	else
	{
		ImGui::Text(sCap.c_str());
	}
	ImGui::Text("Members inside:");
	for (auto& mem : membersInside)
	{
		if (mem.first.get());
		std::string s(mem.first.get()->GetName());
		s += " (";
		s += std::to_string((double)((int)(mem.second*100)/100.0));
		s += "/";
		s += std::to_string(timeInside);
		s += ")";
		ImGui::TextColored(SfToImColor(mem.first.get()->GetHairColor()),s.c_str());
	}
	ImGui::End();
}
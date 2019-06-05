#include "stdafx.h"
#include "infrastructure.h"
#include "Member.h"
#include <string>
#include <vector>
#include <string>
#include <imgui.h>
#include <sfml-imgui/imgui-SFML.hpp>

void Infrastructure::Draw(sf::RenderWindow &window, float x, float y, bool selected) const {
	window.draw(sprInfrastructure);
}
bool Infrastructure::IsTouched(float x_touch, float y_touch) const {
	return false;
}
void Infrastructure::Scale(float scale) {
	return;
}

pugi::xml_document Infrastructure::Serialize() const {
	pugi::xml_document doc;
	return doc;
}
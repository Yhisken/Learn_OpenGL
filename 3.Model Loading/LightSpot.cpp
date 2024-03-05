#include "LightSpot.h"

LightSpot::LightSpot(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color):
	position(_positon),
	angles(_angles),
	color(_color)
{
	constant = 1.0f;
	linear = 0.1f;
	quadratic = 0.001f;
	UpdateDirection();
}

void LightSpot::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = glm::rotateZ(direction, angles.z);
	direction = -direction;
}

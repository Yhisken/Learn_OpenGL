#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color) :
	position(_positon),
	angles(_angles),
	color(_color)
{
	constant = 1.0f;
	linear = 0.1f;
	quadratic = 0.001f;

}

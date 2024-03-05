#pragma once
#include <glm.hpp>
#include<gtx/rotate_vector.hpp>
//#include <gtc/matrix_transform.hpp>
class LightSpot
{
public:
	LightSpot(glm::vec3 _positon, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;
	float constant;
	float linear;
	float quadratic;
	void UpdateDirection();
	float cosPhyInner = 0.94f;
	float cosPhyOutter = 0.9f;
};


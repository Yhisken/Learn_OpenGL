#pragma once
#include "Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Material
{
public:
	Shader* shader;
	unsigned int diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	float shininess;
	Material(Shader * _shader,unsigned int _diffuse,glm::vec3 _specular,glm::vec3 _ambient, float _shininess);
};


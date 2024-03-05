#pragma once
#include <string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	std::string vertexString;
	std::string fragmentString;
	const char* vertexSource;//const 只能写入一次
	const char* fragmentSource;
	unsigned int ID;  // Shader Program ID
	void use();
	void SetUniform3f(const char* paramNameString , glm::vec3 param);//封装
	void SetUniform1f(const char* paramNameString, float param);//封装
	void SetUniform1i(const char* paramNameString, int slot);
	//~Shader();
private:
	void checkCompileErrors(unsigned int shader, std::string type);
};


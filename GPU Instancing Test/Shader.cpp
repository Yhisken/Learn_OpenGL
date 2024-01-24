#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
Shader::Shader(const char* vertexPath , const char* fragmentPath)
{
	ifstream vertexfile;
	ifstream fragmentfile;//Open

	stringstream vertexstream;
	stringstream fragmentstream; //FileBuffer(in Memory)   (next step: in to string(中转站) and become char array)

	vertexfile.open(vertexPath);
	fragmentfile.open(fragmentPath);

	vertexfile.exceptions(ifstream::failbit | ifstream::badbit);
	fragmentfile.exceptions(ifstream::failbit | ifstream::badbit);

	try {
		if (!vertexfile.is_open() || !fragmentfile.is_open()) {
			throw exception("open file error");
		}
		vertexstream << vertexfile.rdbuf();//FileBuffer<<
		fragmentstream << fragmentfile.rdbuf();

		vertexString = vertexstream.str();//string
		fragmentString = fragmentstream.str();

		vertexSource = vertexString.c_str();//char array
		fragmentSource = fragmentString.c_str();

		unsigned int vertex, fragment;
		vertex = glCreateShader(GL_VERTEX_SHADER); //创建Shader类型
		glShaderSource(vertex, 1, &vertexSource, NULL);//将Shader源码附加到Shader对象上
		glCompileShader(vertex);//转为二进制
		checkCompileErrors(vertex, "VERTEX");//错误检测

		fragment = glCreateShader(GL_FRAGMENT_SHADER);//创建Shader类型
		glShaderSource(fragment, 1, &fragmentSource, NULL);	
		glCompileShader(fragment);//转为二进制
		checkCompileErrors(fragment, "FRAGMENT");//错误检测


		ID = glCreateProgram();//创建Program类型
		glAttachShader(ID, vertex);//将Shader对象附加到Program对象上
		glAttachShader(ID, fragment);
		glLinkProgram(ID);//链接Program对象( 把vertex和fragment链接)
		checkCompileErrors(ID, "PROGRAM");//错误检测

		glDeleteShader(vertex);//删除Shader对象
		glDeleteShader(fragment);//连接完，不需要了

		//printf(vertexSource);
		//printf(fragmentSource);
	}
	catch(const std::exception&ex){
		printf(ex.what());
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int shaderID, std::string type)//错误检测
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")//如果不是Program类型
	{
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);//获取Shader对象的信息
		if (!success)
		{
			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);//获取Shader对象的信息
			cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
		}
	}
	else//如果是Program类型
	{
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);//获取Program对象的信息
		if (!success)
		{
			glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);//获取Program对象的信息
			cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
		}
	}
}

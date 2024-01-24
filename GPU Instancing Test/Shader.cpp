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
	stringstream fragmentstream; //FileBuffer(in Memory)   (next step: in to string(��תվ) and become char array)

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
		vertex = glCreateShader(GL_VERTEX_SHADER); //����Shader����
		glShaderSource(vertex, 1, &vertexSource, NULL);//��ShaderԴ�븽�ӵ�Shader������
		glCompileShader(vertex);//תΪ������
		checkCompileErrors(vertex, "VERTEX");//������

		fragment = glCreateShader(GL_FRAGMENT_SHADER);//����Shader����
		glShaderSource(fragment, 1, &fragmentSource, NULL);	
		glCompileShader(fragment);//תΪ������
		checkCompileErrors(fragment, "FRAGMENT");//������


		ID = glCreateProgram();//����Program����
		glAttachShader(ID, vertex);//��Shader���󸽼ӵ�Program������
		glAttachShader(ID, fragment);
		glLinkProgram(ID);//����Program����( ��vertex��fragment����)
		checkCompileErrors(ID, "PROGRAM");//������

		glDeleteShader(vertex);//ɾ��Shader����
		glDeleteShader(fragment);//�����꣬����Ҫ��

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

void Shader::checkCompileErrors(unsigned int shaderID, std::string type)//������
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")//�������Program����
	{
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);//��ȡShader�������Ϣ
		if (!success)
		{
			glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);//��ȡShader�������Ϣ
			cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
		}
	}
	else//�����Program����
	{
		glGetProgramiv(shaderID, GL_LINK_STATUS, &success);//��ȡProgram�������Ϣ
		if (!success)
		{
			glGetProgramInfoLog(shaderID, 1024, NULL, infoLog);//��ȡProgram�������Ϣ
			cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << endl;
		}
	}
}

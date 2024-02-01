#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
using namespace std;

float lastX;
float lastY;
bool firstMouse = true;
//Camera camera(glm::vec3 (0,0,3.0f),glm::vec3 (0,0,0),glm::vec3(0,1.0f,1));
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.speedZ = -1.0f;
	}
	else {
		camera.speedZ = 0.0;
	}

}
void mouse_callback(GLFWwindow* window, double xpos, double ypos) 
{
	if (firstMouse == true) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float deltaX, deltaY;
	deltaX = xpos - lastX;
	deltaY = ypos - lastY;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(deltaX, deltaY);
	//cout << "xpos:" << xpos << "ypos:" << ypos << endl;
}
/*
float vertices[] = {
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // ����
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // ����
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ����
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ����
 // 0 1 2, 2 1 3
};*/
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
unsigned int indices[] = {
	0, 1, 2,
	2, 3, 0
}; //��������

glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};


int main() {


	glfwInit();//��ʼ��GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//���汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//�ΰ汾��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//����ģʽ
	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "ShuoYan_OpenGL", NULL, NULL);//��ߣ�����
	if (window == NULL) {
		cout<<"Failed to create GLFW window"<<endl;
		glfwTerminate();//��ֹ
		return -1;
	}
	glfwMakeContextCurrent(window);//�����ڵ�����������Ϊ��ǰ�̵߳���������
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//���������
	glfwSetCursorPosCallback(window, mouse_callback);//���ص�����

	//��ʼ��GLEW
	glewExperimental = GL_TRUE;//ʹ����glewExperimental(ûɶʵ������)
	if (glewInit() != GLEW_OK) {
		cout<<"Failed to initialize GLEW"<<endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);//�����ӿڴ�С
	//glEnable(GL_CULL_FACE);//�޳�
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);//��Ȳ���

	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");



	unsigned int VAO;//�����������
	glGenVertexArrays(1, & VAO); //&VAO����һ�������������
	glBindVertexArray(VAO);//��VAO

	unsigned int VBO;//���㻺�����
	glGenBuffers(1, &VBO);//����һ�����㻺�����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//�󶨻���
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//���ƶ������ݵ�������

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//�������������
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//����������������


	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,5*sizeof(float) , (void*)0);//�����������ݡ���������ֵ
	glEnableVertexAttribArray(0);//���ö�������
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));//�����������ݡ���������ֵ
	//glEnableVertexAttribArray(1);//������ɫ����
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));//�����������ݡ���������ֵ
	glEnableVertexAttribArray(2);//����UV����

	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);//�������������
	glActiveTexture(GL_TEXTURE0);//��������Ԫ0��
	glBindTexture(GL_TEXTURE_2D, TexBufferA);//�����������

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);//����ͼƬ
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,data);//��������(��������)
		glGenerateMipmap(GL_TEXTURE_2D);//���ɶ༶��Զ����
	}
	else
	{
		cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);//�ͷ�ͼƬ�ڴ�

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);//�������������(ע����gentex����genbuffer)
	glActiveTexture(GL_TEXTURE1);//��������Ԫ0��
	glBindTexture(GL_TEXTURE_2D, TexBufferB);//�����������
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);//����ͼƬ
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);//��������(��������)
		glGenerateMipmap(GL_TEXTURE_2D);//���ɶ༶��Զ����
	}
	else
	{
		cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data2);//�ͷ�ͼƬ�ڴ�

	//����任����
	//glm::mat4 trans;

	glm::mat4 modelMat;

	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
	glm::mat4 viewMat;
	//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	

	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,100.0f);//FOV , ��߱ȣ���ƽ�棬Զƽ�档


	while (!glfwWindowShouldClose(window)) {//ѭ����Ⱦ
		processInput(window);//����

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//����������ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//����

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);//�����������
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);


		glBindVertexArray(VAO);//��VAO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//�������������


		


			myShader->use();

			//=====================================================
			glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);//��������Ԫ |  ���Է���ѭ��֮��
			glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);//��������Ԫ== |   Tex���ò�����Batch
			//=====================================================  ������Ա����沢��֡����
			viewMat = camera.GetViewMatrix();


			for (int i = 0; i < 10; i++) {//10��Batch + 10��
				glm::mat4 modelMat2;
				modelMat2 = glm::translate(modelMat2, cubePositions[i]);
				glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));//���ݱ任����
				glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));//���ݱ任����
				glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));//���ݱ任����
				glDrawArrays(GL_TRIANGLES, 0, 36);//����������(��������
			}



			//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));//���ݱ任����

			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//����������(��������



		

		glfwSwapBuffers(window);//��������
		glfwPollEvents();//����Ƿ񴥷��¼�
		camera.UpdateCameraPos();
	}
	glfwTerminate();//��ֹ
	return 0;
}

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Camera.h"
using namespace std;

#pragma region Camera Declare
//Camera camera(glm::vec3 (0,0,3.0f),glm::vec3 (0,0,0),glm::vec3(0,1.0f,1));
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Light Declare
LightDirectional lightD = LightDirectional(glm::vec3(1.0f, 1.0f, -1.0f),
	glm::vec3(glm::radians(45.0f), glm:: radians(45.0f), 0),
	glm::vec3 (1.0f,1.0f,1.0f));

LightPoint lightP0 = LightPoint(glm::vec3(1.0f,0,0),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 0, 0));
LightPoint lightP1 = LightPoint(glm::vec3(0,1.0f,0),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0, 1.0f, 0));
LightPoint lightP2 = LightPoint(glm::vec3(0, 0, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(0, 0, 1.0f));
LightPoint lightP3 = LightPoint(glm::vec3(1.0f, 1.0f, 1.0f),
	glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
	glm::vec3(1.0f, 1.0f, 1.0f));

LightSpot lightS = LightSpot(glm::vec3(0, 5.0f, 0),
	glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0),
	glm::vec3(1.0f, 1.0f, 1.0f));
#pragma endregion



#pragma region Input Declare
float lastX;
float lastY;
bool firstMouse = true;

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
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.speedX = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.speedX = -1.0f;
	}
	else {
		camera.speedX = 0.0;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera.speedY = -1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera.speedY = 1.0f;
	}
	else {
		camera.speedY = 0.0;
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
#pragma endregion

#pragma region Model Data
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
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

#pragma endregion

unsigned int  LoadImageToGPU(const char* filename,GLint internalFormat,GLenum format,int textureSlot) {
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);//�������������
	glActiveTexture(GL_TEXTURE0 + textureSlot);//��������Ԫ0��
	glBindTexture(GL_TEXTURE_2D, TexBuffer);//�����������

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);//����ͼƬ
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);//��������(��������)
		glGenerateMipmap(GL_TEXTURE_2D);//���ɶ༶��Զ����
	}
	else
	{
		cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);//�ͷ�ͼƬ�ڴ�
	return TexBuffer;
}
int main() {

	#pragma region Open a Window

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

		glEnable(GL_DEPTH_TEST);//��Ȳ���
	#pragma endregion

	#pragma region Init Shader Program
		Shader* myShader = new Shader("vertexSource.vert", "fragmentSource.frag");
	#pragma endregion

#pragma region InitMaterial
		Material* myMaterial = new Material(myShader,
			LoadImageToGPU("container2.png",GL_RGBA,GL_RGBA,0),
			glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3(1.0f, 1.0f, 1.0f),
			32);
#pragma endregion

	#pragma region Init and Load Models to VAO, VBO
		unsigned int VAO;//�����������
		glGenVertexArrays(1, & VAO); //&VAO����һ�������������
		glBindVertexArray(VAO);//��VAO

		unsigned int VBO;//���㻺�����
		glGenBuffers(1, &VBO);//����һ�����㻺�����
		glBindBuffer(GL_ARRAY_BUFFER, VBO);//�󶨻���
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//���ƶ������ݵ�������


		glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,8*sizeof(float) , (void*)0);//�����������ݡ���������ֵ
		glEnableVertexAttribArray(0);//���ö�������
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));//�����������ݡ���������ֵ
		glEnableVertexAttribArray(1);//������ɫ����
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));//�����������ݡ���������ֵ
		glEnableVertexAttribArray(2);//����UV����
		//glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));//�����������ݡ���������ֵ
		//glEnableVertexAttribArray(3);//����UV����
	#pragma endregion

	#pragma region Init and Load Texture
		//unsigned int TexBufferA;
		//TexBufferA = LoadImageToGPU("container.jpg", GL_RGB, GL_RGB, 0);
		//
		//unsigned int TexBufferB;
		//TexBufferB = LoadImageToGPU("awesomefaCe.png", GL_RGBA, GL_RGBA, 0);
	#pragma endregion

	#pragma region Prepare MVP matrices
		//����任����

		glm::mat4 modelMat;
		glm::mat4 viewMat;

		glm::mat4 projMat;
		projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,100.0f);//FOV , ��߱ȣ���ƽ�棬Զƽ�档
	#pragma endregion

	while (!glfwWindowShouldClose(window)) {//ѭ����Ⱦ

		//Process Input
		processInput(window);//����

		//Clear Screen	
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);//����������ɫ
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//����


		viewMat = camera.GetViewMatrix();


			for (int i = 0; i < 10; i++) {
				//Set Model Matrix 
				modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);

				//Set View and Projection Matrices here if you want

				//Set Matreial  -> Shader Program
				myShader->use();

				// Set Material  -> Textures
				//glActiveTexture(GL_TEXTURE0);
				//glBindTexture(GL_TEXTURE_2D, TexBufferA);//�����������
				//glActiveTexture(GL_TEXTURE1);
				//glBindTexture(GL_TEXTURE_2D, TexBufferB);

				//Set Material Uniforms
				//glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);//��������Ԫ  
				//glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);//��������Ԫ== 
				glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));//���ݱ任����
				glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));//���ݱ任����
				glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));//���ݱ任����

				//glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
				glUniform3f(glGetUniformLocation(myShader->ID, "objColor"), 1.0, 1.0f, 1.0f);
				glUniform3f(glGetUniformLocation(myShader->ID, "ambientColor"), 0.1f, 0.1f, 0.1f);
				//glUniform3f(glGetUniformLocation(myShader->ID, "lightPos"), light.position.x, light.position.y, light.position.z);
				//glUniform3f(glGetUniformLocation(myShader->ID, "lightColor"), light.color.x, light.color.y, light.color.z);
				//glUniform3f(glGetUniformLocation(myShader->ID, "lightDirUniform"), light.direction.x, light.direction.y, light.direction.z);
//lightD
				glUniform3f(glGetUniformLocation(myShader->ID, "lightD.pos"), lightD.position.x, lightD.position.y, lightD.position.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightD.color"), lightD.color.x, lightD.color.y, lightD.color.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightD.dirToLight"), lightD.direction.x, lightD.direction.y, lightD.direction.z);
//lighP
				glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.pos"), lightP0.position.x, lightP0.position.y, lightP0.position.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.color"), lightP0.color.x, lightP0.color.y, lightP0.color.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightP0.dirToLight"), lightP0.direction.x, lightP0.direction.y, lightP0.direction.z);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.constant"), lightP0.constant);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.linear"), lightP0.linear);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP0.quadratic"), lightP0.quadratic); 

				glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.pos"), lightP1.position.x, lightP1.position.y, lightP1.position.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.color"), lightP1.color.x, lightP1.color.y, lightP1.color.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightP1.dirToLight"), lightP1.direction.x, lightP1.direction.y, lightP1.direction.z);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.constant"), lightP1.constant);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.linear"), lightP1.linear);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP1.quadratic"), lightP1.quadratic);

				glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.pos"), lightP2.position.x, lightP2.position.y, lightP2.position.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.color"), lightP2.color.x, lightP2.color.y, lightP2.color.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightP2.dirToLight"), lightP2.direction.x, lightP2.direction.y, lightP2.direction.z);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.constant"), lightP2.constant);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.linear"), lightP2.linear);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP2.quadratic"), lightP2.quadratic);

				glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.pos"), lightP3.position.x, lightP3.position.y, lightP3.position.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.color"), lightP3.color.x, lightP3.color.y, lightP3.color.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightP3.dirToLight"), lightP3.direction.x, lightP3.direction.y, lightP3.direction.z);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.constant"), lightP3.constant);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.linear"), lightP3.linear);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightP3.quadratic"), lightP3.quadratic);

				glUniform3f(glGetUniformLocation(myShader->ID, "lightS.pos"), lightS.position.x, lightS.position.y, lightS.position.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightS.color"), lightS.color.x, lightS.color.y, lightS.color.z);
				glUniform3f(glGetUniformLocation(myShader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightS.constant"), lightS.constant);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightS.linear"), lightS.linear);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightS.quadratic"), lightS.quadratic);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
				glUniform1f(glGetUniformLocation(myShader->ID, "lightS.cosPhyOutter"), lightS.cosPhyOutter);
				// 
				//glUniform1f(glGetUniformLocation(myShader->ID, "lightP.constant"), light.constant);
				//glUniform1f(glGetUniformLocation(myShader->ID, "lightP.linear"), light.linear);
				//glUniform1f(glGetUniformLocation(myShader->ID, "lightP.quadratic"), light.quadratic);

				glUniform3f(glGetUniformLocation(myShader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

				myMaterial ->shader->SetUniform3f("material.ambient", myMaterial->ambient);
				//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
				myMaterial->shader->SetUniform1i("material.diffuse", 0);
				myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
				myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);

				// Set Model
				glBindVertexArray(VAO);//��VAO

				// Draw Call
				glDrawArrays(GL_TRIANGLES, 0, 36);//����������(��������
			}
		
		//Clean Up,prepare for next render loop
		glfwSwapBuffers(window);//��������
		glfwPollEvents();//����Ƿ񴥷��¼�
		camera.UpdateCameraPos();
	}
	//Exit Program
	glfwTerminate();//��ֹ
	return 0;
}

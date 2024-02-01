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
	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
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
}; //索引数组

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


	glfwInit();//初始化GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);//主版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);//次版本号
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//核心模式
	//Open GLFW Window
	GLFWwindow* window = glfwCreateWindow(800, 600, "ShuoYan_OpenGL", NULL, NULL);//宽高，标题
	if (window == NULL) {
		cout<<"Failed to create GLFW window"<<endl;
		glfwTerminate();//终止
		return -1;
	}
	glfwMakeContextCurrent(window);//将窗口的上下文设置为当前线程的主上下文
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//隐藏鼠标光标
	glfwSetCursorPosCallback(window, mouse_callback);//鼠标回调函数

	//初始化GLEW
	glewExperimental = GL_TRUE;//使用了glewExperimental(没啥实际意义)
	if (glewInit() != GLEW_OK) {
		cout<<"Failed to initialize GLEW"<<endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, 800, 600);//设置视口大小
	//glEnable(GL_CULL_FACE);//剔除
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);//深度测试

	Shader* myShader = new Shader("vertexSource.txt", "fragmentSource.txt");



	unsigned int VAO;//顶点数组对象
	glGenVertexArrays(1, & VAO); //&VAO生成一个顶点数组对象
	glBindVertexArray(VAO);//绑定VAO

	unsigned int VBO;//顶点缓冲对象
	glGenBuffers(1, &VBO);//生成一个顶点缓冲对象
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定缓冲
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//复制顶点数据到缓冲中

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定索引缓冲对象
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);//复制索引到缓冲中


	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE,5*sizeof(float) , (void*)0);//解析顶点数据。顶点特征值
	glEnableVertexAttribArray(0);//启用顶点属性
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3*sizeof(float)));//解析顶点数据。顶点特征值
	//glEnableVertexAttribArray(1);//启用颜色属性
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));//解析顶点数据。顶点特征值
	glEnableVertexAttribArray(2);//启用UV属性

	unsigned int TexBufferA;
	glGenTextures(1, &TexBufferA);//生成纹理缓冲对象
	glActiveTexture(GL_TEXTURE0);//激活纹理单元0号
	glBindTexture(GL_TEXTURE_2D, TexBufferA);//绑定纹理缓冲对象

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);//加载图片
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,data);//生成纹理(灌入数据)
		glGenerateMipmap(GL_TEXTURE_2D);//生成多级渐远纹理
	}
	else
	{
		cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);//释放图片内存

	unsigned int TexBufferB;
	glGenTextures(1, &TexBufferB);//生成纹理缓冲对象(注意是gentex不是genbuffer)
	glActiveTexture(GL_TEXTURE1);//激活纹理单元0号
	glBindTexture(GL_TEXTURE_2D, TexBufferB);//绑定纹理缓冲对象
	unsigned char* data2 = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);//加载图片
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);//生成纹理(灌入数据)
		glGenerateMipmap(GL_TEXTURE_2D);//生成多级渐远纹理
	}
	else
	{
		cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data2);//释放图片内存

	//计算变换矩阵
	//glm::mat4 trans;

	glm::mat4 modelMat;

	modelMat = glm::rotate(modelMat, glm::radians(-55.0f), glm::vec3(1.0f, 0, 0));
	glm::mat4 viewMat;
	//viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -3.0f));
	

	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,100.0f);//FOV , 宽高比，近平面，远平面。


	while (!glfwWindowShouldClose(window)) {//循环渲染
		processInput(window);//输入

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);//设置清屏颜色
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清屏

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TexBufferA);//绑定纹理缓冲对象
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, TexBufferB);


		glBindVertexArray(VAO);//绑定VAO
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);//绑定索引缓冲对象


		


			myShader->use();

			//=====================================================
			glUniform1i(glGetUniformLocation(myShader->ID, "ourTexture"), 0);//设置纹理单元 |  可以放在循环之外
			glUniform1i(glGetUniformLocation(myShader->ID, "ourFace"), 1);//设置纹理单元== |   Tex设置并不算Batch
			//=====================================================  纹理可以被缓存并多帧复用
			viewMat = camera.GetViewMatrix();


			for (int i = 0; i < 10; i++) {//10个Batch + 10个
				glm::mat4 modelMat2;
				modelMat2 = glm::translate(modelMat2, cubePositions[i]);
				glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat2));//传递变换矩阵
				glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));//传递变换矩阵
				glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));//传递变换矩阵
				glDrawArrays(GL_TRIANGLES, 0, 36);//绘制三角形(索引绘制
			}



			//glUniformMatrix4fv(glGetUniformLocation(myShader->ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));//传递变换矩阵

			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);//绘制三角形(索引绘制



		

		glfwSwapBuffers(window);//交换缓冲
		glfwPollEvents();//检查是否触发事件
		camera.UpdateCameraPos();
	}
	glfwTerminate();//终止
	return 0;
}

#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<iostream>
using namespace std;

int main() {
	/*���������Լ���glfw���г�ʼ��*/
	GLFWwindow *window;
	if (!glfwInit()) {
		return -1;
	}
	window = glfwCreateWindow(640, 480, "Buffer and Shader Practice", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	
	/*���������Ļ���*/
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)  cout << "error" << endl;
	cout << glGetString(GL_VERSION) << endl;		//�������
	

	/*��������ѭ��*/
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
		
}
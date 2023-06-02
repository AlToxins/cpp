#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<iostream>
using namespace std;

int main() {
	/*创建窗口以及对glfw进行初始化*/
	GLFWwindow *window;
	if (!glfwInit()) {
		return -1;
	}
	window = glfwCreateWindow(640, 480, "Buffer and Shader Practice", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	
	/*创建上下文环境*/
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)  cout << "error" << endl;
	cout << glGetString(GL_VERSION) << endl;		//输出环境
	

	/*创建窗口循环*/
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
		
}
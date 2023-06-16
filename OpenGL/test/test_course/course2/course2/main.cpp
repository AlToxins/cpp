#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#define ASSERT(x) if(!(x)) __debugbreak();	//断言函数
#define call(x) clearError();\
	x;\
	ASSERT(logCall(#x, __FILE__, __LINE__))
//#define call(x) clearError() x ASSERT(logCall())
#define speak std::cout<<__TIME__<<endl


using namespace std;

static void clearError() {
	while (glGetError());		//清除错误，确保在logCall函数的上一句调用时其它函数不会发生错误
}

static bool logCall(const char*function, const char*file, int line) {
	while (GLenum error = glGetError()) {	//glGetError=1	
		cout << "OpenGL Error " << error <<" "<<function<<" " <<file<<": "<< "line "<<line<<endl;
		return false;
	}
	return true;
}

static unsigned int compileShader(unsigned int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type==GL_VERTEX_SHADER ? "vertex" : "fragment") << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static int createShader(const string& vertex, const string& fragment) {
	unsigned int program;
	program=glCreateProgram();
	unsigned int vs, fs;
	vs = compileShader(GL_VERTEX_SHADER, vertex);
	fs = compileShader(GL_FRAGMENT_SHADER, fragment);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

struct shaderSource {
	const string vertex;
	const string fragment;
};

static shaderSource parseShaderFile(const string &filepath) {
	enum class shaderType {
		NONE=2, VERTEX=0, FRAGMENT=1
	};
	ifstream stream(filepath);
	string line;
	shaderType type = shaderType::NONE;
	stringstream ss[3];
	while (getline(stream, line)) {
		if (line.find("#shader")!=string::npos) {
			if (line.find("vertex")!=string::npos) type = shaderType::VERTEX;
			else if (line.find("fragment")!=string::npos)type = shaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << endl;
		}
	}
	return { ss[0].str(), ss[1].str() };
}


int main() {
	speak;
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

	glfwSwapInterval(5);		
	

	float position[8]{
		0.5,-0.5,	//0
		0.5,0.5,	//1
		-0.5,-0.5,	//2
		-0.5,0.5	//3
	};
	unsigned int index[]{
		0,1,2,
		1,3,2,
		2,3,1
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
	
	unsigned int ibo;	//index buffer object
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 5 * sizeof(unsigned int), index, GL_STATIC_DRAW);

	shaderSource src = parseShaderFile("square.shader");
	unsigned int program;
	program = createShader(src.vertex, src.fragment);
	glUseProgram(program);

	int location = glGetUniformLocation(program, "u_color");
	ASSERT(location != -1);
	//glUniform4f(location, 0.5,0.8,0.0,1.0);
	
	float r = 0.0;
	float increment = 0.05;

	/*创建窗口循环*/
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glUniform4f(location, r, 0.8, 0.0, 1.0);
		call(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		if (r >1.0)
			increment = -0.01;
		else if (r < 0)
			increment = 0.01;
		r += increment;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
		
}
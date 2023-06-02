#include<GL\glew.h>
#include<GLFW\glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#define speak std::cout<<__TIME__<<endl
#define ASSERT(x) if(!(x)) __debugbreak()
#define Call(x) clearError();\
	x;\
	ASSERT(getError(__FUNCTION__, __FILE__, __LINE__))
using namespace std; 
/*所有静态函数只能在当前文件中调用*/

static void clearError() {
	while (glGetError());
}

static bool getError(const char*function, const char*filepath, int line) {
	while (GLenum error = glGetError()) {
		cout << "OpenGL Error" << error <<" function: "<<function<<" filepath: "<<filepath<<" line: "<<line << endl;
		return false;
	}
	return true;
}

struct shaderSource {
	const string vertexShader;
	const string fragmentShader;
};

static shaderSource parseShaderFile(string filepath) {
	enum class shaderType {
		NONE=2, VERTEX=0, FRAGMENT=1 
	};
	ifstream stream(filepath);
	string line;
	stringstream ss[3];
	shaderType type = shaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos)
				type = shaderType::VERTEX;
			else if (line.find("fragment") != string::npos)
				type = shaderType::FRAGMENT;
		}
		else {
			ss[(int)type] << line << endl;
		}
	}
	return{ ss[0].str(), ss[1].str() };
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
		char* message = (char*)alloca(sizeof(char) * length);
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static unsigned int createShader(const string& vertexShader, const string& fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
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
	

	//创建缓冲区
	float position[12]{
		-0.5,0.25,
		0.5,0.25,
		0,-0.5,
		-0.5,-0.25,
		0.5,-0.25,
		0,0.5
	};

	unsigned int vertex[]{
		0,1,2,
		3,4,5
	};

	const string vertexShader =
		"#version 330 core\n"
		"layout(location=0)in vec4 position;\n"
		"void main(){\n"
		"	gl_Position=position;\n"
		"}";

	const string fragmentShader =
		"#version 330 core\n"
		"layout(location=0)out vec4 color;\n"
		"void main(){\n"
		"	color=vec4(1.0,0.0,0.5,1.0);\n"
		"}";


	shaderSource source = parseShaderFile("star.shader");
	//unsigned int shader = createShader(vertexShader, fragmentShader);
	unsigned int shader = createShader(source.vertexShader, source.fragmentShader);
	glUseProgram(shader);
	


	unsigned int buffer;
	glCreateBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);

	unsigned int ibo;	//index buffer object
	glCreateBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	

	/*创建窗口循环*/
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		//clearError();
		Call(glDrawElements(GL_TRIANGLES, 6, GL_INT, 0));
		//ASSERT(getError());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
		
}
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

struct shaderSource {
	string vertexSource;
	string fragmentSource;
};

static shaderSource parseShaderFile(const string& filepath) {		//解析着色器文件
	ifstream stream(filepath);
	string line;
	stringstream ss[3];
	enum class shaderType {
		NONE = 0, VERTEX = 1, FRAGMENT = 2
	};
	shaderType type = shaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos)
				type = shaderType::VERTEX;
			else if (line.find("fragment") != string::npos)
				type = shaderType::FRAGMENT;
		}
		else {
			ss[(int)type] <<line << '\n';
		}
	}
	return { ss[1].str(), ss[2].str() };
}

static unsigned int compileShader(unsigned int type, const string& source) {
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		cout << "Failed to compile" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << endl;
		cout << message << endl;
		glDeleteShader(id);
		return 0;
	}
	return id;
}

static int createShader(const string& vertexShader, const string& fragmentShader) {
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
	GLFWwindow* window;
	if (!glfwInit()) {
		return -1;
	}
	window = glfwCreateWindow(640,480,"Buffer and Shader",NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {		//此处必须调用初始化glew函数，否则会在创建缓冲区时引发访问冲突
		glfwTerminate();
		return -1;
	}

	float position[6]{
		0.0f, 0.5f,
		-0.5f,-0.5f,
		0.5f,-0.5f
	};

	/*
	const string vertex =
		"#version 330 core\n"
		"layout(location=0) in vec4 position;\n"
		"void main(){\n"
		"gl_Position=position;\n"
		"}\n";
	const string fragment =
		"#version 330 core\n"
		"layout(location=0) out vec4 color;\n"
		"void main(){\n"
		"color=vec4(0.2,0.9,1,1);\n"
		"}\n";
	*/
	shaderSource source = parseShaderFile("triangle.shader");
	const int shader = createShader(source.vertexSource, source.fragmentSource);
	glUseProgram(shader);
	/*创建缓冲区*/
	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(position), position, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES,0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
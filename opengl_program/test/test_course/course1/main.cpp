#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

struct shaderSource {
    string vertexSource;
    string fragmentSource;  
};
static shaderSource parseShader(const string& filepath) {
    ifstream stream(filepath);
    string line;
    stringstream ss[3];
    enum class shaderType {
        NONE = 2, VERTEX = 0, FRAGMENT = 1
    };
    shaderType type = shaderType::NONE;
    while (getline(stream, line)) {  
        if (line.find("#shader") != string::npos) {
            if (line.find("vertex") != string::npos) type = shaderType::VERTEX;
            else if (line.find("fragment") != string::npos)type = shaderType::FRAGMENT;
        }
        else {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}

static unsigned int compileShader(unsigned int type, const string& source) {        //第二个参数为着色器源码
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);       //https://blog.csdn.net/linjf520/article/details/106527656  ，将源码绑定给着色器对象id，第一个参数为shader对象，第二个参数为源码脚本数量，第三个参数装在源码，第四个参数指定string源码数组的长度
    glCompileShader(id);        //https://blog.csdn.net/linjf520/article/details/106528133  ，编译源码
    int result;     //或者void result
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);      //https://blog.csdn.net/alexhu2010q/article/details/86068878        //此参数的作用是返回着色器编译的状态
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);     //此参数的作用是返回着色器的信息日志的长度
        char *message = (char*)alloca(length*sizeof(char));     //alloca的作用是动态分配内存
        glGetShaderInfoLog(id, length, &length, message);       //https://blog.csdn.net/aoxuestudy/article/details/121930593    ，第二个参数指定储存日志信息的字符缓存大小
        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")<<endl;
        cout << message << endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int createShader(const string& vertexShader, const string& fragmentShader) {     //参数为源码--source
    unsigned int program =glCreateProgram();
    unsigned int vs = compileShader( GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);        //将着色器拉到程序当中
    glAttachShader(program, fs);
    glLinkProgram(program);     //连接顶点着色器和片段着色器
    glValidateProgram(program);     //可以通过参数program和GL_VALIDATE_STATUS调用glGetProgramiv来查询，若验证失败则程序将保证不执行
    int result;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE) {
        return 0;
    }
    else cout << "程序验证状态正常";

    glDeleteShader(vs);     //最后删除着色器
    glDeleteShader(fs);

    return program;     //unsigned int类型的数据将返回给着色器对象，最后由glUseProgram调用
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())        //初始化glfw
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL); 
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)cout << "error";      //初始化glew
    cout << glGetString(GL_VERSION) << endl;        //获取版本信息
    float position1[6] = {
        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f
    };
    //创建缓冲区
    unsigned int buffer1;
    glGenBuffers(1, &buffer1);  //首先生成缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, buffer1);     //绑定缓冲区为某种类型的缓冲区
    glBufferData(GL_ARRAY_BUFFER, sizeof(position1), position1, GL_STATIC_DRAW);      //给缓冲区输入数据

    //创建cpu和gpu之间的连接，然后启用指定属性，使得属性数据在gpu中可见（可以被着色器获取）
    glEnableVertexAttribArray(0);       //只有通过该函数启用指定属性，才能在顶点着色器中访问逐个顶点的属性数据，需要在调用glDraw（绘图函数）函数之前调用该函数
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);      //建立cpu和gpu之间的逻辑连接，从而实现将cpu数据上传至gpu，上一个函数决定了属性数据在gpu端是否可见

    //shader
    shaderSource source = parseShader("D:/opengl_program/test/test_course/course1/RedTriangle.shader");
    cout << source.vertexSource;
    cout << source.fragmentSource;

    unsigned int shader = createShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);
                                                                                                                            
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}
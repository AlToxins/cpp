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

static unsigned int compileShader(unsigned int type, const string& source) {        //�ڶ�������Ϊ��ɫ��Դ��
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);       //https://blog.csdn.net/linjf520/article/details/106527656  ����Դ��󶨸���ɫ������id����һ������Ϊshader���󣬵ڶ�������ΪԴ��ű�����������������װ��Դ�룬���ĸ�����ָ��stringԴ������ĳ���
    glCompileShader(id);        //https://blog.csdn.net/linjf520/article/details/106528133  ������Դ��
    int result;     //����void result
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);      //https://blog.csdn.net/alexhu2010q/article/details/86068878        //�˲����������Ƿ�����ɫ�������״̬
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);     //�˲����������Ƿ�����ɫ������Ϣ��־�ĳ���
        char *message = (char*)alloca(length*sizeof(char));     //alloca�������Ƕ�̬�����ڴ�
        glGetShaderInfoLog(id, length, &length, message);       //https://blog.csdn.net/aoxuestudy/article/details/121930593    ���ڶ�������ָ��������־��Ϣ���ַ������С
        cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")<<endl;
        cout << message << endl;
        glDeleteShader(id);
        return 0;
    }
    return id;
}

static unsigned int createShader(const string& vertexShader, const string& fragmentShader) {     //����ΪԴ��--source
    unsigned int program =glCreateProgram();
    unsigned int vs = compileShader( GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);        //����ɫ������������
    glAttachShader(program, fs);
    glLinkProgram(program);     //���Ӷ�����ɫ����Ƭ����ɫ��
    glValidateProgram(program);     //����ͨ������program��GL_VALIDATE_STATUS����glGetProgramiv����ѯ������֤ʧ������򽫱�֤��ִ��
    int result;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (result == GL_FALSE) {
        return 0;
    }
    else cout << "������֤״̬����";

    glDeleteShader(vs);     //���ɾ����ɫ��
    glDeleteShader(fs);

    return program;     //unsigned int���͵����ݽ����ظ���ɫ�����������glUseProgram����
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())        //��ʼ��glfw
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
    if (glewInit() != GLEW_OK)cout << "error";      //��ʼ��glew
    cout << glGetString(GL_VERSION) << endl;        //��ȡ�汾��Ϣ
    float position1[6] = {
        -0.5f,-0.5f,
        0.0f,0.5f,
        0.5f,-0.5f
    };
    //����������
    unsigned int buffer1;
    glGenBuffers(1, &buffer1);  //�������ɻ�����
    glBindBuffer(GL_ARRAY_BUFFER, buffer1);     //�󶨻�����Ϊĳ�����͵Ļ�����
    glBufferData(GL_ARRAY_BUFFER, sizeof(position1), position1, GL_STATIC_DRAW);      //����������������

    //����cpu��gpu֮������ӣ�Ȼ������ָ�����ԣ�ʹ������������gpu�пɼ������Ա���ɫ����ȡ��
    glEnableVertexAttribArray(0);       //ֻ��ͨ���ú�������ָ�����ԣ������ڶ�����ɫ���з������������������ݣ���Ҫ�ڵ���glDraw����ͼ����������֮ǰ���øú���
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);      //����cpu��gpu֮����߼����ӣ��Ӷ�ʵ�ֽ�cpu�����ϴ���gpu����һ����������������������gpu���Ƿ�ɼ�

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
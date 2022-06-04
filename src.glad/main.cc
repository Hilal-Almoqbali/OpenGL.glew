
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

static unsigned int CompileShadder(unsigned int type,const std::string &source);
static unsigned int CreatShadder(const std::string &VertexShadder, const std::string &FragmentShadder);


std::string vertexShadder =
    "#version 330 core \n"
    "\n"
    "layout(location = 0) in vec4 postions;\n"
    "void main()\n"
    "{\n"
    "gl_Position = vec4(postions);\n"
    "}\n\0";

std::string fragmentShadder =
    "#version 330 core \n"
    "\n"
    "layout(location = 0) out vec4 color;\n"
    "void main()\n"
    "{\n"
    "color = vec4(1.0,0.0,0.0,1.0);\n"
    "}\n\0";

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        {return -1;}




    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
        // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

   


    

    float postions[]={// the data
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };


    //||give OpenGL the Data
    unsigned int buffer;//the buffer
    glGenBuffers(1,&buffer);//make a buffer and give it an ID
    glBindBuffer(GL_ARRAY_BUFFER,buffer);//select the type of the buffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),postions,GL_STATIC_DRAW);//identfy the data and the data type to the buffer
    ////////////////


    //Vertex Attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);//tell OpenGL the buffer's layout

    glBindBuffer(GL_ARRAY_BUFFER,0);//select the type of the buffer and useing it



    unsigned int shadder = CreatShadder(vertexShadder,fragmentShadder);
    glUseProgram(shadder);



    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClearColor(0.0f, 0.3f, 0.2f, 9.0f);// to color the window
        glClear(GL_COLOR_BUFFER_BIT);


        glDrawArrays(GL_TRIANGLES,0,3);



        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

static unsigned int CompileShadder(unsigned int type,const std::string &source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();// get a C pointer to the C++ string
    glShaderSource(id,1,&src,NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id,GL_COMPILE_STATUS,&result);

    if(!result)
    {
       
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id,length, &length,message);
        std::cout << "faile compile "<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shadder" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
    }

    return id;
}

static unsigned int CreatShadder(const std::string &VertexShadder, const std::string &FragmentShadder)
{
    
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShadder(GL_VERTEX_SHADER,VertexShadder);
    unsigned int fs = CompileShadder(GL_FRAGMENT_SHADER,FragmentShadder);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}
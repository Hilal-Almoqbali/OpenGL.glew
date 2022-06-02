
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>




int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
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

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
    /* Problem: glewInit failed, something is seriously wrong. */
    fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }
    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));




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


    //glBindBuffer(GL_ARRAY_BUFFER,0);//select the type of the buffer

    




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
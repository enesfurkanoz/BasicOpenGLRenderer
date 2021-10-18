#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
int main(void)
{
    if (!glfwInit())
    {
        std::cout << "GLFW cannot initialized.";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800,600,"Hello World", NULL,NULL);
        
    glfwMakeContextCurrent(window);
    if (window == NULL)
    {
        std::cout << "Window could not createdé!";
        glfwTerminate();
        return -1;
    }

    if (int version = gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Loaded OpenGL version: " << GLAD_VERSION_MAJOR(version) << '.' << GLAD_VERSION_MINOR(version) << std::endl;

        glViewport(0,0,800,600);

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            glClearColor(0.2f, 0.5f, 0.2f, 0.3f);
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
        }
        glfwTerminate();
        return -1;
    }
    else
    {
        std::cout << "Failed to initialize OpenGL Context!";
        return -1;
    }
    return 0;
}
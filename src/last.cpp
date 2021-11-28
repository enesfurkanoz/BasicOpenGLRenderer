#ifndef OPENGL_HEADER_INCUDED
#define OPENGL_HEADER_INCLUDED
#include<glad/gl.h>
#endif // !OPENGL_HEADER_INCLUDED

#include <GLFW/glfw3.h>
#include <iostream>
#include<string>

#include "OpenGL/GLBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexFormat.h"
#include "OpenGL/GLShader.h"
#include "OpenGL/GLProgram.h"


int main(void)
{
    if (!glfwInit())
    {
        std::cout << "GLFW cannot initialized."; 
        return -1;
    }


    float triangle1[] = {
        -0.5, 1.0,
        -1.0, 0.0,
         0.0, 0.0,
         0.5, 1.0,
         1.0, 0.0,
         0.0, 0.0
    };
    float triangle2[] = {
         0.5, 1.0,
         1.0, 0.0,
         0.0, 0.0
    };
    
    float triangle3[] = {
         0.0f, 0.0f,    
        -0.5f,-1.0f,    
         0.5f, -1.0f   
    };
    float triangleAndColor[] = {
         0.0f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,
        -0.5f,-1.0f,   0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -1.0f,  1.0f, 1.0f, 1.0f, 1.0f
    };
    float colors3[] = {
        1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };
    float colors[] = {
        1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f, 1.0f,

        0.0f, 0.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 0.0f, 1.0f
    };

    
    GLFWwindow* window = glfwCreateWindow(800,600,"Hello World", NULL,NULL);
        
    glfwMakeContextCurrent(window);
    
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_COMPAT_PROFILE);

    if (window == NULL)
    {
        std::cout << "Window could not created!";
        glfwTerminate();
        return -1;
    }
    if (int version = gladLoadGL(glfwGetProcAddress))
    {
        std::cout << "Loaded OpenGL version: " << GLAD_VERSION_MAJOR(version) << '.' << GLAD_VERSION_MINOR(version) << std::endl;
        glViewport(0, 0, 800, 600);

        //start experimentation of OpenGL api
        {

            /*GLVertexBuffer<float> vb1(GL_STATIC_DRAW, 2 * sizeof(float));
            GLVertexBuffer<float> colorData(GL_STATIC_DRAW, 4 * sizeof(float));
            GLVertexBuffer<float> vb2(GL_STATIC_DRAW, 2* sizeof(float));*/
            GLVertexBuffer<float> colorData2(GL_STATIC_DRAW, 4* sizeof(float));

            GLVertexBuffer<float> vb3(GL_STATIC_DRAW,6*sizeof(float));
            vb3.setData(18,triangleAndColor);

            /*vb1.setData(12,triangle1);
            vb2.setData(6,triangle3);
            colorData.setData(24,colors);
            colorData2.setData(12,colors3);*/

            //experiment with shaders and programs

            const std::string fragSrc = R"(
                #version 450 core
                in vec4 vcolor;
                out vec4 fcolor;
                void main(){
                	fcolor = vcolor;
                }
            )";
            const std::string vertSrc = R"(
                #version 450 core
                layout(location = 0) in vec2 position;
                layout(location = 1) in vec4 color;
                out vec4 vcolor;
                void main(){
                	gl_Position = vec4(position,0.0f,1.0f);
                	vcolor = color;
                }
                )";

            GLShader vertshader(GL_VERTEX_SHADER, vertSrc.c_str());
            GLShader fragshader(GL_FRAGMENT_SHADER, fragSrc.c_str());

            if (!vertshader.compile())
            {
                GLint length = vertshader.getInfoLogLength();
                GLchar* message = (GLchar*)alloca(length*sizeof(GLchar));
                vertshader.getInfoLog(length,message);
                std::cout << message;
            }
            if (!fragshader.compile())
            {
                GLint length = fragshader.getInfoLogLength();
                GLchar* message = (GLchar*)alloca(length*sizeof(GLchar));
                fragshader.getInfoLog(length,message);
            }
            GLProgram program;
            program.attachShader(vertshader.getShaderID());
            program.attachShader(fragshader.getShaderID());
            program.linkProgram();
            program.detachShader(vertshader.getShaderID());
            program.detachShader(fragshader.getShaderID());
            
            int position = program.getAttribLocation("position");
            int color = program.getAttribLocation("color");
            std::cout << "position: " << position << std::endl;
            std::cout << "color: " << color << std::endl;


            


            /*VertexFormat vf(position, 2, GL_FLOAT, GL_FALSE, 0);
            VertexFormat cf(color, 4, GL_FLOAT, GL_FALSE, 0);*/
            VertexFormat vf(position, 2, GL_FLOAT, GL_FALSE, 0);
            VertexFormat cf(color, 4, GL_FLOAT, GL_FALSE, 2*sizeof(float));
            /*GLVertexArray<float>va1;
            va1.addVertexBuffer(vb1, 0);
            va1.addVertexFormat(vf);
            va1.addVertexBuffer(colorData, 0);
            va1.addVertexFormat(cf);
            va1.enableAttributes();

            GLVertexArray<float>va2;
            va2.addVertexBuffer(vb2, 0);
            va2.addVertexFormat(vf);
            va2.addVertexBuffer(colorData2,0);
            va2.addVertexFormat(cf);
            va2.enableAttributes();*/


            GLVertexArray<float>va;
            va.addVertexBuffer(vb3,0);
            va.addVertexFormat(vf);
            va.addVertexFormat(cf);
            va.enableAttributes();

            while (!glfwWindowShouldClose(window))
            {
                program.use();
                glfwPollEvents();
                glClearColor(0.2f, 0.5f, 0.2f, 0.3f);
                glClear(GL_COLOR_BUFFER_BIT);
                va.bindVerexArray();
                glDrawArrays(GL_TRIANGLES,0,3);
                va.clearBinding();

                /*va1.bindVerexArray();
                glDrawArrays(GL_TRIANGLES, 0, 6);
                va1.clearBinding();
                va2.bindVerexArray();
                glDrawArrays(GL_TRIANGLES,0,3);
                va2.clearBinding();
                program.clearUse();*/


                glfwSwapBuffers(window);
                
            }
        }
        glfwTerminate();
        return 0;
    }
    else
    {
        std::cout << "Failed to load OpenGL!";
        glfwTerminate();
        return -1;
    }

}
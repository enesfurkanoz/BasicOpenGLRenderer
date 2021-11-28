#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<iostream>

#include "OpenGL/GLBuffer.h"
#include "OpenGL/VertexArray.h"
#include "OpenGL/VertexFormat.h"
#include "OpenGL/GLShader.h"
#include "OpenGL/GLProgram.h"

int main(void)
{
	if (!glfwInit())
	{
		std::cout << "GLFW couldd not initialize!" << std::endl;
		return -1;
	}
	GLFWwindow* window = glfwCreateWindow(800,600,"Experiments",NULL,NULL);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	if (int version = gladLoadGL(glfwGetProcAddress))
	{
		std::cout << "Loaded OpenGL version : " << GLAD_VERSION_MAJOR(version) <<"."<< GLAD_VERSION_MINOR(version) << std::endl;
		glViewport(0,0,800,600);

		float positions[] = {
			-1.0, 1.0,
			-1.0,-1.0,
			 1.0, -1.0
		};
		float colors[] = {
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f
		};

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
			GLchar* message = (GLchar*)alloca(length * sizeof(GLchar));
			vertshader.getInfoLog(length, message);
			std::cout << message;
		}
		if (!fragshader.compile())
		{
			GLint length = fragshader.getInfoLogLength();
			GLchar* message = (GLchar*)alloca(length * sizeof(GLchar));
			fragshader.getInfoLog(length, message);
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

		GLVertexBuffer<float> positionsBuffer(GL_DYNAMIC_DRAW, 2*sizeof(float));
		positionsBuffer.setData(6,positions);

		VertexFormat positionsVF(position,2,GL_FLOAT,GL_FALSE,0);

		GLVertexBuffer<float> colorsBuffer(GL_DYNAMIC_DRAW, 4 * sizeof(float));
		colorsBuffer.setData(12,colors);

		VertexFormat colorsVF(color,4,GL_FLOAT,GL_FALSE,0);

		GLVertexArray<float> va;
		va.addVertexBuffer(positionsBuffer,0);
		va.addVertexFormat(positionsVF);
		va.addVertexBuffer(colorsBuffer,0);
		va.addVertexFormat(colorsVF);
		va.enableAttributes();
		va.bindVerexArray();

		program.use();

		//float x = -1.0f;
		//float inc = 0.05f;
		glfwSwapInterval(3);
		while (!glfwWindowShouldClose(window))
		{
			//positionsBuffer.setSubData(0,1,&x);
			glfwPollEvents();
			glClearColor(0.2f, 0.5f, 0.2f, 0.3f);
			glClear(GL_COLOR_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES,0,3);
			glfwSwapBuffers(window);
			/*x += inc;
			if (x > 1.0f || x < -1.0f)
			{
				inc = -inc;
			}*/
		}
		glfwTerminate();
		return 0;
	}
	else
	{
		std::cout << "ERROR: OpenGL could not loaded.";
		glfwTerminate();
		return -1;
	}
}
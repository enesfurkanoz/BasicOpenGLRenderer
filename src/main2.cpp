#include<glad/gl.h>
#include<GLFW/glfw3.h>
#include<iostream>
int main(void)
{

	const GLchar* vSrc = R"(
		#version 450 core
		layout(location = 0) in vec2 position;
		layout(location = 1) in vec4 color;
		out vec4 vcolor;
		void main(){
			gl_Position = vec4(position,0.0f,1.0f);
			vcolor = color;
		}
	)";
	const char* fSrc = R"(
		#version 450 core
		in vec4 vcolor;
		out vec4 fcolor;
		void main(){
			fcolor = vcolor;
		}
	)";
	float positions[] = {
		-0.5, 1.0,
		-1.0, 0.0,
		 0.0, 0.0
	};
	float colors[] = {
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};
	if (!glfwInit())
	{
		glfwTerminate();
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800,600,"Hello World",NULL,NULL);
	glfwMakeContextCurrent(window);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	if (int version = gladLoadGL(glfwGetProcAddress))
	{
		std::cout << "Loaded OpenGL version is: " << GLAD_VERSION_MAJOR(version) << "." << GLAD_VERSION_MINOR(version) << std::endl;
		
		GLuint VBOs[2];
		glCreateBuffers(2,VBOs);

		glNamedBufferData(VBOs[0],6*sizeof(float),positions,GL_STATIC_DRAW);
		glNamedBufferData(VBOs[1],12*sizeof(float),colors,GL_STATIC_DRAW);

		GLuint VAO;
		glCreateVertexArrays(1,&VAO);

		
		

		glVertexArrayVertexBuffer(VAO,0,VBOs[0],0,2*sizeof(float));
		glVertexArrayVertexBuffer(VAO,1,VBOs[1],0,4*sizeof(float));


		GLuint vs = glCreateShader(GL_VERTEX_SHADER);
		GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vs,1,&vSrc,nullptr);
		glShaderSource(fs,1,&fSrc,nullptr);

		glCompileShader(vs);
		/*GLint compiled;
		glGetShaderiv(vs,GL_COMPILE_STATUS,&compiled);
		int length;
		glGetShaderiv(vs,GL_INFO_LOG_LENGTH,&length);
		GLchar* message = (GLchar*)alloca(length*sizeof(GLchar));
		glGetShaderInfoLog(vs,length,&length,message);
		std::cout << message;*/
		glCompileShader(fs);

		GLuint program = glCreateProgram();
		glAttachShader(program,vs);
		glAttachShader(program,fs);

		glLinkProgram(program);
		int position = glGetAttribLocation(program, "position");
		int color = glGetAttribLocation(program, "color");
		glDetachShader(program,vs);
		glDeleteShader(vs);
		glDetachShader(program,fs);
		glDeleteShader(fs);


		std::cout << position << " position\n";
		std::cout << color << " color\n";


		glVertexArrayAttribBinding(VAO,position,0);
		glVertexArrayAttribBinding(VAO,color,1);

		glVertexArrayAttribFormat(VAO,position,2,GL_FLOAT,GL_FALSE,0);
		glVertexArrayAttribFormat(VAO,color,4,GL_FLOAT,GL_FALSE,0);

		glEnableVertexArrayAttrib(VAO, 0);
		glEnableVertexArrayAttrib(VAO, 1);

		glUseProgram(program);

		glViewport(0,0,800,600);
		while (!glfwWindowShouldClose(window))
		{
			glfwPollEvents();
			glClearColor(0.2f, 0.5f, 0.2f, 0.3f);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES,0,3);
			glfwSwapBuffers(window);
		}

		glfwTerminate();
		return 0;
	}
	glfwTerminate();
	return -1;
}
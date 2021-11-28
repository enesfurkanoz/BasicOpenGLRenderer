#pragma once
#include<glad/gl.h>

class GLShader
{
public:
	GLShader(GLenum type, const char* source);
	~GLShader();
	bool compile();
	void getInfoLog(GLint& length,GLchar* infoLog);
	GLint getInfoLogLength();
	GLuint getShaderID();
private:
	GLuint ShaderID;
};

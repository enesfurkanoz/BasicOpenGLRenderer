#include "GLShader.h"

GLShader::GLShader(GLenum type, const char* source)
{
	this->ShaderID = glCreateShader(type);
	glShaderSource(this->ShaderID,1,&source,nullptr);
}

GLShader::~GLShader()
{
	glDeleteShader(this->ShaderID);
}

bool GLShader::compile()
{
	GLint compiled = GL_FALSE;
	glCompileShader(this->ShaderID);
	glGetShaderiv(this->ShaderID,GL_COMPILE_STATUS,&compiled);
	return compiled;
}

void GLShader::getInfoLog(GLint& length,GLchar* infoLog)
{
	glGetShaderInfoLog(this->ShaderID,length,&length,infoLog);
}

GLint GLShader::getInfoLogLength()
{
	GLint length;
	glGetShaderiv(this->ShaderID,GL_INFO_LOG_LENGTH,&length);
	return length;
}

GLuint GLShader::getShaderID()
{
	return this->ShaderID;
}







#include"GLProgram.h"

GLProgram::GLProgram()
{
	this->ProgramID = glCreateProgram();
}

GLProgram::~GLProgram()
{
	glDeleteProgram(this->ProgramID);
}

GLuint GLProgram::getProgrmID()
{
	return this->ProgramID;
}

void GLProgram::getInfoLog(GLint& length, GLchar* infolog)
{
	glGetProgramInfoLog(this->ProgramID,length,&length,infolog);
}

void GLProgram::attachShader(GLuint shaderID)
{
	glAttachShader(this->ProgramID,shaderID);
}

void GLProgram::detachShader(GLuint shaderID)
{
	glDetachShader(this->ProgramID,shaderID);
}

bool GLProgram::linkProgram()
{
	glLinkProgram(this->ProgramID);
	GLint linked = GL_FALSE;
	glGetProgramiv(this->ProgramID,GL_LINK_STATUS,&linked);
	return linked;
}

void GLProgram::use()
{
	glUseProgram(this->ProgramID);
}

void GLProgram::clearUse()
{
	glUseProgram(0);
}

GLint GLProgram::getInfoLogLength()
{
	GLint length;
	glGetProgramiv(this->ProgramID,GL_INFO_LOG_LENGTH,&length);
	return length;
}

GLint GLProgram::getAttribLocation(const GLchar* attribName)
{
	return glGetAttribLocation(this->ProgramID,attribName);
}


bool GLProgram::validateProgram()
{
	glValidateProgram(this->ProgramID);
	GLint valid = GL_FALSE;
	glGetProgramiv(this->ProgramID,GL_VALIDATE_STATUS,&valid);
	return valid;
}
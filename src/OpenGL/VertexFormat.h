#pragma once
#ifndef OPENGL_HEADER_INCUDED
#define OPENGL_HEADER_INCLUDED
#include<glad/gl.h>
#endif // !OPENGL_HEADER_INCLUDED

#include "GLBuffer.h"
#include<vector>

struct VertexFormat
{
public:
	VertexFormat(GLint attribIndex, GLint count, GLenum type, GLboolean normalized, GLuint relativeOffset)
		:attribIndex(attribIndex), count(count), type(type), normalized(normalized), relativeOffset(relativeOffset)
	{};
	GLint attribIndex;
	GLuint count;
	GLenum type;
	GLboolean normalized;
	GLuint relativeOffset;
};

#pragma once
#ifndef OPENGL_HEADER_INCUDED
#define OPENGL_HEADER_INCLUDED
#include<glad/gl.h>
#endif // !OPENGL_HEADER_INCLUDED


template <typename T>
class GLBuffer
{
public:
	GLBuffer(GLenum bufferType, GLenum usageHint, GLsizei stride)
		: type(bufferType), usageHint(usageHint), stride(stride)
	{
		glCreateBuffers(1, &(this->bufferID));
	};
	~GLBuffer() { glDeleteBuffers(1, &(this->bufferID)); };

	void Bind() const
	{
		glBindBuffer(this->type, this->bufferID);
	}
	void unBind() const
	{
		glBindBuffer(this->type,0);
	}
	void setData(unsigned int count, const T* data)
	{
		glNamedBufferData(this->bufferID,count*sizeof(T),data,this->usageHint);
	}
	void setSubData(int offset, unsigned int count, const T* data)
	{
		glNamedBufferSubData(this->bufferID, offset, count*sizeof(T), data);
	}
	GLsizei getStride() const 
	{
		return this->stride;
	}
	GLuint getBufferID() const
	{
		return this->bufferID;
	}
protected:
	GLenum type;
	GLenum usageHint;
	GLuint bufferID;
	GLsizei stride;
};

template<typename T>
class GLVertexBuffer : public GLBuffer<T>
{
public:
	GLVertexBuffer(GLenum usageHint, GLsizei stride)
		: GLBuffer(GL_ARRAY_BUFFER, usageHint,stride){};
	~GLVertexBuffer() { };
};

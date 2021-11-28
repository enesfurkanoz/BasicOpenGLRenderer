#pragma once
#ifndef OPENGL_HEADER_INCUDED
#define OPENGL_HEADER_INCLUDED
#include<glad/gl.h>
#endif // !OPENGL_HEADER_INCLUDED

#include "GLBuffer.h"
#include"VertexFormat.h"
#include<iostream>
#include<vector>

template<typename T>
class GLVertexArray
{
public:
	GLVertexArray()
	{
		glCreateVertexArrays(1, &(this->vertexArrayID));
		this->bindingIndex = 0;
	};
	~GLVertexArray() { glDeleteVertexArrays(1,&(this->vertexArrayID)); };

	GLuint getVertexArrayID()
	{
		return this->vertexArrayID;
	}

	void bindVerexArray()
	{
		glBindVertexArray(this->vertexArrayID);
	}

	void clearBinding()
	{
		glBindVertexArray(0);
	}

	void addVertexBuffer(GLVertexBuffer<T>& vertexBuffer,GLintptr offset)
	{
		std::cout << "VA: " << this->vertexArrayID << " VB: " << vertexBuffer.getBufferID() << " bindingIndex: " << this->bindingIndex << std::endl;
		glVertexArrayVertexBuffer(this->vertexArrayID,this->bindingIndex,
			vertexBuffer.getBufferID(),offset,vertexBuffer.getStride());
		this->bindingIndex++;
	}

	void addVertexFormat(VertexFormat& vertexFormat)
	{
		this->vertexAttribIndices.push_back(vertexFormat.attribIndex);
		std::cout << " VF: " << vertexFormat.count << " attribIndex: " << vertexFormat.attribIndex << std::endl;
		glVertexArrayAttribFormat(this->vertexArrayID, vertexFormat.attribIndex,
			vertexFormat.count, vertexFormat.type, vertexFormat.normalized, vertexFormat.relativeOffset);
		glVertexArrayAttribBinding(this->vertexArrayID,vertexFormat.attribIndex,this->bindingIndex-1);
	}

	void enableAttributes()
	{
		for (GLuint& attribIndex: this->vertexAttribIndices)
		{
			glEnableVertexArrayAttrib(this->vertexArrayID, attribIndex);
			std::cout << "Enabled : " << attribIndex<<std::endl;
		}
	}
	void disbleAttributes()
	{
		for (GLuint attribIndex : this->vertexAttribIndices)
		{
			glDisableVertexArrayAttrib(this->vertexArrayID,attribIndex);
		}
	}
private:
	std::vector<GLuint>vertexAttribIndices;
	GLuint bindingIndex;
	GLuint vertexArrayID;
};

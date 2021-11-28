#include<glad/gl.h>

class GLProgram
{
public:
	GLProgram();
	~GLProgram();
	GLuint getProgrmID();
	void getInfoLog(GLint& length,GLchar*infolog);
	void attachShader(GLuint shaderID);
	void detachShader(GLuint shaderID);
	bool validateProgram();
	bool linkProgram();
	void use();
	void clearUse();
	GLint getInfoLogLength();
	GLint getAttribLocation(const GLchar* attribName);
private:
	GLuint ProgramID;
};

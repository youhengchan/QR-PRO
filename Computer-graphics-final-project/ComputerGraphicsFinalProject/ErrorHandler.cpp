#include "ErrorHandler.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);  // Clearing Errors
}

// Print all the errors
void GLCheckError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error](" << error << ")" << std::endl;
	}
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] ( " << error << ")" << std::endl;
		std::cout << function << " " << file << " : " << line << std::endl;
		return false;
	}
	return true;
}
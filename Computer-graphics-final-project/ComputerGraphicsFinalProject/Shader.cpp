#include "Shader.h"
#include "ErrorHandler.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const std :: string & filepath) 
	:m_FilePath(filepath), m_RendererID(0)
{
	GLCall(ShaderProgramSource sps = ParseShader(filepath));
	
	std::string vertexShader = sps.VertexSource;
	std::cout << "    ----Vertex---" << std::endl << vertexShader << std::endl;

	std::string fragmentShader = sps.FragmentSource;
	std::cout << "    ----Fragment----" << std::endl << fragmentShader << std::endl;

	GLCall(m_RendererID = CreateShader(vertexShader, fragmentShader));
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::Delete() const
{
	GLCall(glDeleteProgram(m_RendererID));
}

void Shader::SetUniform1i(const std::string & name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std :: string & name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniform1f(const std::string& name, float value) 
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));  // GL_FALSE: NO TRANSPOSE
}

int Shader::GetUniformLocation(const std::string & name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	// GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
	{
		std::cout << "Warning: uniform" << name << " doesn't exist\n";
	}
	m_UniformLocationCache[name] = location;
	return location;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	// TODO: Error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) {  // Shader is not compiled successfully
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile the " <<
			(type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<
			"shader" << std::endl;
		std::cout << message << std::endl;  // ±àÒëShaderÊ§°Ü
		glDeleteShader(id); // É¾³ý±àÒëÊ§°ÜµÄshader
		return 0;  // Ê§°ÜÊ±·µ»Ø0
	}
	return id;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	enum class ShaderType {
		None = -1, Vertex = 0, Fragment = 1
	};
	std::ifstream stream(filepath);
	std::stringstream ss[2];
	ShaderType type = ShaderType::None;

	std::string line;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				// set mode to vertex
				type = ShaderType::Vertex;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				// set mode to fragment
				type = ShaderType::Fragment;
			}
		}
		else
		{
			ss[(int)type] << line << "\n";
		}
	}
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string & vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = Shader::CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = Shader::CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

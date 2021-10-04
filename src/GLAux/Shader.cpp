#include "Shader.hpp"
#include "Renderer.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

Shader::Shader(const std::string& filepath)
    : m_FilePath(filepath), m_RendererID(0)
{
    ShaderProgramSource source = ParseShader(filepath);

    // std::cout << "VERTEX" << std::endl << source.VertexSource << std::endl;
    // std::cout << "FRAGMENT" << std::endl << source.FragmentSource << std::endl;

    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

    GLCall( glUseProgram(m_RendererID) );
}

Shader::~Shader()
{
    GLCall( glDeleteProgram(m_RendererID) );
}

void Shader::Bind() const
{
    GLCall( glUseProgram(m_RendererID) );
}

void Shader::Unbind() const
{
    GLCall( glUseProgram(0) );
}

void Shader::SetUniform4f(const std::string& name, glm::vec4& vector)
{
	GLCall( glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w) );
}

void Shader::SetUniform3f(const std::string& name, glm::vec3& vector)
{
	GLCall( glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z) );
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLCall( glUniform1f(GetUniformLocation(name), value) );
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4& matrix)
{
	GLCall( glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]) );
}

int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())	
		return m_UniformLocationCache[name];
	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout<< "Warning: uniform " << name << "doesn't exist!"<<std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	//enum for the shader type state
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	//Still not sure what stringstream is
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;
		}
		else
		{
			//Apending to the stringstream
			ss[(int)type]<<line<<'\n';
		}
	}

	//struct for the shaders. Still don't know what ss[i].str() is
	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//Error hendeling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		//Memory on the stack
		char* message = (char*)alloca(length * sizeof(char));

		//Output error
		glGetShaderInfoLog(id, length, &length, message);
		std::cout<<"Failed to compile "<< (type == GL_VERTEX_SHADER ? "vertex":"fragment") <<" shader!"<<std::endl;
		std::cout<<message<<std::endl;
		glDeleteShader(id);

		return 0;
	}
	//--------------------------

	return id;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	//Not using gl data types
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
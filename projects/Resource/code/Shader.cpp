
#include "Shader.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <cstdlib>
#include "CString.h"

Shader::Shader(const char* shaderPath)
{
	if (strlen(shaderPath) == 0)
		return;
	
	LoadShader(shaderPath);

	path = CString::GetFileFromFullPath(shaderPath);

	std::cout << "Loading: " << path << "\n";
}

void Shader::LoadShader(const char* shaderPath)
{
	Id = glCreateProgram();

	const ShaderSources source = Parse(shaderPath);

	const unsigned int vertex = LinkShaders(GL_VERTEX_SHADER, source.VertexSource);
	CheckCompileErrors(vertex, "Vertex");

	const unsigned int fragment = LinkShaders(GL_FRAGMENT_SHADER, source.FragmentSource);
	CheckCompileErrors(fragment, "Fragment");

	glAttachShader(Id, vertex);
	glAttachShader(Id, fragment);

	glLinkProgram(Id);
	glValidateProgram(Id);
	CheckLinkErrors();

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

ShaderSources Shader::Parse(const char* shaderPath) const
{
	std::ifstream file(shaderPath);

	if (!file.is_open())
	{
		std::cout << "Failed to find the requested file: " << shaderPath << "\n";
		return { "", "" };
	}

	enum class ShaderType
	{
		NONE	 = -1,
		VERTEX   =  0,
		FRAGMENT =  1
	};

	ShaderType type = ShaderType::NONE;

	std::string line;
	std::stringstream ss[2];

	while (getline(file, line))
	{
		if (line.find("vertex") != std::string::npos)
			type = ShaderType::VERTEX;
		else if (line.find("fragment") != std::string::npos)
			type = ShaderType::FRAGMENT;
		else
			ss[int(type)] << line << '\n';
	}

	file.close();

	//cout << ss[0].str() << endl;
	//cout << ss[1].str() << endl;

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::LinkShaders(const unsigned int type, const std::string& source)
{
	const unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);
	
	return id;
}

void Shader::CheckCompileErrors(const unsigned int shader, const std::string& alias) const
{
	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	
	if (!result)
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		
		char* errorMsg = static_cast<char*>(alloca(length * sizeof(char)));
		glGetShaderInfoLog(shader, length, &length, errorMsg);

		std::cout << "\n" << "Shader: " << path << "\n";
		std::cout << "Failed to COMPILE the shader. Error: " << errorMsg << "\n";
		
		glDeleteShader(shader);
	}
}

void Shader::CheckLinkErrors() const
{
	int result;
	glGetProgramiv(Id, GL_LINK_STATUS, &result);
	
	if (!result)
	{
		int length;
		glGetProgramiv(Id, GL_LINK_STATUS, &length);
		
		char* errorMsg = static_cast<char*>(alloca(length * sizeof(char)));
		glGetProgramInfoLog(Id, length, &length, errorMsg);

		std::cout << "\n" << "Shader: " << path << "\n";
		std::cout << "Failed to LINK the shader. Error: " << errorMsg << "\n";
		
		glDeleteShader(Id);
	}
}

int Shader::GetLocation(const std::string& name)
{
	// returns cached value, if found
	if (cache.find(name) != cache.end())
		return cache[name]; 

	// otherwise; insert the value for future look-up
	const int location = glGetUniformLocation(Id, name.c_str());
	cache[name] = location;
	
	return location;
}

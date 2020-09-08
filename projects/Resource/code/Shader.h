#pragma once
#include "core/app.h"
#include <string>
#include <Vector3.h>
#include <Matrix4x4.h>
#include <unordered_map>

struct ShaderSources
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	unsigned int Id;

	Shader() = default;
	explicit Shader(const char* shaderPath);
	
	void Bind() const { glUseProgram(Id); }
	static void UnBind() { glUseProgram(0); }

	void SetValue(const std::string& name, const Matrix4x4& mat, const bool transpose = true) { glUniformMatrix4fv(GetLocation(name), 1, transpose, mat.Ptr()); }
	void SetValue(const std::string& name, const double value) { glUniform1f(GetLocation(name), static_cast<float>(value)); } // Cannot load doubles to shader as it uses float
	void SetValue(const std::string& name, Vector3 value) { glUniform3fv(GetLocation(name), 1, &value[0]); }

	void SetValue(const std::string& name, const int   value)  { glUniform1i(GetLocation(name), value); }
	void SetValue(const std::string& name, const float value)  { glUniform1f(GetLocation(name), value); }
	void SetValue(const std::string& name, const bool  value)  { glUniform1i(GetLocation(name), value); }

	~Shader() = default;

private:
	
	std::string path;
	std::unordered_map<std::string, int> cache;

	// load
	ShaderSources Parse(const char* shaderPath) const;
	void LoadShader(const char* shaderPath);
	static unsigned int LinkShaders(unsigned int type, const std::string& source);

	// error
	void CheckCompileErrors(unsigned int shader, const std::string& alias) const;
	void CheckLinkErrors() const;

	// fetch from cache
	int GetLocation(const std::string& name);
};


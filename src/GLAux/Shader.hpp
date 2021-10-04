#pragma once

#include <glm/glm.hpp>
#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        std::unordered_map<std::string, int> m_UniformLocationCache;

    public:
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        // Set uniforms
        void SetUniform4f(const std::string& name, glm::vec4& vector);
        void SetUniform3f(const std::string& name, glm::vec3& vector);
        void SetUniform1f(const std::string& name, float value);
		void SetUniformMat4f(const std::string& name, glm::mat4& transform);

    private:
        int GetUniformLocation(const std::string& name);
        ShaderProgramSource ParseShader(const std::string& filepath);
        unsigned int CompileShader(unsigned int type, const std::string& source);
        unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

};
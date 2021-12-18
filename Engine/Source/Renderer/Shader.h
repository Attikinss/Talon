#pragma once
#include <string>
#include <memory>
#include <unordered_map>

#include <glm/glm.hpp>

namespace Talon
{
	// TODO: Create Shader instances so that the same Shader
	//		 can be changed on a material to material basis

	class Shader
	{
	public:
		static std::shared_ptr<Shader> Create(const std::string& filepath);

		Shader(const std::string& filepath);
		
		void Reload();
		void Bind();
		void Unbind();

		void BindAttribute(uint32_t index, const std::string& name);
		void SetUniform(const std::string& name, uint32_t value);
		void SetUniform(const std::string& name, int32_t value);
		void SetUniform(const std::string& name, float value);
		void SetUniform(const std::string& name, const glm::vec2& value);
		void SetUniform(const std::string& name, const glm::vec3& value);
		void SetUniform(const std::string& name, const glm::vec4& value);
		void SetUniform(const std::string& name, const glm::mat3& value);
		void SetUniform(const std::string& name, const glm::mat4& value);

		void Load(const std::string& source);
		void Compile();
		uint32_t GetUniformLocation(const std::string& name) const;

	private:
		uint32_t m_ID = 0;
		std::string m_Name;
		std::string m_Filepath;

		std::unordered_map<uint32_t, std::string> m_ShaderSource;
		mutable std::unordered_map<std::string, uint32_t> m_UniformLocations;
	};
}
#pragma once
#include <string>
#include <unordered_map>

namespace Talon
{
	class Shader
	{
	public:
		static Shader* Create(const std::string& filepath);
		
		void Reload();
		void Bind();
		void Unbind();

		void BindAttribute(uint32_t index, const std::string& name);
		void SetUniform(const std::string& name, uint32_t value);
		void SetUniform(const std::string& name, int32_t value);
		void SetUniform(const std::string& name, float value);
		//void SetUniform(const std::string& name, const Vector2& value);
		//void SetUniform(const std::string& name, const Vector3& value);
		//void SetUniform(const std::string& name, const Vector4& value);
		//void SetUniform(const std::string& name, const Matrix3& value);
		//void SetUniform(const std::string& name, const Matrix4& value);

	private:
		Shader(const std::string& filepath);

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
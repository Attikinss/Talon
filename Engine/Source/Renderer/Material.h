#pragma once
#include <memory>
#include <string>

#include <glm/glm.hpp>

namespace Talon
{
	class Shader;

	// TODO: Create material instances so that the same material
	//		 can be changed on an entity to entity basis

	class Material
	{
	public:
		Material(const std::shared_ptr<Shader>& shader)
			: m_Shader(shader) { }
		~Material() = default;

		void SetFloat(const std::string& name, float value);
		void SetInt(const std::string& name, int32_t value);
		void SetUint(const std::string& name, uint32_t value);
		void SetVector2(const std::string& name, const glm::vec2& value);
		void SetVector3(const std::string& name, const glm::vec3& value);
		void SetVector4(const std::string& name, const glm::vec4& value);
		void SetMatrix3(const std::string& name, const glm::mat3& value);
		void SetMatrix4(const std::string& name, const glm::mat4& value);

	private:
		std::shared_ptr<Shader> m_Shader;
	};
}
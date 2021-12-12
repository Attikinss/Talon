#pragma once
#include <glm/glm.hpp>

namespace Talon
{
	enum class Projection { Orthographic, Perspective };

	class Camera
	{
	public:
		Camera(Projection projectionType = Projection::Perspective, float nearPlane = 0.3f, float farPlane = 1000.0f, float fieldOfView = 60.0f);
		Camera(const glm::vec2& viewSize, Projection projectionType = Projection::Perspective, float nearPlane = 0.3f, float farPlane = 1000.0f, float fieldOfView = 60.0f);
		virtual ~Camera() = default;

		void SetFOV(float fieldOfView);
		void SetProjectionType(Projection projectionType);
		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);
		void SetViewSize(const glm::vec2 & viewSize);
		void SetView(const glm::mat4& viewMatrix);

		const glm::mat4& GetView() const { return m_ViewMatrix; }
		const glm::mat4& GetProjection() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewProjection() const { return m_ViewProjectionMatrix; }

	protected:
		void RecalculateProjection();

	protected:
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);

		Projection m_ProjectionType;
		glm::vec2 m_ViewSize;
		float m_NearPlane;
		float m_FarPlane;
		float m_FieldOfView;
	};
}
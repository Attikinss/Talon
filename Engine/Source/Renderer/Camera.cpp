#include "Camera.h"

#include <glm/gtx/quaternion.hpp>

namespace Talon
{
	static glm::quat GetOrientation(const glm::vec3& rotation)
	{
		return glm::quat(glm::radians(rotation * -1.0f));
	}

	Camera::Camera(Projection projectionType, float nearPlane, float farPlane, float fieldOfView)
		: m_ProjectionType(projectionType), m_NearPlane(nearPlane), m_FarPlane(farPlane), m_FieldOfView(fieldOfView)
	{
		// TODO: Pull size from window/viewport
		m_ViewSize = { 1280.0f, 720.0f };

		RecalculateProjection();
	}

	Camera::Camera(const glm::vec2& viewSize, Projection projectionType, float nearPlane, float farPlane, float fieldOfView)
		: m_ViewSize(viewSize), m_ProjectionType(projectionType), m_NearPlane(nearPlane), m_FarPlane(farPlane), m_FieldOfView(fieldOfView)
	{
		RecalculateProjection();
	}

	void Camera::SetFOV(float fieldOfView)
	{
		if (m_FieldOfView == fieldOfView)
			return;

		m_FieldOfView = fieldOfView;
		RecalculateProjection();
	}

	void Camera::SetProjectionType(Projection projectionType)
	{
		if (m_ProjectionType == projectionType)
			return;

		m_ProjectionType = projectionType;
		RecalculateProjection();
	}

	void Camera::SetNearPlane(float nearPlane)
	{
		if (m_NearPlane == nearPlane)
			return;

		m_NearPlane = nearPlane;
		RecalculateProjection();
	}

	void Camera::SetFarPlane(float farPlane)
	{
		if (m_FarPlane == farPlane)
			return;

		m_FarPlane = farPlane;
		RecalculateProjection();
	}

	void Camera::SetViewSize(const glm::vec2& viewSize)
	{
		if (m_ViewSize == viewSize)
			return;

		m_ViewSize = viewSize;
		RecalculateProjection();
	}

	void Camera::SetView(const glm::mat4& viewMatrix)
	{
		m_ViewMatrix = viewMatrix;
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void Camera::RecalculateProjection()
	{
		m_ProjectionMatrix = m_ProjectionType == Projection::Orthographic ?
			glm::ortho(-m_ViewSize.x, m_ViewSize.x, -m_ViewSize.y, m_ViewSize.y, m_NearPlane, m_FarPlane) :
			glm::perspective(glm::radians(m_FieldOfView), m_ViewSize.x / m_ViewSize.y, m_NearPlane, m_FarPlane);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
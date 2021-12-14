#include "EditorCamera.h"

#include "Core/Input.h"
#include "Events/MouseEvent.h"

#include <glm/gtx/quaternion.hpp>

namespace Talon
{
	static std::pair<float, float> PanSpeed(const glm::vec2& viewportSize)
	{
		float x = glm::min(viewportSize.x / 1000.0f, 2.4f);
		float xFactor = 0.0366f * (x * x) - 0.1778f * x + 0.3021f;

		float y = glm::min(viewportSize.y / 1000.0f, 2.4f);
		float yFactor = 0.0366f * (y * y) - 0.1778f * y + 0.3021f;

		return { xFactor, yFactor };
	}

	static float ZoomSpeed(float focalPointDistance)
	{
		float distance = focalPointDistance * 0.5f;
		distance = glm::max(distance, 0.001f);

		float speed = distance * distance;
		speed = glm::min(speed, 100.0f);

		return speed;
	}

	glm::vec3 GetDirectionFront(const glm::quat& orientation)
	{
		glm::vec3 rotation = glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f));
		return rotation;
	}

	glm::vec3 GetDirectionUp(const glm::quat& orientation)
	{
		glm::vec3 rotation = glm::rotate(orientation, glm::vec3(0.0f, 1.0f, 0.0f));
		return rotation;
	}

	glm::vec3 GetDirectionRight(const glm::quat& orientation)
	{
		glm::vec3 rotation = glm::rotate(orientation, glm::vec3(1.0f, 0.0f, 0.0f));
		return rotation;
	}

	glm::vec3 CalculatePosition(const glm::vec3& focalPoint, const glm::quat& orientation, float distance)
	{
		glm::vec3 front = GetDirectionFront(orientation);
		return focalPoint - front * distance;
	}

	void EditorCamera::Update()
	{
		glm::vec2 delta = Input::GetMouseDelta() * 0.5f;

		if (Input::GetKey(KeyCode::Left_Alt))
		{
			if (Input::GetMouseButton(MouseButton::Button_Left))
			{
				if (Input::GetKey(KeyCode::Left_Control))
					Pan(delta * 0.01f);
				else
					Rotate(delta);
			}
			else if (Input::GetMouseButton(MouseButton::Button_Right))
				Zoom(delta.y * 0.01f);
		}
		else if (Input::GetMouseButton(MouseButton::Button_Middle))
			Pan(delta * 0.01f);

		RecalculateView();
	}

	void EditorCamera::OnEvent(Event& evt)
	{
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<MouseScrolledEvent>(BIND_FUNCTION(EditorCamera::OnMouseScroll));
	}

	bool EditorCamera::OnMouseScroll(MouseScrolledEvent& evt)
	{
		float delta = evt.GetOffset().second * -0.15f;
		Zoom(delta);

		return false;
	}

	void EditorCamera::Pan(const glm::vec2& delta)
	{
		auto [xSpeed, ySpeed] = PanSpeed(m_ViewSize);
		m_FocalPoint -= GetDirectionRight(GetOrientation({ -m_Rotation.x, -m_Rotation.y, 0.0f })) * delta.x * xSpeed * m_Distance;
		m_FocalPoint += GetDirectionUp(GetOrientation({ -m_Rotation.x, -m_Rotation.y, 0.0f })) * delta.y * ySpeed * m_Distance;
	}

	void EditorCamera::Rotate(const glm::vec2& delta)
	{
		float yawSign = GetDirectionUp(GetOrientation({ -m_Rotation.x, -m_Rotation.y, 0.0f })).y < 0 ? -1.0f : 1.0f;
		m_Rotation.y -= yawSign * delta.x * 0.8f;
		m_Rotation.x -= delta.y * 0.8f;
	}

	void EditorCamera::Zoom(float delta)
	{
		m_Distance += delta * ZoomSpeed(m_Distance);
		if (m_Distance < 0.1f)
		{
			// TODO: Reenable - The line code below will shift the focal point foward if the new zoom distance is below
			// some arbitary threshold. It's good in theory but causes a few issues so for now it'll be left disabled.
			// m_FocalPoint += GetDirectionFront(GetOrientation({ -m_Rotation.x, -m_Rotation.y, 0.0f }));
			
			m_Distance = 0.1f;
		}
	}

	void EditorCamera::RecalculateView()
	{
		glm::quat orientation = GetOrientation({ -m_Rotation.x, -m_Rotation.y, 0.0f });
		m_Position = CalculatePosition(m_FocalPoint, orientation, m_Distance);

		m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::toMat4(orientation);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);

		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}
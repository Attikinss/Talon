#pragma once
#include "Camera.h"
#include "Events/MouseEvent.h"

namespace Talon
{
	// TODO: Each scene view panel will need its own camera so this
	//		 will need to exist in the scene view for easy reference

	class EditorCamera : public Camera
	{
	public:
		EditorCamera(float distanceFromCenter = 2.5f, const glm::vec3& rotation = { -25.0f, 45.0f, 0.0f })
			: m_Rotation(rotation), m_Distance(glm::abs(distanceFromCenter)), Camera()
		{

		}

		void Update();
		void OnEvent(Event& evt);

	private:
		bool OnMouseScroll(MouseScrolledEvent& evt);

		void Pan(const glm::vec2& delta);
		void Rotate(const glm::vec2& delta);
		void Zoom(float delta);
		void FlyCam(const glm::vec3& direction, const glm::vec2& mouseDelta);

		void RecalculateView();

	private:
		glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };

		float m_Distance = 0.0f;
		float m_FlyCamSpeed = 0.085f;
		bool m_FlyCamMode = false;
	};
}
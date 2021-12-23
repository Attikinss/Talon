#pragma once
#include "TalonEngine.h"

namespace Talon
{
	class EditorPanel
	{
	public:
		EditorPanel(const std::string& name)
			: m_Name(name)
		{
		}
		virtual ~EditorPanel() = default;

		virtual void Update() = 0;
		virtual void Draw(ImGuiWindowFlags additionalFlags = ImGuiWindowFlags_None) = 0;
		virtual void OnEvent(Event& evt) = 0;

		void SetScene(const std::shared_ptr<Scene>& scene)
		{
			m_Scene = scene;
		}

		bool Enabled() { return m_Enabled; }
		void Enable() { m_Enabled = true; }
		void Disable() { m_Enabled = false; }

	protected:
		std::string m_Name;
		std::shared_ptr<Scene> m_Scene;

		bool m_Enabled = true;
		bool m_Focused, m_Hovered = false;
	};
}
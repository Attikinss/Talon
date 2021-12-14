#pragma once
#include "TalonEngine.h"

class EditorPanel
{
public:
	EditorPanel(const std::string& name) 
		: m_Name(name) {}
	virtual ~EditorPanel() = default;

	virtual void Update() = 0;
	virtual void Draw(ImGuiWindowFlags_ additionalFlags = ImGuiWindowFlags_None) = 0;
	virtual void OnEvent(Talon::Event& evt) = 0;

	bool Enabled() { return m_Enabled; }
	void Enable() { m_Enabled = true; }
	void Disable() { m_Enabled = false; }

protected:
	std::string m_Name = std::string();
	bool m_Enabled = true;
};
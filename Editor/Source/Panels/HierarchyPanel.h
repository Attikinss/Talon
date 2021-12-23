#pragma once
#include "EditorPanel.h"

#include <imgui_internal.h>

namespace Talon
{
	class HierarchyPanel : public EditorPanel
	{
	public:
		HierarchyPanel() : EditorPanel("Hierarchy") { }
		HierarchyPanel(const std::shared_ptr<Scene>& scene)
			: EditorPanel("Hierarchy")
		{
			SetScene(scene);
		}

		void Update() override {}
		void OnEvent(Event& evt) override {}

		void Draw(ImGuiWindowFlags additionalFlags = ImGuiWindowFlags_None) override
		{
			ImGui::Begin(m_Name.c_str());
			ImGui::GetCurrentContext()->NavWindowingToggleLayer = false;

			for (auto entity : m_Scene->GetAllEntities())
				DrawNode(entity);

			// Clear scene selection if the left mouse button is
			// clicked but no tree nodes are currently hovered
			if (ImGui::IsMouseClicked(0) && ImGui::IsWindowHovered())
				m_Scene->ClearSelection();

			ImGui::End();
		}

		void DrawNode(Entity entity)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth;

			if (m_Scene->GetSelection().size() && entity == m_Scene->GetSelection()[0])
				flags |= ImGuiTreeNodeFlags_Selected;

			// TODO: if node has no children apply ImGuiTreeNodeFlags_Leaf to flags

			// TODO: Switch out single digit IDs with GUID/UUID??
			std::string name = entity.GetComponent<EntityInfo>().Name;
			bool open = ImGui::TreeNodeEx((void*)(uint64_t)entity.GetID(), flags, name.c_str());
			
			if (ImGui::IsItemClicked())
			{
				m_Scene->ClearSelection();
				m_Scene->AddToSelection(entity);
			}

			if (open)
			{
				// TODO: Recursively draw child nodes

				ImGui::TreePop();
			}
		}
	};
}
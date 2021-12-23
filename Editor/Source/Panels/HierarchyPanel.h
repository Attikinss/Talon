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

		void SetScene(const std::shared_ptr<Scene>& scene)
		{
			m_Scene = scene;
		}

		void Update() override {}
		void OnEvent(Event& evt) override {}

		void Draw(ImGuiWindowFlags additionalFlags = ImGuiWindowFlags_None) override
		{
			ImGui::Begin(m_Name.c_str());
			ImGui::GetCurrentContext()->NavWindowingToggleLayer = false;

			for (auto entity : m_Scene->GetAllEntities())
				DrawNode(entity);

			ImGui::End();
		}

		void DrawNode(Entity entity)
		{
			ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_OpenOnArrow;
			if (entity == m_Selection)
				flags |= ImGuiTreeNodeFlags_Selected;

			// TODO: if node has no children apply ImGuiTreeNodeFlags_Leaf to flags

			// TODO: Switch out single digit IDs with GUID/UUID??
			bool open = ImGui::TreeNodeEx((void*)(uint64_t)entity.GetID(), flags, entity.GetComponent<EntityInfo>().Name.c_str());
			if (ImGui::IsItemClicked())
				m_Selection = entity;

			if (open)
			{
				// TODO: Recursively draw child nodes

				ImGui::TreePop();
			}
		}

		void SelectEntity(Entity entity)
		{
			m_Selection = entity;
		}

	private:
		std::shared_ptr<Scene> m_Scene;
		Entity m_Selection;
	};
}
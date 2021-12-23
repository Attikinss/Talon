#pragma once
#include "EditorPanel.h"

#include <imgui_internal.h>
#include <glm/gtc/type_ptr.hpp>

namespace Talon
{
	class DetailsPanel : public EditorPanel
	{
	public:
		DetailsPanel() : EditorPanel("Details") { }
		DetailsPanel(const std::shared_ptr<Scene>& scene)
			: EditorPanel("Details")
		{
			SetScene(scene);
		}

		void Update() override
		{

		}

		void Draw(ImGuiWindowFlags additionalFlags = ImGuiWindowFlags_None) override
		{
			ImGui::Begin(m_Name.c_str());
			ImGui::GetCurrentContext()->NavWindowingToggleLayer = false;

			if (m_Scene.get())
			{
				auto selection = m_Scene->GetSelection();
				if (selection.size())
					DrawComponents(selection[0]);
			}

			ImGui::End();
		}
		
		void OnEvent(Event& evt) override
		{

		}

	private:
		void DrawComponents(Entity entity)
		{
			if (entity.HasComponent<EntityInfo>())
			{
				auto& info = entity.GetComponent<EntityInfo>();

				// Create and reset a local buffer
				char buffer[64];
				uint32_t bufferSize = sizeof(buffer);
				uint32_t stringSize = strlen(info.Name.c_str());
				memset(buffer, 0, bufferSize);

				// Copy current entity name into buffer
				uint32_t copySize = stringSize > bufferSize ? bufferSize : stringSize;
				memcpy(buffer, info.Name.c_str(), copySize);

				// Update entity name if buffer changes
				if (ImGui::InputText("Name", buffer, sizeof(buffer)))
					info.Name = std::string(buffer);
			}

			if (entity.HasComponent<Transform>())
			{
				if (ImGui::TreeNodeEx((void*)typeid(Transform).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth, Transform::GetName()))
				{
					auto& transform = entity.GetComponent<Transform>();
					ImGui::DragFloat3("Position", glm::value_ptr(transform.Position), 0.1f);

					if (ImGui::DragFloat3("Rotation", glm::value_ptr(transform.EulerAngles)), 0.1f)
						transform.Rotation = glm::quat(glm::radians(transform.EulerAngles));

					ImGui::DragFloat3("Scale", glm::value_ptr(transform.Scale), 0.1f);

					ImGui::TreePop();
				}
			}

			if (entity.HasComponent<MeshRenderer>())
			{
				auto& meshRenderer = entity.GetComponent<MeshRenderer>();

				ImGui::Checkbox("##enabled", &meshRenderer.Enabled);
				ImGui::SameLine();

				if (ImGui::TreeNodeEx((void*)typeid(MeshRenderer).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth, MeshRenderer::GetName()))
				{

					ImGui::TreePop();
				}
			}

			if (entity.HasComponent<Light>())
			{
				auto& light = entity.GetComponent<Light>();

				ImGui::Checkbox("##enabled", &light.Enabled);
				ImGui::SameLine();

				if (ImGui::TreeNodeEx((void*)typeid(Light).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth, Light::GetName()))
				{

					ImGui::TreePop();
				}
			}

			if (entity.HasComponent<WorldCamera>())
			{
				auto& cameraComponent = entity.GetComponent<WorldCamera>();
				auto& camera = cameraComponent.GetCamera();

				ImGui::Checkbox("##enabled", &cameraComponent.Enabled);
				ImGui::SameLine();

				if (ImGui::TreeNodeEx((void*)typeid(WorldCamera).hash_code(), ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth, WorldCamera::GetName()))
				{
					// Update camera projection
					std::string value = camera.m_ProjectionType == Projection::Orthographic ? "Orthographic" : "Perspective";
					if (ImGui::BeginCombo("Projection", value.c_str()))
					{
						if (ImGui::Selectable("Orthographic"))
							camera.SetProjectionType(Projection::Orthographic);
						else if (ImGui::Selectable("Perspective"))
							camera.SetProjectionType(Projection::Perspective);

						ImGui::EndCombo();
					}

					float fov = camera.m_FieldOfView;
					float nearPlane = camera.m_NearPlane;
					float farPlane = camera.m_FarPlane;

					// Update field of view
					if (ImGui::SliderFloat("Field of View", &fov, FLT_MIN, 179.0f))
						camera.SetFOV(fov);

					// Update near clipping plane
					if (ImGui::DragFloat("Near Plane", &nearPlane, 0.1f))
						camera.SetNearPlane(nearPlane);

					// Update far clipping plane
					if (ImGui::DragFloat("Far Plane", &farPlane, 0.1f))
						camera.SetFarPlane(farPlane);

					ImGui::TreePop();
				}
			}
		}
	};
}
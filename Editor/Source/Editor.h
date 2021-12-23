#pragma once
#include "TalonEngine.h"
#include "Panels/HierarchyPanel.h"
#include "Panels/GameViewPanel.h"
#include "Panels/SceneViewPanel.h"

namespace Talon
{
	class Editor : public Layer
	{
	public:
		Editor()
			: Layer("Editor")
		{

		}

		void Attach() override
		{

		}

		void Detach() override
		{

		}

		void Initialise() override
		{
			m_CurrentScene = std::make_shared<Scene>();
			m_SceneHierarchy = HierarchyPanel(m_CurrentScene);
			m_GameView = GameViewPanel(m_CurrentScene);
			m_SceneView = SceneViewPanel(m_CurrentScene);

			m_Camera = m_CurrentScene->CreateEntity("Camera");
			m_Camera.GetComponent<Transform>().Position = { 0.0f, 0.0f, 10.0f };
			GameViewPanel::SetCamera(&m_Camera.AddComponent<WorldCamera>().GetCamera());

			m_Light = m_CurrentScene->CreateEntity("Directional Light");
			m_Light.GetComponent<Transform>().Rotation = glm::quatLookAt(glm::normalize(glm::vec3(-1.5f, -2.0f, -2.5f)), { 0.0f, 1.0f, 0.0f });

			m_TestMaterial = std::make_shared<Material>(Shader::Create("Assets/Shaders/DefaultLit.glsl"));

			m_Cube = m_CurrentScene->CreateEntity("Cube");
			auto& meshRenderer = m_Cube.AddComponent<MeshRenderer>();
			meshRenderer.SetMesh(MeshLoader::Load("Assets/Models/cube.obj")[0]);
			meshRenderer.SetMaterial(m_TestMaterial);

			m_CubeAlbedo = Texture2D::Create("Assets/Textures/greasy-pan-2-albedo.png");
			m_CubeNormal = Texture2D::Create("Assets/Textures/greasy-pan-2-normal.png");

			m_TestMaterial->Bind();
			m_TestMaterial->SetInt("u_AlbedoTex", 0);
			m_TestMaterial->SetInt("u_NormalTex", 1);

			RendererCommand::SetClearColour({ 0.15f, 0.15f, 0.15f, 1.0f });
			RendererCommand::SetFaceCull(true);
			RendererCommand::SetFaceCullType(FaceCullType::Back);
			RendererCommand::SetPrimitiveType(PrimitiveType::Triangles);
			RendererCommand::SetDepthTest(true);
		}

		void Update() override
		{
			m_CurrentScene->Update();

			m_CubeAlbedo->Bind(0);
			m_CubeNormal->Bind(1);

			m_TestMaterial->Bind();

			m_TestMaterial->SetVector3("u_LightDirection", m_Light.GetComponent<Transform>().Forward);
			m_TestMaterial->SetVector3("u_LightPosition", { -0.75f, -1.5f, -2.5f });
			m_TestMaterial->SetVector3("u_Attenuation", { 1.0f, 0.01f, 0.002f });

			// TODO: Add to lighting uniform buffer
			m_TestMaterial->SetVector3("u_AmbientLightColour", glm::vec3(0.1f));

			// Update panels
			m_GameView.Update();
			m_SceneView.Update();
			m_SceneHierarchy.Update();

			// Draw to game view
			m_GameView.BeginFrame();
			m_CurrentScene->Render(m_GameView.GetCamera());
			m_GameView.EndFrame();

			// Draw to scene view
			m_SceneView.BeginFrame();
			m_CurrentScene->Render(m_SceneView.GetCamera());
			m_SceneView.EndFrame();
		}

		void DrawGUI() override
		{
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New", "Ctrl+N", false, true)) {}
					if (ImGui::MenuItem("Open...", "Ctrl+O", false, true)) {}

					if (ImGui::MenuItem("Save", "Ctrl+S", false, true)) {}
					if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S", false, true)) {}
					if (ImGui::MenuItem("Exit", "Ctrl+W")) {}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Window"))
				{
					if (ImGui::MenuItem("Viewport", "Ctrl+1", false, true)) {}
					if (ImGui::MenuItem("Properties", "Ctrl+2", false, true)) {}
					if (ImGui::MenuItem("Hierarchy", "Ctrl+3", false, true)) {}

					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Help"))
				{
					if (ImGui::MenuItem("About Talon", "", false, true)) {}
					if (ImGui::MenuItem("Documentation", "", false, true)) {}
					if (ImGui::MenuItem("Release Notes", "", false, true)) {}

					ImGui::EndMenu();
				}

				ImGui::EndMainMenuBar();
			}

			// Draw panel GUIs
			m_GameView.Draw();
			m_SceneView.Draw();
			m_SceneHierarchy.Draw();
		}

		void Shutdown() override
		{

		}

		void ProcessEvents(Event& evt) override
		{
			m_GameView.OnEvent(evt);
			m_SceneView.OnEvent(evt);
			m_SceneHierarchy.OnEvent(evt);
		}

	private:
		GameViewPanel m_GameView;
		SceneViewPanel m_SceneView;
		HierarchyPanel m_SceneHierarchy;

		Entity m_Camera;
		Entity m_Cube;
		Entity m_Light;

		std::shared_ptr<Scene> m_CurrentScene;
		std::shared_ptr<Material> m_TestMaterial;

		std::shared_ptr<Texture2D> m_CubeAlbedo;
		std::shared_ptr<Texture2D> m_CubeNormal;
	};
}
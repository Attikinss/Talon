#pragma once
#include "TalonEngine.h"
#include "Panels/GameView.h"
#include "Panels/SceneView.h"

namespace Talon
{
	class Editor : public Layer
	{
	public:
		Editor()
			: Layer("Editor")
		{
			m_Viewports.push_back(new SceneView("Scene"));
			m_Viewports.push_back(new GameView("Game"));
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
			m_Camera = m_CurrentScene->CreateEntity();
			m_Camera.GetComponent<Transform>().Position = { 0.0f, 0.0f, 10.0f };
			GameView::SetCamera(&m_Camera.AddComponent<WorldCamera>().GetCamera());

			m_Light = m_CurrentScene->CreateEntity();
			m_Light.GetComponent<Transform>().Rotation = glm::quatLookAt(glm::normalize(glm::vec3(-1.5f, -2.0f, -2.5f)), { 0.0f, 1.0f, 0.0f });

			m_TestMaterial = std::make_shared<Material>(Shader::Create("Assets/Shaders/DefaultLit.glsl"));

			m_Cube = m_CurrentScene->CreateEntity();
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

			for (auto& vp : m_Viewports)
			{
				vp->Update();

				vp->BeginFrame();
				m_CurrentScene->Render(vp->GetCamera());
				vp->EndFrame();
			}
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

			if (m_Viewports.size() == 1)
				m_Viewports[0]->Draw(ImGuiWindowFlags_NoMove);
			else
			{
				for (auto& vp : m_Viewports)
					vp->Draw();
			}
		}

		void Shutdown() override
		{
			for (auto& vp : m_Viewports)
				delete vp;

			m_Viewports.clear();
		}

		void ProcessEvents(Event& evt) override
		{
			for (auto& vp : m_Viewports)
				vp->OnEvent(evt);
		}

	private:
		std::vector<Viewport*> m_Viewports;

		Entity m_Camera;
		Entity m_Cube;
		Entity m_Light;

		std::shared_ptr<Scene> m_CurrentScene;
		std::shared_ptr<Material> m_TestMaterial;

		std::shared_ptr<Texture2D> m_CubeAlbedo;
		std::shared_ptr<Texture2D> m_CubeNormal;
	};
}
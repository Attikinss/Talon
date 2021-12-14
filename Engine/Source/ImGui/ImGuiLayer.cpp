#include "ImGuiLayer.h"

#include "Core/Input.h"
#include "Core/Logger.h"
#include "Core/Window.h"

#include "Renderer/RenderContext.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>

namespace Talon
{
	ImGuiLayer::ImGuiLayer(const std::string& name)
		: Layer(name)
	{

	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoDecoration
			| ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus;
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		static bool dockspaceOpen = true;

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace", &dockspaceOpen, windowFlags);
		ImGui::PopStyleVar();

		ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		ImVec2 minWindowSize = style.WindowMinSize;
		style.WindowMinSize = { 192.0f, 192.0f };

		ImGuiID dockspaceID = ImGui::GetID("MyDockSpace");
		ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;
		ImGui::DockSpace(dockspaceID, { 0.0f, 0.0f }, dockspaceFlags);
	}

	void ImGuiLayer::End()
	{
		ImGui::End();

		ImGuiIO& io = ImGui::GetIO();
		auto [x, y] = Window::Get().GetSize();
		io.DisplaySize = ImVec2((float)x, (float)y);

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			// TODO: Abstract GLFW stuff out of this file

			GLFWwindow* currentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(currentContext);
		}
	}

	void ImGuiLayer::Attach()
	{

	}

	void ImGuiLayer::Detach()
	{

	}

	void ImGuiLayer::Initialise()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigWindowsMoveFromTitleBarOnly = true;

		// Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		
		// Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		// Enable Multi-Viewport / Platform Windows
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// Enable Gamepad Controls
		// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		
		// Remove icons from taskbars
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		
		// io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup styling

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(Window::Get().GetWindowHandle(), true);
		ImGui_ImplOpenGL3_Init("#version 450");

		io.KeyMap[ImGuiKey_Tab] = (int)KeyCode::Tab;
		io.KeyMap[ImGuiKey_LeftArrow] = (int)KeyCode::Left;
		io.KeyMap[ImGuiKey_RightArrow] = (int)KeyCode::Right;
		io.KeyMap[ImGuiKey_UpArrow] = (int)KeyCode::Up;
		io.KeyMap[ImGuiKey_DownArrow] = (int)KeyCode::Down;
		io.KeyMap[ImGuiKey_PageUp] = (int)KeyCode::Page_Up;
		io.KeyMap[ImGuiKey_PageDown] = (int)KeyCode::Page_Down;
		io.KeyMap[ImGuiKey_Home] = (int)KeyCode::Home;
		io.KeyMap[ImGuiKey_End] = (int)KeyCode::End;
		io.KeyMap[ImGuiKey_Insert] = (int)KeyCode::Insert;
		io.KeyMap[ImGuiKey_Delete] = (int)KeyCode::Delete;
		io.KeyMap[ImGuiKey_Backspace] = (int)KeyCode::Backspace;
		io.KeyMap[ImGuiKey_Space] = (int)KeyCode::Space;
		io.KeyMap[ImGuiKey_Enter] = (int)KeyCode::Enter;
		io.KeyMap[ImGuiKey_Escape] = (int)KeyCode::Escape;
		io.KeyMap[ImGuiKey_KeyPadEnter] = (int)KeyCode::KP_Enter;
		io.KeyMap[ImGuiKey_A] = (int)KeyCode::A;
		io.KeyMap[ImGuiKey_C] = (int)KeyCode::C;
		io.KeyMap[ImGuiKey_V] = (int)KeyCode::V;
		io.KeyMap[ImGuiKey_X] = (int)KeyCode::X;
		io.KeyMap[ImGuiKey_Y] = (int)KeyCode::Y;
		io.KeyMap[ImGuiKey_Z] = (int)KeyCode::Z;
	}

	void ImGuiLayer::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::ProcessEvents(Event& evt)
	{
		ImGuiIO& io = ImGui::GetIO();

		evt.m_Used |= evt.IsInCategory(CategoryMouse) & io.WantCaptureMouse;
		evt.m_Used |= evt.IsInCategory(CategoryKeyboard) & io.WantCaptureKeyboard;
	}
}
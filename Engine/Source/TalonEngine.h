#pragma once

// Core
#include "Core/Application.h"
#include "Core/Input.h"
#include "Core/Logger.h"
#include "Core/Time.h"
#include "Core/Window.h"

// Components
#include "ECS/Entity.h"
#include "ECS/EntityRegistry.h"
#include "ECS/Light.h"
#include "ECS/MeshRenderer.h"
#include "ECS/Transform.h"

// Events
#include "Events/ApplicationEvent.h"
#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"

// ImGui
#include <imgui.h>
#include "ImGui/ImGuiLayer.h"

// Rendering
#include "Renderer/EditorCamera.h"
#include "Renderer/Framebuffer.h"
#include "Renderer/MeshLoader.h"
#include "Renderer/RendererCommand.h"
#include "Renderer/Material.h"
#include "Renderer/Shader.h"

#ifdef INCLUDE_ENTRY
#include "EntryPoint.h"
#endif
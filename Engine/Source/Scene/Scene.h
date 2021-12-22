#pragma once
#include "ECS/EntityRegistry.h"
#include "Events/Event.h"

namespace Talon
{
	class Camera;

	class Scene
	{
	public:
		Scene(const std::string& name = "Untitled");
		~Scene();

		void Update();
		void Render(const Camera& camera);
		void OnEvent(Event& evt);

		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		EntityRegistry& GetRegistry() { return m_Registry; }

		static Scene& GetCurrent() { return *s_CurrentScene; }
		inline static Scene* s_CurrentScene = nullptr;

	private:
		std::string m_Name;
		bool m_IsCurrent = false;

		EntityRegistry m_Registry;
	};
}
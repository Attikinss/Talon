#pragma once
#include "ECS/EntityRegistry.h"
#include "Events/Event.h"

namespace Talon
{
	class Scene
	{
	public:
		Scene(const std::string& name = "Untitled");
		~Scene();

		void Update();
		void OnEvent(Event& evt);

		Entity CreateEntity();
		void DestroyEntity(Entity entity);

		EntityRegistry& GetRegistry() { return m_Registry; }

	private:
		std::string m_Name;

		EntityRegistry m_Registry;
	};
}
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

		Entity CreateEntity(const std::string& name = "Entity");
		void DestroyEntity(Entity entity);

		std::vector<Entity> GetAllEntities()
		{
			std::vector<Entity> entites;
			entites.reserve(m_Registry.m_Registry.size());

			m_Registry.m_Registry.each([&](auto id)
			{
				entites.emplace_back(this, id);
			});

			return entites;
		}

		EntityRegistry& GetRegistry() { return m_Registry; }

		void AddToSelection(Entity selection);
		const std::vector<Entity>& GetSelection() const { return m_Selection; }
		void ClearSelection() { m_Selection.clear(); }

		static const std::shared_ptr<Scene>& GetCurrent() { return s_CurrentScene; }
		inline static std::shared_ptr<Scene> s_CurrentScene;

	private:
		std::string m_Name;
		bool m_IsCurrent = false;

		EntityRegistry m_Registry;
		std::vector<Entity> m_Selection;
	};
}
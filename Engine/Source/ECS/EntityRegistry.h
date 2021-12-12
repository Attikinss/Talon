#pragma once
#include <entt/entt.hpp>

namespace Talon
{
	class Entity;

	class EntityRegistry
	{
	public:
		EntityRegistry();
		~EntityRegistry();

		Entity CreateEntity();
		void DestroyEntity(entt::entity entityHandle);

		template<typename T, typename... Args>
		T& AddComponent(entt::entity entityHandle, Args&&... args)
		{
			return m_Registry.emplace<T>(entityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent(entt::entity entityHandle)
		{
			return m_Registry.get<T>(entityHandle);
		}

		template<typename T>
		bool HasComponent(entt::entity entityHandle)
		{
			return m_Registry.any_of<T>(entityHandle);
		}

		template<typename T>
		void RemoveComponent(entt::entity entityHandle)
		{
			m_Registry.remove<T>(entityHandle);
		}

		template<typename T>
		bool TryGetComponent(entt::entity entityHandle, T** component)
		{
			component = m_Registry.get<T>(entityHandle);
			return component != nullptr;
		}

	private:
		entt::registry m_Registry;
	};
}
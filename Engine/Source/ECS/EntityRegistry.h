#pragma once
#include <entt/entt.hpp>

namespace Talon
{
	class Entity;

	template<typename T>
	using ComponentCollection = entt::basic_view<entt::entity, entt::exclude_t<>, T>;

	class EntityRegistry
	{
		friend class Scene;

	public:
		EntityRegistry();
		~EntityRegistry();

		entt::entity CreateEntity();
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
		ComponentCollection<T> GetComponentsOfType()
		{
			return m_Registry.view<T>();
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
		bool TryGetComponent(entt::entity entityHandle, T* component)
		{
			T foundComponent = m_Registry.get<T>(entityHandle);
			*component = foundComponent;

			return component != nullptr;
		}

	private:
		entt::registry m_Registry;
	};
}
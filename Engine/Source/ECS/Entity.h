#pragma once
#include "EntityRegistry.h"
#include "Core/Logger.h"

#include <entt/entt.hpp>

namespace Talon
{
	class Entity
	{
	public:
		Entity(EntityRegistry* registry);
		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			// TODO: Assert if T not compoent?

			if (HasComponent())
			{
				Logger::Error("Entity already has [{0}] component!", T::GetName());
				return nullptr;
			}

			return m_Registry->AddComponent(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			// TODO: Assert if T not compoent?

			if (!HasComponent())
			{
				Logger::Error("Entity does not have [{0}] component!", T::GetName());
				return nullptr;
			}

			return m_Registry->GetComponent<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			// TODO: Assert if T not compoent?

			return m_Registry->HasComponent<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			// TODO: Assert if T not compoent?

			if (!HasComponent())
			{
				Logger::Error("Entity does not have [{0}] component!", T::GetName());
				return nullptr;
			}

			m_Registry->RemoveComponent<T>(m_EntityHandle);
		}

		template<typename T>
		bool TryGetComponent(T** component)
		{
			// TODO: Assert if T not compoent?

			component = m_Registry->m_Registry.get<T>(m_EntityHandle, component);
			return component != nullptr;
		}

	private:
		entt::entity m_EntityHandle;
		EntityRegistry* m_Registry;
	};
}
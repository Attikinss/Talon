#pragma once
#include "Core/Logger.h"
#include "EntityRegistry.h"
#include "Transform.h"

#include <entt/entt.hpp>

namespace Talon
{
	// TODO: Make Enities shared pointers?

	class Entity
	{
	public:
		Entity(EntityRegistry* registry, entt::entity handle);
		~Entity();

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			// TODO: Assert if T not component?

			if (HasComponent<T>())
			{
				Logger::Error("Entity already has [{0}] component!", T::GetName());
				_ASSERT(false);
			}

			Component& component = m_Registry->AddComponent<T>(m_EntityHandle, std::forward<Args>(args)...);
			component.m_Entity = this;

			return (T&)component;
		}

		template<typename T>
		T& GetComponent()
		{
			// TODO: Assert if T not component?

			if (!HasComponent<T>())
			{
				Logger::Error("Entity does not have [{0}] component!", T::GetName());
				_ASSERT(false);
			}

			return m_Registry->GetComponent<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			// TODO: Assert if T not component?

			return m_Registry->HasComponent<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			// TODO: Assert if T not component?

			if (!HasComponent())
			{
				Logger::Error("Entity does not have [{0}] component!", T::GetName());
				_ASSERT(false);
			}

			m_Registry->RemoveComponent<T>(m_EntityHandle);
		}

		template<typename T>
		bool TryGetComponent(T** component)
		{
			// TODO: Assert if T not compoent?

			component = m_Registry->TryGetComponent<T>(m_EntityHandle, component);
			return component != nullptr;
		}

	private:
		entt::entity m_EntityHandle = entt::null;
		EntityRegistry* m_Registry = nullptr;
	};
}
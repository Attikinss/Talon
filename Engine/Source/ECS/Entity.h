#pragma once
#include "Core/Logger.h"
#include "EntityRegistry.h"
#include "Transform.h"

#include "Scene/Scene.h"

#include <entt/entt.hpp>

namespace Talon
{
	// TODO: Make Enities shared pointers?

	class Entity
	{
		friend class Scene;

	public:
		Entity() = default;
		Entity(Scene* scene, entt::entity handle)
			: m_Scene(scene), m_EntityHandle(handle)
		{
			AddComponent<Transform>();
		}

		~Entity() = default;

		void Destroy()
		{
			m_Scene->DestroyEntity(*this);
		}

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			// TODO: Assert if T not component?

			if (HasComponent<T>())
			{
				Logger::Error("Entity already has [{0}] component!", T::GetName());
				_ASSERT(false);
			}

			Component& component = m_Scene->GetRegistry().AddComponent<T>(m_EntityHandle, std::forward<Args>(args)...);
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

			return m_Scene->GetRegistry().GetComponent<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			// TODO: Assert if T not component?

			return m_Scene->GetRegistry().HasComponent<T>(m_EntityHandle);
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

			m_Scene->GetRegistry().RemoveComponent<T>(m_EntityHandle);
		}

		template<typename T>
		bool TryGetComponent(T** component)
		{
			// TODO: Assert if T not compoent?

			component = m_Scene->GetRegistry().TryGetComponent<T>(m_EntityHandle, component);
			return component != nullptr;
		}

	private:
		entt::entity m_EntityHandle = entt::null;
		Scene* m_Scene = nullptr;
	};
}
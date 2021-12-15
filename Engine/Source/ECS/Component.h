#pragma once

namespace Talon
{
	class Entity;

	class Component
	{
		friend class Entity;

	public:
		Component() = default;
		virtual ~Component() = default;

		virtual void OnEditorUpdate() {}
		virtual void OnUpdate() {}
		virtual void OnFixedUpdate() {}

	protected:
		Entity* m_Entity = nullptr;
	};
}
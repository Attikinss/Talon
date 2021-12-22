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

	protected:
		Entity* m_Entity = nullptr;
	};
}
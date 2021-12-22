#pragma once

namespace Talon
{
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
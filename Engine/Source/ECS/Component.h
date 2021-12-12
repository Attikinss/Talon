#pragma once

namespace Talon
{
	class Entity;

	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

	protected:
		Entity* m_Entity = nullptr;
	};
}
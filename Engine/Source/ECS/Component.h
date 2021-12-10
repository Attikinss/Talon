#pragma once
#include "Entity.h"

namespace Talon
{
	class Component
	{
	public:
		Component() = default;
		virtual ~Component() = default;

		virtual const char* GetName() = 0;
	};
}
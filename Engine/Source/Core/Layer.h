#pragma once
#include <string>
#include "Events/Event.h"

namespace Talon
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer")
			: m_DebugName(name) {}

		virtual ~Layer() = default;

		virtual void Attach() {}
		virtual void Detach() {}

		virtual void Initialise() {}
		virtual void Update() {}
		virtual void Shutdown() {}
		virtual void ProcessEvents(Event& evt) {}

		inline const std::string& GetNane() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};
}
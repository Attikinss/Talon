#pragma once
#include "Core/Layer.h"

namespace Talon
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer(const std::string& name = "ImGuiLayer");
		~ImGuiLayer();

		void Begin();
		void End();

		void Attach() override;
		void Detach() override;

		void Initialise() override;
		void Shutdown() override;
		void ProcessEvents(Event& evt) override;
	};
}
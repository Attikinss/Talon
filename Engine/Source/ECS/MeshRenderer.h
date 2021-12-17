#pragma once
#include "Component.h"
#include <memory>

namespace Talon
{
	class Mesh;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer() = default;
		MeshRenderer(const std::shared_ptr<Mesh>& mesh)
			: m_Mesh(mesh) { }
		~MeshRenderer() = default;

		// TODO: Revise this function, could be better utilised elsewhere?
		void Render();

		const std::shared_ptr<Mesh>& GetMesh() const { return m_Mesh; }
		void SetMesh(const std::shared_ptr<Mesh>& mesh) { m_Mesh = mesh; }

		static const char* GetName() { return "MeshRenderer"; }

	private:
		std::shared_ptr<Mesh> m_Mesh;
	};
}
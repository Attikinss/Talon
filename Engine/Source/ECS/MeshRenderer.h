#pragma once
#include "Component.h"
#include <memory>

namespace Talon
{
	class Mesh;
	class Material;

	class MeshRenderer : public Component
	{
		friend class Scene;

	public:
		MeshRenderer() = default;
		MeshRenderer(const std::shared_ptr<Mesh>& mesh)
			: m_Mesh(mesh) { }
		~MeshRenderer() = default;

		const std::shared_ptr<Material>& GetMaterial() const { return m_Material; }
		void SetMaterial(const std::shared_ptr<Material>& material) { m_Material = material; }

		const std::shared_ptr<Mesh>& GetMesh() const { return m_Mesh; }
		void SetMesh(const std::shared_ptr<Mesh>& mesh) { m_Mesh = mesh; }

		static const char* GetName() { return "MeshRenderer"; }

	private:
		std::shared_ptr<Mesh> m_Mesh;
		std::shared_ptr<Material> m_Material;
	};
}
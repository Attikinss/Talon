#include "MeshRenderer.h"

#include "Entity.h"
#include "Renderer/RendererCommand.h"

namespace Talon
{
	void MeshRenderer::Render()
	{
		RendererCommand::Submit(m_Mesh, m_Material, m_Entity->GetComponent<Transform>().GetTransform());
	}
}
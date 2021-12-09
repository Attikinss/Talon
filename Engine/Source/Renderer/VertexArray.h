#pragma once
#include "IndexBuffer.h"
#include "VertexBuffer.h"

#include <memory>
#include <vector>

namespace Talon
{
	class VertexArray
	{
	public:
		static std::shared_ptr<VertexArray> Create();

		VertexArray();
		~VertexArray();

		void Bind();
		void Unbind();

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

	private:
		uint32_t m_ID = 0;
		uint32_t m_AttributeCount = 0;

		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}
#pragma once
#include "BufferLayout.h"

#include <memory>

namespace Talon
{
	class VertexBuffer
	{
	public:
		static std::shared_ptr<VertexBuffer> Create(uint32_t size);
		static std::shared_ptr<VertexBuffer> Create(uint32_t size, void* data);

		VertexBuffer(uint32_t size);
		VertexBuffer(uint32_t size, void* data);
		~VertexBuffer();

		void SetData(uint32_t size, void* data, uint32_t offset = 0);
		void SetLayout(const BufferLayout& layout) { m_Layout = layout; }
		void Bind();
		void Unbind();

		BufferLayout& GetLayout() { return m_Layout; }
		uint32_t GetSize() const { return m_Size; }

	private:
		uint32_t m_ID = 0;
		uint32_t m_Size = 0;

		BufferLayout m_Layout;
	};
}
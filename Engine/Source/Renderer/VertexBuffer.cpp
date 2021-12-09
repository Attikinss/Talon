#include "VertexBuffer.h"

#include <glad/gl.h>

namespace Talon
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		return std::make_shared<VertexBuffer>(size);
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size, void* data)
	{
		return std::make_shared<VertexBuffer>(size, data);
	}

	VertexBuffer::VertexBuffer(uint32_t size)
		: m_Size(size)
	{
		// Create buffer and assign size but leave it empty
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, nullptr, GL_DYNAMIC_DRAW);
	}

	VertexBuffer::VertexBuffer(uint32_t size, void* data)
		: m_Size(size)
	{
		// Create and write to buffer
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, data, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
		m_ID = 0;
	}

	void VertexBuffer::SetData(uint32_t size, void* data, uint32_t offset)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

		void* buffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY | GL_MAP_UNSYNCHRONIZED_BIT);
		memcpy((&buffer)[offset], data, size);

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}

	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_ID);
	}

	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
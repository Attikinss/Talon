#include "IndexBuffer.h"

#include <glad/gl.h>

namespace Talon
{
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t size)
	{
		return std::make_shared<IndexBuffer>(size);
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::Create(uint32_t size, void* data)
	{
		return std::make_shared<IndexBuffer>(size, data);
	}

	IndexBuffer::IndexBuffer(uint32_t size)
		: m_Count(size / sizeof(uint32_t))
	{
		// Create buffer and assign size but leave it empty
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, nullptr, GL_DYNAMIC_DRAW);
	}

	IndexBuffer::IndexBuffer(uint32_t size, void* data)
		: m_Count(size / sizeof(uint32_t))
	{
		// Create and write to buffer
		glCreateBuffers(1, &m_ID);
		glNamedBufferData(m_ID, size, data, GL_STATIC_DRAW);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &m_ID);
		m_ID = 0;
	}

	void IndexBuffer::SetData(uint32_t size, void* data, uint32_t offset)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);

		void* buffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY | GL_MAP_UNSYNCHRONIZED_BIT);
		memcpy((&buffer)[offset], data, size);

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}

	void IndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}

	void IndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID);
	}
}
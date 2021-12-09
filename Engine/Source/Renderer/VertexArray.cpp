#include "VertexArray.h"

#include <glad/gl.h>

namespace Talon
{
	static GLenum DataTypeToOpenGLType(DataType type)
	{
		switch (type)
		{
			case DataType::Bool:
				return GL_BOOL;

			case DataType::Float:
			case DataType::Float2:
			case DataType::Float3:
			case DataType::Float4:
			case DataType::Mat3:
			case DataType::Mat4:
				return GL_FLOAT;

			case DataType::Int:
			case DataType::Int2:
			case DataType::Int3:
			case DataType::Int4:
				return GL_INT;
		}

		return GL_NONE;
	}

	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		return std::make_shared<VertexArray>();
	}

	VertexArray::VertexArray()
	{
		// Create and bind vertex array
		glCreateVertexArrays(1, &m_ID);
		glBindVertexArray(m_ID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &m_ID);
		m_ID = 0;
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(m_ID);

		for (uint32_t i = 0; i < m_AttributeCount; i++)
			glEnableVertexAttribArray(i);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);

		for (uint32_t i = 0; i < m_AttributeCount; i++)
			glDisableVertexAttribArray(i);
	}

	void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		m_VertexBuffers.push_back(buffer);

		glBindVertexArray(m_ID);
		buffer->Bind();

		uint32_t index = 0;
		const auto& layout = buffer->GetLayout();
		auto elements = layout.GetElements();

		for (const auto& element : elements)
		{
			uint32_t componentCount = element.GetComponentCount();
			uint32_t valueType = DataTypeToOpenGLType(element.Type);
			uint32_t normalised = element.Normalised ? GL_TRUE : GL_FALSE;
			uint32_t stride = layout.GetStride();
			uint32_t offset = element.Offset;

			uint32_t glAttribs = componentCount < 4 ? 1 : 4 % componentCount;
			for (uint32_t j = 0; j < glAttribs; j++)
			{
				// This assumes the data is always of float type
				uint64_t dataOffset = (uint64_t)(offset + componentCount * j);

				glEnableVertexAttribArray(m_AttributeCount + index);
				glVertexAttribPointer(m_AttributeCount + index, componentCount / glAttribs, valueType, normalised, stride, (void*)dataOffset);

				if (element.Instanced)
					glVertexAttribDivisor(m_AttributeCount + index, 1);

				index++;
			}
		}

		m_AttributeCount += index;

		Unbind();
		buffer->Unbind();
	}

	void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
	{
		m_IndexBuffer = buffer;

		glBindVertexArray(m_ID);
		m_IndexBuffer->Bind();

		glBindVertexArray(0);
		m_IndexBuffer->Unbind();
	}
}
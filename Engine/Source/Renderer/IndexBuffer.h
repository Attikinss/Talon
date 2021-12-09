#pragma once
#include <memory>

namespace Talon
{
	class IndexBuffer
	{
	public:
		static std::shared_ptr<IndexBuffer> Create(uint32_t count);
		static std::shared_ptr<IndexBuffer> Create(uint32_t count, void* data);

		IndexBuffer(uint32_t size);
		IndexBuffer(uint32_t size, void* data);
		~IndexBuffer();

		void SetData(uint32_t size, void* data, uint32_t offset = 0);
		void Bind();
		void Unbind();

		uint32_t GetCount() const { return m_Count; }

	private:
		uint32_t m_ID = 0;
		uint32_t m_Count = 0;
	};
}
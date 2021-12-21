#pragma once
#include <memory>

namespace Talon
{
	class UniformBuffer
	{
	public:
		static std::shared_ptr<UniformBuffer> Create(uint32_t size, uint32_t binding = 0);

		UniformBuffer(uint32_t size, uint32_t binding = 0);
		~UniformBuffer();

		void SetData(uint32_t size, void* data, uint32_t offset = 0);

	private:
		uint32_t m_ID = 0;
	};
}
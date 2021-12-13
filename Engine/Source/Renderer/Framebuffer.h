#pragma once
#include <glm/glm.hpp>

#include <memory>
#include <vector>

namespace Talon
{
	enum class FramebufferTextureFormat
	{
		None = 0,
		RGBA8,
		DEPTH24_STENCIL8,
	};

	struct FramebufferTextureInfo
	{
		FramebufferTextureFormat Format;

		FramebufferTextureInfo() = default;
		FramebufferTextureInfo(FramebufferTextureFormat format)
			: Format(format) {}
	};

	struct FramebufferAttachmentInfo
	{
		std::vector<FramebufferTextureInfo> TextureFormats;

		FramebufferAttachmentInfo() = default;
		FramebufferAttachmentInfo(std::initializer_list<FramebufferTextureInfo> formats)
			: TextureFormats(formats) {}
	};

	struct FramebufferCreateInfo
	{
		uint32_t Width = 0, Height = 0;
		FramebufferAttachmentInfo Attachments;
	};

	class Framebuffer
	{
	public:
		static std::shared_ptr<Framebuffer> Create(const FramebufferCreateInfo& createInfo);

		Framebuffer(FramebufferCreateInfo createInfo);
		~Framebuffer();

		const FramebufferCreateInfo& GetInfo() const;
		uint32_t GetColourAttachment(uint32_t index = 0) const;
		void Bind() const;
		void Unbind() const;
		void Resize(const glm::vec2& size, bool forceCreate = false);
		void Resize(uint32_t width, uint32_t height, bool forceCreate = false);
		void BindTexture(uint32_t index);

	private:
		uint32_t m_ID = 0;
		FramebufferCreateInfo m_CreateInfo;
		std::vector<FramebufferTextureFormat> m_ColourAttachmentFormats;
		FramebufferTextureFormat m_DepthAttachmentFormat = FramebufferTextureFormat::None;

		std::vector<uint32_t> m_ColourAttachments;
		uint32_t m_DepthAttachment = 0;
	};
}
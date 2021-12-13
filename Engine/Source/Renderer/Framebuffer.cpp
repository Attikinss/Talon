#include "Framebuffer.h"
#include "Core/Logger.h"
#include "Core/Window.h"

#include <glad/gl.h>

namespace Talon
{
	namespace Utilities
	{
		void BindTexture(uint32_t id, uint32_t unit = 0)
		{
			glActiveTexture(GL_TEXTURE0 + unit);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void CreateTextures(uint32_t* out, uint32_t count = 1)
		{
			glCreateTextures(GL_TEXTURE_2D, count, out);
		}

		void AttachColourTexture(uint32_t id, uint32_t samples, GLenum format, uint32_t width, uint32_t height, uint32_t unit)
		{
			// Create & Attach Colour Target
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + unit, GL_TEXTURE_2D, id, 0);
		}

		void AttachDepthTexture(uint32_t id, uint32_t samples, GLenum format, GLenum attachment, uint32_t width, uint32_t height)
		{
			// Create & Attach Depth Target
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, nullptr);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, id, 0);
		}
	}

	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferCreateInfo& createInfo)
	{
		return std::make_shared<Framebuffer>(createInfo);
	}

	Framebuffer::Framebuffer(FramebufferCreateInfo createInfo)
		: m_CreateInfo(createInfo)
	{
		for (auto format : createInfo.Attachments.TextureFormats)
		{
			if (format.Format == FramebufferTextureFormat::RGBA8)
				m_ColourAttachmentFormats.emplace_back(format.Format);
			else if (format.Format == FramebufferTextureFormat::DEPTH24_STENCIL8)
				m_DepthAttachmentFormat = format.Format;
		}

		if (createInfo.Width == 0 || createInfo.Height == 0)
		{
			auto [x, y] = Window::Get().GetSize();
			Resize(x, y, true);
		}
		else
			Resize(createInfo.Width, createInfo.Height, true);
	}

	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_ID);
		glDeleteTextures((uint32_t)m_ColourAttachments.size(), m_ColourAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	const FramebufferCreateInfo& Framebuffer::GetInfo() const
	{
		return m_CreateInfo;
	}

	uint32_t Framebuffer::GetColourAttachment(uint32_t index) const
	{
		_ASSERT(index < m_ColourAttachments.size());

		return m_ColourAttachments[index];
	}

	void Framebuffer::Bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);
		glViewport(0, 0, m_CreateInfo.Width, m_CreateInfo.Height);
	}

	void Framebuffer::Unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::Resize(const glm::vec2& size, bool forceCreate)
	{
		Resize((uint32_t)size.x, (uint32_t)size.y, forceCreate);
	}

	void Framebuffer::Resize(uint32_t width, uint32_t height, bool forceCreate)
	{
		if ((!forceCreate && width == m_CreateInfo.Width && height == m_CreateInfo.Height) || (width <= 0 || height <= 0))
			return;

		m_CreateInfo.Width = width;
		m_CreateInfo.Height = height;

		// Clear/delete current frame buffer and it's attachments when this function is called again
		if (m_ID)
		{
			glDeleteFramebuffers(1, &m_ID);
			glDeleteTextures((uint32_t)m_ColourAttachments.size(), m_ColourAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColourAttachments.clear();
			m_DepthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_ID);

		if (m_ColourAttachmentFormats.size() > 0)
		{
			m_ColourAttachments.resize(m_ColourAttachmentFormats.size());
			Utilities::CreateTextures(m_ColourAttachments.data(), (uint32_t)m_ColourAttachments.size());

			for (uint32_t i = 0; i < m_ColourAttachments.size(); i++)
			{
				Utilities::BindTexture(m_ColourAttachments[i]);
				Utilities::AttachColourTexture(m_ColourAttachments[i], 0, GL_RGBA8, m_CreateInfo.Width, m_CreateInfo.Height, i);
			}
		}

		if (m_DepthAttachmentFormat != FramebufferTextureFormat::None)
		{
			Utilities::CreateTextures(&m_DepthAttachment);
			Utilities::BindTexture(m_DepthAttachment);
			Utilities::AttachDepthTexture(m_DepthAttachment, 0, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_CreateInfo.Width, m_CreateInfo.Height);
		}

		if (m_ColourAttachments.size() > 1)
		{
			// TODO: Assert here if too many colour attachments
			//		 (Figure out how many is too many...)

			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers((uint32_t)m_ColourAttachments.size(), buffers);
		}
		else if (m_ColourAttachments.empty())
			glDrawBuffer(GL_NONE);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			Logger::Error("Framebuffer failed to complete!");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Framebuffer::BindTexture(uint32_t index)
	{
		_ASSERT(index < m_ColourAttachments.size());

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_ColourAttachments[index]);
	}
}
#include "Texture.h"

#include <glad/gl.h>

namespace Talon
{
	std::shared_ptr<Texture2D> Texture2D::Create(const TextureCreateInfo& createInfo)
	{
		return std::make_shared<Texture2D>(createInfo);
	}

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		return std::make_shared<Texture2D>(filepath);
	}

	Texture2D::Texture2D(const TextureCreateInfo& createInfo)
		: m_Width(createInfo.Width), m_Height(createInfo.Height)
	{
		// The use of GL_TEXTURE_2D here kinda defeats the purpose of 'Create' over 'Gen'. Too bad!

		// Create and bind new texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);

		// Bind?
		if (createInfo.BindingUnit >= 0)
			Bind(createInfo.BindingUnit);

		// Specify texture storage formatting
		glTextureStorage2D(m_ID, 0, createInfo.InternalFormat, createInfo.Width, createInfo.Height);

		// Setup filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, createInfo.MinificationFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, createInfo.MagnificationFilter);

		// Setup wrapping modes
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, createInfo.WrapModeR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, createInfo.WrapModeS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, createInfo.WrapModeT);

		// Specify texture format and data to be written
		glTextureSubImage2D(m_ID, 0, 0, 0, createInfo.Width, createInfo.Height, createInfo.Format, createInfo.DataType, createInfo.PixelData);

		// Gen mips?
		if (createInfo.GenerateMipMaps)
			glGenerateMipmap(GL_TEXTURE_2D);
	}

	Texture2D::Texture2D(const std::string& filepath)
	{

	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture2D::Reload()
	{

	}

	void Texture2D::Bind(uint32_t unit)
	{
		glBindTextureUnit(unit, m_ID);
	}

	void Texture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
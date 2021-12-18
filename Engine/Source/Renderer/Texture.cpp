#include "Texture.h"
#include "Core/Logger.h"

#include <StbImage/stb_image.h>
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
		Reload(createInfo);
	}

	Texture2D::Texture2D(const std::string& filepath)
		: m_Filepath(filepath)
	{
		if (m_Filepath.empty())
		{
			Logger::Error("Failed to load texture: No filepath specified!");
			_ASSERT(false);
		}

		// Reset if handle was already created
		if (m_ID)
			glDeleteTextures(1, &m_ID);

		// Inverts the pixels of the image loaded to accomodate for OpenGL's top to bottom rendering
		stbi_set_flip_vertically_on_load(true);

		// Load in image
		int32_t width, height, channelCount;
		uint8_t* pixelData = stbi_load(m_Filepath.c_str(), &width, &height, &channelCount, 0);
		m_Width = width;
		m_Height = height;

		//uint32_t n = width * height * channelCount;
		//uint32_t i = 0;
		//while (i < n)
		//	Logger::Warn("(IT: {3}) R: {0}, G: {1}, B: {2}", pixelData[i++], pixelData[i++], pixelData[i++], i);

		if (pixelData)
		{
			// TODO: Pretty hard coded for now but this will change eventually
			TextureCreateInfo createInfo;
			createInfo.DataType = GL_UNSIGNED_BYTE;
			createInfo.GenerateMipMaps = true;
			createInfo.Width = width;
			createInfo.Height = height;
			createInfo.MinificationFilter = GL_LINEAR;
			createInfo.MagnificationFilter = GL_LINEAR;
			createInfo.PixelData = pixelData;
			createInfo.WrapModeR = GL_REPEAT;
			createInfo.WrapModeS = GL_REPEAT;
			createInfo.WrapModeT = GL_REPEAT;

			if (channelCount == 1)
			{
				createInfo.Format = GL_RED;
				createInfo.InternalFormat = GL_R8;
			}
			else if (channelCount == 2)
			{
				createInfo.Format = GL_RG;
				createInfo.InternalFormat = GL_RG8;
			}
			else if (channelCount == 3)
			{
				createInfo.Format = GL_RGB;
				createInfo.InternalFormat = GL_RGB8;
			}
			else if (channelCount == 4)
			{
				createInfo.Format = GL_RGBA;
				createInfo.InternalFormat = GL_RGBA8;
			}

			Reload(createInfo);
		}
		else
			Logger::Error("Failed to load texture: Invalid file!");

		// Release the memory of image currently loaded
		stbi_image_free(pixelData);
	}

	Texture2D::~Texture2D()
	{
		glDeleteTextures(1, &m_ID);
	}

	void Texture2D::Bind(uint32_t unit)
	{
		glBindTextureUnit(unit, m_ID);
	}

	void Texture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture2D::Reload(const TextureCreateInfo& createInfo)
	{
		// The use of GL_TEXTURE_2D here kinda defeats the purpose of 'Create' over 'Gen'. Too bad!

		// Create and bind new texture
		glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);

		// Bind?
		if (createInfo.BindingUnit >= 0)
			Bind(createInfo.BindingUnit);

		// Specify texture storage formatting
		glTextureStorage2D(m_ID, 1, createInfo.InternalFormat, createInfo.Width, createInfo.Height);

		// Setup filtering
		glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, createInfo.MinificationFilter);
		glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, createInfo.MagnificationFilter);

		// Setup wrapping modes
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_R, createInfo.WrapModeR);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, createInfo.WrapModeS);
		glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, createInfo.WrapModeT);

		// Specify texture format and data to be written
		glTextureSubImage2D(m_ID, 0, 0, 0, createInfo.Width, createInfo.Height, createInfo.Format, createInfo.DataType, createInfo.PixelData);

		// Gen mips?
		if (createInfo.GenerateMipMaps)
			glGenerateTextureMipmap(m_ID);
	}
}
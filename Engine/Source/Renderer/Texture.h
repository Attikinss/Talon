#pragma once
#include <memory>
#include <string>

namespace Talon
{
	struct TextureCreateInfo
	{
		// Specifies the number of colour components in the texture.
		uint32_t InternalFormat = 0;

		// The format of the pixel data.
		uint32_t Format = 0;

		// The data type of the pixel data.
		uint32_t DataType = 0;
		
		// The unit this texture will be bound to upon creation.
		// (Default = -1, anything less than 0 = no bind)
		int32_t BindingUnit = -1;

		uint32_t MinificationFilter = 0;
		uint32_t MagnificationFilter = 0;

		uint32_t Samples = 0;

		uint32_t WrapModeR = 0;
		uint32_t WrapModeS = 0;
		uint32_t WrapModeT = 0;

		bool GenerateMipMaps = false;

		// A pointer to optional pixel data in memory. If specified Width, Height and Depth is ignored during creation.
		void* PixelData = nullptr;

		// Specifying 0 (default value) will ignore width during creation. Also ignored if PixelData is specified.
		int32_t Width = 0;

		// Specifying 0 (default value) will ignore height during creation. Also ignored if PixelData is specified.
		// Note: Width must be assigned a value of 1+ if height is not 0.
		int32_t Height = 0;

		// Specifying 0 (default value) will ignore depth during creation. Also ignored if PixelData is specified.
		// Note: Width and height must be assigned a value of 1+ if depth is not 0.
		int32_t Depth = 0;
	};

	class Texture
	{
	public:
		Texture() = default;
		virtual ~Texture() = default;

		virtual void Bind(uint32_t unit = 0) = 0;
		virtual void Unbind() = 0;
		
		uint32_t GetID() const { return m_ID; }

	protected:
		uint32_t m_ID = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static std::shared_ptr<Texture2D> Create(const TextureCreateInfo& createInfo);
		static std::shared_ptr<Texture2D> Create(const std::string& filepath);

		Texture2D(const TextureCreateInfo& createInfo);
		Texture2D(const std::string& filepath);
		~Texture2D();

		void Bind(uint32_t unit = 0) override;
		void Unbind() override;

	private:
		void Reload(const TextureCreateInfo& createInfo);

	private:
		std::string m_Filepath;
		uint32_t m_Width = 0, m_Height = 0;
	};
}
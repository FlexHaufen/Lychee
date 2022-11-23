/**
 * @file OpenGLTexture.h
 * @author flaxhaufen
 * @brief 
 * @version 0.1
 * @date 2022-11-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"
#include "Lychee/Renderer/Texture.h"

// *** NAMESPACE ***
namespace Lychee {

	class OpenGLTexture2D : public Texture2D {
	public:
		OpenGLTexture2D(u32 width, u32 height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual u32 GetWidth() const override { return m_Width;  }
		virtual u32 GetHeight() const override { return m_Height; }
		virtual u32 GetRendererID() const override { return m_RendererID; }

		virtual const std::string& GetPath() const override { return m_Path; }
		
		virtual void SetData(void* data, u32 size) override;

		virtual void Bind(u32 slot = 0) const override;

		virtual bool IsLoaded() const override { return m_IsLoaded; }

		virtual bool operator==(const Texture& other) const override {
			return m_RendererID == other.GetRendererID();
		}
	private:
		std::string m_Path;
		bool m_IsLoaded = false;
		u32 m_Width, m_Height;
		u32 m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}
/**
 * @file OpenGLFramebuffer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

#include "Lychee/Renderer/Framebuffer.h"


// *** NAMESPACE ***
namespace Lychee {

	class OpenGLFramebuffer : public Framebuffer {
	public:
		OpenGLFramebuffer(const sFramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(u32 width, u32 height) override;
		virtual s32 ReadPixel(u32 attachmentIndex, s32 x, s32 y) override;

		virtual void ClearAttachment(u32 attachmentIndex, s32 value) override;

		virtual u32 GetColorAttachmentRendererID(u32 index = 0) const override { LY_CORE_ASSERT(index < m_ColorAttachments.size()); return m_ColorAttachments[index]; }

		virtual const sFramebufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		u32 m_RendererID = 0;
		sFramebufferSpecification m_Specification;

		std::vector<sFramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		sFramebufferTextureSpecification m_DepthAttachmentSpecification = eFramebufferTextureFormat::None;

		std::vector<u32> m_ColorAttachments;
		u32 m_DepthAttachment = 0;
	};

}
/**
 * @file Framebuffer.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-02-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

	enum class eFramebufferTextureFormat {
		None = 0,

		// Color
		RGBA8,
		RED_INTEGER,

		// Depth/stencil
		DEPTH24STENCIL8,

		// Defaults
		Depth = DEPTH24STENCIL8
	};

	struct sFramebufferTextureSpecification {
		sFramebufferTextureSpecification() = default;
		sFramebufferTextureSpecification(eFramebufferTextureFormat format)
			: TextureFormat(format) {}

		eFramebufferTextureFormat TextureFormat = eFramebufferTextureFormat::None;
	};

	struct sFramebufferAttachmentSpecification {
		sFramebufferAttachmentSpecification() = default;
		sFramebufferAttachmentSpecification(std::initializer_list<sFramebufferTextureSpecification> attachments)
			: Attachments(attachments) {}

		std::vector<sFramebufferTextureSpecification> Attachments;
	};

	struct sFramebufferSpecification {
		u32 Width = 0, Height = 0;
		sFramebufferAttachmentSpecification Attachments;
		u32 Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer {
	public:

		Framebuffer(const sFramebufferSpecification& spec);
		~Framebuffer();

		void Bind();
		void Unbind();

		void Invalidate();

		void Resize(u32 width, u32 height);
		s32 ReadPixel(u32 attachmentIndex, s32 x, s32 y);

		void ClearAttachment(u32 attachmentIndex, s32 value);

		u32 GetColorAttachmentRendererID(u32 index = 0) const { if (index >= m_ColorAttachments.size()) LY_CORE_ERROR("FrameBuffer: index >= color"); return m_ColorAttachments[index]; }

		const sFramebufferSpecification& GetSpecification() const { return m_Specification; }

	private:
		u32 m_RendererID = 0;
		sFramebufferSpecification m_Specification;

		std::vector<sFramebufferTextureSpecification> m_ColorAttachmentSpecifications;
		sFramebufferTextureSpecification m_DepthAttachmentSpecification = eFramebufferTextureFormat::None;

		std::vector<u32> m_ColorAttachments;
		u32 m_DepthAttachment = 0;
	};
}
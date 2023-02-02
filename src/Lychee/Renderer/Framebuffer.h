/**
 * @file Framebuffer.h
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
		virtual ~Framebuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(u32 width, u32 height) = 0;
		virtual s32 ReadPixel(u32 attachmentIndex, s32 x, s32 y) = 0;

		virtual void ClearAttachment(u32 attachmentIndex, s32 value) = 0;

		virtual u32 GetColorAttachmentRendererID(u32 index = 0) const = 0;

		virtual const sFramebufferSpecification& GetSpecification() const = 0;

		static Ref<Framebuffer> Create(const sFramebufferSpecification& spec);
	};
}
/**
 * @file ContentBrowserPanel.h
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include <Lychee/lypch.h>
#include <Lychee/Lychee.h>

// *** DEFINES ***

// *** NAMESPACE ***
namespace Lychee {

    class ContentBrowserPanel {
	public:
		ContentBrowserPanel() = default;
		ContentBrowserPanel(const Ref<Scene>& scene) { SetContext(scene); }

		void SetContext(const Ref<Scene>& scene) { m_Context = scene; }

		void OnImGuiRender();

	private:
		void DrawEntityNode(Entity& entity);
		void DrawComponents(Entity& entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext = { } ;
	};

}
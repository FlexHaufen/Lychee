/**
 * @file ContentBrowserPanel.cpp
 * @author flexhaufen
 * @brief 
 * @version 0.1
 * @date 2024-01-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// *** INCLUDE ***
#include "LycheeApp/src/Panels/ContentBrowserPanel.h"

// *** DEFINES ***


// *** NAMESPACE ***
namespace Lychee {

    void ContentBrowserPanel::OnImGuiRender() {
		ImGui::Begin("Entity Browser Panel");


		if (m_Context) {
            ImGui::Text("Entities:");
            static UUID currentEntity;
            if (ImGui::BeginListBox("##entity_listBox", ImVec2(-FLT_MIN, 0))) {
                m_Context->GetRegistry().view<Component::Tag>().each([&](auto entityID, auto& tag) {
                    Entity entity(entityID, m_Context.get());

                    const b8 is_selected = (currentEntity == entity.GetUUID());
                    if (ImGui::Selectable(entity.GetTag().c_str(), is_selected)) {
                        currentEntity = entity.GetUUID();
                    }

                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected) {
                        ImGui::SetItemDefaultFocus();
                        m_SelectionContext = entity;
                        //AC_CORE_TRACE("Selected: {0}", entity.GetTag());
                    }   
                });
                ImGui::EndListBox();
            }
			
            if (ImGui::Button("Add Entity")) {
                m_Context->CreateEntity();
            }
            ImGui::SameLine();
            if (ImGui::Button("Remove Entity")) {
                m_Context->DestroyEntity(m_SelectionContext);
                m_SelectionContext = {};
            }
		}
		ImGui::End();
    }
}
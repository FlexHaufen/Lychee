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
		ImGui::Begin("Content Browser");

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
            if (ImGui::Button("Remove Entity") && m_SelectionContext) {
                m_Context->DestroyEntity(m_SelectionContext);
                m_SelectionContext = {};
            }
		}
		ImGui::End();
        
        ImGui::Begin("Properties");
        if (m_SelectionContext) {


            // Simple selection popup (if you want to show the current selection inside the Button itself,
            // you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
            s8 selectedComponent = -1;
            if (ImGui::Button("Add Component")) {
                ImGui::OpenPopup("popup_Components");
            }
            ImGui::SameLine();
            ImGui::TextUnformatted(selectedComponent == -1 ? "" : Component::availableComponents[selectedComponent]);
            if (ImGui::BeginPopup("popup_Components")) {
                ImGui::SeparatorText("Components");
                for (int i = 0; i < IM_ARRAYSIZE(Component::availableComponents); i++) {
                    if (ImGui::Selectable(Component::availableComponents[i])) {
                        selectedComponent = i;
                    
                        switch(selectedComponent) {
                            case 0:
                                if (!m_SelectionContext.HasComponent<Component::RectShape>())
                                m_SelectionContext.AddComponent<Component::RectShape>();
                                break;
                            default:
                                LY_WARN("Componet was selected but could not be added");
                                break;
                        }
                    }
                }
                ImGui::EndPopup();
            }

            ImGui::SeparatorText("Components");

            DrawComponents(m_SelectionContext);
        }
        else {
            ImGui::Text("No entity selected");
        }
        ImGui::End();
    }


    void ContentBrowserPanel::DrawComponents(Entity& entity) {
        if (entity.HasComponent<Component::Tag>() && ImGui::CollapsingHeader("Tag")) {
            auto &tag = entity.GetComponent<Component::Tag>().tag;
            auto &uuid = entity.GetComponent<Component::Tag>().uuid;         

            char buffer[256];
            strcpy_s(buffer, tag.c_str());

            // InputText for renaming
            ImGui::Text("Tag:");
            ImGui::SameLine();
            if (ImGui::InputText("##Tag_NameFiled: ", buffer, sizeof(buffer), ImGuiInputTextFlags_EnterReturnsTrue)) {
                tag = buffer;
            }

            // TODO (flex): Use LableText instead
            ImGui::Text("UUID: ");
            ImGui::SameLine();
            ImGui::TextColored(Conv::sfColor_to_ImColor(LY_COLOR_LIME), std::to_string(uuid).c_str());

            ImGui::Text("Index: ");
            ImGui::SameLine();
            ImGui::TextColored(Conv::sfColor_to_ImColor(LY_COLOR_LIME), std::to_string((u32)entity).c_str());
        }

        if (entity.HasComponent<Component::Transform>() && ImGui::CollapsingHeader("Transform")) {
            auto &transform = entity.GetComponent<Component::Transform>();

            ImGui::SliderInt("render layer", (s32*)&transform.renderLayer, 0, 9);

            static f32 f1[2] = {transform.pos.x, transform.pos.y};
            ImGui::InputFloat2("pos", f1);
            transform.pos = {f1[0], f1[1]};

            static f32 f2[2] = {transform.scale.x, transform.scale.y};
            ImGui::InputFloat2("Scale", f2);
            transform.scale = {f2[0], f2[1]};

            ImGui::InputFloat("Rotation", &transform.rotation);
        }

        if (entity.HasComponent<Component::RectShape>() && ImGui::CollapsingHeader("RectShape")) {
            auto &rectShape = entity.GetComponent<Component::RectShape>();

            static f32 f1[2] = {rectShape.size.x, rectShape.size.y};
            ImGui::InputFloat2("size", f1);
            rectShape.size = {f1[0], f1[1]};

            static ImVec4 color = Conv::sfColor_to_ImColor(rectShape.color);
            static f32 f2[4] = {color.x, color.y, color.z, color.w};
            ImGui::ColorEdit4("color", f2);
            rectShape.color = Conv::ImColor_to_sfColor(ImVec4(f2[0], f2[1], f2[2], f2[3]));
        }
    }
}
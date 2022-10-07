/**
 * @file SettingsPanel.cpp
 * @author flexhaufen
 * @brief Settings Panel
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//*** INCLUDES ***
#include <Lychee/lypch.h>
#include "SettingsPanel.h"


//*** DEFINES ***
#define LY_SETTINGS_PANEL_TAB_SIZE  ImVec2(75, 25)

//*** NAMESPACE ***
namespace Lychee {

        SettingsPanel::SettingsPanel() {
            p_open = false;
        }


        void SettingsPanel::OnImGuiRender(bool *p_open) {
            if (!ImGui::Begin("Settings", p_open, ImGuiWindowFlags_AlwaysAutoResize)) {
                ImGui::End();
                return;
            }

            static u8 currentTab;
            

            // Settings Tabs
            // TODO: render tabs inside of "if"?
            {            
                ImGui::SameLine();
                if (ImGui::Button("General", LY_SETTINGS_PANEL_TAB_SIZE)) {
                    currentTab = 0;
                }
                ImGui::SameLine();

                if (ImGui::Button("View", LY_SETTINGS_PANEL_TAB_SIZE)) {
                    currentTab = 1;
                }
                ImGui::SameLine();
                if (ImGui::Button("Simulation", LY_SETTINGS_PANEL_TAB_SIZE)) {
                    currentTab = 2;
                }
                ImGui::SameLine();
                if (ImGui::Button("Misc", LY_SETTINGS_PANEL_TAB_SIZE)) {
                    currentTab = 3;
                }
            }

            // NOTE: Just some demo to see if it's working
            static bool enabled = true;
            ImGui::MenuItem("Enabled", "", &enabled);
            ImGui::BeginChild("child", ImVec2(0, 60), true);
            for (int i = 0; i < 10; i++)
                ImGui::Text("Scrolling Text %d", i);
            ImGui::EndChild();
            static float f = 0.5f;
            static int n = 0;
            ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
            ImGui::InputFloat("Input", &f, 0.1f);
            ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");            
            ImGui::End();
        }

}
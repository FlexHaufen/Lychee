/**
 * @file CalculatorPanel.cpp
 * @author flexhaufen
 * @brief Content Browser
 * @version 0.1
 * @date 2022-09-28
 * 
 * @copyright Copyright (c) 2022
 * 
 */

//*** INCLUDES ***
#include <Lychee/lypch.h>
#include "CalculatorPanel.h"
#include "solve.h"

#include <imgui.h>

//*** DEFINES ***
//#define LY_TRACE_CALC

//*** NAMESPACE ***
namespace Lychee {

	 CalculatorPanel::CalculatorPanel() {
	
	}

	void CalculatorPanel::OnImGuiRender(bool* p_open) {
		if (!ImGui::Begin("Calculator", p_open, ImGuiWindowFlags_AlwaysAutoResize)) {
			ImGui::End();
			return;
        }
		
		static c8 str[128] = "";		// input as c string
		static f32 result_f=0;			// output as f32
		static c8 result_c[128] = "";	// output as c string

		ImGui::InputTextWithHint("##label", "input text", str, IM_ARRAYSIZE(str));
		if (ImGui::IsItemEdited()) {
			#ifdef LY_TRACE_CALC
				LY_TRACE("INPUT {0}", str);
				LY_TRACE("RES {0}", result_f);
			#endif
			result_f = CalcSolve(str, 0, std::strlen(str), &result_f);
		}
		sprintf(result_c, "%f", result_f);
		
	
		ImGui::NewLine();
		ImGui::Text("Result:");
		ImGui::SameLine();
		if (ImGui::Button(result_c)) {
            ImGui::LogToClipboard();
            ImGui::LogText(result_c);
			ImGui::LogFinish();
        }
		if (ImGui::IsItemHovered()) {
			ImGui::SetTooltip("Copy to clipboard");
		}

		ImGui::End();
	}

}

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

#include <imgui.h>

//*** DEFINES ***

//*** NAMESPACE ***
namespace Lychee {

	CalculatorPanel::CalculatorPanel(void) {
	}

	void CalculatorPanel::OnImGuiRender(void) {
		ImGui::Begin("Calculator");

		static float padding = 16.0f;
		static float thumbnailSize = 128.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);


		ImGui::Columns(1);

		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		// TODO: status bar
		ImGui::End();
	}

}

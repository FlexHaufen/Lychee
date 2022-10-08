/**
 * @file SettingsPanel.h
 * @author flexhaufen
 * @brief Settings Panel
 * @version 0.1
 * @date 2022-10-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

//*** INCLUDE ***


//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {

    class SettingsPanel {
    
    public:
        SettingsPanel();

        void OnImGuiRender(bool* p_open);

    public:
        bool p_open;

    private:

    };
}
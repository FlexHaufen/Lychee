/**
 * @file Application.cpp
 * @author flexhaufen
 * @brief Application Lyche
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// *** INCLUDES ***
#include "Lychee/Application.h"

// *** DEFINE ***
#define LY_RUNNING true

// *** NAMESPACE ***
namespace Lychee {
    
    Application::Application() {
        Lychee::Log::Init();
        LY_INFO("Init App");
    }

    Application::~Application() {
        LY_INFO("Quitting App");
    }

    void Application::Run() {
        while (LY_RUNNING) {
            
        }   
    }
}
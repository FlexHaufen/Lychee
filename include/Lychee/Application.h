/**
 * @file Application.h
 * @author flexhaufen
 * @brief Application Lychee
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

//*** INCLUDES ***
#include "Lychee/Core/Core.h"

//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {

    /**
     * @brief Application class
     * 
     */
    class Application {
    public:
        /**
         * @brief Construct a new Application object
         * 
         */
        Application();

        /**
         * @brief Destroy the Application object
         * 
         */
        virtual ~Application();

        void Run();
    };
}
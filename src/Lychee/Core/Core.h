/**
 * @file Core.h
 * @author flexhaufen
 * @brief core of the engine
 * @version 0.1
 * @date 2022-09-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
# pragma once

// *** INCLUDES ***

// ** Events **
#include "Lychee/Events/KeyEvent.h"

// ** Window **
//*** DEFINES ***


//*** NAMESPACE ***
namespace Lychee {

    /**
     * @brief Core
     * 
     */
    class Core {

        public:

            /**
             * @brief Construct a new Core object
             * 
             */
            Core();

            /**
             * @brief Destroy the Core object
             * 
             */
            ~Core();

            /**
             * @brief Running loop
             * 
             */
            void Run();

        private:

        // *** MEMBERS ***
        //Scope<Window> m_Window;
    };
}
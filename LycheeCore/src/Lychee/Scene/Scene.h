/**
 * @file Scene.cpp
 * @author flexhaufen
 * @brief Sceen Class
 * @version 0.1
 * @date 2024-01-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#pragma once

// *** INCLUDES ***
#include "Lychee/lypch.h"
//#include "Lychee/Scene/Entity/Entity.h"
#include "Lychee/Scene/Entity/Components.h"
#include "Lychee/Core/Time/DeltaTime.h"
#include "Lychee/Renderer/Renderer.h"
#include "Lychee/Renderer/Camera.h"
#include "Lychee/Events/Event.h"

//*** DEFINES ***
#define LY_MAX_RENDERLAYERS     10

//*** NAMESPACE ***
namespace Lychee {
    class Entity;

    /**
     * @brief World Scene
     * 
     */
    class Scene {

    public:
        Scene();
        ~Scene();

        static Ref<Scene> Copy(Ref<Scene> other);

        /**
         * @brief Create a Entity object
         * 
         * @param tag       tag (name) of entity
         * @return Entity 
         */
        Entity CreateEntity(const std::string& name = "entity");

        /**
         * @brief Create a Entity with a uuid
         * 
         * @param uuid      given uuid
         * @param name      given name
         * @return Entity   created entity
         */
        Entity CreateEntityWithUUID(UUID uuid, const std::string& name = "entity");

        /**
         * @brief Destroys given entity
         * 
         * @param entity 
         */
        void DestroyEntity(Entity &entity);


        // ** Scene Handling **

		void OnViewportResize(uint32_t width, uint32_t height) { m_Renderer.OnWindowResize(width, height); m_Camera.UpdateViewPort(width, height); };

        void OnRuntimeStart();

        void OnRuntimeStop();

        void OnRuntimeUpdate(DeltaTime dt);

        void OnEditorUpdate(DeltaTime dt);

		entt::registry& GetRegistry() { return m_Registry; }

    private:

        // ** Members **
        entt::registry      m_Registry;             // entt Registry

        bool m_IsRuntimeRunning = false;            // true if runtime is running

        Renderer m_Renderer;
        Camera m_Camera;

        friend class Entity;                        // Entity class
    };
}
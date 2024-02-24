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
#include "Lychee/Scene/Camera/Camera.h"
#include "Lychee/Core/Time/DeltaTime.h"

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

        void OnRuntimeStart();

        void OnRuntimeStop();

        void OnRuntimeUpdate(DeltaTime dt);


        /**
         * @brief Update function
         * 
         * @param dt delta time
         */
        void OnUpdate(DeltaTime dt);

        //void OnRender(Camera& editorCamera);

		entt::registry& GetRegistry() { return m_Registry; }

    private:

        // ** Members **
        sf::RenderTexture   m_RenderTexture;        // sf::RenderTexture
        entt::registry      m_Registry;             // entt Registry

        b8 m_IsRuntimeRunning = false;              // true if runtime is running

        friend class Entity;                        // Entity class
    };
}
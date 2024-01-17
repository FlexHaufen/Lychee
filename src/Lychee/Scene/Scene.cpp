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

// *** INCLUDES ***
#include "Lychee/Scene/Scene.h"
#include "Lychee/Scene/Entity/Entity.h"


// *** DEFINE ***

// *** NAMESPACE ***
namespace Lychee {

    Scene::Scene(){
        LY_CORE_INFO("Initializing Scene");
		m_RenderTexture.create(LY_WINDOW_SIZE_X, LY_WINDOW_SIZE_Y);
    }

    Scene::~Scene() {
        LY_CORE_INFO("Terminating Scene");
    }

    Entity Scene::CreateEntity(const std::string& name) {
        return CreateEntityWithUUID(UUID(), name);
	}

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name) {
        Entity entity = { m_Registry.create(), this };
		auto& tag = entity.AddComponent<Component::Tag>();
        tag.uuid = uuid;
		tag.tag = name;

        // m_EntityMap[uuid] = entity;

		return entity;
    }

    void Scene::DestroyEntity(Entity &entity) {

        // Destory Body from registry
        m_Registry.destroy(entity);
    }



    void Scene::OnUpdate(DeltaTime dt) {
        
    }


    sf::RenderTexture& Scene::OnRender(Camera& editorCamera) {
		m_RenderTexture.clear(LY_SCENE_CLEAR_BACKGROUND);

        // ------ RENDER HERE -------

		sf::RectangleShape rs;
		rs.setSize({50, 50});
		rs.setFillColor({250, 100, 50, 255});

		m_RenderTexture.draw(rs);

		// --------------------------

        m_RenderTexture.setView(editorCamera.GetView());
		m_RenderTexture.display();


        return m_RenderTexture;
    }
}
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
        LY_CORE_INFO("Scene: Initializing");
		m_RenderTexture.create(LY_WINDOW_SIZE_X, LY_WINDOW_SIZE_Y);
    }

    Scene::~Scene() {
        LY_CORE_INFO("Scene: Terminating");
    }

    Entity Scene::CreateEntity(const std::string& name) {
        return CreateEntityWithUUID(UUID(), name);
	}

    Entity Scene::CreateEntityWithUUID(UUID uuid, const std::string& name) {
        Entity entity = { m_Registry.create(), this };
		auto& tag = entity.AddComponent<Component::Tag>();
        tag.uuid = uuid;
		tag.tag = name;

		auto& transform = entity.AddComponent<Component::Transform>();

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
		m_RenderTexture.clear(LY_SCENE_CLEAR_COLOR);

        // ------ RENDER HERE -------
        
        // Render Transform origin
        m_Registry.view<Component::Tag, Component::Transform>().each([&]( auto e, auto &tag, auto &transform) {
            //if (transform.renderLayer != i) {
            //    return;
            //}

            // Dont draw if not in view of main camera
            Entity entity = {e, this};
            sf::CircleShape c;
            c.setRadius(2);
            c.setFillColor(sf::Color::Red);
            c.setPosition(sf::Vector2f(transform.pos.x - 2, transform.pos.y - 2));
            m_RenderTexture.draw(c);
        });

        m_Registry.view<Component::RectShape, Component::Transform>().each([&](auto e, auto &rectShape, auto &transform) {
            Entity entity = {e, this};
            sf::RectangleShape rs(sf::Vector2f(rectShape.size.x, rectShape.size.y));
            rs.setPosition(transform.pos.x, transform.pos.y);
            rs.setFillColor(rectShape.color);
            m_RenderTexture.draw(rs);
        });

		// --------------------------

        m_RenderTexture.setView(editorCamera.GetView());
		m_RenderTexture.display();


        return m_RenderTexture;
    }
}
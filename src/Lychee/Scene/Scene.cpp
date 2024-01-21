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

    // *** Scene Handling ***


    void Scene::OnRuntimeStart() {
        m_IsRuntimeRunning = true;


        // Start physics
        // TODO (flex): Serialize gravity
        m_PhysicsWorld = new b2World(b2Vec2(0.0f, -9.8f));
    
        m_Registry.view<Component::RigidBody, Component::Transform>().each([&](auto e, auto& rigidBody, auto& transform) {
            Entity entity = {e, this};

            rigidBody.bodyDef.position = b2Vec2(transform.pos.x / LY_DEG_PER_RAD, transform.pos.y / LY_DEG_PER_RAD);
            rigidBody.bodyDef.angle = transform.rotation / LY_PPM;

            rigidBody.runtimeBody= m_PhysicsWorld->CreateBody(&rigidBody.bodyDef);
            rigidBody.runtimeBody->SetFixedRotation(true);

            // Add collider
            if (entity.HasComponent<Component::Collider>()) {
				auto& collider = entity.GetComponent<Component::Collider>();
                collider.fixture.shape = &collider.shape;
				rigidBody.runtimeBody->CreateFixture(&collider.fixture);
			}
        });
    }

    void Scene::OnRuntimeStop() {
        m_IsRuntimeRunning = false;
    

        // Stop physics
        delete m_PhysicsWorld;
        m_PhysicsWorld = nullptr;
    }



    void Scene::OnRuntimeUpdate(DeltaTime dt) {
        const int32_t velocityIterations = 6;
        const int32_t positionIterations = 2;
        m_PhysicsWorld->Step(dt, velocityIterations, positionIterations);

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
            sf::CircleShape c;
            c.setRadius(2);
            c.setFillColor(sf::Color::Red);
            c.setPosition(sf::Vector2f(transform.pos.x - 2, transform.pos.y - 2));
            m_RenderTexture.draw(c);
        });

        m_Registry.view<Component::RectShape, Component::Transform>().each([&](auto e, auto &rectShape, auto &transform) {
            sf::RectangleShape rs(rectShape.size);
            rs.setPosition(transform.pos);
            rs.setFillColor(rectShape.color);
            m_RenderTexture.draw(rs);
        });

		// --------------------------

        m_RenderTexture.setView(editorCamera.GetView());
		m_RenderTexture.display();


        return m_RenderTexture;
    }
}
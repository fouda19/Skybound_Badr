#pragma once

#include "../ecs/entity.hpp"
#include "camera.hpp"
#include "mesh-renderer.hpp"
#include "light.hpp"
#include "free-camera-controller.hpp"
#include "movement.hpp"
#include "enemy.hpp"
#include <iostream>

namespace our {

    // Given a json object, this function picks and creates a component in the given entity
    // based on the "type" specified in the json object which is later deserialized from the rest of the json object
    inline void deserializeComponent(const nlohmann::json& data, Entity* entity){
        std::string type = data.value("type", "");
        Component* component = nullptr;
        //TODO: (Req 8) Add an option to deserialize a "MeshRendererComponent" to the following if-else statement
        if(type == CameraComponent::getID()){
            component = entity->addComponent<CameraComponent>();
        } else if (type == FreeCameraControllerComponent::getID()) {
            component = entity->addComponent<FreeCameraControllerComponent>();
        } else if (type == MovementComponent::getID()) {
            component = entity->addComponent<MovementComponent>();
        }
        else if (type == MeshRendererComponent::getID()) {
            std::cout << "mesh Component Added" << std::endl;

            component = entity->addComponent<MeshRendererComponent>();
        }
        else if (type == EnemyComponent::getID()) {
            std::cout << "enemy Component Added" << std::endl;

            component = entity->addComponent<EnemyComponent>();

        }
        else if(type == LightComponent::getID()){
            std::cout << "Light Component Added" << std::endl;
            component = entity->addComponent<LightComponent>();
            std::cout << "Type: " << type << std::endl;
            std::cout << "Entity: " << entity << std::endl;
            std::cout << "Component: " << component << std::endl;
        }
        if(component) component->deserialize(data);
    }

}
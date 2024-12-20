#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    // This component denotes that any renderer should draw the scene relative to this camera.
    // We do not define the eye, center or up here since they can be extracted from the entity local to world matrix
    class EnemyComponent : public Component {
    public:
        bool isMovingRight = true;
        bool isMovingLeft = false;
        glm::vec3 position = {0, 0, 0}; // Each frame, the entity should move as follows: position += linearVelocity * deltaTime 

        // The ID of this component type is "Movement"
        static std::string getID() { return "Enemy"; }

        // Reads linearVelocity & angularVelocity from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}
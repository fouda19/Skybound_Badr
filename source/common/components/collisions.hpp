#pragma once

#include "../ecs/component.hpp"
#include <glm/glm.hpp>

namespace our
{

    // This component denotes that the MovementSystem will move the owning entity by a certain linear and angular velocity.
    // This component is added as a simple example for how use the ECS framework to implement logic.
    // For more information, see "common/systems/movement.hpp"
    // For a more complex example of how to use the ECS framework, see "free-camera-controller.hpp"
    class CollisionComponent : public Component
    {
    public:
        glm::vec3 startBoundingBox, endBoundingBox;

        // The ID of this component type is "Movement"
        static std::string getID() { return "Collision"; }

        // Reads linearVelocity & angularVelocity from the given json object
        void deserialize(const nlohmann::json &data) override;
        bool isColliding(glm::vec3 startBoundingBoxA, glm::vec3 endBoundingBoxA, glm::vec3 startBoundingBoxB, glm::vec3 endBoundingBoxB)
        {
            if (startBoundingBoxA.x <= endBoundingBoxB.x &&
                endBoundingBoxA.x >= startBoundingBoxB.x &&
                startBoundingBoxA.y <= endBoundingBoxB.y &&
                endBoundingBoxA.y >= startBoundingBoxB.y &&
                startBoundingBoxA.z <= endBoundingBoxB.z &&
                endBoundingBoxA.z >= startBoundingBoxB.z)
            {
                return true;
            }
            return false;
        }
    };

}

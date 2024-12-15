#pragma once

#include "../ecs/world.hpp"
#include "../components/enemy.hpp"
#include "../components/movement.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic. 
    // For more information, see "common/components/movement.hpp"
    class EnemySystem {
    public:

        // This should be called every frame to update all entities containing a MovementComponent. 
        void update(World* world, float deltaTime) {
            // For each entity in the world
            for(auto entity : world->getEntities()){
                // Get the movement component if it exists
                EnemyComponent* enemy = entity->getComponent<EnemyComponent>();
                // MovementComponent* movement = entity->getComponent<MovementComponent>();
                // If the movement component exists
                if(enemy){
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    if(entity->localTransform.position.x - enemy->position.x > 5 )
                    {
                        enemy->isMovingLeft = true;
                        enemy->isMovingRight = false;
                    }
                    else if(entity->localTransform.position.x - enemy->position.x < -5 ) 
                    {
                        enemy->isMovingRight = true;
                        enemy->isMovingLeft = false;
                    }
                    if(enemy->isMovingRight)
                    {
                        entity->localTransform.position.x += static_cast<decltype(entity->localTransform.position.x)>(2.0 * deltaTime);
                    }
                    else {
                        entity->localTransform.position.x -= static_cast<decltype(entity->localTransform.position.x)>(2.0 * deltaTime);

                    }

                }
            }
        }

    };

}

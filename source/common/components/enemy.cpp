#include "enemy.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads camera parameters from the given json object
    void EnemyComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        position = data.value("position", position);
        
    }
    
}
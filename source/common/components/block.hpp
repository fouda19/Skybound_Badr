#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>
#include <json/json.hpp>
namespace our
{
    class BlockComponent : public Component
    {
    public:
        int speed;
        static std::string getID() { return "Block"; }

        void deserialize(const nlohmann::json &data) override;
    };

}
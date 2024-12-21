#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>
#include <json/json.hpp>
namespace our
{
    class CoinComponent : public Component
    {
    public:
        int speed;
        static std::string getID() { return "Coin"; }

        void deserialize(const nlohmann::json &data) override;
    };

}
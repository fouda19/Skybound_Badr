#include "block.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"
// #include <json/json.hpp>
namespace our
{

    void BlockComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;
        }
}
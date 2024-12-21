#pragma once

#include <unordered_set>
#include "entity.hpp"

namespace our {

    struct Light {
        int type; // The type of the light (DIRECTIONAL or SPOT or POINT)
        glm::vec3 position; // The position of the light in the world space
        glm::vec3 direction; // The direction of the light in the world space
        glm::vec3 color; // The color of the light
        glm::vec3 attenuation; // The attenuation of the light
        glm::vec2 cone_angles; // The cone angles of the light
    };
    // This class holds a set of entities
    class World {
        std::unordered_set<Entity*> entities; // These are the entities held by this world
        std::unordered_set<Entity*> markedForRemoval; // These are the entities that are awaiting to be deleted
                                                      // when deleteMarkedEntities is called
    public:
        Light lights[16]; // An array of lights that will be used to store the lights in the world
        int light_count = 0; // The number of lights in the world

        World() = default;

        // This will deserialize a json array of entities and add the new entities to the current world
        // If parent pointer is not null, the new entities will be have their parent set to that given pointer
        // If any of the entities has children, this function will be called recursively for these children
        void deserialize(const nlohmann::json& data, Entity* parent = nullptr);

        // This adds an entity to the entities set and returns a pointer to that entity
        // WARNING The entity is owned by this world so don't use "delete" to delete it, instead, call "markForRemoval"
        // to put it in the "markedForRemoval" set. The elements in the "markedForRemoval" set will be removed and
        // deleted when "deleteMarkedEntities" is called.
        Entity* add() {
            //TODO: (Req 8) Create a new entity, set its world member variable to this,
            // and don't forget to insert it in the suitable container.
            Entity* entity = new Entity();
            entity->world = this;
            entities.insert(entity);
            return entity;
        }

        // This returns and immutable reference to the set of all entites in the world.
        const std::unordered_set<Entity*>& getEntities() {
            return entities;
        }

        // This marks an entity for removal by adding it to the "markedForRemoval" set.
        // The elements in the "markedForRemoval" set will be removed and deleted when "deleteMarkedEntities" is called.
        void markForRemoval(Entity* entity){
            //TODO: (Req 8) If the entity is in this world, add it to the "markedForRemoval" set.
            for(Entity* e : entities){
                if(e == entity){
                    markedForRemoval.insert(entity);
                    return;
                }
            }
        }

        // This removes the elements in "markedForRemoval" from the "entities" set.
        // Then each of these elements are deleted.
        void deleteMarkedEntities(){
            //TODO: (Req 8) Remove and delete all the entities that have been marked for removal
             for(Entity* entity : markedForRemoval){
                entities.erase(entity);
                delete entity;
            }
            markedForRemoval.clear();
        }

        //This deletes all entities in the world
        void clear(){
            //TODO: (Req 8) Delete all the entites and make sure that the containers are empty
            for(Entity* entity : entities){
                delete entity;
            }
            entities.clear();
            markedForRemoval.clear();
        }

        //Since the world owns all of its entities, they should be deleted alongside it.
        ~World(){
            clear();
        }

        // The world should not be copyable
        World(const World&) = delete;
        World &operator=(World const &) = delete;
    };

}
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include <iostream>

#include "entity.h"

class Player;
class Projectile;

namespace cb::Entities
{
    class Block : public Entity
    {
        public:
            // Constructors
            Block(float x, float y, float width, float height);

            // Game loop
            void draw(sf::RenderTarget &target, const Camera &camera);
            void update(float dt);

            // Collision managers
            void collide(const Entity* entity);
            void collidePlayer(const Entity* player);
            void collideProjectile(const Entity* projectile);

            // Getters
            float getX() const;
            float getY() const;
            float getWidth() const;
            float getHeight() const;
            EntityTypes getType() const;

        private:
            // Graphics
            sf::RectangleShape representation;
            
            // Properties
            float x, y, width , height;
            int zIndex;
            bool collides;
            bool deleteFromScene;
            int health;

    };
}

#endif
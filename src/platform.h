#ifndef PLATFORM_H
#define PLATFORM_H

// #include "game_object.h"
#include "projectile.h"
#include "block.h"

namespace cb::Entities
{
    class Platform : public Block
    {
        public:
            // Constructors
            Platform(float x, float y, float width, float height);

            // Collision managers
            void collideProjectile(const Entity* projectile);
            void collide(const Entity* entity);

            // Game loop
            void draw(sf::RenderTarget &target, const Camera &camera);

            // Getters
            float getX();
            float getWidth();
            bool requestsDeletion() const;

        private:
            // Graphics
            sf::RectangleShape representation;
            // Properties
            float x, y, width, height;
            int health, zIndex;
            bool collides, deleteFromScene;
    };
}

#endif

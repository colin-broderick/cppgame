#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "entity.h"
#include "camera.h"

namespace cb::Entities
{
    class Projectile : public Entity
    {
        public:
            // Constructors
            Projectile(float x, float y, float dx, float dy);

            // Game loop
            void draw(sf::RenderTarget &target, const Camera &camera);
            void update(float dt);

            // Collision managers
            void collide(const Entity* entity);
            void collidePlayer(const Entity* player);
            void collideBlock(const Entity* block);
            void collideProjectile(const Entity* projectile);

            // Getters
            EntityTypes getType() const;
            float getRadius() const;
            float getX() const;
            float getY() const;
            float getDx() const;
            float getDy() const;
            bool requestsDeletion() const;


        private:
            // Properties
            float x, y, dx, dy, radius, mass, lastX, lastY;
            int zIndex;
            bool deleteFromScene;

            // Graphics
            sf::CircleShape representation;
    };
}

#endif

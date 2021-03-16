#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "camera.h"
#include "entity.h"
#include "block.h"
#include "projectile.h"

namespace cb::Entities
{
    class Player : public Entity
    {
        public:
            // Constructors
            Player(float x, float y, float dx, float dy);

            // Game loop
            void draw(sf::RenderTarget &target, const cb::Entities::Camera &camera);
            void right();
            void left();
            void up();
            void down();
            void jump();
            void stopUp();
            void stopDown();
            void stopJump();
            void stopLeft();
            void stopRight();
            void meleeAttack();
            void keyDown(const sf::Event &event);
            void keyUp(const sf::Event &event);
            void mouseDown(const sf::Event &event);
            void update(float dt);

            // Collision managers
            void collide(const cb::Entities::Entity* entity);
            void collideBlock(const cb::Entities::Entity* block);
            void collideProjectile(const cb::Entities::Entity* projectile);

            // Getters
            float getX() const;
            float getY() const;
            float getWidth() const;
            float getHeight() const;
            float getFacing() const;
            float getVerticalCameraFactor() const;
            int getHealth() const;
            EntityTypes getType() const;

            // Setters
            void reduceHealth(int pain);

        private:
            // Graphics
            sf::RectangleShape representation;

            // Properties
            float x, y, width, height, lastX, lastY;
            float dx, lastDx;
            float dy, lastDy;
            int health;
            float dx2;
            float dy2;
            float dragCoefficientX;
            float dragCoefficientY;
            bool movingRight;
            bool movingLeft;
            bool jumping;
            bool lookingUp;
            bool lookingDown;
            float verticalCameraFactor;
            int zIndex;
            float facing;
    };
}

#endif

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum EntityTypes
{
    EntityType,
    BlockType,
    PlayerType,
    PlatformType,
    CameraType,
    ProjectileType
};

namespace cb::Entities
{
    class Camera;

    class Entity
    {   
        public:
            virtual void collide(const Entity* entity);
            virtual void draw(sf::RenderTarget &target, const cb::Entities::Camera &camera);
            virtual void update(float dt);
            virtual void keyDown(const sf::Event &event); 
            virtual void keyUp(const sf::Event &event);  
            virtual float getX() const;
            virtual float getY() const;
            virtual float getWidth() const;
            virtual float getHeight() const;  
            virtual bool collidesWith(const Entity &entiry) const;
            virtual EntityTypes getType() const;
            virtual float getRadius() const;
            virtual float getDx() const;
            virtual float getDy() const;
            virtual bool requestsDeletion() const;


    };
}

#endif

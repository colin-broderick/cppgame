#include <math.h>

#include "projectile.h"

// Constructors ===================================================================================

cb::Entities::Projectile::Projectile(float x, float y, float dx, float dy)
{
    this->x = x;
    this->y = y;
    this->dx = dx;
    this->dy = dy;
    this->radius = 3;
    this->mass = 1;
    this->zIndex = 0;
    this->deleteFromScene = false;

    representation.setOrigin(radius, radius);
    representation.setPosition(sf::Vector2f{x, y});
    representation.setRadius(this->radius);
    representation.setFillColor(sf::Color::Yellow);
}

// Game loop ======================================================================================

void cb::Entities::Projectile::draw(sf::RenderTarget &target, const cb::Entities::Camera &camera)
{
    // representation.setOrigin(x - camera.x, y - camera.y);
    representation.setPosition(x - camera.getX(), y - camera.getY());
    target.draw(representation);
}

void cb::Entities::Projectile::update(float dt)
{
    lastX = x;
    lastY = y;
    x = x + dx * dt;
    y = y + dy * dt;
}

// Collision managers =============================================================================

void cb::Entities::Projectile::collide(const cb::Entities::Entity* entity)
{
    switch (entity->getType())
    {
        case ProjectileType:
            collideProjectile(entity);
            break;
        case BlockType:
            collideBlock(entity);
            break;
        case PlayerType:
            collidePlayer(entity);
            break;
        default:
            break;
    }
}

void cb::Entities::Projectile::collidePlayer(const cb::Entities::Entity* player)
{
    this->deleteFromScene = true;
}

void cb::Entities::Projectile::collideBlock(const cb::Entities::Entity* block)
{
    if (lastY + radius < block->getY() || lastY - radius > block->getY() + block->getHeight())
    {
        y = lastY;
        dy = -dy;
    }
    else
    {
        x = lastX;
        dx = -dx;
    }
}

void cb::Entities::Projectile::collideProjectile(const cb::Entities::Entity* projectile)
{
    sf::Vector2f collisionVector{
        projectile->getX() - x,
        projectile->getY() - y
    };
    float distance = sqrt((projectile->getX()-x)*(projectile->getX()-x) + (projectile->getY()-y)*(projectile->getY()-y));
    sf::Vector2f collisionVectorNorm = collisionVector/distance;
    sf::Vector2f relativeVelocityVector{
        dx - projectile->getDx(),
        dy - projectile->getDy()
    };
    float speed = relativeVelocityVector.x*collisionVectorNorm.x + relativeVelocityVector.y*collisionVectorNorm.y;
    float impulse = speed;  // TODO Calculate impulse here.
    if (speed > 0)    
    {
        dx -= speed*collisionVectorNorm.x;
        dy -= speed*collisionVectorNorm.y;
    }
}

// Getters ========================================================================================

EntityTypes cb::Entities::Projectile::getType() const
{
    return ProjectileType;
}

float cb::Entities::Projectile::getRadius() const
{
    return radius;
}

float cb::Entities::Projectile::getX() const
{
    return x;
}

float cb::Entities::Projectile::getY() const
{
    return y;
}

float cb::Entities::Projectile::getDx() const
{
    return dx;
}

float cb::Entities::Projectile::getDy() const
{
    return dy;
}

bool cb::Entities::Projectile::requestsDeletion() const
{
    return deleteFromScene;
}

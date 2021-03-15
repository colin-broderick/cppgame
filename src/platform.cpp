#include "platform.h"
#include "camera.h"

// Constructors ===================================================================================

/** \brief Platform constructor.
 * \param x
 * \param y
 * \param width
 * \param height
 */
cb::Entities::Platform::Platform(float x, float y, float width, float height)
: Block(x, y, width, height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->zIndex = 0;
    this->collides = true;
    this->deleteFromScene = false;
    this->health = 100;
    this->representation.setPosition(sf::Vector2f{x, y});
    this->representation.setSize(sf::Vector2f{width, height});
    this->representation.setFillColor(sf::Color::Green);
}

// Collision managers ============================================================================

/** \brief Control how the block responds to collisions.
 * \param entity The object the block has collided with.
 */
void cb::Entities::Platform::collide(const Entity* entity)
{
    switch (entity->getType())
    {
    case ProjectileType:
        collideProjectile(entity);
        break;
    default:
        break;
    }
}

/** \brief Manage collisions with projectiles.
 * \param projectile The projectile the platform has collided with.
 */
void cb::Entities::Platform::collideProjectile(const cb::Entities::Entity* projectile)
{
    health -= 5;
    representation.setFillColor(sf::Color(0, 255, 0, sf::Uint8(health/100.0f*255)));
    if (health <= 0)
    {
        deleteFromScene = true;
    }
}

void cb::Entities::Platform::draw(sf::RenderTarget &target, const Camera &camera)
{
    representation.setPosition(x - camera.getX(), y - camera.getY());
    target.draw(representation);
}

bool cb::Entities::Platform::requestsDeletion() const
{
    return deleteFromScene;
}
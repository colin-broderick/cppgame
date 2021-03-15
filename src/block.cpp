#include "block.h"
#include "camera.h"

// Constructors ===================================================================================

/** \brief Block constructor.
 * \param x x position of top left corner of block.
 * \param y y position of top left corner of block.
 * \param width Width of block in pixels.
 * \param height Height of block in pixels.
 */
cb::Entities::Block::Block(float x, float y, float width, float height)
{
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
    this->zIndex = 0;
    this->collides = true;
    this->deleteFromScene = false;
    this->health = 100;
    this->representation.setPosition(sf::Vector2f{x, y});
    this->representation.setSize(sf::Vector2f{width, height});
    this->representation.setFillColor(sf::Color::Cyan);
}

// Game loop ======================================================================================

/** \brief Apply these changes to the block with each frame.
 */
void cb::Entities::Block::update(float dt)
{
    if (health <= 0)
    {
        deleteFromScene = true;
    }
}

/** \brief Draw the block into the scene.
 * \param target What to draw onto.
 * \param camera Camera from whose position drawing will be relative.
 */
void cb::Entities::Block::draw(sf::RenderTarget &target, const cb::Entities::Camera &camera)
{
    representation.setPosition(x - camera.getX(), y - camera.getY());
    target.draw(representation);
}

// Collision managers =============================================================================

/** \brief Control how the block responds to collisions.
 * \param entity The object the block has collided with.
 */
void cb::Entities::Block::collide(const Entity* entity)
{
    
}

/** \brief Control how the block responds to collisions with the player.
 * \param player The object the block has collided with.
 */
void cb::Entities::Block::collidePlayer(const Entity* player)
{

}

/** \brief Control how the block responds to collisions with projectiles..
 * \param projectile The object the block has collided with.
 */
void cb::Entities::Block::collideProjectile(const Entity* projectile)
{

}

// Getters ========================================================================================

float cb::Entities::Block::getX() const
{
    return x;
}

float cb::Entities::Block::getY() const
{
    return y;
}

float cb::Entities::Block::getWidth() const
{
    return width;
}

float cb::Entities::Block::getHeight() const
{
    return height;
}

EntityTypes cb::Entities::Block::getType() const
{
    return BlockType;
}

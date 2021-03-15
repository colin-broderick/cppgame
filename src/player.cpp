#include "player.h"
#include <iostream>

// Constructors ===================================================================================

/** \brief Player constructor.
 * \param x Starting x position of the player.
 * \param y Starting y position of the player.
 * \param dx Starting x velocity of the player.
 * \param dy Starting y velocity of the player.
 */
cb::Entities::Player::Player(float x, float y, float dx, float dy)
{
    this->x = x;
    this->y = y;
    this->width = 65;
    this->height = 80;
    this->dx = dx;
    this->dy = dy;
    this->dx2 = 0;
    this->dy2 = 400;
    this->dragCoefficientX = 0.085;
    this->dragCoefficientY = 0.01;
    this->movingRight = false;
    this->movingLeft = false;
    this->jumping = false;
    this->lookingUp = false;
    this->lookingDown = false;
    this->health = 300;
    this->verticalCameraFactor = 0;
    this->zIndex = 10;
    this->facing = 1;

    representation.setPosition(sf::Vector2f{x, y});
    representation.setSize(sf::Vector2f{width, height});
    representation.setFillColor(sf::Color::Magenta);
}

// Game loop ======================================================================================

/** \brief Drawing function for the player.
 * \param target What to draw the player on.
 * \param camera Relative to which the player is drawn.
 */
void cb::Entities::Player::draw(sf::RenderTarget &target, const cb::Entities::Camera &camera)
{
    representation.setPosition(x - camera.getX(), y - camera.getY());
    target.draw(representation);
}

/** \brief Start the player moving right. */
void cb::Entities::Player::right()
{
    movingRight = true;
    dx2 = 1000;
}

/** \brief Start the player moving left. */
void cb::Entities::Player::left()
{
    movingLeft = true;
    dx2 = -1000;
}

/** \brief Start the player looking up. */
void cb::Entities::Player::up()
{
    lookingUp = true;
}

/** \brief Start the player looking down. */
void cb::Entities::Player::down()
{
    lookingDown = true;
}

/** \brief Start a jump by setting vertical velocity high. */
void cb::Entities::Player::jump()
{
    dy = -400;
}

/** \brief Stop the player looking up. */
void cb::Entities::Player::stopUp()
{
    lookingUp = false;
}

/** \brief Stop the player looking down. */
void cb::Entities::Player::stopDown()
{
    lookingDown = false;
}

/** \brief Stop the player jumping. */
void cb::Entities::Player::stopJump()
{

}

/** \brief Stop the player moving left. */
void cb::Entities::Player::stopLeft()
{
    movingLeft = false;
    dx2 = 0;
}

/** \brief Stop the player moving right. */
void cb::Entities::Player::stopRight()
{
    movingRight = false;
    dx2 = 0;
}

/** \brief Handle key press events. 
 * \param event The event object containing information about what key was pressed.
 */
void cb::Entities::Player::keyDown(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::Space)
    {
        jump();
    }
    else if (event.key.code == sf::Keyboard::A)
    {
        left();
    }
    else if (event.key.code == sf::Keyboard::D)
    {
        right();
    }
    else if (event.key.code == sf::Keyboard::E)
    {

    }
    else if (event.key.code == sf::Keyboard::W)
    {
        up();
    }
    else if (event.key.code == sf::Keyboard::S)
    {
        down();
    }
    else if (event.key.code == sf::Keyboard::Q)
    {

    }
}

/** \brief Handle key up events.
 * \param event The event object containing information about what key was released.
 */
void cb::Entities::Player::keyUp(const sf::Event &event)
{
    if (event.key.code == sf::Keyboard::A)
    {
        stopLeft(); 
    }
    else if (event.key.code == sf::Keyboard::D)
    {
        stopRight();
    }
    else if (event.key.code == sf::Keyboard::W)
    {
        stopUp();
    }
    else if (event.key.code == sf::Keyboard::S)
    {
        stopDown();
    }
}

/** \brief Handle mouse down events.
 * \param event The event object containing information about what mouse button was pressed.
 */
void cb::Entities::Player::mouseDown(const sf::Event &event)
{
    // TODO Implement.
}

/** \brief Update the state of the player in each frame.
 * \param dt How much time in seconds has passed since the last frame update.
 */
void cb::Entities::Player::update(float dt)
{
    // Horizontal camera tracking.
    if (movingLeft == movingRight)
    {
        facing = facing*0.99;
        dx2 = 0;
    }
    else if (movingLeft)
    {
        facing = facing*0.95 - 0.05;
        dx2 = -1000; 
    }
    else if (movingRight)
    {
        facing = facing*0.95 + 0.05;
        dx2 = 1000;
    }

    // Vertical camera tracking.
    if (lookingDown == lookingUp) // So player is doing both or neither
    {
        verticalCameraFactor = verticalCameraFactor*0.95;
    }
    else if (lookingUp)
    {
        verticalCameraFactor = verticalCameraFactor*0.95 + 0.05;
    }
    else if (lookingDown)
    {
        verticalCameraFactor = verticalCameraFactor*0.95 - 0.05;
    }

    // Update position and speed.
    lastX = x;
    lastY = y;
    x = x + dx * dt;
    y = y + dy * dt;
    lastDx = dx;
    lastDy = dy;
    dx = (1 - dragCoefficientX) * dx + dx2 * dt;
    dy = (1 - dragCoefficientY) * dy + dy2 * dt;
}

// Collision managers =============================================================================

void cb::Entities::Player::collide(const cb::Entities::Entity* entity)
{
    switch (entity->getType())
    {
        case BlockType:
            collideBlock(entity);
            break;
        default:
            break;
    }
}

void cb::Entities::Player::collideBlock(const cb::Entities::Entity* block)
{
    // Detect and respond to vertical collisions.
    if ((lastY + height < block->getY()) || (lastY > block->getY() + block->getHeight()))
    {
        y = lastY;
        dy = 0;
    }
    else
    {
        x = lastX;
        dx = -0.8 * dx;
    }
}

void cb::Entities::Player::collideProjectile(const Entity* projectile)
{
    health -= 10;
}

// Getters ========================================================================================

float cb::Entities::Player::getX() const
{
    return x;
}

float cb::Entities::Player::getY() const
{
    return y;
}

float cb::Entities::Player::getWidth() const
{
    return width;
}

float cb::Entities::Player::getHeight() const
{
    return height;
}

float cb::Entities::Player::getFacing() const
{
    return facing;
}

float cb::Entities::Player::getVerticalCameraFactor() const
{
    return verticalCameraFactor;
}

EntityTypes cb::Entities::Player::getType() const
{
    return PlayerType;
}

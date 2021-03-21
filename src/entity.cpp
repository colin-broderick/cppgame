#include "entity.h"

void cb::Entities::Entity::collide(const Entity* entity)
{
    std::cout << "Did you mean to call Entity::collide?" << std::endl;
}

void cb::Entities::Entity::draw(sf::RenderTarget &target, const cb::Entities::Camera &camera)
{
    std::cout << "Did you mean to call Entity::draw?" << std::endl;
}
void cb::Entities::Entity::update(float dt)
{
    std::cout << "Did you mean to call Entity::update?" << std::endl;
}
void cb::Entities::Entity::keyDown(const sf::Event &event)
{
    std::cout << "Did you mean to call Entity::keyDown?" << std::endl;
}
void cb::Entities::Entity::keyUp(const sf::Event &event)
{
    std::cout << "Did you mean to call Entity::keyUp?" << std::endl;
}
float cb::Entities::Entity::getX() const
{
    std::cout << "Did you mean to call Entity::getX?" << std::endl;
    return 0;
}
float cb::Entities::Entity::getY() const
{
    std::cout << "Did you mean to call Entity::getY?" << std::endl;
    return 0;
}
float cb::Entities::Entity::getWidth() const
{
    std::cout << "Did you mean to call Entity::getWidth?" << std::endl;
    return 0;
}
float cb::Entities::Entity::getHeight() const
{
    std::cout << "Did you mean to call Entity::getHeight?" << std::endl;
    return 0;
}
bool cb::Entities::Entity::collidesWith(const Entity &entiry) const
{
    std::cout << "Did you mean to call Entity::collidesWith?" << std::endl;
    return false;
}
EntityTypes cb::Entities::Entity::getType() const
{
    std::cout << "Did you mean to call Entity::getType?" << std::endl;
    return EntityType;
}
float cb::Entities::Entity::getRadius() const
{
    std::cout << "Did you mean to call Entity::getRadius?" << std::endl;
    return 0;
}
float cb::Entities::Entity::getDx() const
{
    std::cout << "Did you mean to call Entity::getDx?" << std::endl;
    return 0;
}
float cb::Entities::Entity::getDy() const
{
    std::cout << "Did you mean to call Entity::getDy?" << std::endl;
    return 0;
}
bool cb::Entities::Entity::requestsDeletion() const
{
    // std::cout << "Did you mean to call Entity::requestsDeletion?" << std::endl;
    return false;
}
void cb::Entities::Entity::reduceHealth(int pain)
{
    std::cout << "Did you mean to call Entity::reduceHealth?" << std::endl;
}
void cb::Entities::Entity::setDx(float newValue)
{
    std::cout << "Did you mean to call Entity::setDx?" << std::endl;
}

void cb::Entities::Entity::setDy(float newValue)
{
    std::cout << "Did you mean to call Entity::setDy?" << std::endl;
}

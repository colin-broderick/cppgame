#include "collisions.h"

namespace cb::Collisions
{
    std::map<EntityTypes, std::map<EntityTypes, cb::Collisions::CollisionFunction>> collisions;

    /** \brief Immediately returns false for any impossible collision check.
     * \param T Entity 1.
     * \param U Entity 2.
     */
    template<typename T, typename U>
    bool UnpossiblePair(T one, U two)
    {
        return false;
    }
}

/** \brief Jump matrix pointing entity combinations to collision checking functions. */
void cb::Collisions::initCollisionMap()
{
    collisions[BlockType][PlayerType] = cb::Collisions::Block_Player;
    collisions[PlayerType][BlockType] = cb::Collisions::Player_Block;
    collisions[BlockType][BlockType] = cb::Collisions::UnpossiblePair;
    collisions[PlayerType][PlayerType] = cb::Collisions::UnpossiblePair;
    collisions[PlayerType][ProjectileType] = cb::Collisions::Player_Projectile;
    collisions[ProjectileType][PlayerType] = cb::Collisions::Projectile_Player;
    collisions[BlockType][ProjectileType] = cb::Collisions::Block_Projectile;
    collisions[ProjectileType][BlockType] = cb::Collisions::Projectile_Block;
    collisions[ProjectileType][ProjectileType] = cb::Collisions::Projectile_Projectile;
    collisions[PlatformType][PlayerType] = cb::Collisions::Platform_Player;
    collisions[PlatformType][BlockType] = cb::Collisions::UnpossiblePair;
    collisions[PlatformType][ProjectileType] = cb::Collisions::Platform_Projectile;
    collisions[PlayerType][PlatformType] = cb::Collisions::Player_Platform;
    collisions[BlockType][PlatformType] = cb::Collisions::UnpossiblePair;
    collisions[ProjectileType][PlatformType] = cb::Collisions::Projectile_Platform;
    collisions[PlatformType][PlatformType] = cb::Collisions::UnpossiblePair;
}

// Entity collisions ==============================================================================

/** \brief Check whether a player object has collided with a block object.
 * \param player Pointer to Player/Entity.
 * \param block Pointer to Block/Entity.
 * \return True if colliding, false otherwise.
 */
bool cb::Collisions::Player_Block(cb::Entities::Entity* player, cb::Entities::Entity* block)
{
    return rectangleRectangleIntersect(player, block);
}

bool cb::Collisions::Block_Player(cb::Entities::Entity* block, cb::Entities::Entity* player)
{
    return cb::Collisions::Player_Block(player, block);
}

bool cb::Collisions::Player_Projectile(cb::Entities::Entity* player, cb::Entities::Entity* projectile)
{
    return false;
}

bool cb::Collisions::Projectile_Player(cb::Entities::Entity* projectile, cb::Entities::Entity* player)
{
    return Player_Projectile(player, projectile);
}

bool cb::Collisions::Block_Projectile(cb::Entities::Entity* block, cb::Entities::Entity* projectile)
{
    return rectangleCircleIntersect(block, projectile);
}

bool cb::Collisions::Projectile_Block(cb::Entities::Entity* projectile, cb::Entities::Entity* block)
{
    return Block_Projectile(block, projectile);
}

bool cb::Collisions::Projectile_Projectile(cb::Entities::Entity* projectile1, cb::Entities::Entity* projectile2)
{
    return circleCircleInterset(projectile1, projectile2);
}

bool cb::Collisions::Platform_Player(cb::Entities::Entity* platform, cb::Entities::Entity* player)
{
    // todo
    return false;
}

bool cb::Collisions::Platform_Projectile(cb::Entities::Entity* platform, cb::Entities::Entity* projectile)
{
    // todo
    return false;
}

bool cb::Collisions::Player_Platform(cb::Entities::Entity* player, cb::Entities::Entity* platform)
{
    // todo
    return false;
}

bool cb::Collisions::Projectile_Platform(cb::Entities::Entity* projectile, cb::Entities::Entity* platform)
{
    // todo
    return false;
}

// Shape collisions ===============================================================================

bool cb::Collisions::circleCircleInterset(cb::Entities::Entity* ent1, cb::Entities::Entity* ent2)
{
    auto x1 = ent1->getX();
    auto y1 = ent1->getY();
    auto x2 = ent2->getX();
    auto y2 = ent2->getY();
    if (((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1)) < (2*ent1->getRadius())*(2*ent1->getRadius()))
    {
        return true;
    }
    return false;
}

bool cb::Collisions::rectangleCircleIntersect(cb::Entities::Entity* rectangle, cb::Entities::Entity* circle)
{
    if (circle->getX() > rectangle->getX() + rectangle->getWidth() + circle->getRadius()) {return false;}
    if (circle->getY() > rectangle->getY() + rectangle->getHeight() + circle->getRadius()) {return false;}
    if (circle->getX() < rectangle->getX() - circle->getRadius()) {return false;}
    if (circle->getY() < rectangle->getY() - circle->getRadius()) {return false;}
    return true;
}

bool cb::Collisions::rectangleRectangleIntersect(cb::Entities::Entity* rectangle1, cb::Entities::Entity* rectangle2)
{
    if (rectangle1->getX() + rectangle1->getWidth() < rectangle2->getX()) {return false;}
    if (rectangle1->getX() > rectangle2->getX() + rectangle2->getWidth()) {return false;}
    if (rectangle1->getY() + rectangle1->getHeight() < rectangle2->getY()) {return false;}
    if (rectangle1->getY() > rectangle2->getY() + rectangle2->getHeight()) {return false;}
    return true;
}

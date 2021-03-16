#include "collisions.h"

namespace cb::Collisions
{
    std::map<EntityTypes, std::map<EntityTypes, cb::Collisions::CollisionFunction>> collisions;

    template<typename T, typename U>
    bool UnpossiblePair(T one, U two)
    {
        return false;
    }
}

/** \brief Check whether a player object has collided with a block object.
 * \param player Pointer to Player/Entity.
 * \param block Pointer to Block/Entity.
 * \return True if colliding, false otherwise.
 */
bool cb::Collisions::Player_Block(cb::Entities::Entity* player, cb::Entities::Entity* block)
{
    if (player->getX() + player->getWidth() < block->getX()) {return false;}
    if (player->getX() > block->getX() + block->getWidth()) {return false;}
    if (player->getY() + player->getHeight() < block->getY()) {return false;}
    if (player->getY() > block->getY() + block->getHeight()) {return false;}
    return true;
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
    return false;
}

bool cb::Collisions::Block_Projectile(cb::Entities::Entity* block, cb::Entities::Entity* projectile)
{
    if (projectile->getX() > block->getX() + block->getWidth() + projectile->getRadius()) {return false;}
    if (projectile->getY() > block->getY() + block->getHeight() + projectile->getRadius()) {return false;}
    if (projectile->getX() < block->getX() - projectile->getRadius()) {return false;}
    if (projectile->getY() < block->getY() - projectile->getRadius()) {return false;}
    return true;
}

bool cb::Collisions::Projectile_Block(cb::Entities::Entity* projectile, cb::Entities::Entity* block)
{
    return Block_Projectile(block, projectile);
}

bool cb::Collisions::Projectile_Projectile(cb::Entities::Entity* projectile1, cb::Entities::Entity* projectile2)
{
    return circleCircleInterset(projectile1, projectile2);
}

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
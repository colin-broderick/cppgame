#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <map>

#include "player.h"
#include "block.h"


namespace cb::Collisions
{
    typedef bool (*CollisionFunction)(cb::Entities::Entity*, cb::Entities::Entity*);
    void initCollisionMap();
    
    // Entity collisions
    bool Player_Block(cb::Entities::Entity* player, cb::Entities::Entity* block);
    bool Block_Player(cb::Entities::Entity* block, cb::Entities::Entity* player);
    bool Player_Projectile(cb::Entities::Entity* player, cb::Entities::Entity* projectile);
    bool Projectile_Player(cb::Entities::Entity* projectile, cb::Entities::Entity* player);
    bool Block_Projectile(cb::Entities::Entity* block, cb::Entities::Entity* projectile);
    bool Projectile_Block(cb::Entities::Entity* projectile, cb::Entities::Entity* block);
    bool Projectile_Projectile(cb::Entities::Entity* projectile1, cb::Entities::Entity* projectile2);
    bool Platform_Player(cb::Entities::Entity* platform, cb::Entities::Entity* player);
    bool Platform_Projectile(cb::Entities::Entity* platform, cb::Entities::Entity* projectile);
    bool Player_Platform(cb::Entities::Entity* player, cb::Entities::Entity* platform);
    bool Projectile_Platform(cb::Entities::Entity* projectile, cb::Entities::Entity* platform);
    
    // Shape collisions
    bool circleCircleInterset(cb::Entities::Entity* ent1, cb::Entities::Entity* ent2);
    bool rectangleCircleIntersect(cb::Entities::Entity* rectangle, cb::Entities::Entity* circle);
    bool rectangleRectangleIntersect(cb::Entities::Entity* rectangle1, cb::Entities::Entity* rectangle2);
}

#endif

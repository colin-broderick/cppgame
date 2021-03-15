#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <map>

#include "player.h"
#include "block.h"


namespace cb::Collisions
{
    typedef bool (*CollisionFunction)(cb::Entities::Entity*, cb::Entities::Entity*);
    
    // Entity collisions
    bool Player_Block(cb::Entities::Entity* player, cb::Entities::Entity* block);
    bool Block_Player(cb::Entities::Entity* block, cb::Entities::Entity* player);
    bool Block_Block(cb::Entities::Entity* block1, cb::Entities::Entity* block2);
    bool Player_Player(cb::Entities::Entity* player1, cb::Entities::Entity* player2);
    bool Player_Projectile(cb::Entities::Entity* player, cb::Entities::Entity* projectile);
    bool Projectile_Player(cb::Entities::Entity* projectile, cb::Entities::Entity* player);
    bool Block_Projectile(cb::Entities::Entity* block, cb::Entities::Entity* projectile);
    bool Projectile_Block(cb::Entities::Entity* projectile, cb::Entities::Entity* block);
    bool Projectile_Projectile(cb::Entities::Entity* projectile1, cb::Entities::Entity* projectile2);
    bool Platform_Player(cb::Entities::Entity* platform, cb::Entities::Entity* player);
    bool Platform_Block(cb::Entities::Entity* platform, cb::Entities::Entity* block);
    bool Platform_Projectile(cb::Entities::Entity* platform, cb::Entities::Entity* projectile);
    bool Player_Platform(cb::Entities::Entity* player, cb::Entities::Entity* platform);
    bool Block_Platform(cb::Entities::Entity* block, cb::Entities::Entity* platform);
    bool Projectile_Platform(cb::Entities::Entity* projectile, cb::Entities::Entity* platform);
    bool Platform_Platform(cb::Entities::Entity* platform1, cb::Entities::Entity* platform2);
    
    // Shape collisions
    bool circleCircleInterset(cb::Entities::Entity* ent1, cb::Entities::Entity* ent2);

    void initCollisionMap();
}


#endif

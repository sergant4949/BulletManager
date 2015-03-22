#ifndef BULLETMANAGER_H
#define BULLETMANAGER_H

#define REACTION_AREA 0.04

#include <cmath>
#include <map>
#include <mutex>
#include "float2.h"
#include "Bullet.h"
#include "Wall.h"

class BulletManager {
    private:
        static BulletManager* instance;
        std::multimap<float, Bullet*>* bulletList;
        
        BulletManager();
        BulletManager(const BulletManager&);
        BulletManager& operator=(BulletManager&);
    public:
        ~BulletManager();
        
        static BulletManager* getInstance();
        
        void Update(float time);
        void Fire( float2 pos, float2 dir, float speed, float time, float life_time);
        float distanceToWall(float distToCorner1, float distToCorner2, float lenWall);
        bool parallel(Bullet* cBullet, Wall* cWall);
};

#endif // BULLETMANAGER_H
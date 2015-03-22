#include "BulletManager.h"

BulletManager* BulletManager::instance = 0;
std::mutex mtxBullets;

BulletManager::BulletManager() {
    bulletList = new std::multimap<float, Bullet*>();
}

BulletManager::~BulletManager() {
    bulletList->clear();
    delete bulletList;
}

BulletManager* BulletManager::getInstance() {
    if ( !instance ) {
        instance = new BulletManager();
    }
    return instance;
}

void BulletManager::Update(float time) {
    std::map<unsigned, Wall*>* wallList = Wall::getWallsList();
    std::multimap<float, Bullet*>::iterator bulletIt = bulletList->begin();
    std::map<unsigned, Wall*>::iterator wallIt = wallList->begin();
    float2 currentPos;
    float distToWall, distToCorner1, distToCorner2, lenWall;
    Bullet* cBullet;
    Wall* cWall;
    bool rebounded;

    for ( ; bulletIt != bulletList->end() && time >= bulletIt->second->getTime(); ) {
        cBullet = bulletIt->second;
        if ( cBullet->getDeathTime() <= time ) {
            std::lock_guard<std::mutex> lock(mtxBullets);
            bulletIt = bulletList->erase(bulletIt);
        } else {
            currentPos = cBullet->getCurrentPosition(time);
            rebounded = false;
            for ( ; wallIt != wallList->end() && !rebounded; ++wallIt ) {
                cWall = wallIt->second;
                if ( !parallel(cBullet, cWall)) {
                    distToCorner1 = currentPos.distance(cWall->getFirstCorner());
                    distToCorner2 = currentPos.distance(cWall->getSecondCorner());
                    lenWall = cWall->len();
                    distToWall = distanceToWall(distToCorner1, distToCorner2, lenWall);
                    if ( distToWall <= REACTION_AREA && distToCorner1 < lenWall && distToCorner2 < lenWall) {
                        std::lock_guard<std::mutex> lock(mtxBullets);
                        cBullet->rebound(cWall, currentPos, time);
                        delete cWall;
                        rebounded = true;
                    }
                }
            }
            ++bulletIt;
        }
    }
}

void BulletManager::Fire(float2 pos, float2 dir, float speed, float time, float life_time) {
    Bullet* newBullet = new Bullet(pos, dir, speed, time, life_time);

    std::lock_guard<std::mutex> lock(mtxBullets);
    bulletList->insert(std::pair<float, Bullet*>(time, newBullet));
}


float BulletManager::distanceToWall(float distToCorner1, float distToCorner2, float lenWall) {
    float p = (distToCorner1 + distToCorner2 + lenWall) / 2;
    return 2*std::sqrt(p*(p-distToCorner1)*(p-distToCorner2)*(p-lenWall))/lenWall;
}

bool BulletManager::parallel(Bullet* cBullet, Wall* cWall) {
    float bulletDeltaX = cBullet->getDeltaX();
    float bulletDeltaY = cBullet->getDeltaY();
    float wallDeltaX = cWall->getDeltaX();
    float wallDeltaY = cWall->getDeltaY();
    bool retValue = false;

    if ( bulletDeltaY == 0 && wallDeltaY == 0 ) {
        retValue = true;
    }
    if ( bulletDeltaY * wallDeltaY != 0 && std::abs(bulletDeltaX/bulletDeltaY) == std::abs(wallDeltaX/wallDeltaY) ) {
        retValue = true;
    }
    return retValue;
}

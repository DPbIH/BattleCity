#pragma once

#include "Singleton.h"
#include "Dispatcher.h"
#include "Dispatchable.h"

class Tank;
class Terrain;
class Mine;
class Bullet;

class CollisionManager
	: public Singleton<CollisionManager>
{
public:
	CollisionManager();
	void Handle( Dispatchable& obj1, Dispatchable& obj2 );

private:
	static void CollideTanks( Tank& tank1, Tank& tank2 );
	static void CollideTankTerrain( Tank& tank, Terrain& terrain );
	static void CollideTankBullet( Tank& tank, Bullet& bullet );
	static void CollideTankMine( Tank& tank, Mine& mine );
	static void CollideBulletMine( Bullet& bullet, Mine& mine );
	static void CollideBulletTerrain( Bullet& bullet, Terrain& terrain );
	static void CollideBullets( Bullet& bullet1, Bullet& bullet2 );

	void InitHandlersDispatcher();

	Dispatcher handlersDispatcher_;

};

inline CollisionManager& CollisionManagerInstance()
{
	return CollisionManager::Instance();
}
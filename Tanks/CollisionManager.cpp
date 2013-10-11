#include "stdafx.h"
#include "Tank.h"
#include "Terrain.h"
#include "Mine.h"
#include "Bullet.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	InitHandlersDispatcher();
}

void CollisionManager::InitHandlersDispatcher()
{
	handlersDispatcher_.Add<Tank, Tank>(CollisionManager::CollideTanks);
	handlersDispatcher_.Add<Tank, Terrain>(CollisionManager::CollideTankTerrain);
	handlersDispatcher_.Add<Tank, Bullet>(CollisionManager::CollideTankBullet);
	handlersDispatcher_.Add<Tank, Mine>(CollisionManager::CollideTankMine);
	handlersDispatcher_.Add<Bullet, Mine>(CollisionManager::CollideBulletMine);
	handlersDispatcher_.Add<Bullet, Terrain>(CollisionManager::CollideBulletTerrain);
	handlersDispatcher_.Add<Bullet, Bullet>(CollisionManager::CollideBullets);
}

void CollisionManager::CollideTanks( Tank&, Tank& )
{
	MessageBeep(MB_OK);
}

void CollisionManager::CollideTankTerrain( Tank& tank, Terrain& terrain )
{
	switch( terrain.Type() )
	{
	case Terrain::Rock:
		MessageBeep(MB_ICONHAND);
		break;

	case Terrain::Ice:
		if( ! tank.IsSkidding() )
		{
			tank.SetCoordinates( terrain.GetCoordinates() );
			tank.Skid();
		}
		break;

	case Terrain::Grass:
		tank.SetCoordinates( terrain.GetCoordinates() );
		break;
	}
}

void CollisionManager::CollideTankBullet( Tank& tank, Bullet& bullet )
{
	MessageBeep(MB_ICONQUESTION);
	bullet.SetCoordinates( tank.GetCoordinates() );
	bullet.Explode();
	bullet.Damage(tank);
	bullet.Die();
}

void CollisionManager::CollideTankMine( Tank& tank, Mine& mine )
{
	MessageBeep(MB_ICONSTOP);
	tank.SetCoordinates( mine.GetCoordinates() );
	mine.Explode();
	mine.Damage(tank);
	mine.Die();
}

void CollisionManager::CollideBulletMine( Bullet& bullet, Mine& mine )
{
	MessageBeep(MB_ICONSTOP);
	bullet.SetCoordinates( mine.GetCoordinates() );
	mine.Explode();
	bullet.Explode();
	mine.Die();
	bullet.Die();
}

void CollisionManager::CollideBulletTerrain( Bullet& bullet, Terrain& terrain )
{
	if( terrain.Type() != Terrain::Rock )
	{
		bullet.SetCoordinates( terrain.GetCoordinates() );
		return;
	}

	MessageBeep(MB_ICONSTOP);
	bullet.Explode();
	bullet.Damage(terrain);
}

void CollisionManager::CollideBullets( Bullet& bullet1, Bullet& bullet2 )
{
	MessageBeep(MB_ICONSTOP);
	bullet1.SetCoordinates( bullet2.GetCoordinates() );
	bullet1.Explode();
	bullet1.Die();
	bullet2.Die();
}

void CollisionManager::Handle( Dispatchable& obj1, Dispatchable& obj2 )
{
	handlersDispatcher_.Call(obj1, obj2);
}
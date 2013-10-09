#include "stdafx.h"
#include "Tank.h"
#include "Obstacle.h"
#include "Bullet.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
	InitHandlersDispatcher();
}

void CollisionManager::InitHandlersDispatcher()
{
}

void CollisionManager::Handle( Dispatchable& obj1, Dispatchable& obj2 )
{
	handlersDispatcher_.Call(obj1, obj2);
}
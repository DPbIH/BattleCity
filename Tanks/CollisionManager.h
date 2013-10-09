#pragma once

#include "Singleton.h"
#include "Dispatcher.h"
#include "Dispatchable.h"

class CollisionManager
	: public Singleton<CollisionManager>
{
public:
	CollisionManager();
	void Handle( Dispatchable& obj1, Dispatchable& obj2 );

private:
	void InitHandlersDispatcher();

	Dispatcher handlersDispatcher_;

};

inline CollisionManager& CollisionManagerInstance()
{
	return CollisionManager::Instance();
}
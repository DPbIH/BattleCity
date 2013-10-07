#pragma once

#include <list>
#include "Thread.h"
#include "CriticalSection.h"

class SubscriberBase;

class PublisherBase
{
	typedef sync::ObjectLevelLockable<sync::CriticalSection>	sync_t;
	typedef sync_t::Lock										lock_t;

public:
	virtual ~PublisherBase() = 0 {}
	virtual void Subscribe( SubscriberBase* subscriber );
	virtual void Unsubscribe( SubscriberBase* subscriber );
	virtual void Notify();

protected:
	sync_t sync_;
	typedef std::list<SubscriberBase*> SubscribersListT;

	SubscribersListT subscribers_;
};
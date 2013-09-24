#pragma once

#include <vector>

class SubscriberBase;

class PublisherBase
{
public:
	virtual ~PublisherBase() = 0 {}
	virtual void Subscribe( SubscriberBase* subscriber );
	virtual void Notify();

protected:
	typedef std::vector<SubscriberBase*> SubscribersListT;

	SubscribersListT subscribers_;
};
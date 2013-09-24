#pragma once

class PublisherBase;

class SubscriberBase
{
public:
	virtual ~SubscriberBase() = 0 {}
	virtual void Update( PublisherBase* publisher ) = 0;
};
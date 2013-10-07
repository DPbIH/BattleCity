#include "stdafx.h"
#include "SubscriberBase.h"
#include "PublisherBase.h"

void PublisherBase::Subscribe( SubscriberBase* subscriber )
{
	lock_t lock(sync_);

	subscribers_.push_back( subscriber );
}

void PublisherBase::Unsubscribe( SubscriberBase* subscriber )
{
	lock_t lock(sync_);

	subscribers_.erase( std::remove( subscribers_.begin(), subscribers_.end(), subscriber ), subscribers_.end() );
}

void PublisherBase::Notify()
{
	lock_t lock(sync_);

	for each( auto subscriber in subscribers_ )
	{
		subscriber->Update( this );
	}
}

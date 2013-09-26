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
	SubscribersListT::iterator it = std::find( subscribers_.begin(), subscribers_.end(), subscriber );
	if( it != subscribers_.end() )
	{
		subscribers_.erase(it);
	}
}

void PublisherBase::Notify()
{
	lock_t lock(sync_);
	for each( const auto& subscriber in subscribers_ )
	{
		subscriber->Update( this );
	}
}

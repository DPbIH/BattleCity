#include "stdafx.h"
#include "SubscriberBase.h"
#include "PublisherBase.h"

#define UNSUBSCRIBED NULL

void PublisherBase::Subscribe( SubscriberBase* subscriber )
{
	lock_t lock(sync_);

	Cleanup();
	subscribers_.push_back( subscriber );
}

void PublisherBase::Cleanup()
{
	subscribers_.remove( UNSUBSCRIBED );
}

void PublisherBase::Unsubscribe( SubscriberBase* subscriber )
{
	lock_t lock(sync_);

	SubscribersListT::iterator it = std::find( subscribers_.begin(), subscribers_.end(), subscriber );
	if( it != subscribers_.end() )
	{
		*it = UNSUBSCRIBED;
	}
}

void PublisherBase::Notify()
{
	lock_t lock(sync_);

	for each( auto subscriber in subscribers_ )
	{
		if( subscriber != UNSUBSCRIBED )
		{
			subscriber->Update( this );
		}
	}
}

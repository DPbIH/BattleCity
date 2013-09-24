#include "stdafx.h"
#include "SubscriberBase.h"
#include "PublisherBase.h"

void PublisherBase::Subscribe( SubscriberBase* subscriber )
{
	subscribers_.push_back( subscriber );
}

void PublisherBase::Notify()
{
	for each( const auto& subscriber in subscribers_ )
	{
		subscriber->Update( this );
	}
}

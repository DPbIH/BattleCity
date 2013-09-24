#include "stdafx.h"
#include "GraphicObjectVisitor.h"
#include "GraphicObjectsRegistry.h"

void GraphicObjectsRegistry::Add( const GraphicObjectBase::Ptr& goPtr )
{
	lock_t lock(sync_);
	AddImpl( goPtr );
}

void GraphicObjectsRegistry::AddImpl( const GraphicObjectBase::Ptr& goPtr )
{
	goObjects_.push_back( goPtr );
}

void GraphicObjectsRegistry::Accept( GraphicObjectVisitor& visitor )
{
	lock_t lock(sync_);

	BOOST_FOREACH( GOObjectsVectorT::value_type& val, goObjects_ )
	{
		if( visitor.InterruptionRequested() )
		{
			break;
		}

		val->Accept( visitor );
	}
}
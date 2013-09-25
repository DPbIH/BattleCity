#include "stdafx.h"
#include "GraphicObjectVisitor.h"
#include "GraphicObjectsRegistry.h"

void GraphicObjectsRegistry::Add( size_t UID, const GraphicObjectBase::Ptr& goPtr )
{
	lock_t lock(sync_);
	AddImpl( UID, goPtr );
}

void GraphicObjectsRegistry::AddImpl( size_t UID, const GraphicObjectBase::Ptr& goPtr )
{
	goObjects_[UID] = goPtr;
}

void GraphicObjectsRegistry::Remove( size_t UID )
{
	lock_t lock(sync_);
	RemoveImpl( UID );
}

void GraphicObjectsRegistry::RemoveImpl( size_t UID )
{
	goObjects_.erase( UID );
}

void GraphicObjectsRegistry::Accept( GraphicObjectVisitor& visitor )
{
	lock_t lock(sync_);

	BOOST_FOREACH( GOObjectsMapT::value_type& val, goObjects_ )
	{
		if( visitor.InterruptionRequested() )
		{
			break;
		}

		val.second->Accept( visitor );
	}
}
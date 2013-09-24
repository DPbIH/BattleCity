#pragma once

#include "Singleton.h"
#include "GraphicObjectBase.h"
#include "Thread.h"
#include "CriticalSection.h"
#include <vector>

class GraphicObjectVisitor;

class GraphicObjectsRegistry
	: public Singleton<GraphicObjectsRegistry>
{
	typedef sync::ObjectLevelLockable<sync::CriticalSection>	sync_t;
	typedef sync_t::Lock										lock_t;
	typedef std::vector<GraphicObjectBase::Ptr>			GOObjectsVectorT;

public:
	void Add( const GraphicObjectBase::Ptr& goPtr );
	void Accept( GraphicObjectVisitor& visitor );

private:
	void AddImpl( const GraphicObjectBase::Ptr& goPtr );

	sync_t				sync_;
	GOObjectsVectorT	goObjects_;

};

inline GraphicObjectsRegistry& GORegistry()
{
	return GraphicObjectsRegistry::Instance();
}
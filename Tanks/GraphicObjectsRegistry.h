#pragma once

#include "Singleton.h"
#include "GraphicObjectBase.h"
#include "Thread.h"
#include "CriticalSection.h"
#include <map>

class GraphicObjectVisitor;

class GraphicObjectsRegistry
	: public Singleton<GraphicObjectsRegistry>
{
	typedef sync::ObjectLevelLockable<sync::CriticalSection>	sync_t;
	typedef sync_t::Lock										lock_t;
	typedef std::map<size_t, GraphicObjectBase::Ptr>			GOObjectsMapT;

public:
	void Add( size_t UID, const GraphicObjectBase::Ptr& goPtr );
	void Remove( size_t UID );
	void Accept( GraphicObjectVisitor& visitor );

private:
	void AddImpl( size_t UID, const GraphicObjectBase::Ptr& goPtr );
	void RemoveImpl( size_t UID );

	sync_t			sync_;
	GOObjectsMapT	goObjects_;

};

inline GraphicObjectsRegistry& GORegistry()
{
	return GraphicObjectsRegistry::Instance();
}
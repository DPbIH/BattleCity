#include "stdafx.h"
#include "Tank.h"
#include "Bullet.h"
#include "Terrain.h"
#include "Mine.h"
#include "GraphicObjectBase.h"
#include "RegistryLookupVisitor.h"

RegistryLookupVisitor::RegistryLookupVisitor()
	: foundObj_(NULL)
{
}

void RegistryLookupVisitor::SetLookupPos( const Coordinates& pos )
{
	lookupPos_ = pos;
}

void RegistryLookupVisitor::Visit( Bullet* bullet )
{
	DoVisit( bullet );
}

void RegistryLookupVisitor::Visit( Tank* tank )
{
	DoVisit( tank );
}

void RegistryLookupVisitor::Visit( Terrain* terrain )
{
	DoVisit( terrain );
}

void RegistryLookupVisitor::Visit( Mine* mine )
{
	DoVisit( mine );
}

void RegistryLookupVisitor::DoVisit( GraphicObjectBase* obj )
{
	if( ! obj->IsGarbage() &&
		! obj->Hidden() &&
		( obj->GetCoordinates() == lookupPos_ )
		)
	{
		foundObj_ = obj;
		RequestInterruption();
	}
}

GraphicObjectBase* RegistryLookupVisitor::GetResult()
{
	return foundObj_;
}
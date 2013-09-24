#include "stdafx.h"
#include "Tank.h"
#include "Bullet.h"
#include "Obstacle.h"
#include "GraphicObjectBase.h"
#include "RegistryLookupVisitor.h"

RegistryLookupVisitor::RegistryLookupVisitor()
	: foundObj_(NULL)
{
}

void RegistryLookupVisitor::SetLookupPos( unsigned int x, unsigned int y )
{
	x_ = x;
	y_ = y;
}

void RegistryLookupVisitor::Visit( Bullet* bullet )
{
	DoVisit( bullet );
}

void RegistryLookupVisitor::Visit( Tank* tank )
{
	DoVisit( tank );
}

void RegistryLookupVisitor::Visit( Obstacle* obstacle )
{
	DoVisit( obstacle );
}

void RegistryLookupVisitor::DoVisit( GraphicObjectBase* obj )
{
	if( ! obj->IsGarbage() && ! obj->Hidden() &&( obj->GetX() == x_ ) && ( obj->GetY() == y_ ) )
	{
		foundObj_ = obj;
		RequestInterruption();
	}
}

GraphicObjectBase* RegistryLookupVisitor::GetResult()
{
	return foundObj_;
}
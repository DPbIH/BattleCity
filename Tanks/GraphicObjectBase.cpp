#include "stdafx.h"
#include "Helpers.h"
#include "Renderer.h"
#include "CollisionManager.h"
#include "GraphicObjectBase.h"

GraphicObjectBase::GraphicObjectBase()
	: uid_( CreateUID() )
	, lastMoveDirection_( GlobalDeclarations::North )
	, isGarbage_( false )
	, isHidden_( false )
	, health_(0)
	, destructible_(true)
	, damagePoints_(0)
{
}

size_t GraphicObjectBase::UID()
{
	return uid_;
}

void GraphicObjectBase::Draw( Renderer* renderer )
{
	if( ! Hidden() && ! IsGarbage() )
	{
		DrawImpl(renderer);
	}
}

void GraphicObjectBase::Move( size_t delta, GlobalDeclarations::Direction direction )
{
	size_t newX = coords_.X;
	size_t newY = coords_.Y;

	switch( direction )
	{
	case GlobalDeclarations::North:
		newY = newY + delta;
		break;
	case GlobalDeclarations::South:
		newY = delta > newY ? 0 : newY - delta;
		break;
	case GlobalDeclarations::West:
		newX = delta > newX ? 0 : newX - delta;
		break;
	case GlobalDeclarations::East:
		newX = newX + delta;
		break;
	}

	lastMoveDirection_ = direction;

	if( GraphicObjectBase* collision = Helpers::FindGraphicObjectByPosition( Coordinates(newX, newY) ) )
	{
		HandleCollision( collision );
		return;
	}

	SetCoordinates( newX, newY );
}

void GraphicObjectBase::HandleCollision( GraphicObjectBase* other )
{
	if( other != this )
	{
		CollisionManagerInstance().Handle( *this, *other );
	}
}

bool GraphicObjectBase::IsGarbage()
{
	return isGarbage_;
}

void GraphicObjectBase::IsGarbage( bool isGarbage )
{
	isGarbage_ = isGarbage;
}

bool GraphicObjectBase::Hidden()
{
	return isHidden_;
}

void GraphicObjectBase::Show()
{
	isHidden_ = false;
}

void GraphicObjectBase::Hide()
{
	isHidden_ = true;
}

Coordinates GraphicObjectBase::GetCoordinates() const
{
	return coords_;
}

void GraphicObjectBase::SetCoordinates( const Coordinates& newPosition )
{
	coords_ = newPosition;
}

void GraphicObjectBase::SetCoordinates( size_t newX, size_t newY )
{
	coords_.X = newX;
	coords_.Y = newY;
}

size_t GraphicObjectBase::newInstanceCounter_ = 0;

size_t GraphicObjectBase::CreateUID()
{
	return InterlockedIncrement( &newInstanceCounter_ );
}

void GraphicObjectBase::Damage( GraphicObjectBase& other )
{
	other.GetDamaged( damagePoints_ );
}

void GraphicObjectBase::GetDamaged( size_t damagePoints )
{
	if( ! destructible_ )
	{
		return;
	}

	if( health_ > damagePoints )
	{
		health_ -= damagePoints;
	}
	else
	{
		health_ = 0;
		Die();
	}
}

void GraphicObjectBase::Die()
{
	IsGarbage(true);
}

void GraphicObjectBase::Explode()
{
	Die();
}
#include "stdafx.h"
#include "Helpers.h"
#include "Renderer.h"
#include "GraphicObjectBase.h"

GraphicObjectBase::GraphicObjectBase()
	: uid_( CreateUID() )
	, lastMoveDirection_( North )
	, isGarbage_( false )
	, isHidden_( false )
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

void GraphicObjectBase::Move( size_t delta, Direction direction )
{
	size_t newX = coords_.X;
	size_t newY = coords_.Y;

	switch( direction )
	{
	case North:
		newY = newY + delta;
		break;
	case South:
		newY = delta > newY ? 0 : newY - delta;
		break;
	case West:
		newX = delta > newX ? 0 : newX - delta;
		break;
	case East:
		newX = newX + delta;
		break;
	}

	if( GraphicObjectBase* collision = Helpers::FindGraphicObjectByPosition( Coordinates(newX, newY) ) )
	{
		if( collision != this )
		{
			HandleCollision( collision );
		}
	}
	else
	{
		SetCoordinates( newX, newY );
	}

	lastMoveDirection_ = direction;
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
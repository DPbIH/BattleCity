#include "stdafx.h"
#include "Helpers.h"
#include "Renderer.h"
#include "GraphicObjectBase.h"

GraphicObjectBase::GraphicObjectBase()
	: lastMoveDirection_( North )
	, isGarbage_( false )
	, isHidden_( false )
{
	PinTo(0, 0);
}

void GraphicObjectBase::Draw( Renderer* renderer )
{
	if( ! Hidden() && ! IsGarbage() )
	{
		DrawImpl(renderer);
	}
}

void GraphicObjectBase::Move( int delta, Direction direction )
{
	unsigned int newX = GetX();
	unsigned int newY = GetY();

	switch( direction )
	{
	case North:
		newY = GetY() + delta;
		break;
	case South:
		newY = delta > GetY() ? 0 : GetY() - delta;
		break;
	case West:
		newX = delta > GetX() ? 0 : GetX() - delta;
		break;
	case East:
		newX = GetX() + delta;
		break;
	}

	if( GraphicObjectBase* collision = Helpers::FindGraphicObjectByPosition( newX, newY ) )
	{
		if( collision != this )
		{
			HandleCollision( collision );
		}
	}
	else
	{
		SetPos( newX, newY );
	}

	lastMoveDirection_ = direction;
}

void GraphicObjectBase::PinTo( unsigned int x, unsigned int y )
{
	SetPos(x,y);
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

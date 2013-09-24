#include "stdafx.h"
#include "Locatable2D.h"

Locatable2D::Locatable2D()
	: x_(0), y_(0)
{
}

Locatable2D::Locatable2D( unsigned int x, unsigned int y )
	: x_(x), y_(y)
{

}

Locatable2D::Locatable2D( const Locatable2D& other )
	: x_(other.x_), y_(other.y_)
{
}

void Locatable2D::SetPos( unsigned int x, unsigned int y )
{
	x_ = x;
	y_ = y;
}

void Locatable2D::SetX( unsigned int x )
{
	x_= x;
}

void Locatable2D::SetY( unsigned int y )
{
	y_ = y;
}

void Locatable2D::GetPos( unsigned int& x, unsigned int& y ) const
{
	x = x_;
	y = y_;
}

unsigned int Locatable2D::GetX() const
{
	return x_;
}

unsigned int Locatable2D::GetY() const
{
	return y_;
}

bool Locatable2D::Intersects( const Locatable2D& other ) const
{
	return ( GetX() == other.GetX() ) && ( GetY() == other.GetY() );
}

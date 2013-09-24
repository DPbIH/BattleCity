#include "stdafx.h"
#include "Coordinates.h"

Coordinates::Coordinates()
	: X(0), Y(0)
{
}

Coordinates::Coordinates( size_t x, size_t y )
	: X(x), Y(y)
{
}

Coordinates::Coordinates( const Coordinates& other )
	: X(other.X), Y(other.Y)
{
}

Coordinates& Coordinates::operator=( const Coordinates& other )
{
	X = other.X;
	Y = other.Y;

	return *this;
}

Coordinates& Coordinates::operator+( const Coordinates& other )
{
	X += other.X;
	Y += other.Y;

	return *this;
}

Coordinates& Coordinates::operator-( const Coordinates& other )
{
	assert( (X >= other.X) && (Y >= other.Y) );

	X = ( X < other.X ) ? 0 : X - other.X;
	Y = ( Y < other.Y ) ? 0 : Y - other.Y;

	return *this;
}

bool operator==( const Coordinates& lhs, const Coordinates& rhs )
{
	return ( lhs.X == rhs.X ) && ( lhs.Y == rhs.Y );
}
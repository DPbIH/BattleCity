#pragma once

#include "Tank.h"
#include <boost/shared_ptr.hpp>

class Player
{
public:
	typedef boost::shared_ptr<Player> Ptr;

	void UseVehicle( const Tank::Ptr& tank )
	{
		vehicle_ = tank;
	}

	Tank::Ptr Vehicle()
	{
		return vehicle_;
	}

	size_t Scores();
	bool IsDead();


private:
	Tank::Ptr vehicle_;

};
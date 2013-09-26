#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

class GameScreen
	: boost::noncopyable
{
public:
	typedef boost::shared_ptr<GameScreen> Ptr;
	virtual void Draw() = 0;
};
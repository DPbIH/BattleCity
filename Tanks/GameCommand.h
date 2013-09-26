#pragma once

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

class Game;

class GameCommand
	: boost::noncopyable
{
public:
	typedef boost::shared_ptr<GameCommand> Ptr;

	GameCommand( Game* game );
	virtual ~GameCommand() = 0;
	virtual void Execute() = 0;

protected:
	Game* game_;

};
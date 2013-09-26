#pragma once

#include "GameCommand.h"
#include "DummyCommand.h"
#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

class Game;

class GameCommandsFactory
	: boost::noncopyable
{
public:
	typedef boost::shared_ptr<GameCommandsFactory> Ptr;

	GameCommandsFactory( Game* game ) : game_(game) { assert(game_); }
	virtual ~GameCommandsFactory() = 0 {}
	virtual GameCommand::Ptr OnKeyEscape() { return GameCommand::Ptr( new DummyCommand(game_) ); }
	virtual GameCommand::Ptr OnKeyEnter() { return GameCommand::Ptr( new DummyCommand(game_) ); }
	virtual GameCommand::Ptr OnKeySpace() { return GameCommand::Ptr( new DummyCommand(game_) ); }
	virtual GameCommand::Ptr OnKeyArrowDown() { return GameCommand::Ptr( new DummyCommand(game_) ); }
	virtual GameCommand::Ptr OnKeyArrowUp() { return GameCommand::Ptr( new DummyCommand(game_) ); }
	virtual GameCommand::Ptr OnKeyArrowLeft() { return GameCommand::Ptr( new DummyCommand(game_) ); }
	virtual GameCommand::Ptr OnKeyArrowRight() { return GameCommand::Ptr( new DummyCommand(game_) ); }

protected:
	Game* game_;

};
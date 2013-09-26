#include "stdafx.h"
#include "Game.h"
#include "GameState.h"

Game::Game()
	: evtListener_( new KeyboardEventsListener )
{
	evtListener_->Start();
}

void Game::ShowMenu()
{
	SetCurrentState( GameMenu );
	Start();
}

void Game::Start()
{
	currentState_->Start();
}

void Game::Stop()
{
	currentState_->Stop();
}

void Game::Pause()
{
	currentState_->Pause();
}

void Game::Resume()
{
	currentState_->Resume();
}

void Game::PushState( StateName name, GameState::Ptr state )
{
	gameStates_[name] = state;
}

void Game::SetCurrentState( StateName name )
{
	ChangeState( GetState( name ) );
}

GameState::Ptr Game::GetState( StateName name )
{
	return gameStates_.at(name);
}

void Game::InitStatesMap()
{
}

void Game::ChangeState( GameState::Ptr nextState )
{
	assert( nextState );

	if( currentState_ )
	{
		currentState_->OnLeave();
	}

	currentState_ = nextState;
	currentState_->OnEnter();
}
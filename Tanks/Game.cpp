#include "stdafx.h"
#include "Game.h"
#include "GameState.h"
#include "LevelMapFileParser.h"
#include "LevelBuilder.h"
#include "GraphicObjectsfactory.h"

const char* mapfile = "d:\\map.txt";

Game::Game()
	: paused_(false)
	, running_(false)
{
}

void Game::Init()
{
	StartKeyboardListener();
}

void Game::StartKeyboardListener()
{
	evtListener_.reset( new KeyboardEventsListener );
	evtListener_->Start();
}

void Game::LoadRandomLevel()
{
	GraphicObjectsFactory::Ptr factory( new GraphicObjectsFactory );
	LevelBuilder::Ptr builder( new LevelBuilder( factory ) );
	LevelMapFileParser parser( builder );
	parser.Parse( mapfile );
	currentLevel_ = builder->GetLevel();
}

void Game::Run()
{
	running_ = true;

	while( running_ )
	{
		Update();
		Sleep(17);
	}
}

void Game::Update()
{
	currentState_->Update();
}

void Game::Pause()
{
	paused_ = ! paused_;
}

void Game::Stop()
{
	running_ = false;
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

Player::Ptr Game::Player()
{
	return currentLevel_->Player();
}
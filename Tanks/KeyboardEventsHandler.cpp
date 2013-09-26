#include "stdafx.h"
#include "Tank.h"
#include "PublisherBase.h"
#include "KeyboardEventsHandler.h"


KeyboardEventsHandler::KeyboardEventsHandler( const KeyboardEventsListener::Ptr& evtListener,
	const GameCommandsFactory::Ptr& factory )
	: evtListener_(evtListener)
	, cmdFactory_( factory )
	, isStarted_(false)
{
	assert( evtListener_ );
	assert( cmdFactory_ );
}

KeyboardEventsHandler::~KeyboardEventsHandler()
{
	Stop();
}

void KeyboardEventsHandler::Start()
{
	if( ! isStarted_ )
	{
		evtListener_->Subscribe( this );
		isStarted_ = true;
	}
}

void KeyboardEventsHandler::Stop()
{
	if( isStarted_ )
	{
		evtListener_->Unsubscribe( this );
		isStarted_ = false;
	}
}

void KeyboardEventsHandler::Update( PublisherBase* publisher )
{
	if( evtListener_.get() != publisher )
	{
		return;
	}

	switch( evtListener_->CurrentEventRecord().wVirtualKeyCode )
	{
	case VK_LEFT:
		cmdFactory_->OnKeyArrowLeft()->Execute();
		OnKeyLeftArrow();
		break;

	case VK_RIGHT:
		cmdFactory_->OnKeyArrowRight()->Execute();
		OnKeyRightArrow();
		break;

	case VK_UP:
		cmdFactory_->OnKeyArrowUp()->Execute();
		OnKeyUpArrow();
		break;

	case VK_DOWN:
		cmdFactory_->OnKeyArrowDown()->Execute();
		OnKeyDownArrow();
		break;

	case VK_SPACE:
		cmdFactory_->OnKeySpace()->Execute();
		OnKeySpace();
		break;

	case VK_ESCAPE:
		cmdFactory_->OnKeyEscape()->Execute();
		break;

	case VK_RETURN:
		cmdFactory_->OnKeyEnter()->Execute();
		break;
	}
}

void KeyboardEventsHandler::SetTank( Tank* go )
{
	go_ = go;
}

void KeyboardEventsHandler::OnKeyDownArrow()
{
	go_->Move(1, GlobalDeclarations::South);
}

void KeyboardEventsHandler::OnKeyUpArrow()
{
	go_->Move(1, GlobalDeclarations::North);
}

void KeyboardEventsHandler::OnKeyLeftArrow()
{
	go_->Move(1, GlobalDeclarations::West);
}

void KeyboardEventsHandler::OnKeyRightArrow()
{
	go_->Move(1, GlobalDeclarations::East);
}

void KeyboardEventsHandler::OnKeySpace()
{
	go_->Fire();
}

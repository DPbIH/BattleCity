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
		break;

	case VK_RIGHT:
		cmdFactory_->OnKeyArrowRight()->Execute();
		break;

	case VK_UP:
		cmdFactory_->OnKeyArrowUp()->Execute();
		break;

	case VK_DOWN:
		cmdFactory_->OnKeyArrowDown()->Execute();
		break;

	case VK_SPACE:
		cmdFactory_->OnKeySpace()->Execute();
		break;

	case VK_ESCAPE:
		cmdFactory_->OnKeyEscape()->Execute();
		break;

	case VK_RETURN:
		cmdFactory_->OnKeyEnter()->Execute();
		break;
	}
}

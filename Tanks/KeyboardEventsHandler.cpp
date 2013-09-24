#include "stdafx.h"
#include "Tank.h"
#include "PublisherBase.h"
#include "KeyboardEventsHandler.h"


KeyboardEventsHandler::KeyboardEventsHandler( const KeyboardEventsListener::Ptr& evtListener )
	: evtListener_(evtListener)
{
	evtListener_->Subscribe( this );
}

KeyboardEventsHandler::~KeyboardEventsHandler()
{
	// evtListener_->Unsubscribe( this );
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
		OnKeyLeftArrow();
		break;

	case VK_RIGHT:
		OnKeyRightArrow();
		break;

	case VK_UP:
		OnKeyUpArrow();
		break;

	case VK_DOWN:
		OnKeyDownArrow();
		break;

	case VK_SPACE:
		OnKeySpace();
		break;
	}
}

void KeyboardEventsHandler::SetTank( Tank* go )
{
	go_ = go;
}

void KeyboardEventsHandler::OnKeyDownArrow()
{
	go_->Move(1, South);
}

void KeyboardEventsHandler::OnKeyUpArrow()
{
	go_->Move(1, North);
}

void KeyboardEventsHandler::OnKeyLeftArrow()
{
	go_->Move(1, West);
}

void KeyboardEventsHandler::OnKeyRightArrow()
{
	go_->Move(1, East);
}

void KeyboardEventsHandler::OnKeySpace()
{
	go_->Fire();
}

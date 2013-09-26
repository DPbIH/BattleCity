#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "SubscriberBase.h"
#include "KeyboardEventsListener.h"
#include "GameCommandsFactory.h"

class Tank;

class KeyboardEventsHandler
	: public SubscriberBase
	, boost::noncopyable
{
public:
	typedef boost::shared_ptr<KeyboardEventsHandler> Ptr;

	KeyboardEventsHandler( const KeyboardEventsListener::Ptr& evtListener,
		const GameCommandsFactory::Ptr& factory );
	~KeyboardEventsHandler();
	void Start();
	void Stop();
	void Update( PublisherBase* publisher );
	void SetTank( Tank* go );

private:
	void OnKeyDownArrow();
	void OnKeyUpArrow();
	void OnKeyLeftArrow();
	void OnKeyRightArrow();
	void OnKeySpace();

	KeyboardEventsListener::Ptr evtListener_;
	Tank* go_;

	bool isStarted_;

	GameCommandsFactory::Ptr cmdFactory_;

};
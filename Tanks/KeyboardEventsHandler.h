#pragma once

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "SubscriberBase.h"
#include "KeyboardEventsListener.h"

class Tank;

class KeyboardEventsHandler
	: public SubscriberBase
	, boost::noncopyable
{
public:
	typedef boost::shared_ptr<KeyboardEventsHandler> Ptr;

	KeyboardEventsHandler( const KeyboardEventsListener::Ptr& evtListener );
	~KeyboardEventsHandler();
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

};
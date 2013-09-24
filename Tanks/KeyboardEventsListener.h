#pragma once

#include <windows.h>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include "PublisherBase.h"

class KeyboardEventsListener
	: public PublisherBase
	, boost::noncopyable
{
public:
	typedef boost::shared_ptr<KeyboardEventsListener> Ptr;

	KeyboardEventsListener();
	~KeyboardEventsListener();
	void Start();
	void Stop();
	const KEY_EVENT_RECORD& CurrentEventRecord();

private:
	void LaunchListeningThread();
	void InterruptListeningThread();
	void ListenerThreadProc();

	boost::thread listeningThread_;
	bool isStarted_;
	KEY_EVENT_RECORD currEvt_;
};
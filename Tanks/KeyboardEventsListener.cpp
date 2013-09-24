#include "stdafx.h"
#include <stdio.h>
#include "KeyboardEventsListener.h"

KeyboardEventsListener::KeyboardEventsListener()
: isStarted_(false)
{
}

KeyboardEventsListener::~KeyboardEventsListener()
{
	Stop();
}

void KeyboardEventsListener::Start()
{
	if( isStarted_ )
	{
		return;
	}

	LaunchListeningThread();
	isStarted_ = true;
}

void KeyboardEventsListener::Stop()
{
	InterruptListeningThread();
	isStarted_ = false;
}

void KeyboardEventsListener::LaunchListeningThread()
{
	listeningThread_ = boost::thread(&KeyboardEventsListener::ListenerThreadProc, this);
}

void KeyboardEventsListener::InterruptListeningThread()
{
	listeningThread_.interrupt();
}

void KeyboardEventsListener::ListenerThreadProc()
{
	DWORD cNumRead;
	INPUT_RECORD irInBuf[128];
	int counter=0;

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	while(true)
	{
		if ( ! ReadConsoleInput(
			hStdin,      // input buffer handle
			irInBuf,     // buffer to read into
			128,         // size of read buffer
			&cNumRead) ) // number of records read
		{
			break;
		}

		for (DWORD i = 0; i < cNumRead; i++)
		{
			INPUT_RECORD irec = irInBuf[i];
			if( ( KEY_EVENT == irec.EventType ) && irec.Event.KeyEvent.bKeyDown )
			{
				currEvt_ = irec.Event.KeyEvent;
				Notify();
			}
		}
	}
}

const KEY_EVENT_RECORD& KeyboardEventsListener::CurrentEventRecord()
{
	return currEvt_;
}

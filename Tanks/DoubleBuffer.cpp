#include "stdafx.h"
#include "DoubleBuffer.h"

ConsoleBuffer::ConsoleBuffer(HANDLE h)
	: hCon_(h)
{
}

ConsoleBuffer::~ConsoleBuffer()
{
	CloseHandle( hCon_ );
}

void ConsoleBuffer::SetActive()
{
	assert( SetConsoleActiveScreenBuffer( hCon_ ) );
}

void ConsoleBuffer::Write( const std::string& str, COORD coord, WORD attribs )
{
	DWORD written;
	SetConsoleCursorPosition(hCon_, coord);
	assert( SetConsoleCursorPosition(hCon_, coord) );
	assert( SetConsoleTextAttribute(hCon_, attribs) );
	assert( WriteConsoleA(hCon_, str.c_str(), str.length(), &written, NULL) );
}

void ConsoleBuffer::Cleanup()
{
	COORD coordScreen = { 0, 0 };
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	assert(GetConsoleScreenBufferInfo( hCon_, &csbi ) );
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	CHAR_INFO* consoleBuffer = new CHAR_INFO[dwConSize];
	for (int y = 0; y < csbi.dwSize.Y; ++y)
	{
		for (int x = 0; x < csbi.dwSize.X; ++x)
		{
			consoleBuffer[x + csbi.dwSize.X * y].Char.AsciiChar = ' ';
			consoleBuffer[x + csbi.dwSize.X * y].Attributes = csbi.wAttributes;
		}
	}

	COORD charBufSize = { csbi.dwSize.X, csbi.dwSize.Y };
	COORD characterPos = { 0, 0 };
	SMALL_RECT writeArea = { 0, 0, csbi.dwSize.X - 1, csbi.dwSize.Y - 1 };

	assert(WriteConsoleOutputA(hCon_, consoleBuffer, charBufSize, characterPos, &writeArea) );

	delete[] consoleBuffer;
}


DoubleConsoleBuffer::DoubleConsoleBuffer()
{
	InitBuffers();
}

void DoubleConsoleBuffer::InitBuffers()
{
	buf1st_.reset( new ConsoleBuffer( CreateConsoleBuffer() ) );
	buf2nd_.reset( new ConsoleBuffer( CreateConsoleBuffer() ) );
	buf1st_->SetActive();
	firstIsActive_ = true;
}

void ResizeConsole( HANDLE hConsole, SHORT xSize, SHORT ySize ) {
	CONSOLE_SCREEN_BUFFER_INFO csbi; // Hold Current Console Buffer Info
	SMALL_RECT srWindowRect;         // Hold the New Console Size
	COORD coordScreen;

	assert(GetConsoleScreenBufferInfo( hConsole, &csbi ));

	// Get the Largest Size we can size the Console Window to
	coordScreen = GetLargestConsoleWindowSize( hConsole );

	// Define the New Console Window Size and Scroll Position
	srWindowRect.Right  = (SHORT)(min(xSize, coordScreen.X) - 1);
	srWindowRect.Bottom = (SHORT)(min(ySize, coordScreen.Y) - 1);
	srWindowRect.Left   = srWindowRect.Top = (SHORT)0;

	// Define the New Console Buffer Size
	coordScreen.X = xSize;
	coordScreen.Y = ySize;

	// If the Current Buffer is Larger than what we want, Resize the
	// Console Window First, then the Buffer
	if( (DWORD)csbi.dwSize.X * csbi.dwSize.Y > (DWORD) xSize * ySize)
	{
		assert(SetConsoleWindowInfo( hConsole, TRUE, &srWindowRect ));
		assert(SetConsoleScreenBufferSize( hConsole, coordScreen ));
	}

	// If the Current Buffer is Smaller than what we want, Resize the
	// Buffer First, then the Console Window
	if( (DWORD)csbi.dwSize.X * csbi.dwSize.Y < (DWORD) xSize * ySize )
	{
		assert(SetConsoleScreenBufferSize( hConsole, coordScreen ));
		assert(SetConsoleWindowInfo( hConsole, TRUE, &srWindowRect ));
	}
}

HANDLE DoubleConsoleBuffer::CreateConsoleBuffer()
{
	HANDLE buf = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
	if( buf != INVALID_HANDLE_VALUE )
	{
		CONSOLE_CURSOR_INFO curinf = { 1, FALSE };
		assert(SetConsoleCursorInfo(buf, &curinf));
		ResizeConsole(buf, 100, 50);
	}

	return buf;
}

void DoubleConsoleBuffer::FlipBuffers()
{
	if( firstIsActive_ )
	{
		buf2nd_->SetActive();
	}
	else
	{
		buf1st_->SetActive();
	}

	firstIsActive_ = ! firstIsActive_;
}

void DoubleConsoleBuffer::Write( const std::string& str, COORD coord, WORD attribs,  BufferType targetBuf )
{
	if ( targetBuf == ActiveBuffer )
	{
		if( firstIsActive_ )
		{
			buf1st_->Write( str, coord, attribs );
		}
		else
		{
			buf2nd_->Write( str, coord, attribs );
		}
	}
	else
	{
		if( firstIsActive_ )
		{
			buf2nd_->Write( str, coord, attribs );
		}
		else
		{
			buf1st_->Write( str, coord, attribs );
		}
	}
}

void DoubleConsoleBuffer::CleanupBuffer( BufferType targetBuf )
{
	if ( targetBuf == ActiveBuffer )
	{
		if( firstIsActive_ )
		{
			buf1st_->Cleanup();
		}
		else
		{
			buf2nd_->Cleanup();
		}
	}
	else
	{
		if( firstIsActive_ )
		{
			buf2nd_->Cleanup();
		}
		else
		{
			buf1st_->Cleanup();
		}
	}
}

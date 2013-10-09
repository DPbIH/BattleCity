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
	: width_(100)
	, height_(50)
{
	fontSize_.X = fontSize_.Y = 8;

	InitBuffers();
}

void DoubleConsoleBuffer::InitBuffers()
{
	buf1st_.reset( new ConsoleBuffer( CreateConsoleBuffer() ) );
	buf2nd_.reset( new ConsoleBuffer( CreateConsoleBuffer() ) );
	buf1st_->SetActive();
	firstIsActive_ = true;
}

HANDLE DoubleConsoleBuffer::CreateConsoleBuffer()
{
	HANDLE buf = CreateConsoleScreenBuffer( GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL );
	if( buf != INVALID_HANDLE_VALUE )
	{
		//SetFontSize( buf, fontSize_ );
		HideCursor( buf );
		ResizeConsole( buf, width_, height_ );
	}

	return buf;
}

void DoubleConsoleBuffer::ResizeConsole( HANDLE hConsole, size_t xSize, size_t ySize )
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT srWindowRect;
	COORD coordScreen;

	assert(GetConsoleScreenBufferInfo( hConsole, &csbi ));

	coordScreen = GetLargestConsoleWindowSize( hConsole );

	srWindowRect.Right  = min((SHORT)xSize, coordScreen.X) - 1;
	srWindowRect.Bottom = min((SHORT)ySize, coordScreen.Y) - 1;
	srWindowRect.Left   = srWindowRect.Top = (SHORT)0;

	coordScreen.X = xSize;
	coordScreen.Y = ySize;

	if( (DWORD)csbi.dwSize.X * csbi.dwSize.Y > (DWORD) xSize * ySize)
	{
		assert(SetConsoleWindowInfo( hConsole, TRUE, &srWindowRect ));
		assert(SetConsoleScreenBufferSize( hConsole, coordScreen ));
	}

	if( (DWORD)csbi.dwSize.X * csbi.dwSize.Y < (DWORD) xSize * ySize )
	{
		assert(SetConsoleScreenBufferSize( hConsole, coordScreen ));
		assert(SetConsoleWindowInfo( hConsole, TRUE, &srWindowRect ));
	}
}

void DoubleConsoleBuffer::SetFontSize( HANDLE hConsole, COORD fontSize )
{
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

	assert(GetCurrentConsoleFontEx( hConsole, false, &cfi ));

	cfi.dwFontSize.X = fontSize.X;
	cfi.dwFontSize.Y = fontSize.Y;

	assert(SetCurrentConsoleFontEx( hConsole, false, &cfi ));
}

void DoubleConsoleBuffer::HideCursor( HANDLE hConsole )
{
	CONSOLE_CURSOR_INFO curinf = { 1, FALSE };
	assert(SetConsoleCursorInfo(hConsole, &curinf));
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

DoubleConsoleBuffer::BufferPtr DoubleConsoleBuffer::GetTargetBuf( BufferType bufType )
{
	bool targetIs1stBuf = ( (bufType == ActiveBuffer) && firstIsActive_ ) ||
		( (bufType == BackgroundBuffer) && ! firstIsActive_ );

	return targetIs1stBuf ? buf1st_ : buf2nd_;
}

void DoubleConsoleBuffer::Write( const std::string& str, COORD coord, WORD attribs,  BufferType targetBuf )
{
	GetTargetBuf( targetBuf )->Write( str, coord, attribs );
}

void DoubleConsoleBuffer::CleanupBuffer( BufferType targetBuf )
{
	GetTargetBuf( targetBuf )->Cleanup();
}

size_t DoubleConsoleBuffer::Height()
{
	return height_;
}

size_t DoubleConsoleBuffer::Width()
{
	return width_;
}

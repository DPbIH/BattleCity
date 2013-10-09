#pragma once

#include "Singleton.h"

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <string>

class ConsoleBuffer
	: boost::noncopyable
{
public:
	ConsoleBuffer(HANDLE h);
	~ConsoleBuffer();
	void SetActive();
	void Write( const std::string& str, COORD coord, WORD attribs );
	void Cleanup();

private:
	HANDLE hCon_;

};


class DoubleConsoleBuffer
	: public Singleton<DoubleConsoleBuffer>
{
public:
	enum BufferType { ActiveBuffer, BackgroundBuffer };

	DoubleConsoleBuffer();
	void FlipBuffers();
	void Write( const std::string& str, COORD coord, WORD attribs,  BufferType targetBuf = ActiveBuffer );
	void CleanupBuffer( BufferType targetBuf = ActiveBuffer );
	size_t Height();
	size_t Width();

private:
	typedef boost::shared_ptr<ConsoleBuffer> BufferPtr;

	void InitBuffers();
	HANDLE CreateConsoleBuffer();
	void ResizeConsole( HANDLE hConsole, size_t xSize, size_t ySize );
	void SetFontSize( HANDLE hConsole, COORD fontSize );
	void HideCursor( HANDLE hConsole );
	BufferPtr GetTargetBuf( BufferType bufType );

	BufferPtr buf1st_;
	BufferPtr buf2nd_;

	bool firstIsActive_;
	size_t width_, height_;
	COORD fontSize_;
};

inline DoubleConsoleBuffer& Console()
{
	return DoubleConsoleBuffer::Instance();
}
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

private:
	void InitBuffers();
	HANDLE CreateConsoleBuffer();

	typedef boost::shared_ptr<ConsoleBuffer> BufferPtr;

	BufferPtr buf1st_;
	BufferPtr buf2nd_;

	bool firstIsActive_;
};

inline DoubleConsoleBuffer& Console()
{
	return DoubleConsoleBuffer::Instance();
}
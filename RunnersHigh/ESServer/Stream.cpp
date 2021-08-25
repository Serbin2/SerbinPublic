#include "Stream.h"

void Stream::CleanUp()
{
	ZeroMemory(m_buf, MAX_STREAM_SIZE);
	m_position = 0;
	m_offset = 0;
}

Stream::Stream()
	:m_position(0), m_offset(0)
{
	ZeroMemory(m_buf, MAX_STREAM_SIZE);
}

Stream::~Stream()
{
	CleanUp();
}
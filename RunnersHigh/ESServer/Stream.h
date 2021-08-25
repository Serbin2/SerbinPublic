#pragma once

#include <vector>
#include <string>

#include "Define.h"


// 스트림은 단지 버퍼의 통로라고 생각합니다. 받은(보낼) 데이터는 패킷 클래스에서의 해석을 통하여
// 제대로된 데이터를 만들어냅니다.


const int COBJECT_PACKET_SIZE = sizeof(unsigned int) + sizeof(bool) + (sizeof(float) * 5);

class Stream
{
	// 스트림 버퍼를 읽을 때 사용함
	unsigned int m_position;
	// 스트림 버퍼있는 데이터 길이
	unsigned int m_offset;
	char m_buf[MAX_STREAM_SIZE];


	bool CheckWrite(unsigned int len)
	{
		// 현재길이 + 쓰기길이 : 전체길이 비교
		if ((unsigned long long)m_offset + len > sizeof(m_buf))
		{
			/// TODO : Log 
			return false;
		}
		return true;
	};

	bool CheckRead(unsigned int len)
	{
		// 읽은 위치 + 읽을 길이 : 현재 길이 비교
		if (m_position + len > m_offset)
		{
			/// TODO : Log
			return false;
		}
		return true;
	}

public:
	Stream();
	~Stream();

	void CleanUp();
	char* GetBuf() { return m_buf; }
	bool IsBufEmpty() { return(m_offset <= 0); }
	unsigned int size() { return m_offset; }

	static void StreamCpyBuffer(const Stream& stream, char* Rowbuffer)
	{
		memcpy_s(Rowbuffer, MAX_STREAM_SIZE, stream.m_buf, stream.m_offset);
	}

	static void BufferCpyStream(Stream& stream, const char* RowBuffer, const unsigned size)
	{
		stream.m_offset = size;
		memcpy_s(stream.m_buf, MAX_STREAM_SIZE, RowBuffer, size);
	}

	template <typename T>
	void WriteBuffer(T& value);

	template <typename T>
	void WriteBuffer(T* value);

	template <typename T>
	void WriteBuffer(std::vector<T>& value);

	//template <typename T>
	//void WriteBuffer(CObject& obj);

	template <typename T>
	void ReadBuffer(T& target);

	template <typename T>
	void ReadBuffer(T* value);

	template <typename T>
	void ReadBuffer(std::vector<T>& value);

	template <typename T>
	void operator << (T& target);

	template <typename T>
	void operator >> (T& target);
};

template<typename T>
inline void Stream::WriteBuffer(T& value)
{
	unsigned int size = sizeof(T);

	if (!CheckWrite(size))
		return;

	memcpy_s(m_buf + m_offset, MAX_STREAM_SIZE - m_offset, &value, size);
	m_offset += size;
}

template<>
inline void Stream::WriteBuffer(std::string& value)
{
	unsigned int size = value.size();

	if (!CheckWrite(sizeof(int)))
		return;

	WriteBuffer(size);

	if (!CheckWrite(size * sizeof(char)))
		return;

	for (unsigned int i = 0; i < size; i++)
	{
		WriteBuffer(value[i]);
	}
}

//template<>
//inline void Stream::WriteBuffer(CObject& value)
//{
//	unsigned int size = COBJECT_PACKET_SIZE;
//
//	if (!CheckWrite(size))
//		return;
//
//	int id = value.GetID();
//	float radius = value.GetRadius();
//	bool collision = value.GetIsCollision();
//	int velocity = value.GetSpeed();
//	Vector2 goal = value.GetGoal();
//	Vector2 position = value.GetPosition();
//
//	WriteBuffer(id);
//	WriteBuffer(radius);
//	WriteBuffer(collision);
//	WriteBuffer(velocity);
//	WriteBuffer(position.x);
//	WriteBuffer(position.y);
//	WriteBuffer(goal.x);
//	WriteBuffer(goal.y);
//}

template<typename T>
inline void Stream::WriteBuffer(T* value)
{
	WriteBuffer(*value);
}

template<typename T>
inline void Stream::WriteBuffer(std::vector<T>& value)
{
	unsigned int size = value.size();

	if (!CheckWrite(sizeof(int)))
		return;

	WriteBuffer(size);

	if (!CheckWrite(size * sizeof(T)))
		return;

	for (int i = 0; i < size; i++)
	{
		WriteBuffer(value[i]);
	}
}

//template<>
//inline void Stream::WriteBuffer(std::vector<CObject*>& value)
//{
//	unsigned int size = value.size();
//
//	if (!CheckWrite(sizeof(int)))
//		return;
//
//	WriteBuffer(size);
//
//	if (!CheckWrite(size * COBJECT_PACKET_SIZE))
//		return;
//
//	for (int i = 0; i < size; i++)
//	{
//		WriteBuffer(value[i]);
//	}
//}

template<typename T>
inline void Stream::ReadBuffer(T& target)
{
	unsigned int size = sizeof(target);

	if (!CheckRead(size))
		return;

	memcpy_s(&target, size, m_buf + m_position, size);
	m_position += size;
}

//template<>
//inline void Stream::ReadBuffer(CObject& obj)
//{
//	unsigned int size = COBJECT_PACKET_SIZE;
//
//	if (!CheckRead(size))
//		return;
//
//	int id = -1;
//	int velocity = 0;
//	bool collision = false;
//	float radius, px, py, gx, gy;
//
//	radius = px = py = gx = gy = 0.f;
//
//	ReadBuffer(id);
//	ReadBuffer(radius);
//	ReadBuffer(collision);
//	ReadBuffer(velocity);
//	ReadBuffer(px);
//	ReadBuffer(py);
//	ReadBuffer(gx);
//	ReadBuffer(gy);
//
//	obj.SetID(id);
//	obj.SetIsCoilision(collision);
//	obj.SetSpeed(velocity);
//	obj.SetPosition(Vector2(px, py));
//	obj.SetGoal(gx, gy);
//	obj.SetRadius(radius);
//}

template<>
inline void Stream::ReadBuffer(std::string& value)
{
	unsigned int size = 0;

	if (!CheckRead(sizeof(int)))
		return;

	ReadBuffer(size);

	if (!CheckRead(size * sizeof(char)))
		return;

	char OneChar;
	for (unsigned int i = 0; i < size; i++)
	{
		ReadBuffer(OneChar);
		value += OneChar;
	}
}

template<typename T>
inline void Stream::ReadBuffer(T* value)
{
	ReadBuffer(*value);
}


template<typename T>
inline void Stream::ReadBuffer(std::vector<T>& value)
{
	unsigned int size = 0;

	if (!CheckRead(sizeof(int)))
		return;

	ReadBuffer(size);

	if (!CheckRead(size * sizeof(T)))
		return;

	T OneData;
	for (int i = 0; i < size; i++)
	{
		ReadBuffer(OneData);
		value.push_back(OneData);
	}
}

//template<>
//inline void Stream::ReadBuffer(std::vector<CObject*>& value)
//{
//	int size = 0;
//
//	if (!CheckRead(sizeof(int)))
//		return;
//
//	ReadBuffer(size);
//
//	if (!CheckRead(size * sizeof(COBJECT_PACKET_SIZE)))
//		return;
//
//	for (int i = 0; i < size; i++)
//	{
//		ReadBuffer(value[i]);
//	}
//}

template<typename T>
inline void Stream::operator<<(T& target)
{
	WriteBuffer(target);
}

template<typename T>
inline void Stream::operator>>(T& target)
{
	ReadBuffer(target);
}

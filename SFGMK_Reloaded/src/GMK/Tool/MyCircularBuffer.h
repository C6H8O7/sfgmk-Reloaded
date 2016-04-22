#ifndef MYCIRCULARBUFFER_H
#define MYCIRCULARBUFFER_H

#include "stdafx.h"

template <typename T, UINT32 SIZE, BOOL MULTI_PRODUCER = FALSE, BOOL MULTI_CONSUMER = FALSE>
class MyCircularBuffer
{
public:

	MyCircularBuffer();
	~MyCircularBuffer();

	T* data;

	inline UINT32 getSize();

	inline BOOL isEmpty()
	{
		return writeIndex == readIndex;
	}

	inline void forward(UINT32& _cursor);

	inline void write(T& _object);
	inline bool read(T& _pobject);

protected:

	UINT32 size;
	UINT32 writeIndex, readIndex;

	MySemaphore* semaphoreWrite;
	MySemaphore* semaphoreRead;

	MyMutex mutexWrite, mutexRead;
};

template <typename T, UINT32 SIZE, BOOL MULTI_PRODUCER = FALSE, BOOL MULTI_CONSUMER = FALSE>
MyCircularBuffer<T, SIZE, MULTI_PRODUCER, MULTI_CONSUMER>::MyCircularBuffer()
{
	size = SIZE;

	data = new T[size];

	semaphoreWrite = new MySemaphore(SIZE, SIZE);
	semaphoreRead = new MySemaphore(0, SIZE);

	writeIndex = readIndex = 0;
}

template <typename T, UINT32 SIZE, BOOL MULTI_PRODUCER = FALSE, BOOL MULTI_CONSUMER = FALSE>
MyCircularBuffer<T, SIZE, MULTI_PRODUCER, MULTI_CONSUMER>::~MyCircularBuffer()
{
	delete[] data;

	delete semaphoreWrite;
	delete semaphoreRead;
}

template <typename T, UINT32 SIZE, BOOL MULTI_PRODUCER = FALSE, BOOL MULTI_CONSUMER = FALSE>
UINT32 MyCircularBuffer<T, SIZE, MULTI_PRODUCER, MULTI_CONSUMER>::getSize()
{
	return size;
}

template <typename T, UINT32 SIZE, BOOL MULTI_PRODUCER = FALSE, BOOL MULTI_CONSUMER = FALSE>
void MyCircularBuffer<T, SIZE, MULTI_PRODUCER, MULTI_CONSUMER>::forward(UINT32& _cursor)
{
	_cursor = (++_cursor) % SIZE;
}

template <typename T, UINT32 SIZE, BOOL MULTI_PRODUCER = FALSE, BOOL MULTI_CONSUMER = FALSE>
void MyCircularBuffer<T, SIZE, MULTI_PRODUCER, MULTI_CONSUMER>::write(T& _object)
{
	semaphoreWrite->P();
	if(MULTI_PRODUCER) mutexWrite.P();

		data[writeIndex % SIZE] = _object;
		writeIndex = (++writeIndex) % SIZE;

	if(MULTI_PRODUCER) mutexRead.V();
	semaphoreRead->V();
}

template <typename T, UINT32 SIZE, BOOL MULTI_PRODUCER = FALSE, BOOL MULTI_CONSUMER = FALSE>
bool MyCircularBuffer<T, SIZE, MULTI_PRODUCER, MULTI_CONSUMER>::read(T& _pobject)
{
	semaphoreRead->P();
	if(MULTI_CONSUMER) mutexRead.P();

		_pobject = data[readIndex % SIZE];
		readIndex = (++readIndex) % SIZE;

	if(MULTI_CONSUMER) mutexRead.V();
	semaphoreWrite->V();

	return true;
}

#endif
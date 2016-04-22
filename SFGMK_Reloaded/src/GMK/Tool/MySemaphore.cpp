#include "stdafx.h"

MySemaphore::MySemaphore(LONG _initialCount, LONG _maxCount, LPCSTR _name)
{
	m_hSemaphore = CreateSemaphoreA(0, _initialCount, _maxCount, _name);
}

MySemaphore::~MySemaphore()
{
	CloseHandle(m_hSemaphore);
}

DWORD MySemaphore::P(DWORD _timeout)
{
	return WaitForSingleObject(m_hSemaphore, _timeout);
}

BOOL MySemaphore::V(LONG _releaseCount)
{
	return ReleaseSemaphore(m_hSemaphore, _releaseCount, 0);
}
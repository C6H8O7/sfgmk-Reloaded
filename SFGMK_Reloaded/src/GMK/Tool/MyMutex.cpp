#include "stdafx.h"

MyMutex::MyMutex(LPCSTR _name)
{
	m_hMutex = CreateMutexA(0, 0, _name);
}

MyMutex::~MyMutex()
{
	CloseHandle(m_hMutex);
}

DWORD MyMutex::P(DWORD _timeout)
{
	return WaitForSingleObject(m_hMutex, _timeout);
}

BOOL MyMutex::V()
{
	return ReleaseMutex(m_hMutex);
}
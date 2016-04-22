#ifndef MYSEMAPHORE_H
#define MYSEMAPHORE_H

#include "stdafx.h"

class MySemaphore
{
public:

	MySemaphore(LONG _initialCount = 1, LONG _maxCount = 1, LPCSTR _name = "");
	~MySemaphore();

	DWORD P(DWORD _timeout = INFINITE);
	BOOL V(LONG _releaseCount = 1);

protected:

	HANDLE m_hSemaphore;
};

#endif
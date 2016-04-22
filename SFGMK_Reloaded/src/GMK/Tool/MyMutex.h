#ifndef MYMUTEX_H
#define MYMUTEX_H

#include "stdafx.h"

class MyMutex
{
public:

	MyMutex(LPCSTR _name = "");
	~MyMutex();

	DWORD P(DWORD _timeout = INFINITE);
	BOOL V();

protected:

	HANDLE m_hMutex;
};

#endif
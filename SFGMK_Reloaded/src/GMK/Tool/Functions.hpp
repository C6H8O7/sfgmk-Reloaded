#pragma once

#include "stdafx.h"

#define SAFE_FREE(a) if( a != NULL ) { free(a); a = NULL; }
#define SAFE_DELETE(a) if( a != NULL ) { delete a; a = NULL; }

#define GMK_CLASS_PROPERTY_DEF(T, P, N, V)			T P;

#define GMK_CLASS_PROPERTY_FUNCS(T, P, N, V)		T get ## N () { return P; } \
													V set ## N ( T N ) { P = N; } \
													T * get ## N ## Ptr() { return &P; }

/*int dtAlign4(int x) 
{
	return (x + 3) & ~3; 
}*/
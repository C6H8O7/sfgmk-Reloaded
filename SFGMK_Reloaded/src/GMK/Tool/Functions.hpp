#pragma once


#define SAFE_FREE(a) if( a != NULL ) { free(a); a = NULL; }
#define SAFE_DELETE(a) if( a != NULL ) { delete a; a = NULL; }

/*int dtAlign4(int x) 
{
	return (x + 3) & ~3; 
}*/
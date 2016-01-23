#ifndef SFGMKR_DEFS_H
#define SFGMKR_DEFS_H

#define SFGMKR_MYGUI_DEBUG true
#define SFGMKR_ASSETSMANAGER_DEBUG true
#define SFGMKR_IA_DEBUG false
#define SFGMKR_SOUND_DEBUG false
#define SFGMKR_APP_DEBUG true

#define ASCII_NUMBER_GAP -48

typedef void							r_void;

typedef bool							r_bool;
								
typedef char							r_int8;
typedef short							r_int16;
typedef int								r_int32;
typedef long long						r_int64;

typedef unsigned char					r_uint8;
typedef unsigned short					r_uint16;
typedef unsigned int					r_uint32;
typedef unsigned long long				r_uint64;

typedef float							r_float;
typedef double							r_double;

typedef std::string						r_string;

#include "GMK\Math\vector2.hpp"
typedef gmk::math::vector2<r_float>		r_vector2f;
typedef gmk::math::vector2<r_int32>		r_vector2i;

typedef sf::Vector3f					r_vector3f;

#ifdef SFGMKR_ANDROID
	#define fopen_s(A,B,C) (*A) = fopen(B,C)
	#define fscanf_s fscanf
	#define sprintf_s sprintf
	#define fread_s(A,B,C,D,E) fread(A,C,D,E)
#endif

#endif
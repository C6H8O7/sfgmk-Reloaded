/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		14/12/2014
	@brief		Regroupe les constantes utiles pour les calculs math�matiques, ainsi que des fonctions
				de calculs de base.

--------------------------------------------------------------------------------------------------*/

#ifndef MATH_HPP
#define MATH_HPP

#include "stdafx.h"

namespace gmk
{
	namespace math
	{
		//Constantes
		const r_float G = -9.81f;
		#define EPSILON 0.00001f
		#define PI 3.14159265358979323846f
		#define PI_2 1.57079632679489661923f
		#define PI_4 0.785398163397448309616f
		#define PI_X_2 6.28318530718f

		#define X_UNIT_VECTOR_2D sf::Vector2f(1.0f, 0.0f)
		#define Y_UNIT_VECTOR_2D sf::Vector2f(0.0f, -1.0f)

		#define X_UNIT_VECTOR_3D sf::Vector3f(1.0f, 0.0f, 0.0f)
		#define Y_UNIT_VECTOR_3D sf::Vector2f(0.0f, -1.0f, 0.0f)
		#define Z_UNIT_VECTOR_3D sf::Vector2f(0.0f, 0.0f, 1.0f)

		//Macros
		#define ABS(A) ((A)>=(0)?(A):((-1)*(A)))
		#define RAND(MIN,MAX) ((MIN)+((rand())%((ABS(((MAX)-(MIN))))+(1)))) //Limite 32767
		#define SQUARE(a) ((a)*(a))
		#define CUBE(a) ((a)*(a)*(a))
		#define MAX(a,b) (((a) > (b)) ? (a) : (b))
		#define MIN(a,b) (((a) < (b)) ? (a) : (b))
		#define RAD_TO_DEG(a) ((a) * 57.2957795131f)
		#define DEG_TO_RAD(a) ((a) * 0.01745329251f)

		//Magic Square Root
		r_float Msqrt(const r_float& _Number);	//Une iteration
		r_float Msqrt(const r_float& _Number, const r_int32& _Iteration);	//Plusieurs it�rations (plus pr�cis), un indice 3 donne g�n�ralement un r�sultat convenable

		//Puissance / Factorielle
		r_int32 Pow(const r_int32& _Number, const r_int32& _Pow);
		r_float Pow(const r_float& _Number, const r_int32& _Pow);
		r_int32 Factorial(r_int32 _Number);

		//Distance
		template<typename T>
		r_float Calc_Distance(const T& _X1, const T& _Y1, const T& _X2, const T& _Y2)
		{
			T X = _X1 - _X2;
			T Y = _Y1 - _Y2;

			return Msqrt(X*X + Y*Y);
		}

		template<typename T>
		T Calc_DistanceSquared(const T& _X1, const T& _Y1, const T& _X2, const T& _Y2)
		{
			T X = _X1 - _X2;
			T Y = _Y1 - _Y2;

			return (X*X + Y*Y);
		}

		template<typename T>
		r_float Calc_Distance(const T& _X1, const T& _Y1, const T& _Z1, const T& _X2, const T& _Y2, const T& _Z2)
		{
			T X = _X1 - _X2;
			T Y = _Y1 - _Y2;
			T Z = _Z1 - _Z2;

			return Msqrt(X*X + Y*Y + Z*Z);
		}

		template<typename T>
		T Calc_DistanceSquared(const T& _X1, const T& _Y1, const T& _Z1, const T& _X2, const T& _Y2, const T& _Z2)
		{
			T X = _X1 - _X2;
			T Y = _Y1 - _Y2;
			T Z = _Z1 - _Z2;

			return (X*X + Y*Y + Z*Z);
		}

		sf::Vector2f Clamp_Vector(const sf::Vector2f& _vector, r_float _min, r_float _max);

		r_float Calc_Distance(const sf::Vector2f& _Element1, const sf::Vector2f& _Element2);
		r_float Calc_Distance(const sf::Vector2f& _Element1, const sf::Vector3f& _Element2);
		r_float Calc_Distance(const sf::Vector3f& _Element1, const sf::Vector3f& _Element2);
		r_float Calc_DistanceSquared(const sf::Vector2f& _Element1, const sf::Vector2f& _Element2);
		r_float Calc_DistanceSquared(const sf::Vector3f& _Element1, const sf::Vector3f& _Element2);

		//Angle
		r_float Calc_Angle(const sf::Vector2f& _VectorOne, const sf::Vector2f& _VectorTwo);

		//Vector
		sf::Vector2f Calc_Vector(const sf::Vector2f& _OriginePoint, const sf::Vector2f& _FinalPoint);
		sf::Vector3f Calc_Vector(const sf::Vector3f& _OriginePoint, const sf::Vector3f& _FinalPoint);
		sf::Vector3f Convert2dTo3d(const sf::Vector2f& _Vector2d, const r_float& _Z = 0.0f);
		sf::Vector2f Convert3dTo2d(const sf::Vector3f& _Vector3d);

		r_float DotProduct(const sf::Vector2f& _Vector1, const sf::Vector2f& _Vector2);
		r_float DotProduct(const sf::Vector3f& _Vector1, const sf::Vector3f& _Vector2);
		sf::Vector2f CrossProduct(const sf::Vector2f& _Vector1, const sf::Vector2f& _Vector2);
		sf::Vector3f CrossProduct(const sf::Vector3f& _Vector1, const sf::Vector3f& _Vector2);

		r_void RotateVector(r_vector2f& _Vector, const r_float& _Angle);

		//Norme
		r_float Calc_Norm(const sf::Vector2f& _Vector);
		r_float Calc_Norm(const sf::Vector3f& _Vector);
		r_float Calc_NormSquared(const sf::Vector2f& _Vector);
		r_float Calc_NormSquared(const sf::Vector3f& _Vector);
		sf::Vector2f Calc_UnitVector(const sf::Vector2f& _Vector);
		sf::Vector3f Calc_UnitVector(const sf::Vector3f& _Vector);

		//Physique
		r_bool ProjectionsIntersects(const r_float& _l1, const r_float& _r1, const r_float& _l2, const r_float& _r2);
		r_bool RectsIntersects(const r_float& _x1, const r_float& _y1, const r_float& _w1, const r_float& _h1, const r_float& _x2, const r_float& _y2, const r_float& _w2, const r_float& _h2);
	}
}

#endif
#include "stdafx.h"

namespace gmk
{
	namespace math
	{
		//Magic Square Root
		inline r_float Msqrt(const r_float& _Number)	//Une iteration
		{
			long i;
			r_float x2, y;
			const r_float threehalfs = 1.5F;

			x2 = _Number * 0.5F;
			y = _Number;
			i = *(long *)&y;                       // evil floating point bit level hacking
			i = 0x5f3759df - (i >> 1);               // what the fuck?
			y = *(r_float *)&i;
			y = y * (threehalfs - (x2 * y * y));

			return _Number * y;
		}

		inline r_float Msqrt(const r_float& _Number, const r_int32& _Iteration)	//Plusieurs itérations (plus précis)
		{
			long i;
			r_float x2, y;
			const r_float threehalfs = 1.5F;

			x2 = _Number * 0.5F;
			y = _Number;
			i = *(long *)&y;                       // evil floating point bit level hacking
			i = 0x5f3759df - (i >> 1);               // what the fuck?
			y = *(r_float *)&i;
			for( r_int32 j(0); j < _Iteration; j++ )
				y = y * (threehalfs - (x2 * y * y));

			return _Number * y;
		}

		//Puissance / Factorielle
		r_int32 Pow(const r_int32& _Number, const r_int32& _Pow)
		{
			r_int32 iResult = _Number;

			if( _Pow == 0 )
				return 1;

			for( r_int32 i(0); i < _Pow - 1; i++ )
				iResult *= _Number;

			return iResult;
		}

		r_float Pow(const r_float& _Number, const r_int32& _Pow)
		{
			r_float iResult = _Number;

			if( _Pow == 0 )
				return 1;

			for( r_int32 i(0); i < _Pow - 1; i++ )
				iResult *= _Number;

			return iResult;
		}

		r_int32 Factorial(r_int32 _Number)
		{
			//Factorielle 0 = 1
			if( _Number == 0 )
				return 1;

			r_int32 _Value = _Number - 1;

			while( _Value > 1 )
			{
				_Number *= _Value;
				_Value--;
			}

			return _Number;
		}

		//Distance
		sf::Vector2f Clamp_Vector(const sf::Vector2f& _vector, r_float _min, r_float _max)
		{
			r_float l = Msqrt(_vector.x * _vector.x + _vector.y * _vector.y);

			if (l < _min)
				return _vector * (_min / l);
			else if(l > _max)
				return _vector * (_max / l);

			return _vector;
		}

		r_float Calc_Distance(const sf::Vector2f& _Element1, const sf::Vector2f& _Element2)
		{
			r_float x = _Element1.x - _Element2.x;
			r_float y = _Element1.y - _Element2.y;

			return Msqrt(x*x + y*y);
		}

		r_float Calc_Distance(const sf::Vector2f& _Element1, const sf::Vector3f& _Element2)
		{
			sf::Vector2f Conversion(_Element2.x, _Element2.y);

			return Calc_Distance(_Element1, Conversion);
		}

		r_float Calc_Distance(const sf::Vector3f& _Element1, const sf::Vector3f& _Element2)
		{
			r_float x = _Element1.x - _Element2.x;
			r_float y = _Element1.y - _Element2.y;
			r_float z = _Element1.z - _Element2.z;

			return Msqrt(x*x + y*y + z*z);
		}

		r_float Calc_DistanceSquared(const sf::Vector2f& _Element1, const sf::Vector2f& _Element2)
		{
			r_float x = _Element1.x - _Element2.x;
			r_float y = _Element1.y - _Element2.y;

			return x*x + y*y;
		}

		r_float Calc_DistanceSquared(const sf::Vector3f& _Element1, const sf::Vector3f& _Element2)
		{
			r_float x = _Element1.x - _Element2.x;
			r_float y = _Element1.y - _Element2.y;
			r_float z = _Element1.z - _Element2.z;

			return x*x + y*y + z*z;
		}

		//Angle
		r_float Calc_Angle(const sf::Vector2f& _VectorOne, const sf::Vector2f& _VectorTwo)
		{
			r_float fScalarProduct = _VectorOne.x * _VectorTwo.x + _VectorOne.y * _VectorTwo.y;
			r_float fVectorOneNorm = Msqrt((_VectorOne.x * _VectorOne.x) + (_VectorOne.y * _VectorOne.y));
			r_float fVectorTwoNorm = Msqrt((_VectorTwo.x * _VectorTwo.x) + (_VectorTwo.y * _VectorTwo.y));

			return acos(fScalarProduct / (fVectorOneNorm*fVectorTwoNorm));
		}

		r_bool IsLeft(const r_vector2f& _V1, const r_vector2f& _V2)
		{
			return ((_V1.x * _V2.y - _V1.y * _V2.x) > 0.0f);
		}

		//Vector
		sf::Vector2f Calc_Vector(const sf::Vector2f& _OriginePoint, const sf::Vector2f& _FinalPoint)
		{
			return sf::Vector2f(_FinalPoint.x - _OriginePoint.x, _FinalPoint.y - _OriginePoint.y);
		}

		sf::Vector3f Calc_Vector(const sf::Vector3f& _OriginePoint, const sf::Vector3f& _FinalPoint)
		{
			return sf::Vector3f(_FinalPoint.x - _OriginePoint.x, _FinalPoint.y - _OriginePoint.y, _FinalPoint.z - _OriginePoint.z);
		}

		sf::Vector3f Convert2dTo3d(const sf::Vector2f& _Vector2d, const r_float& _Z)
		{
			return sf::Vector3f(_Vector2d.x, _Vector2d.y, _Z);
		}

		sf::Vector2f Convert3dTo2d(const sf::Vector3f& _Vector3d)
		{
			return sf::Vector2f(_Vector3d.x, _Vector3d.y);
		}

		r_float DotProduct(const sf::Vector2f& _Vector1, const sf::Vector2f& _Vector2)
		{
			return _Vector1.x * _Vector2.x + _Vector1.y * _Vector2.y;
		}

		r_float DotProduct(const sf::Vector3f& _Vector1, const sf::Vector3f& _Vector2)
		{
			return _Vector1.x * _Vector2.x + _Vector1.y * _Vector2.y + _Vector1.z * _Vector2.z;
		}

		sf::Vector2f CrossProduct(const sf::Vector2f& _Vector1, const sf::Vector2f& _Vector2)
		{
			return sf::Vector2f(_Vector1.x * _Vector2.y, _Vector2.x * _Vector1.y);
		}

		sf::Vector3f CrossProduct(const sf::Vector3f& _Vector1, const sf::Vector3f& _Vector2)
		{
			return sf::Vector3f(_Vector1.y * _Vector2.z - _Vector1.z * _Vector2.y, _Vector1.x * _Vector2.z - _Vector1.z * _Vector2.x, _Vector1.x * _Vector2.y - _Vector1.y * _Vector2.x);
		}

		r_void RotateVector(r_vector2f& _Vector, const r_float& _Angle)
		{
			r_float fLength = math::Calc_Norm(_Vector);
			_Vector.x = cos(_Angle) * fLength;
			_Vector.y = sin(_Angle) * fLength;
		}

		//Norme
		r_float Calc_Norm(const sf::Vector2f& _Vector)
		{
			return Msqrt(_Vector.x * _Vector.x + _Vector.y * _Vector.y);
		}

		r_float Calc_Norm(const sf::Vector3f& _Vector)
		{
			return Msqrt(_Vector.x * _Vector.x + _Vector.y * _Vector.y + _Vector.z * _Vector.z);
		}

		r_float Calc_NormSquared(const sf::Vector2f& _Vector)
		{
			return _Vector.x * _Vector.x + _Vector.y * _Vector.y;
		}

		r_float Calc_NormSquared(const sf::Vector3f& _Vector)
		{
			return _Vector.x * _Vector.x + _Vector.y * _Vector.y + _Vector.z * _Vector.z;
		}

		sf::Vector2f Calc_UnitVector(const sf::Vector2f& _Vector)
		{
			r_float fNorm = Calc_Norm(_Vector);

			if( fNorm == 0.0f )
				return r_vector2f(0.0f, 0.0f);

			return _Vector / fNorm;
		}

		sf::Vector3f Calc_UnitVector(const sf::Vector3f& _Vector)
		{
			r_float fNorm = Calc_Norm(_Vector);

			if( fNorm == 0.0f )
				return r_vector3f(0.0f, 0.0f, 0.0f);

			return _Vector / fNorm;
		}

		//Physique
		r_bool ProjectionsIntersects(const r_float& _l1, const r_float& _r1, const r_float& _l2, const r_float& _r2)
		{
			if( ((_l1 <= _l2 && _r1 >= _r2) || (_l1 >= _l2 && _r1 <= _r2))
			   || ((_l1 >= _l2 && _l1 <= _r2) || (_r1 >= _l2 && _r1 <= _r2)) )
				return true;

			return false;
		}

		r_bool RectsIntersects(const r_float& _x1, const r_float& _y1, const r_float& _w1, const r_float& _h1, const r_float& _x2, const r_float& _y2, const r_float& _w2, const r_float& _h2)
		{
			r_float t1 = _y1, t2 = _y2;
			r_float l1 = _x1, l2 = _x2;
			r_float b1 = _y1 + _h1, b2 = _y2 + _h2;
			r_float r1 = _x1 + _w1, r2 = _x2 + _w2;

			if( ProjectionsIntersects(l1, r1, l2, r2) )
				if( ProjectionsIntersects(t1, b1, t2, b2) )
					return true;

			return false;
		}
	}
}
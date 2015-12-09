namespace gmk
{
	namespace math
	{
		//Magic Square Root
		inline float Msqrt(const float& _Number)	//Une iteration
		{
			long i;
			float x2, y;
			const float threehalfs = 1.5F;

			x2 = _Number * 0.5F;
			y = _Number;
			i = *(long *)&y;                       // evil floating point bit level hacking
			i = 0x5f3759df - (i >> 1);               // what the fuck?
			y = *(float *)&i;
			y = y * (threehalfs - (x2 * y * y));

			return _Number * y;
		}

		inline float Msqrt(const float& _Number, const int& _Iteration)	//Plusieurs it�rations (plus pr�cis)
		{
			long i;
			float x2, y;
			const float threehalfs = 1.5F;

			x2 = _Number * 0.5F;
			y = _Number;
			i = *(long *)&y;                       // evil floating point bit level hacking
			i = 0x5f3759df - (i >> 1);               // what the fuck?
			y = *(float *)&i;
			for( int j(0); j < _Iteration; j++ )
				y = y * (threehalfs - (x2 * y * y));

			return _Number * y;
		}

		//Puissance / Factorielle
		int Pow(const int& _Number, const int& _Pow)
		{
			int iResult = _Number;

			if( _Pow == 0 )
				return 1;

			for( int i(0); i < _Pow - 1; i++ )
				iResult *= _Number;

			return iResult;
		}

		float Pow(const float& _Number, const int& _Pow)
		{
			float iResult = _Number;

			if( _Pow == 0 )
				return 1;

			for( int i(0); i < _Pow - 1; i++ )
				iResult *= _Number;

			return iResult;
		}

		int Factorial(int _Number)
		{
			//Factorielle 0 = 1
			if( _Number == 0 )
				return 1;

			int _Value = _Number - 1;

			while( _Value > 1 )
			{
				_Number *= _Value;
				_Value--;
			}

			return _Number;
		}

		//Distance
		float Calc_Distance(const sf::Vector2f& _Element1, const sf::Vector2f& _Element2)
		{
			float x = _Element1.x - _Element2.x;
			float y = _Element1.y - _Element2.y;

			return Msqrt(x*x + y*y);
		}

		float Calc_Distance(const sf::Vector2f& _Element1, const sf::Vector3f& _Element2)
		{
			sf::Vector2f Conversion(_Element2.x, _Element2.y);

			return Calc_Distance(_Element1, Conversion);
		}

		float Calc_Distance(const sf::Vector3f& _Element1, const sf::Vector3f& _Element2)
		{
			float x = _Element1.x - _Element2.x;
			float y = _Element1.y - _Element2.y;
			float z = _Element1.z - _Element2.z;

			return Msqrt(x*x + y*y + z*z);
		}

		float Calc_DistanceSquared(const sf::Vector2f& _Element1, const sf::Vector2f& _Element2)
		{
			float x = _Element1.x - _Element2.x;
			float y = _Element1.y - _Element2.y;

			return x*x + y*y;
		}

		float Calc_DistanceSquared(const sf::Vector3f& _Element1, const sf::Vector3f& _Element2)
		{
			float x = _Element1.x - _Element2.x;
			float y = _Element1.y - _Element2.y;
			float z = _Element1.z - _Element2.z;

			return x*x + y*y + z*z;
		}

		//Angle
		float Calc_Angle(const sf::Vector2f& _VectorOne, const sf::Vector2f& _VectorTwo)
		{
			float fScalarProduct = _VectorOne.x * _VectorTwo.x + _VectorOne.y * _VectorTwo.y;
			float fVectorOneNorm = Msqrt((_VectorOne.x * _VectorOne.x) + (_VectorOne.y * _VectorOne.y));
			float fVectorTwoNorm = Msqrt((_VectorTwo.x * _VectorTwo.x) + (_VectorTwo.y * _VectorTwo.y));

			return acos(fScalarProduct / (fVectorOneNorm*fVectorTwoNorm));
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

		sf::Vector3f Convert2dTo3d(const sf::Vector2f& _Vector2d, const float& _Z)
		{
			return sf::Vector3f(_Vector2d.x, _Vector2d.y, _Z);
		}

		sf::Vector2f Convert3dTo2d(const sf::Vector3f& _Vector3d)
		{
			return sf::Vector2f(_Vector3d.x, _Vector3d.y);
		}

		float DotProduct(const sf::Vector2f& _Vector1, const sf::Vector2f& _Vector2)
		{
			return _Vector1.x * _Vector2.x + _Vector1.y * _Vector2.y;
		}

		float DotProduct(const sf::Vector3f& _Vector1, const sf::Vector3f& _Vector2)
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

		//Norme
		float Calc_Norm(const sf::Vector2f& _Vector)
		{
			return Msqrt(_Vector.x * _Vector.x + _Vector.y * _Vector.y);
		}

		float Calc_Norm(const sf::Vector3f& _Vector)
		{
			return Msqrt(_Vector.x * _Vector.x + _Vector.y * _Vector.y + _Vector.z * _Vector.z);
		}

		float Calc_NormSquared(const sf::Vector2f& _Vector)
		{
			return _Vector.x * _Vector.x + _Vector.y * _Vector.y;
		}

		float Calc_NormSquared(const sf::Vector3f& _Vector)
		{
			return _Vector.x * _Vector.x + _Vector.y * _Vector.y + _Vector.z * _Vector.z;
		}

		sf::Vector2f Calc_UnitVector(const sf::Vector2f& _Vector)
		{
			float fNorm = Calc_Norm(_Vector);

			return _Vector / fNorm;
		}

		sf::Vector3f Calc_UnitVector(const sf::Vector3f& _Vector)
		{
			float fNorm = Calc_Norm(_Vector);

			return _Vector / fNorm;
		}

		//Physique
		bool ProjectionsIntersects(const float& _l1, const float& _r1, const float& _l2, const float& _r2)
		{
			if( ((_l1 <= _l2 && _r1 >= _r2) || (_l1 >= _l2 && _r1 <= _r2))
			   || ((_l1 >= _l2 && _l1 <= _r2) || (_r1 >= _l2 && _r1 <= _r2)) )
				return true;

			return false;
		}

		bool RectsIntersects(const float& _x1, const float& _y1, const float& _w1, const float& _h1, const float& _x2, const float& _y2, const float& _w2, const float& _h2)
		{
			float t1 = _y1, t2 = _y2;
			float l1 = _x1, l2 = _x2;
			float b1 = _y1 + _h1, b2 = _y2 + _h2;
			float r1 = _x1 + _w1, r2 = _x2 + _w2;

			if( ProjectionsIntersects(l1, r1, l2, r2) )
				if( ProjectionsIntersects(t1, b1, t2, b2) )
					return true;

			return false;
		}
	}
}
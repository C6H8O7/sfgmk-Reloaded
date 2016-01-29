#include "stdafx.h"

namespace gmk
{
	namespace math
	{
		template <typename T>
		class vector2 : public sf::Vector2<T>
		{
		public:

			vector2()
				: sf::Vector2<T>()
			{

			}

			vector2(T _x, T _y)
				: sf::Vector2<T>(_x, _y)
			{

			}

			template <typename U>
			vector2(const sf::Vector2<U>& vector)
				: sf::Vector2<T>(vector)
			{

			}

			template <typename U>
			vector2(const vector2<U>& vector)
				: sf::Vector2<T>(vector)
			{

			}

			inline vector2 normalised()
			{
				r_float l = magic_sqrt((r_float)sf::Vector2<T>::x * sf::Vector2<T>::x + (r_float)sf::Vector2<T>::y * sf::Vector2<T>::y);
				return (*this) / l;
			}

			inline vector2& normalise()
			{
				(*this) = normalised();
				return (*this);
			}

			inline vector2 clamped(r_float _min, r_float _max)
			{
				r_float l = magic_sqrt((r_float)sf::Vector2<T>::x * sf::Vector2<T>::x + (r_float)sf::Vector2<T>::y * sf::Vector2<T>::y);
				if (l < _min) return (*this) * (_min / l);
				else if (l > _max) return (*this) * (_max / l);
				return (*this);
			}

			inline vector2& clamp(r_float _min, r_float _max)
			{
				(*this) = clamped(_min, _max);
				return (*this);
			}

			inline r_float length()
			{
				return magic_sqrt((r_float)sf::Vector2<T>::x * sf::Vector2<T>::x + (r_float)sf::Vector2<T>::y * sf::Vector2<T>::y);
			}

			inline T length2()
			{
				return sf::Vector2<T>::x * sf::Vector2<T>::x + sf::Vector2<T>::y * sf::Vector2<T>::y;
			}

			inline T lengthSquared()
			{
				return length2();
			}

			inline T dot(vector2& _vector)
			{
				return sf::Vector2<T>::x * _vector.x + sf::Vector2<T>::y * _vector.y;
			}

			inline r_float angle(vector2& _vector)
			{
				// xx' + yy' = ||U|| * ||V|| * cos(U, V)
				return acosf(dot(_vector) / (length() * _vector.length()));
			}

			inline static r_float magic_sqrt(const r_float& _Number)
			{
				long i;
				r_float x2, y;
				const r_float threehalfs = 1.5F;

				x2 = _Number * 0.5F;
				y = _Number;
				i = *(long *)&y;						// evil floating point bit level hacking
				i = 0x5f3759df - (i >> 1);				// what the fuck?
				y = *(r_float *)&i;
				y = y * (threehalfs - (x2 * y * y));

				return _Number * y;
			}
		};
	}
}
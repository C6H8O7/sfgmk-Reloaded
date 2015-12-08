/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		02/01/2015
	@brief		Matrice carr� de dimension 2, surcharg�e pour compatibilit� avec sf::vector2f

--------------------------------------------------------------------------------------------------*/

#ifndef MATRIX_22_HPP
#define MATRIX_22_HPP

namespace gmk
{
	namespace math
	{
		class Matrix22
		{
			private:
				float m_fArray[4];

			public:
				Matrix22();
				Matrix22(float _Value1, float _Value2, float _Value3, float _Value4);
				Matrix22(float _Value[4]);
				~Matrix22();

				sf::Vector2f operator*(sf::Vector2f& _Vector2);
		};
	}
}

#endif
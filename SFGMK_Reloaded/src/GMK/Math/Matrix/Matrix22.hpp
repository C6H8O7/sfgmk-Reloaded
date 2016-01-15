/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		02/01/2015
	@brief		Matrice carré de dimension 2, surchargée pour compatibilité avec sf::vector2f

--------------------------------------------------------------------------------------------------*/

#ifndef MATRIX_22_HPP
#define MATRIX_22_HPP

#include "stdafx.h"

namespace gmk
{
	namespace math
	{
		class Matrix22
		{
			private:
				r_float m_fArray[4];

			public:
				Matrix22();
				Matrix22(const r_float& _Value1, const r_float& _Value2, const r_float& _Value3, const r_float& _Value4);
				Matrix22(const r_float _Value[4]);
				~Matrix22();

				r_vector2f operator*(const r_vector2f& _Vector2);
		};
	}
}

#endif
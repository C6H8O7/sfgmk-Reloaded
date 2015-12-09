/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		07/07/2015
	@brief		Matrice carr� de dimension 2, classe sp�cialis�e de matrix22 pour faciliter les rotations

--------------------------------------------------------------------------------------------------*/

#ifndef MATRIX_ROTATION_22_HPP
#define MATRIX_ROTATION_22_HPP

namespace gmk
{
	namespace math
	{
		class MatrixRotation22 : public Matrix22
		{
			public:
				MatrixRotation22(const float& _Rotation);
				~MatrixRotation22();
		};
	}
}

#endif
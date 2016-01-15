/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		09/03/2015
	@brief		Courbe d'interpolation

--------------------------------------------------------------------------------------------------*/

#ifndef CATMULL_ROM_HPP
#define CATMULL_ROM_HPP

#include "stdafx.h"

namespace gmk
{
	namespace math
	{
		class CatmullRom : public Curb
		{
			public:
				CatmullRom(const r_int32& _PointNumber, const r_float& _Time = 1.0f);
				~CatmullRom();

				r_void update(const r_float& _TimeDelta);

				r_void computeCoords();

			private:
				r_int32 m_iPointNumber;
				r_int32 m_iCurrentPoint;
		};
	}
}

#endif
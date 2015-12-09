/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		09/03/2015
	@brief		Courbe d'interpolation

--------------------------------------------------------------------------------------------------*/

#ifndef CATMULL_ROM_HPP
#define CATMULL_ROM_HPP

namespace gmk
{
	namespace math
	{
		class CatmullRom : public Curb
		{
			public:
				CatmullRom(const int& _PointNumber, const float& _Time = 1.0f);
				~CatmullRom();

				void update(const float& _TimeDelta);

				void computeCoords();

			private:
				int m_iPointNumber;
				int m_iCurrentPoint;
		};
	}
}

#endif
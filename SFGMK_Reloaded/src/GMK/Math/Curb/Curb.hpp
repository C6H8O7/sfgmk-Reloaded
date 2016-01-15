/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		09/03/2015
	@brief		Class mère des différentes courbes d'interpolation

--------------------------------------------------------------------------------------------------*/

#ifndef CURB_HPP
#define CURB_HPP

#include "stdafx.h"

namespace gmk
{
	namespace math
	{
		class Curb
		{
			protected:
				sf::Vector3f* m_Points;
				sf::Vector3f m_CurrentPos;
				r_float m_fTotalTime;
				r_float m_fCurrentTime;
				r_float m_fTimeRatio;

			public:
				Curb(const r_float& _Duration);
				virtual ~Curb();

				virtual r_void update(const r_float& _TimeDelta) = 0;

				virtual r_void computeCoords() = 0;

				const sf::Vector3f* getPoints();
				const sf::Vector3f& getCurrentPosition();
				const r_float& getTotalTime();
				const r_float& getCurrentTime();
				const r_float& getTimeRatio();
		};
	}
}

#endif
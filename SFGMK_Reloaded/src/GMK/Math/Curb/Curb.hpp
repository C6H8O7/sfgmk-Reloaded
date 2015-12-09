/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		09/03/2015
	@brief		Class mère des différentes courbes d'interpolation

--------------------------------------------------------------------------------------------------*/

#ifndef CURB_HPP
#define CURB_HPP

namespace gmk
{
	namespace math
	{
		class Curb
		{
			protected:
				sf::Vector3f* m_Points;
				sf::Vector3f m_CurrentPos;
				float m_fTotalTime;
				float m_fCurrentTime;
				float m_fTimeRatio;

			public:
				Curb(const float& _Duration);
				virtual ~Curb();

				virtual void update(const float& _TimeDelta) = 0;

				virtual void computeCoords() = 0;

				const sf::Vector3f* getPoints();
				const sf::Vector3f& getCurrentPosition();
				const float& getTotalTime();
				const float& getCurrentTime();
				const float& getTimeRatio();
		};
	}
}

#endif
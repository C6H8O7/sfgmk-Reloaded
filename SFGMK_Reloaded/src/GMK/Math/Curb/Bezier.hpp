/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		02/03/2015
	@brief		Courbe de Bézier

--------------------------------------------------------------------------------------------------*/

#ifndef BEZIER_HPP
#define BEZIER_HPP


namespace gmk
{
	namespace math
	{
		class Bezier : public Curb
		{
			public:
				Bezier(const sf::Vector3f& _Origin = sf::Vector3f(0.0f, 0.0f, 0.0f), const sf::Vector3f& Arrival = sf::Vector3f(0.0f, 0.0f, 0.0f), const sf::Vector3f& _ControlPoint1 = sf::Vector3f(0.0f, 0.0f, 0.0f), const sf::Vector3f& _ControlPoint2 = sf::Vector3f(0.0f, 0.0f, 0.0f), const float& _Time = 1.0f);
				Bezier(const sf::Vector3f _Points[4], const float& _Time = 1.0f);
				~Bezier();

				void update(const float& _TimeDelta);

				void computeCoords();
		};
	}
}

#endif
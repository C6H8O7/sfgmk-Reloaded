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
				Bezier(const sf::Vector3f& _Origin = sf::Vector3f(0.0f, 0.0f, 0.0f), const sf::Vector3f& Arrival = sf::Vector3f(0.0f, 0.0f, 0.0f), const sf::Vector3f& _ControlPoint1 = sf::Vector3f(0.0f, 0.0f, 0.0f), const sf::Vector3f& _ControlPoint2 = sf::Vector3f(0.0f, 0.0f, 0.0f), const r_float& _Time = 1.0f);
				Bezier(const sf::Vector3f _Points[4], const r_float& _Time = 1.0f);
				~Bezier();

				r_void update(const r_float& _TimeDelta);

				r_void computeCoords();
		};
	}
}

#endif
/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		  /10/2015
	@brief		Conteneur des valeurs d'une courbe (+ nom et couleur si on veut l'afficher par la suite)

--------------------------------------------------------------------------------------------------*/

#ifndef GRAPH_CURB_HPP
#define GRAPH_CURB_HPP

#include "stdafx.h"

namespace gmk
{
	namespace math
	{
		class GraphCurb
		{
			private:
				gmk::vector<r_vector2f> m_Values;
				r_string m_Name;
				sf::Color m_Color;

			public:
				GraphCurb(const r_string& _Name, const sf::Color& _Color = sf::Color::Blue);
				~GraphCurb();

				r_void addValue(const r_vector2f& _NewValue);
				gmk::vector<r_vector2f>& getValues();

				const r_string& getName();
				const sf::Color& getColor();
		};
	}
}

#endif
#ifndef GRAPH_CURB_HPP
#define GRAPH_CURB_HPP

namespace gmk
{
	namespace math
	{
		class GraphCurb
		{
			private:

				gmk::vector<sf::Vector2f> m_Values;
				std::string m_Name;
				sf::Color m_Color;

			public:
				GraphCurb(const std::string& _Name, const sf::Color& _Color = sf::Color::Blue);
				~GraphCurb();

				void addValue(const sf::Vector2f& _NewValue);
				gmk::vector<sf::Vector2f>& getValues();

				const std::string& getName();
				const sf::Color& getColor();
		};
	}
}

#endif
namespace gmk
{
	namespace math
	{
		GraphCurb::GraphCurb(const r_string& _Name, const sf::Color& _Color) : m_Name(_Name), m_Color(_Color)
		{
		}

		GraphCurb::~GraphCurb()
		{
			m_Values.clear();
		}


		r_void GraphCurb::addValue(const r_vector2f& _NewValue)
		{
			m_Values.push_back(_NewValue);
		}

		vector<r_vector2f>& GraphCurb::getValues()
		{
			return m_Values;
		}


		const r_string& GraphCurb::getName()
		{
			return m_Name;
		}

		const sf::Color& GraphCurb::getColor()
		{
			return m_Color;
		}
	}
}
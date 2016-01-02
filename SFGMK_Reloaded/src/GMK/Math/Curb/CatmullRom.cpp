namespace gmk
{
	namespace math
	{
		CatmullRom::CatmullRom(const r_int32& _PointNumber, const r_float& _Time) : Curb(_Time), m_iPointNumber(_PointNumber), m_iCurrentPoint(0)
		{
			m_Points = new sf::Vector3f[m_iPointNumber + 2];
			m_Points[0] = m_Points[1] = sf::Vector3f(100.0f, 100.0f, 0.0f);
			m_Points[2] = sf::Vector3f(500.0f, 1000.0f, 0.0f);
			m_Points[3] = m_Points[4] = sf::Vector3f(1000.0f, 100.0f, 0.0f);
		}

		CatmullRom::~CatmullRom()
		{

		}


		r_void CatmullRom::update(const r_float& _TimeDelta)
		{
			m_fCurrentTime += _TimeDelta;
			m_fTimeRatio = m_fCurrentTime / m_fTotalTime;

			//Update coordonnees
			m_fTimeRatio < 1.0f ? computeCoords() : m_CurrentPos = m_Points[m_iPointNumber + 1];
		}


		r_void CatmullRom::computeCoords()
		{
			r_int32 iIndex[4];
			for( r_int32 i(0); i < 4; i++ )
				iIndex[i] = (m_iCurrentPoint + i) < (m_iPointNumber + 2) ? m_iPointNumber + i : m_iPointNumber;

			r_float t3 = m_fTimeRatio * m_fTimeRatio * m_fTimeRatio;
			r_float t2 = m_fTimeRatio * m_fTimeRatio;

			r_float f1 = -0.5f * t3 + t2 - 0.5f * m_fTimeRatio;
			r_float f2 = 1.5f * t3 - 2.5f * t2 + 1.0f;
			r_float f3 = -1.5f * t3 + 2.0f * t2 + 0.5f * m_fTimeRatio;
			r_float f4 = 0.5f * t3 - 0.5f * t2;

			m_CurrentPos.x = m_Points[iIndex[0]].x * f1 + m_Points[iIndex[1]].x * f2 + m_Points[iIndex[2]].x * f3 + m_Points[iIndex[3]].x * f4;
			m_CurrentPos.y = m_Points[iIndex[0]].y * f1 + m_Points[iIndex[1]].y * f2 + m_Points[iIndex[2]].y * f3 + m_Points[iIndex[3]].y * f4;
		}
	}
}
namespace gmk
{
	Polygon::Polygon() : m_PolygonPtr(NULL)
	{
	}

	Polygon::~Polygon()
	{
	}


	r_bool Polygon::addPoint(const ePOLYGON_GROUP& _PointGroup, const r_vector2f& _MousePos)
	{
		if( _PointGroup == ePOLYGON_GROUP::ePolygon )
			addPointToPoly(m_Polygons, m_LastPolygonPoints, _MousePos);
		else if( _PointGroup == ePOLYGON_GROUP::eHole )
			addPointToPoly(m_Holes, m_LastHolePoints, _MousePos);
		else
			return false;

		return true;
	}

	r_void Polygon::addPointToPoly(ClipperLib::Paths& _Poly, ClipperLib::Path& _LastPointPoly, const r_vector2f& _MousePos)
	{
		r_bool bPolyComplete(false);

		//Crée le nouveau point
		ClipperLib::IntPoint NewPoint = { (ClipperLib::cInt)_MousePos.x, (ClipperLib::cInt)_MousePos.y };

		//Si le point ferme la forme, on stocke la forme
		for( ClipperLib::IntPoint& Point : _LastPointPoly )
		{
			if( gmk::math::Calc_Distance(r_vector2f((r_float)Point.X, (r_float)Point.Y), r_vector2f((r_float)NewPoint.X, (r_float)NewPoint.Y)) <= POLYGON_DISTANCE_TO_CLOSE )
			{
				bPolyComplete = true;
				NewPoint.X = Point.X;
				NewPoint.Y = Point.Y;
			}
		}

		//Stocke le nouveau point
		_LastPointPoly << NewPoint;

		//Si on a fermé la forme, on la stocke
		if( bPolyComplete )
		{
			_Poly.push_back(_LastPointPoly);
			_LastPointPoly.clear();
		}
	}
}
/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		03/01/2016
	@brief		Surcouche pour p2t::Polygon + clipper

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_POLYGON_HPP
#define SFGMKR_POLYGON_HPP


namespace gmk
{
	#define POLYGON_DISTANCE_TO_CLOSE 4.0f

	class Polygon
	{
		public:
			Polygon();
			~Polygon();

		private:
			p2t::Polygon* m_PolygonPtr;
			p2t::Triangles m_Triangles;

			ClipperLib::Paths m_Polygons, m_Holes;
			ClipperLib::Path m_LastPolygonPoints, m_LastHolePoints;

		public:
			enum ePOLYGON_GROUP
			{
				eHole = 0,
				ePolygon
			};

			r_bool addPoint(const ePOLYGON_GROUP& _PointGroup, const r_vector2f& _MousePos);

		private:
			r_void addPointToPoly(ClipperLib::Paths& _Poly, ClipperLib::Path& _LastPointPoly, const r_vector2f& _MousePos);
	};
}


#endif
/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		03/01/2016
	@brief		Surcouche pour p2t::Polygon + clipper

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_POLYGON_HPP
#define SFGMKR_POLYGON_HPP


class SFMLCanvas;

namespace gmk
{
	#define POLYGON_DISTANCE_TO_CLOSE 16.0f

	class Polygon
	{
		public:
			Polygon();
			~Polygon();

		private:
			std::vector<p2t::Polygon*> m_Polygons;
			std::vector<p2t::Triangles> m_Triangles;

			ClipperLib::Paths m_Polys, m_Holes, m_MergeSolution;
			ClipperLib::Path m_LastPolygonPoints, m_LastHolePoints;

		public:
			enum ePOLYGON_GROUP
			{
				eHole = 0,
				ePolygon
			};

			r_bool addPoint(const ePOLYGON_GROUP& _PointGroup, const r_vector2f& _MousePos);
			r_void mergeAll();
			r_void triangulate();

			std::vector<p2t::Polygon*>& getPolygons();
			std::vector<p2t::Triangles>& getTriangles();
			ClipperLib::Paths& getPolys();
			ClipperLib::Paths& getHoles();
			ClipperLib::Paths& getMerge();
			ClipperLib::Path& getLastPoly();
			ClipperLib::Path& getLastHole();

			r_void drawLastPoints(SFMLCanvas* _Render);
			r_void drawPolys(SFMLCanvas* _Render);
			r_void drawMerge(SFMLCanvas* _Render);
			r_void drawTriangles(SFMLCanvas* _Render);

			r_uint32 getTriangleNumber();

		private:
			r_void addPointToPoly(ClipperLib::Paths& _Poly, ClipperLib::Path& _LastPointPoly, const r_vector2f& _MousePos);

			r_void merge(ClipperLib::Paths& _Polygons, const ClipperLib::ClipType& _MergeType);

			r_void drawPoly(SFMLCanvas* _Render, ClipperLib::Path _Poly, sf::Color _Color, const r_bool& _AddLastLine = false);
	};
}


#endif
namespace gmk
{
	Polygon::Polygon()
	{
	}

	Polygon::~Polygon()
	{
		m_Polygons.clear();
		m_Triangles.clear();
		m_Polys.clear();
		m_Holes.clear();
		m_MergeSolution.clear();
		m_LastPolygonPoints.clear();
		m_LastHolePoints.clear();
	}


	r_bool Polygon::addPoint(const ePOLYGON_GROUP& _PointGroup, const r_vector2f& _MousePos)
	{
		if( _PointGroup == ePOLYGON_GROUP::ePolygon )
		{
			addPointToPoly(m_Polys, m_LastPolygonPoints, _MousePos);

			//Merge
			if( m_Polys.size() > 1 )
				merge(m_Polys, ClipperLib::ClipType::ctUnion);
		}
		else if( _PointGroup == ePOLYGON_GROUP::eHole )
		{
			addPointToPoly(m_Holes, m_LastHolePoints, _MousePos);

			//Merge
			if( m_Holes.size() > 1 )
				merge(m_Holes, ClipperLib::ClipType::ctUnion);
		}
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

	r_void Polygon::merge(ClipperLib::Paths& _Polygons, const ClipperLib::ClipType& _MergeType)
	{
		//Merge last achieved
		ClipperLib::Clipper ClipPolys;
		ClipperLib::Paths Merge;

		for( size_t i(0); i < _Polygons.size(); i++ )
			ClipPolys.AddPath(_Polygons[i], ClipperLib::ptSubject, true);
		ClipPolys.Execute(_MergeType, Merge, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

		_Polygons.clear();
		_Polygons = Merge;
	}

	r_void Polygon::mergeAll()
	{
		ClipperLib::Clipper ClipPolys;

		for( size_t i(0); i < m_Polys.size(); i++ )
			ClipPolys.AddPath(m_Polys[i], ClipperLib::ptSubject, true);
		for( size_t i(0); i < m_Holes.size(); i++ )
			ClipPolys.AddPath(m_Holes[i], ClipperLib::ptClip, true);

		ClipPolys.Execute(ClipperLib::ctDifference, m_MergeSolution, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

		m_Polys.clear();
		for( size_t i(0); i < m_MergeSolution.size(); i++ )
			m_Polys.push_back(m_MergeSolution[i]);
	}

	r_void Polygon::triangulate()
	{
		for( size_t i(0); i < m_MergeSolution.size(); i++ )
		{
			p2t::Polygon* NewPolygon = new p2t::Polygon(m_MergeSolution[0], m_Holes);
			NewPolygon->triangulation();
			m_Triangles.push_back(NewPolygon->triangles());
			m_Polygons.push_back(NewPolygon);
		}

		m_Holes.clear();
	}


	std::vector<p2t::Polygon*>& Polygon::getPolygons()
	{
		return m_Polygons;
	}

	std::vector<p2t::Triangles>& Polygon::getTriangles()
	{
		return m_Triangles;
	}

	ClipperLib::Paths& Polygon::getPolys()
	{
		return m_Polys;
	}

	ClipperLib::Paths& Polygon::getHoles()
	{
		return m_Holes;
	}

	ClipperLib::Paths& Polygon::getMerge()
	{
		return m_MergeSolution;
	}

	ClipperLib::Path& Polygon::getLastPoly()
	{
		return m_LastPolygonPoints;
	}

	ClipperLib::Path& Polygon::getLastHole()
	{
		return m_LastHolePoints;
	}


	r_void Polygon::drawPoly(SFMLCanvas* _Render, ClipperLib::Path _Poly, sf::Color _Color, const r_bool& _AddLastLine)
	{
		if( _Poly.size() )
		{
			for( size_t i(0); i < _Poly.size() - 1; i++ )
			{
				sf::Vertex line[] =
				{
					sf::Vertex(r_vector2f((r_float)_Poly[i].X, (r_float)_Poly[i].Y), _Color),
					sf::Vertex(r_vector2f((r_float)_Poly[i + 1].X, (r_float)_Poly[i + 1].Y), _Color)
				};

				_Render->draw(line, 2, sf::Lines);
			}

			if( _AddLastLine )
			{
				sf::Vertex line[] =
				{
					sf::Vertex(r_vector2f((r_float)_Poly[_Poly.size() - 1].X, (r_float)_Poly[_Poly.size() - 1].Y), _Color),
					sf::Vertex(r_vector2f((r_float)_Poly[0].X, (r_float)_Poly[0].Y), _Color)
				};

				_Render->draw(line, 2, sf::Lines);
			}
		}
	}

	r_void Polygon::drawLastPoints(SFMLCanvas* _Render)
	{
		if( m_LastPolygonPoints.size() )
		{
			drawPoly(_Render, m_LastPolygonPoints, sf::Color::Blue);
			sf::Vertex line[] =
			{
				sf::Vertex(r_vector2f((r_float)m_LastPolygonPoints[m_LastPolygonPoints.size() - 1].X, (r_float)m_LastPolygonPoints[m_LastPolygonPoints.size() - 1].Y), sf::Color::Blue),
				sf::Vertex(r_vector2f(SFMLCanvas::editorCanvas->getInputManager()->getMouse().getWorldPosition()), sf::Color::Blue)
			};
			_Render->draw(line, 2, sf::Lines);
		}

		if( m_LastHolePoints.size() )
		{
			drawPoly(_Render, m_LastHolePoints, sf::Color::Red);
			sf::Vertex line[] =
			{
				sf::Vertex(r_vector2f((r_float)m_LastHolePoints[m_LastHolePoints.size() - 1].X, (r_float)m_LastHolePoints[m_LastHolePoints.size() - 1].Y), sf::Color::Red),
				sf::Vertex(r_vector2f(SFMLCanvas::editorCanvas->getInputManager()->getMouse().getWorldPosition()), sf::Color::Red)
			};
			_Render->draw(line, 2, sf::Lines);
		}
	}

	r_void Polygon::drawPolys(SFMLCanvas* _Render)
	{
		for( size_t i(0); i < m_Polys.size(); i++ )
			drawPoly(_Render, m_Polys[i], sf::Color::Blue, true);
		for( size_t i(0); i < m_Holes.size(); i++ )
			drawPoly(_Render, m_Holes[i], sf::Color::Red, true);
	}

	r_void Polygon::drawMerge(SFMLCanvas* _Render)
	{
		for( size_t i(0); i < m_MergeSolution.size(); i++ )
			drawPoly(_Render, m_MergeSolution[i], sf::Color::Yellow, true);
	}

	r_void Polygon::drawTriangles(SFMLCanvas* _Render)
	{
		for( size_t it(0); it < m_Triangles.size(); it++ )
		{
			for( auto& TempTri : m_Triangles[it] )
			{
				sf::VertexArray TriVert(sf::Triangles, 3U);
				for( r_int32 i(0); i < 3; i++ )
				{
					TriVert[i].position = r_vector2f((r_float)m_Polygons[it]->points()[TempTri[i]]->x, (r_float)m_Polygons[it]->points()[TempTri[i]]->y);
					sf::Uint8 ui8Color = RAND(0, 255);
					TriVert[i].color = sf::Color(ui8Color, ui8Color, ui8Color, 255);

				}
				_Render->draw(TriVert);
			}
		}
	}


	r_uint32 Polygon::getTriangleNumber()
	{
		r_uint32 Result(0U);

		for( size_t i(0); i < m_Triangles.size(); i++ )
			Result += m_Triangles[i].size();

		return Result;
	}
}
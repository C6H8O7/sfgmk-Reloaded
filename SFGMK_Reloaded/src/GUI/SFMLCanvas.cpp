#ifdef SFGMKR_EDITOR
SFMLCanvas::SFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
	: wxPanel(Parent, Id, Position, Size, Style)
{
	sf::RenderWindow::create(GetHandle());

	m_fWidth = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_fHeight = SFGMKR_DEFAULT_SFML_SIZE_Y;
	
	sf::View view;
	view.setCenter(sf::Vector2f(m_fWidth / 2.0f, m_fHeight / 2.0f));
	view.setSize(sf::Vector2f((float)m_fWidth, (float)m_fHeight));

	sf::RenderWindow::setSize(sf::Vector2u(m_fWidth, m_fHeight));
	sf::RenderWindow::setView(view);

	m_InputManager = new gmk::InputManager(this);
}
#endif

#ifndef SFGMKR_EDITOR
SFMLCanvas::SFMLCanvas()
{
	sf::RenderWindow::create(sf::VideoMode((unsigned int)SFGMKR_DEFAULT_SFML_SIZE_X, (unsigned int)SFGMKR_DEFAULT_SFML_SIZE_Y), "SFGMK Reloaded");

	m_fWidth = SFGMKR_DEFAULT_SFML_SIZE_X;
	m_fHeight = SFGMKR_DEFAULT_SFML_SIZE_Y;

	sf::View view;
	view.setCenter(sf::Vector2f(m_fWidth / 2.0f, m_fHeight / 2.0f));
	view.setSize(sf::Vector2f((float)m_fWidth, (float)m_fHeight));

	sf::RenderWindow::setSize(sf::Vector2u((unsigned int)m_fWidth, (unsigned int)m_fHeight));
	sf::RenderWindow::setView(view);

	m_InputManager = new gmk::InputManager(this);
}
#endif

SFMLCanvas::~SFMLCanvas()
{
	delete m_InputManager;
}

#ifdef SFGMKR_EDITOR
void SFMLCanvas::OnIdle(wxIdleEvent& _event)
{
	// On génère un rafraîchissement du contrôle, afin d'assurer un framerate maximum
	Refresh(false);

	_event.RequestMore(true);
}

void SFMLCanvas::OnPaint(wxPaintEvent& _event)
{
	// On prépare le contrôle à être dessiné
	wxPaintDC dc(this);

	// On laisse la classe dérivée se mettre à jour et dessiner dans le contrôle
	OnUpdate();

#ifdef SFGMKR_EDITOR
	static float timer = 0;
	static float* timeDeltaPtr = &gmk::TimeManager::GetSingleton()->deltaTime;

	timer += *timeDeltaPtr;

	if (timer >= 0.05f)
	{
		timer = 0.0f;

		MyGUI* gui = MyGUI::GetGUI();

		gui->Update_PropertyGrid();

		char status[50];
		sprintf_s(status, "Updated in: %.2f ms (%d FPS)", *timeDeltaPtr * 1000.0f, (int)(1.0f / *timeDeltaPtr));
		gui->GUI_StatusBar->SetStatusText(status);
	}
#endif
}

void SFMLCanvas::OnEraseBackground(wxEraseEvent& _event)
{

}

BEGIN_EVENT_TABLE(SFMLCanvas, wxPanel)
	EVT_IDLE(SFMLCanvas::OnIdle)
	EVT_ERASE_BACKGROUND(SFMLCanvas::OnEraseBackground)
	EVT_PAINT(SFMLCanvas::OnPaint)
END_EVENT_TABLE()
#endif

/*void addLastPoint(ClipperLib::Paths& _Poly, ClipperLib::Path& _LastPointPoly, sf::Vector2f _MousePos)
{
	bool bPolyComplete(false);

	//Crée le nouveau point
	ClipperLib::IntPoint NewPoint = { (ClipperLib::cInt)_MousePos.x, (ClipperLib::cInt)_MousePos.y };

	//Si le point ferme la forme, on stocke la forme
	for( ClipperLib::IntPoint& Point : _LastPointPoly )
	{
		if( gmk::math::Calc_Distance(sf::Vector2f((float)Point.X, (float)Point.Y), sf::Vector2f((float)NewPoint.X, (float)NewPoint.Y)) < 8.0f )
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

void drawPoly(SFMLCanvas* _Render, ClipperLib::Path _Poly, sf::Color _Color)
{
	if( _Poly.size() )
	{
		for( size_t i(0); i < _Poly.size() - 1; i++ )
		{
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f((float)_Poly[i].X, (float)_Poly[i].Y), _Color),
				sf::Vertex(sf::Vector2f((float)_Poly[i + 1].X, (float)_Poly[i + 1].Y), _Color)
			};

			_Render->draw(line, 2, sf::Lines);
		}
	}
}*/

void SFMLCanvas::OnUpdate()
{
	// On efface la vue
	clear(sf::Color(0, 128, 128));

	// Pre update
	m_InputManager->update();
	gmk::TimeManager::GetSingleton()->update();

	// Update gameobjects / components
	gmk::vector<GameObject*>& gameobjects = SFMLCanvas::project->getCurrentScene()->getGameObjects();

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->update(this);

	for (unsigned int i = 0; i < gameobjects.getElementNumber(); i++)
		gameobjects[i]->draw(this);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Tests polys
	/*static ClipperLib::Paths Polygons, Holes, MergePolys, MergeHoles;
	static ClipperLib::Path LastPointsPoly, LastPointsHole;
	static ClipperLib::Clipper ClipPolys, ClipHoles;

	//Nouveau point
	if( m_InputManager->getMouse().getButtonState(sf::Mouse::Left) == KEY_PRESSED )
		addLastPoint(Polygons, LastPointsPoly, (sf::Vector2f)m_InputManager->getMouse().getWindowPosition());
	else if( m_InputManager->getMouse().getButtonState(sf::Mouse::Right) == KEY_PRESSED )
		addLastPoint(Holes, LastPointsHole, (sf::Vector2f)m_InputManager->getMouse().getWindowPosition());

	//Merge
	if( m_InputManager->getKeyboard().getKeyState(sf::Keyboard::Return) == KEY_PRESSED )
	{
		for( size_t i(0); i < Holes.size(); i++ )
			ClipHoles.AddPath(Holes[i], ClipperLib::ptSubject, true);
		ClipHoles.Execute(ClipperLib::ctUnion, MergeHoles, ClipperLib::pftNonZero, ClipperLib::pftNonZero);

		for( size_t i(0); i < Polygons.size(); i++ )
			ClipPolys.AddPath(Polygons[i], ClipperLib::ptSubject, true);
		for( size_t i(0); i < Holes.size(); i++ )
			ClipPolys.AddPath(Holes[i], ClipperLib::ptClip, true);
		ClipPolys.Execute(ClipperLib::ctDifference, MergePolys, ClipperLib::pftNonZero, ClipperLib::pftNonZero);
	}

	//Draws
	if( LastPointsPoly.size() )
	{
		drawPoly(this, LastPointsPoly, sf::Color::Blue);
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f((float)LastPointsPoly[LastPointsPoly.size() - 1].X, (float)LastPointsPoly[LastPointsPoly.size() - 1].Y), sf::Color::Blue),
			sf::Vertex(sf::Vector2f(m_InputManager->getMouse().getWindowPosition()), sf::Color::Blue)
		};
		this->draw(line, 2, sf::Lines);
	}

	if( LastPointsHole.size() )
	{
		drawPoly(this, LastPointsHole, sf::Color::Red);
		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f((float)LastPointsHole[LastPointsHole.size() - 1].X, (float)LastPointsHole[LastPointsHole.size() - 1].Y), sf::Color::Red),
			sf::Vertex(sf::Vector2f(m_InputManager->getMouse().getWindowPosition()), sf::Color::Red)
		};
		this->draw(line, 2, sf::Lines);
	}

	for( size_t i(0); i < Polygons.size(); i++ )
		drawPoly(this, Polygons[i], sf::Color::Blue);
	for( size_t i(0); i < Holes.size(); i++ )
		drawPoly(this, Holes[i], sf::Color::Red);
	if( MergeHoles.size() )
	{
		for( size_t i(0); i < MergeHoles.size(); i++ )
		{
			drawPoly(this, MergeHoles[i], sf::Color::Black);
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f((float)MergeHoles[i][MergeHoles[i].size() - 1].X, (float)MergeHoles[i][MergeHoles[i].size() - 1].Y), sf::Color::Black),
				sf::Vertex(sf::Vector2f((float)MergeHoles[i][0].X, (float)MergeHoles[i][0].Y), sf::Color::Black)
			};
			this->draw(line, 2, sf::Lines);
		}
	}
	if( MergePolys.size() )
	{
		for( size_t i(0); i < MergePolys.size(); i++ )
		{
			drawPoly(this, MergePolys[i], sf::Color::Yellow);
			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f((float)MergePolys[i][MergePolys[i].size() - 1].X, (float)MergePolys[i][MergePolys[i].size() - 1].Y), sf::Color::Yellow),
				sf::Vertex(sf::Vector2f((float)MergePolys[i][0].X, (float)MergePolys[i][0].Y), sf::Color::Yellow)
			};
			this->draw(line, 2, sf::Lines);
		}
	}*/

	/*static bool bLoaded(false);
	static p2t::Polygon* MyPoly = NULL;
	static p2t::Triangles MyTri;
	if( !bLoaded )
	{
		bLoaded = true;
		MyPoly = new p2t::Polygon("crazybox1.bdm");
		MyPoly->triangulation();
		MyTri = MyPoly->triangles();
	}

	for( auto& TempTri : MyTri )
	{
		sf::VertexArray TriVert(sf::Triangles, 3U);
		for( int i(0); i < 3; i++ )
		{
			TriVert[i].position = sf::Vector2f((float)MyPoly->points()[TempTri[i]]->x, (float)MyPoly->points()[TempTri[i]]->y);
			TriVert[i].color = sf::Color(RAND(0, 255), RAND(0, 255), RAND(0, 255), 255);

		}
		this->draw(TriVert);
	}*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// On affiche tout ça à l'écran
	display();
}

gmk::InputManager* SFMLCanvas::getInputManager()
{
	return m_InputManager;
}

bool SFMLCanvas::isEditor()
{
	return false;
}

#ifdef SFGMKR_EDITOR
	bool SFMLCanvas::isPlaying = false;
#else
	bool SFMLCanvas::isPlaying = true;
#endif
	
SFMLCanvas* SFMLCanvas::gameCanvas = 0;
SFMLCanvas* SFMLCanvas::editorCanvas = 0;
Project* SFMLCanvas::project = 0;
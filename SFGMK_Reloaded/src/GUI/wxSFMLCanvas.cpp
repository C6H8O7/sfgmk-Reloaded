wxSFMLCanvas::wxSFMLCanvas(wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style)
	: wxPanel(Parent, Id, Position, Size, Style)
{
	// Test� sous Windows XP seulement (devrait fonctionner sous X11 et
	// les autres versions de Windows - aucune id�e concernant MacOS)
	sf::RenderWindow::create(GetHandle());

	m_fWidth = 1280.0f;
	m_fHeight = 720.0f;
	
	sf::View view;
	view.setCenter(sf::Vector2f(m_fWidth / 2.0f, m_fHeight / 2.0f));
	view.setSize(sf::Vector2f((float)m_fWidth, (float)m_fHeight));

	sf::RenderWindow::setSize(sf::Vector2u(m_fWidth, m_fHeight));
	sf::RenderWindow::setView(view);

	texture.loadFromFile("goomba.png");

	sprite.setTexture(texture);
}

wxSFMLCanvas::~wxSFMLCanvas()
{

}

void wxSFMLCanvas::OnIdle(wxIdleEvent& _event)
{
	// On g�n�re un rafra�chissement du contr�le, afin d'assurer un framerate maximum
	Refresh();
}

void wxSFMLCanvas::OnPaint(wxPaintEvent& _event)
{
	// On pr�pare le contr�le � �tre dessin�
	wxPaintDC dc(this);

	// On laisse la classe d�riv�e se mettre � jour et dessiner dans le contr�le
	OnUpdate();

	// On affiche tout �a � l'�cran
	display();
}

void wxSFMLCanvas::OnEraseBackground(wxEraseEvent& _event)
{

}

void wxSFMLCanvas::OnUpdate()
{
	// On efface la vue
	clear(sf::Color(0, 128, 128));

	sprite.setPosition(0, 0);
	draw(sprite);
}

BEGIN_EVENT_TABLE(wxSFMLCanvas, wxPanel)
EVT_IDLE(wxSFMLCanvas::OnIdle)
EVT_ERASE_BACKGROUND(wxSFMLCanvas::OnEraseBackground)
EVT_PAINT(wxSFMLCanvas::OnPaint)
END_EVENT_TABLE()
ComponentPolygon::ComponentPolygon(GameObject * _parent)
	: GameObjectComponent("Polygon", _parent), m_PolygonNumber(0U), m_HoleNumber(0U), m_TriangleNumber(0U)
{
#ifdef SFGMKR_EDITOR
	OnRegistration();
#endif
}

ComponentPolygon::~ComponentPolygon()
{
}


r_void ComponentPolygon::OnUpdate(SFMLCanvas * _canvas)
{
}

r_void ComponentPolygon::OnDraw(SFMLCanvas * _canvas)
{
	if( _canvas->isEditor() )
	{
		m_Polygon.drawLastPoints(_canvas);
		m_Polygon.drawPolys(_canvas);
		m_Polygon.drawTriangles(_canvas);
		m_Polygon.drawMerge(_canvas);
	}
}

r_void ComponentPolygon::OnMembersUpdate()
{
}

#ifdef SFGMKR_EDITOR
r_void ComponentPolygon::OnRegistration()
{
	beginRegister();

	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Polygons", &m_PolygonNumber, 0, true);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Holes", &m_HoleNumber, 0, true);
	registerProperty(ePROPERTY_TYPE::TYPE_INT, "Triangles", &m_TriangleNumber, 0, true);

	endRegister();
}

r_void ComponentPolygon::OnEditorUpdate()
{
	//Add mouse position as a point
	if( SFMLCanvas::editorCanvas->getInputManager()->getMouse().getButtonState(sf::Mouse::Left) == gmk::eKeyStates::eKEY_PRESSED )
		m_Polygon.addPoint(gmk::Polygon::ePOLYGON_GROUP::ePolygon, SFMLCanvas::editorCanvas->getInputManager()->getMouse().getWorldPosition());
	else if( SFMLCanvas::editorCanvas->getInputManager()->getMouse().getButtonState(sf::Mouse::Right) == gmk::eKeyStates::eKEY_PRESSED )
		m_Polygon.addPoint(gmk::Polygon::ePOLYGON_GROUP::eHole, SFMLCanvas::editorCanvas->getInputManager()->getMouse().getWorldPosition());

	//Merge
	else if( SFMLCanvas::editorCanvas->getInputManager()->getKeyboard().getKeyState(sf::Keyboard::A) == gmk::eKeyStates::eKEY_PRESSED )
		m_Polygon.mergeAll();

	//Triangulation
	else if( SFMLCanvas::editorCanvas->getInputManager()->getKeyboard().getKeyState(sf::Keyboard::Z) == gmk::eKeyStates::eKEY_PRESSED )
		m_Polygon.triangulate();

	m_PolygonNumber = m_Polygon.getPolygonNumber();
	m_HoleNumber = m_Polygon.getHoleNumber();
	m_TriangleNumber = m_Polygon.getTriangleNumber();
}
#endif

r_void ComponentPolygon::OnXMLSave(tinyxml2::XMLElement * _element)
{
}

r_void ComponentPolygon::OnXMLLoad(tinyxml2::XMLElement * _element)
{
}
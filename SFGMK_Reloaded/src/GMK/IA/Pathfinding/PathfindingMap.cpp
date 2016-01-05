namespace gmk
{
	PathfindingMap::PathfindingMap() : m_uiMap(NULL), m_Size(0, 0), m_uiCaseNumber(0U)
	{

	}

	PathfindingMap::~PathfindingMap()
	{
		freeMap();
	}

	r_void PathfindingMap::freeMap()
	{
		if( m_uiMap != NULL )
		{
			free(m_uiMap);
			m_uiMap = NULL;
		}
	}

	r_uint8* PathfindingMap::getMap()
	{
		return m_uiMap;
	}

	const r_vector2i& PathfindingMap::getSize()
	{
		return m_Size;
	}

	const r_uint32& PathfindingMap::getCaseNumber()
	{
		return m_uiCaseNumber;
	}

	r_bool PathfindingMap::loadMapFromFile(const r_int8* _FileName, r_vector2i& _Begin, r_vector2i& _End)
	{
		freeMap();

		FILE* FileToLoad = NULL;
		fopen_s(&FileToLoad, _FileName, "r");
		if( !FileToLoad )
		{
			std::cout << "File " << _FileName << " not found." << std::endl;
			return false;
		}
		
		//Chargement:
		if (SFGMKR_IA_DEBUG)
			std::cout << "Load file " << _FileName << std::endl;

		//Taille de la map
		fscanf_s(FileToLoad, "%d %d", &m_Size.x, &m_Size.y);
		m_uiMap = (r_uint8*)malloc(sizeof(r_uint8) * (m_Size.x * m_Size.y));

		if( m_uiMap == NULL )
		{
			std::cout << "Error" << std::endl;
			return false;
		}
		
		//Begin et end
		r_int8 cBuffer = '\0';

		while( (cBuffer = fgetc(FileToLoad)) != '\n' );
		fscanf_s(FileToLoad, "%d", &_Begin.x);
		cBuffer = fgetc(FileToLoad);
		fscanf_s(FileToLoad, "%d", &_Begin.y);

		while( (cBuffer = fgetc(FileToLoad)) != '\n' );
		fscanf_s(FileToLoad, "%d", &_End.x);
		cBuffer = fgetc(FileToLoad);
		fscanf_s(FileToLoad, "%d", &_End.y);

		while( (cBuffer = fgetc(FileToLoad)) != '\n' );

		//Valeurs des cases
		r_uint32 uiCaseNumber = m_uiCaseNumber = m_Size.x * m_Size.y;
		r_int32 iIteration(0);
		r_int32 iX(0), iY(0);

		while( (cBuffer = fgetc(FileToLoad)) != EOF && uiCaseNumber > 0U )
		{
			if( !(cBuffer == '\n') )
			{
				uiCaseNumber--;

				m_uiMap[iIteration] = cBuffer + ASCII_NUMBER_GAP;
				
				iIteration++;
				iX++;
			}
			else
			{
				iY++;
				iX = 0;
			}
		}
		
		fclose(FileToLoad);
		return true;
	}

	r_void PathfindingMap::setTerrainType(const r_int32& _X, const r_int32& _Y, const ePATHFINDING_TERRAIN_TYPE& _Type)
	{
		r_int32 iIndex = getIndex(r_vector2i(_X, _Y));
		if( !(iIndex == eOUT_OF_MAP) )
			m_uiMap[iIndex] = _Type;
	}

	r_void PathfindingMap::draw(sf::RenderTarget * _render, sf::Transform _transform)
	{
		//Draw map
		sf::Vector2f DecalX(0.0f, m_CaseSize);
		sf::Vector2f DecalY(m_CaseSize, 0.0f);
		sf::Vertex LineX[] = { sf::Vertex(sf::Vector2f(0, 0), CASE_OUTLINE_COLOR), sf::Vertex(sf::Vector2f(m_CaseSize * m_Size.x, 0), CASE_OUTLINE_COLOR) };
		sf::Vertex LineY[] = { sf::Vertex(sf::Vector2f(0, 0), CASE_OUTLINE_COLOR), sf::Vertex(sf::Vector2f(0, m_CaseSize * m_Size.y), CASE_OUTLINE_COLOR) };

		for (int i(0); i <= m_Size.y; i++)
		{
			_render->draw(LineX, 2, sf::Lines, _transform);
			LineX[0].position += DecalX;
			LineX[1].position += DecalX;
		}
		for (int i(0); i <= m_Size.x; i++)
		{
			_render->draw(LineY, 2, sf::Lines, _transform);
			LineY[0].position += DecalY;
			LineY[1].position += DecalY;
		}

		//Draw walls
		sf::RectangleShape Case(sf::Vector2f(m_CaseSize - 2.0f, m_CaseSize - 2.0f));
		Case.setFillColor(WALL_COLOR);
		Case.setOutlineThickness(0);

		for (int i(0); i < m_Size.x; i++)
		{
			for (int j(0); j < m_Size.y; j++)
			{
				if (getTerrainType(sf::Vector2i(i, j)) == eWALL)
				{
					Case.setPosition(sf::Vector2f(i * m_CaseSize + 1.0f, j * m_CaseSize + 1.0f));
					_render->draw(Case, _transform);
				}
			}
		}
	}
}
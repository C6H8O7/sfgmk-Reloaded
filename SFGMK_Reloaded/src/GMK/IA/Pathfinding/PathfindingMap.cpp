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


	sf::Uint8* PathfindingMap::getMap()
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
		std::cout << "Load file " << _FileName << std::endl;

		//Taille de la map
		fscanf_s(FileToLoad, "%d %d", &m_Size.x, &m_Size.y);
		m_uiMap = (sf::Uint8*)malloc(sizeof(sf::Uint8) * (m_Size.x * m_Size.y));

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
}
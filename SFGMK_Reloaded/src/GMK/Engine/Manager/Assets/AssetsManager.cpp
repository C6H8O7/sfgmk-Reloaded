namespace gmk
{
	AssetsManager::AssetsManager()
		: m_AssetsKeyword(SFGMKR_ASSETSMANAGER_KEYWORD)
	{
		m_AssetsPath = "../assets/";
	}

	AssetsManager::~AssetsManager()
	{

	}

	AssetsManager* AssetsManager::GetSingleton()
	{
		static AssetsManager singleton;

		return &singleton;
	}

	std::string AssetsManager::getAssetsPath()
	{
		return m_AssetsPath;
	}

	void AssetsManager::setAssetsPath(std::string _path)
	{
		m_AssetsPath = _path;
	}

	std::string AssetsManager::getAssetPath(std::string _path)
	{
		if (_path.find(m_AssetsKeyword) != std::string::npos)
		{
			std::string path = m_AssetsPath + _path.substr(m_AssetsKeyword.size());

			if(SFGMKR_ASSETSMANAGER_DEBUG)
				std::cout << "[INFO] AssetsManager : file " << path << " requested" << std::endl;

			return path;
		}
		else
		{
			if (SFGMKR_ASSETSMANAGER_DEBUG)
				std::cout << "[ERROR] AssetsManager : requested bad asset path" << std::endl;

			return "NULL";
		}
	}

#ifdef SFGMKR_EDITOR
	std::string AssetsManager::createAssetPath(std::string _path)
	{
		size_t i = _path.find_last_of("\\assets\\");

		if (i != std::string::npos)
		{
			std::string asset_path = _path.substr(i + std::string("\\assets\\").size());
			std::string created_path = SFGMKR_ASSETSMANAGER_KEYWORD + asset_path;

			if (SFGMKR_ASSETSMANAGER_DEBUG)
				std::cout << "[INFO] AssetsManager : path " << created_path << " created" << std::endl;

			return created_path;
		}
		else
		{
			if (SFGMKR_ASSETSMANAGER_DEBUG)
				std::cout << "[ERROR] AssetsManager : failed to create path" << std::endl;

			return "NULL";
		}
	}
#endif

}
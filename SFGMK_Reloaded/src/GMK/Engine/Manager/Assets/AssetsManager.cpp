namespace gmk
{
	AssetsManager::AssetsManager()
		: m_AssetsKeyword(SFGMKR_ASSETSMANAGER_KEYWORD)
	{

	}

	AssetsManager::~AssetsManager()
	{

	}

	AssetsManager* AssetsManager::GetSingleton()
	{
		static AssetsManager singleton;

		return &singleton;
	}

	std::string AssetsManager::getAssetPath(std::string _path)
	{
		if (_path.find(m_AssetsKeyword) != std::string::npos)
		{
			std::string assets_path = SFMLCanvas::project->getAssetsPath();

			std::string path = _path;
			
			if(assets_path.size())
				path = assets_path + "\\" + _path.substr(m_AssetsKeyword.size());

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
}
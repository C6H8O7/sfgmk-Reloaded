#include "stdafx.h"

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

	r_string AssetsManager::getAssetPath(r_string _path)
	{
		if (_path.find(m_AssetsKeyword) != r_string::npos)
		{
			r_string assets_path = SFMLCanvas::project->getAssetsPath();

			r_string path = _path;
			
			if (assets_path.size())
			{
#ifndef SFGMKR_ANDROID
				path = assets_path + "\\" + _path.substr(m_AssetsKeyword.size());
#else
				path = "assets/" + _path.substr(m_AssetsKeyword.size());
#endif
			}

			if (SFGMKR_ASSETSMANAGER_DEBUG)
				Debug::Log("[INFO] AssetsManager : file " + _path + " requested: " + path);

			std::replace(path.begin(), path.end(), '\\', '/');

			return path;
		}
		else
		{
			if (SFGMKR_ASSETSMANAGER_DEBUG)
				Debug::Log("[ERROR] AssetsManager : requested bad asset path");

			return "NULL";
		}
	}
}
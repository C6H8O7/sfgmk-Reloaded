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

			std::replace(path.begin(), path.end(), '\\', '/');

			if (SFGMKR_ASSETSMANAGER_DEBUG)
				Debug::Log("[INFO] AssetsManager : file " + _path + " requested");

			return path;
		}
		else
		{
			if (SFGMKR_ASSETSMANAGER_DEBUG)
				Debug::Log("[ERROR] AssetsManager : requested bad asset path");

			return "NULL";
		}
	}

	r_int8*& AssetsManager::getScript(r_string _path, r_bool _reload)
	{
		if (m_Scripts.find(_path) == m_Scripts.end() || _reload)
		{
			if (_reload)
				delete m_Scripts[_path];

			r_string assetPath = getAssetPath(_path);
			m_Scripts[_path] = gmk::loadFile(assetPath);
		}

		return m_Scripts[_path];
	}

	sf::Texture& AssetsManager::getTexture(r_string _path)
	{
		if (m_Textures.find(_path) == m_Textures.end())
		{
			r_string assetPath = getAssetPath(_path);
			m_Textures[_path].loadFromFile(assetPath);
		}

		return m_Textures[_path];
	}

	sf::Font& AssetsManager::getFont(r_string _path)
	{
		if (m_Fonts.find(_path) == m_Fonts.end())
		{
			r_string assetPath = getAssetPath(_path);
			m_Fonts[_path].loadFromFile(assetPath);
		}

		return m_Fonts[_path];
	}
}
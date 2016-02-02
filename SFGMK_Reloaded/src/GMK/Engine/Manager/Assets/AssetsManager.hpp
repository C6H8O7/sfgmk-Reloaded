#ifndef SFGMKR_ASSETSMANAGER_HPP
#define SFGMKR_ASSETSMANAGER_HPP

#include "stdafx.h"

#define SFGMKR_ASSETSMANAGER_KEYWORD "assets:"

namespace gmk
{
	class AssetsManager
	{
	public:

		static AssetsManager* GetSingleton();

		r_string getAssetPath(r_string _path);

		r_int8*& getScript(r_string _path);
		sf::Texture& getTexture(r_string _path);
		sf::Font& getFont(r_string _path);

	protected:

		r_string m_AssetsKeyword;

		std::map<r_string, sf::Texture> m_Textures;
		std::map<r_string, r_int8*> m_Scripts;
		std::map<r_string, sf::Font> m_Fonts;

		AssetsManager();
		~AssetsManager();
	};
}

#endif
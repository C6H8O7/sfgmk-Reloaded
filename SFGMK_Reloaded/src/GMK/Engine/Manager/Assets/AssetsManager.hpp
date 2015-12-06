#ifndef SFGMKR_ASSETSMANAGER_HPP
#define SFGMKR_ASSETSMANAGER_HPP

#define SFGMKR_ASSETSMANAGER_KEYWORD "assets:"

namespace gmk
{
	class AssetsManager
	{
	public:

		static AssetsManager* GetSingleton();

		std::string getAssetPath(std::string _path);

	protected:

		std::string m_AssetsKeyword;

		AssetsManager();
		~AssetsManager();
	};
}

#endif
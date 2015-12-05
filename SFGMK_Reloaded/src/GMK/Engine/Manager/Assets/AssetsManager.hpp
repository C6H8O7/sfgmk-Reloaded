#ifndef SFGMKR_ASSETSMANAGER_HPP
#define SFGMKR_ASSETSMANAGER_HPP

#define SFGMKR_ASSETSMANAGER_DEBUG true

#define SFGMKR_ASSETSMANAGER_KEYWORD "assets:"

namespace gmk
{
	class AssetsManager
	{
	public:

		static AssetsManager* GetSingleton();

		std::string getAssetsPath();
		void setAssetsPath(std::string _path);

		std::string getAssetPath(std::string _path);

#ifdef SFGMKR_EDITOR
		std::string createAssetPath(std::string _path);
#endif

	protected:

		std::string m_AssetsKeyword;

		std::string m_AssetsPath;

		AssetsManager();
		~AssetsManager();
	};
}

#endif
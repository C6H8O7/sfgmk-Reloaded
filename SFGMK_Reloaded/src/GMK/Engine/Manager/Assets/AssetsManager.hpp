#ifndef SFGMKR_ASSETSMANAGER_HPP
#define SFGMKR_ASSETSMANAGER_HPP

#define SFGMKR_ASSETSMANAGER_KEYWORD "assets:"

namespace gmk
{
	class AssetsManager
	{
	public:

		static AssetsManager* GetSingleton();

		r_string getAssetPath(r_string _path);

	protected:

		r_string m_AssetsKeyword;

		AssetsManager();
		~AssetsManager();
	};
}

#endif
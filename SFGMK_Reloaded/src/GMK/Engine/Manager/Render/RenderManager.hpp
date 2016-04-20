#ifndef SFGMKR_RENDERMANAGER_HPP
#define SFGMKR_RENDERMANAGER_HPP

#include "stdafx.h"

namespace gmk
{
	class RenderManager
	{
	public:

		static RenderManager* GetInstance();

		r_void registerPostShader(sf::Shader* _postShader);
		r_void unregisterPostShader(sf::Shader* _postShader);
		r_void registerOneShotPostShader(sf::Shader* _postShader);

		r_void applyPostShaders(sf::RenderTexture* _renderTexture);

	private:

		RenderManager();
		~RenderManager();

		gmk::vector<sf::Shader*> m_postShaders;
		gmk::vector<sf::Shader*> m_oneShotPostShaders;
	};
}

#endif
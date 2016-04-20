#include "stdafx.h"

namespace gmk
{
	RenderManager::RenderManager()
	{

	}

	RenderManager::~RenderManager()
	{
		
	}

	RenderManager* RenderManager::GetInstance()
	{
		static RenderManager instance;
		return &instance;
	}

	r_void RenderManager::registerPostShader(sf::Shader* _postShader)
	{
		m_postShaders.push_back(_postShader);
	}

	r_void RenderManager::unregisterPostShader(sf::Shader* _postShader)
	{
		m_postShaders.push_back(_postShader);
	}

	r_void RenderManager::registerOneShotPostShader(sf::Shader* _postShader)
	{
		m_oneShotPostShaders.push_back(_postShader);
	}

	r_void RenderManager::applyPostShaders(sf::RenderTexture* _renderTexture)
	{
		sf::Sprite sprite(_renderTexture->getTexture());

		for (r_uint32 i = 0; i < m_postShaders.size(); i++)
		{
			_renderTexture->draw(sprite, m_postShaders[i]);
			sprite.setTexture(_renderTexture->getTexture(), true);
		}

		for (r_uint32 i = 0; i < m_oneShotPostShaders.size(); i++)
		{
			_renderTexture->draw(sprite, m_oneShotPostShaders[i]);
			sprite.setTexture(_renderTexture->getTexture(), true);
		}

		m_oneShotPostShaders.clear();
	}
}
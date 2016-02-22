#include "stdafx.h"

namespace gmk
{
	Sprite::Sprite()
	{

	}

	Sprite::Sprite(std::string _asset, r_bool _isAnim)
	{
		gmk::AssetsManager* assetsman = gmk::AssetsManager::GetSingleton();

		m_isAnim = _isAnim;
		m_Animation = 0;

		if( m_isAnim )
			setAnimation(assetsman->getSpriteAnimation(_asset));
		else
			setTexture(assetsman->getTexture(_asset), true);
	}

	Sprite::~Sprite()
	{
		if( m_Animation )
			delete m_Animation;
	}

	SpriteAnimation* Sprite::getAnimation()
	{
		return m_Animation;
	}

	r_void Sprite::setAnimation(gmk::SpriteAnimation& _animation)
	{
		if( m_isAnim && m_Animation )
		{
			delete m_Animation;
			m_Animation = 0;
		}

		m_Animation = new SpriteAnimation(_animation);

		m_isAnim = true;

		m_Animation->update(*this, 0.0f);
	}

	r_void Sprite::deleteAnimation()
	{
		if( m_isAnim && m_Animation )
		{
			m_isAnim = false;
			delete m_Animation;
			m_Animation = NULL;
		}
	}

	r_bool Sprite::getIsAnimation()
	{
		return m_isAnim;
	}

	r_void Sprite::setRelativOrigin(r_float _rox, r_float _roy)
	{
		const sf::IntRect& rec = getTextureRect();

		return setOrigin(rec.width * _rox, rec.height * _roy);
	}

	sf::Vector2f Sprite::getCenter()
	{
		return sf::Vector2f(getTextureRect().width * 0.5f, getTextureRect().height * 0.5f);
	}

	sf::Vector2f Sprite::getSize()
	{
		return sf::Vector2f(getGlobalBounds().width, getGlobalBounds().height);
	}

	r_void Sprite::finalizeSprite(r_float _timeDelta)
	{
		if( m_isAnim && m_Animation )
			m_Animation->update(*this, _timeDelta);
	}

	gmk::Sprite& Sprite::finalize(r_float _timeDelta)
	{
		finalizeSprite(_timeDelta);

		return *this;
	}

	r_void Sprite::setLoop(r_bool _loop)
	{
		if( m_Animation )
			m_Animation->setLoop(_loop);
	}

	r_bool Sprite::getLoop()
	{
		if( m_Animation )
			return m_Animation->getLoop();

		return false;
	}

	r_void Sprite::pause()
	{
		if (m_Animation)
			m_Animation->pause();
	}

	r_void Sprite::stop()
	{
		if (m_Animation)
			m_Animation->stop();
	}

	r_void Sprite::play()
	{
		if (m_Animation)
			m_Animation->play();
	}
}
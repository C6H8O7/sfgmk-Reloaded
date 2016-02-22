#include "stdafx.h"

namespace gmk
{
	SpriteAnimation::SpriteAnimation()
	{

	}

	SpriteAnimation::SpriteAnimation(gmk::SpriteAnimation& _copy)
	{
		m_isLoop = _copy.m_isLoop;
		m_fTimer = _copy.m_fTimer;
		m_iCurrentFrame = _copy.m_iCurrentFrame;
		m_isPlaying = _copy.m_isPlaying;

		m_Frames = _copy.m_Frames;
	}

	SpriteAnimation::~SpriteAnimation()
	{
		freeFrames();
	}

	r_void SpriteAnimation::update(gmk::Sprite& _sprite, r_float _timeDelta)
	{
		r_int32 currentFrame = m_iCurrentFrame;

		if(m_isPlaying)
			m_fTimer += _timeDelta;

		while( m_fTimer >= m_Frames[m_iCurrentFrame]->duration )
		{
			m_fTimer -= m_Frames[m_iCurrentFrame++]->duration;

			if( m_iCurrentFrame >= (r_int32)m_Frames.size() )
			{
				if( m_isLoop )
					m_iCurrentFrame = 0;
				else
					m_iCurrentFrame = (r_int32)m_Frames.size() - 1;
			}
		}

		if (m_iCurrentFrame != currentFrame || m_fTimer == 0.0f)
		{
			_sprite.setTexture(*m_Frames[m_iCurrentFrame]->texture, true);

			if(m_Frames[m_iCurrentFrame]->rectangleUsed)
				_sprite.setTextureRect(m_Frames[m_iCurrentFrame]->rectangle);
		}
	}

	r_void SpriteAnimation::freeFrames()
	{
		for(r_uint32 i = 0; i < m_Frames.size(); i++)
			delete m_Frames[i];
	}

	r_void SpriteAnimation::addFrame(std::string _asset, r_float _duration, sf::IntRect _rectangle)
	{
		sf::Texture& texture = gmk::AssetsManager::GetSingleton()->getTexture(_asset);

		gmk::SpriteAnimationFrame* frame = new gmk::SpriteAnimationFrame();

		frame->texture = &texture;
		frame->duration = _duration;

		frame->rectangle = _rectangle;

		if (!_rectangle.width && !_rectangle.height)
			frame->rectangleUsed = false;
		else
			frame->rectangleUsed = true;

		m_Frames.push_back(frame);
	}

	r_void SpriteAnimation::setLoop(r_bool _loop)
	{
		m_isLoop = _loop;
	}

	r_bool SpriteAnimation::getLoop()
	{
		return m_isLoop;
	}

	r_void SpriteAnimation::loadFromFile(std::string _file)
	{
		tinyxml2::XMLDocument doc;
		doc.LoadFile(_file.c_str());

		tinyxml2::XMLElement* config = doc.FirstChildElement("Config");

		r_int32 isSpriteSheet = 0;
		config->QueryIntAttribute("isSpriteSheet", &isSpriteSheet);

		r_int32 nbFrames = 1;
		config->QueryIntAttribute("nbFrames", &nbFrames);

		r_int32 isLoop = 1;
		config->QueryIntAttribute("isLoop", &isLoop);

		if (isLoop) m_isLoop = true;
		else m_isLoop = false;

		if(isSpriteSheet)
		{
			tinyxml2::XMLElement* spriteSheet = doc.FirstChildElement("SpriteSheet");

			r_int32 width = spriteSheet->IntAttribute("width");
			r_int32 height = spriteSheet->IntAttribute("height");
			r_int32 nbWidth = spriteSheet->IntAttribute("nbWidth");
			r_int32 nbHeight = spriteSheet->IntAttribute("nbHeight");

			r_int32 w = width / nbWidth;
			r_int32 h = height / nbHeight;

			tinyxml2::XMLElement* frames = doc.FirstChildElement("Frames");
			tinyxml2::XMLElement* frame = frames->FirstChildElement("Frame");

			for( r_int32 i = 0; i < nbFrames; i++ )
			{
				std::string filePath = frame->Attribute("asset");
				r_float duration = frame->FloatAttribute("duration");

				r_int32 x = i % nbWidth;
				r_int32 y = i / nbWidth;

				addFrame(filePath, duration, sf::IntRect(x * w, y * h, w, h));

				frame = frame->NextSiblingElement("Frame");
			}
		}
		else
		{
			tinyxml2::XMLElement* frames = doc.FirstChildElement("Frames");
			tinyxml2::XMLElement* frame = frames->FirstChildElement("Frame");

			for (r_int32 i = 0; i < nbFrames; i++)
			{
				std::string filePath = frame->Attribute("asset");
				r_float duration = frame->FloatAttribute("duration");

				addFrame(filePath, duration);

				frame = frame->NextSiblingElement("Frame");
			}
		}
	}

	void SpriteAnimation::pause()
	{
		m_isPlaying = false;
	}

	void SpriteAnimation::stop()
	{
		m_fTimer = 0.0f;
		m_iCurrentFrame = 0;
		m_isPlaying = false;
	}

	void SpriteAnimation::play()
	{
		m_isPlaying = true;
	}
}
/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		25/11/2014
	@brief		Fichier d'entête de SpriteAnimation

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_SPRITEANIMATION_HPP
#define SFGMKR_SPRITEANIMATION_HPP

#include "stdafx.h"

namespace gmk
{
	class Sprite;

	struct SpriteAnimationFrame
	{
		sf::Texture *texture;
		r_float duration;
		sf::IntRect rectangle;
		r_bool rectangleUsed;
	};

	class SpriteAnimation
	{
		public:

			SpriteAnimation();
			SpriteAnimation(gmk::SpriteAnimation& _copy);
			~SpriteAnimation();

			r_void freeFrames();

			r_void update(gmk::Sprite& _sprite, r_float _timeDelta);

			r_void addFrame(std::string _asset, r_float _duration, sf::IntRect _rectangle = sf::IntRect());

			r_void setLoop(r_bool _loop);
			r_bool getLoop();

			r_void loadFromFile(std::string _file);

			r_void pause();
			r_void stop();
			r_void play();

		private:

			r_bool m_isLoop = true;
			r_bool m_isPlaying = true;

			r_float m_fTimer = 0.0f;
			r_int32 m_iCurrentFrame = 0;

			std::vector<gmk::SpriteAnimationFrame*> m_Frames;
	};
}


#endif
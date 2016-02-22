/*--------------------------------------------------------------------------------------------------

	@author		GMK
	@date		25/11/2014
	@brief		Fichier d'entête de Sprite

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMKR_SPRITE_HPP
#define SFGMKR_SPRITE_HPP

#include "stdafx.h"

namespace gmk
{
	class Sprite : public sf::Sprite
	{
		public:

			Sprite();
			Sprite(std::string _asset, r_bool _isAnim);
			~Sprite();

			SpriteAnimation* getAnimation();
			r_void setAnimation(gmk::SpriteAnimation& _animation);
			r_void deleteAnimation();
			r_bool getIsAnimation();

			r_void setRelativOrigin(r_float _rox, r_float _roy);

			sf::Vector2f getCenter();
			sf::Vector2f getSize();

			gmk::Sprite& finalize(r_float _timeDelta);

			r_void setLoop(r_bool _loop);
			r_bool getLoop();

			r_void pause();
			r_void stop();
			r_void play();

		protected:

			r_void finalizeSprite(r_float _timeDelta);

			r_bool m_isAnim = false;
			SpriteAnimation* m_Animation = 0;
	};
}


#endif
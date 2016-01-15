/*--------------------------------------------------------------------------------------------------

@author		GMK
@date		13/11/2015
@brief		Prise en charge des maps exportees par Tiled

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_TILEDMAP_HPP
#define SFGMK_TILEDMAP_HPP

#include "stdafx.h"

namespace gmk
{
	struct TiledLayer
	{
		r_string name;
		r_int32 width, height, alpha;
		sf::RenderTexture texture;
		sf::Sprite sprite;
	};

	class TiledMap
	{
		public:

			TiledMap();
			~TiledMap();

			r_bool loadFromFile(r_string _filePath);

			r_void unload();

			r_void draw(sf::RenderTarget* _render, sf::Transform _transform);

		protected:

			r_int32 m_width, m_height;
			r_int32 m_tileWidth, m_tileHeight;

			r_int32 m_firstGid;
			r_string m_name;
			r_int32 m_spacing, m_margin, m_tileCount;

			r_string m_source;
			r_int32 m_sourceWidth, m_sourceHeight;

			sf::Texture *m_texture;

			sf::Sprite *m_tiles;

			gmk::vector<TiledLayer*> m_layers;
	};
}

#endif
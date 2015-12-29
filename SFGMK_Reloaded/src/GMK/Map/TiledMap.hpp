/*--------------------------------------------------------------------------------------------------

@author		GMK
@date		13/11/2015
@brief		Prise en charge des maps exportees par Tiled

--------------------------------------------------------------------------------------------------*/

#ifndef SFGMK_TILEDMAP_HPP
#define SFGMK_TILEDMAP_HPP

namespace gmk
{
	struct TiledLayer
	{
		std::string name;
		int width, height, alpha;
		sf::RenderTexture texture;
		sf::Sprite sprite;
	};

	class TiledMap
	{
		public:

			TiledMap();
			~TiledMap();

			bool loadFromFile(std::string& _filePath);

			void unload();

			void draw(sf::RenderTarget* _render, sf::Transform _transform);

		protected:

			int m_width, m_height;
			int m_tileWidth, m_tileHeight;

			int m_firstGid;
			std::string m_name;
			int m_spacing, m_margin, m_tileCount;

			std::string m_source;
			int m_sourceWidth, m_sourceHeight;

			sf::Texture *m_texture;

			sf::Sprite *m_tiles;

			gmk::vector<TiledLayer*> m_layers;
	};
}

#endif
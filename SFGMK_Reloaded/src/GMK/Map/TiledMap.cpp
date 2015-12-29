#include "TiledMap.hpp"
namespace gmk
{
	TiledMap::TiledMap() : m_texture(0), m_tiles(0)
	{

	}

	TiledMap::~TiledMap()
	{
		unload();
	}

	bool TiledMap::loadFromFile(std::string& _filePath)
	{
		unload();

		tinyxml2::XMLDocument mapFile;
		mapFile.LoadFile(_filePath.c_str());

		tinyxml2::XMLElement *map = mapFile.FirstChildElement("map");

		m_width = map->IntAttribute("width");
		m_height = map->IntAttribute("height");
		m_tileWidth = map->IntAttribute("tilewidth");
		m_tileHeight = map->IntAttribute("tileheight");

		tinyxml2::XMLElement *tileset = map->FirstChildElement("tileset");

		m_firstGid = tileset->IntAttribute("firstgid");
		m_name = tileset->Attribute("name");
		m_spacing = tileset->IntAttribute("spacing");
		m_margin = tileset->IntAttribute("margin");
		m_tileCount = tileset->IntAttribute("tilecount");

		tinyxml2::XMLElement *image = tileset->FirstChildElement("image");

		m_source = image->Attribute("source");
		m_sourceWidth = image->IntAttribute("width");
		m_sourceHeight = image->IntAttribute("height");

		std::string resName = m_source;

		std::string resPath = _filePath.substr(0, _filePath.find_last_of('\\') + 1) + resName;

		m_texture = new sf::Texture();
		m_texture->loadFromFile(resPath);
		
		m_tiles = new sf::Sprite[m_tileCount];

		int nW = (m_sourceWidth + m_spacing - 2 * m_margin) / m_tileWidth;
		int nH = (m_sourceHeight + m_spacing - 2 * m_margin) / m_tileHeight;

		sf::IntRect rect;
		rect.width = m_tileWidth;
		rect.height = m_tileHeight;

		int k = 0;
		for (int j = 0; j < nH; j++)
		{
			for (int i = 0; i < nW; i++)
			{
				rect.left = m_margin + i * (m_tileWidth + m_spacing);
				rect.top = m_margin + j * (m_tileHeight + m_spacing);

				m_tiles[k].setTexture(*m_texture);
				m_tiles[k].setTextureRect(rect);

				k++;
			}
		}

		tinyxml2::XMLElement *layerElement = map->FirstChildElement("layer");
		while(layerElement)
		{
			TiledLayer *tiledLayer = new TiledLayer;

			tiledLayer->name = layerElement->Attribute("name");
			tiledLayer->width = layerElement->IntAttribute("width");
			tiledLayer->height = layerElement->IntAttribute("height");
			
			float opacity = layerElement->FloatAttribute("opacity");
			
			if (opacity == 0.0f)
				opacity = 1.0f;

			tiledLayer->alpha = (int)(opacity * 255);

			tinyxml2::XMLElement *tileElement = layerElement->FirstChildElement("data")->FirstChildElement("tile");

			tiledLayer->texture.create(tiledLayer->width * m_tileWidth, tiledLayer->height * m_tileHeight);

			k = 0;

			while (tileElement)
			{
				int x = (k % tiledLayer->width) * m_tileWidth;
				int y = (k / tiledLayer->height) * m_tileHeight;

				int gid = tileElement->IntAttribute("gid") - m_firstGid;

				m_tiles[gid].setPosition((float)x, (float)y);
				tiledLayer->texture.draw(m_tiles[gid]);

				k++;

				tileElement = tileElement->NextSiblingElement("tile");
			}

			tiledLayer->texture.display();
			tiledLayer->sprite.setTexture(tiledLayer->texture.getTexture());

			m_layers.push_back(tiledLayer);

			layerElement = layerElement->NextSiblingElement("layer");
		}

		return true;
	}

	void TiledMap::unload()
	{
		if (m_tiles)
		{
			delete[] m_tiles;

			m_layers.deleteAndClear();

			delete m_texture;

			m_tiles = 0;
		}
	}

	void TiledMap::draw(sf::RenderTarget* _render, sf::Transform _transform)
	{
		for (unsigned int i = 0; i < m_layers.getElementNumber(); i++)
			_render->draw(m_layers[i]->sprite, _transform);
	}
}
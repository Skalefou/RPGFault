#include "map.hpp"

Map::Map() : scrollingX(0), scrollingY(0), m_LimitMapX(0), m_LimitMapY(0)
{

}

sf::Vector2f Map::mousePositionWithScrolling(const sf::Vector2i localPosition, sf::RenderWindow &window) const
{
	sf::Vector2f mousePosition = window.mapPixelToCoords(localPosition);
	mousePosition.x += (scrollingX * 32);
	mousePosition.y += (scrollingY * 32);
	return mousePosition;
}

void Map::placeTile(const signed int idSelector, sf::RenderWindow& window)
{
	const sf::Vector2f mousePosition = mousePositionWithScrolling(sf::Mouse::getPosition(window), window);
	const bool x = ((unsigned int)(mousePosition.x / 32) >= m_LimitMapX), y = ((unsigned int)(mousePosition.y / 32) >= m_LimitMapY), limitMouse = (mousePosition.x >= 0 && mousePosition.y >= 0 && mousePosition.x < 1920 && mousePosition.y < 1080);
	if (limitMouse && (x || y))
	{
		const unsigned int differenceX = ((unsigned int)(mousePosition.x / 32) + 1 - m_LimitMapX), differenceY = ((unsigned int)(mousePosition.y / 32) + 1 - m_LimitMapY);
		if (x)
		{
			for (unsigned int x = m_LimitMapX; x < m_LimitMapX + differenceX; x++)
			{
				m_map.push_back(std::vector<signed int>());
				if (m_LimitMapY > 0)
					for (unsigned int y = 0; y < m_LimitMapY; y++)
						m_map[x].push_back(-1);
			}
			m_LimitMapX += differenceX;
		}
		if (y)
		{
			for (unsigned int x = 0; x < std::size(m_map); x++)
				for (unsigned int y = m_LimitMapY; y < m_LimitMapY + differenceY; y++)
					m_map[x].push_back(-1);
			m_LimitMapY += differenceY;
		}
	}
	if(limitMouse)
		m_map[((unsigned int)(mousePosition.x / 32))][((unsigned int)(mousePosition.y / 32))] = idSelector;
}

void Map::deleteTile(sf::RenderWindow& window)
{
	const sf::Vector2f mousePosition = mousePositionWithScrolling(sf::Mouse::getPosition(window), window);
	if ((unsigned int)(mousePosition.x / 32) < m_LimitMapX && (unsigned int)(mousePosition.y / 32) < m_LimitMapY)
		placeTile(-1, window);
}

void Map::draw(sf::RenderWindow& window, Texture& tileTexture) const
{
	for (unsigned int x = 0; x < m_LimitMapX; x++)
		for (unsigned int y = 0; y < m_LimitMapY; y++)
			if (m_map[x][y] >= 0)
				tileTexture.draw(m_map[x][y], (float)((x * 32) - (scrollingX * 32)), (float)((y * 32) - (scrollingY * 32)), window);
}

void Map::mainMap(const signed int idSelector, const bool inventoryOn, sf::RenderWindow& window, Texture& tileTexture)
{
	if (!(inventoryOn))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && idSelector >= 0)
			placeTile(idSelector, window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			deleteTile(window);
	}
	if(m_LimitMapX > 0 && m_LimitMapY > 0)
		draw(window, tileTexture);
}



#include "map.hpp"
#include <iostream>

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

void Map::PlaceTile(const signed int idSelector, sf::RenderWindow& window)
{
	const sf::Vector2f mousePosition = mousePositionWithScrolling(sf::Mouse::getPosition(window), window);
	if ((unsigned int)(mousePosition.x / 32) > m_LimitMapX || (unsigned int)(mousePosition.y / 32) > m_LimitMapY)
	{
		const unsigned int differenceX = (unsigned int)((mousePosition.x / 32) - m_LimitMapX), differenceY = (unsigned int)((mousePosition.y / 32) - m_LimitMapY);
		m_map.resize(m_LimitMapX + differenceX);
		for (unsigned int x = 0; x < m_map.size(); x++)
			m_map[x].resize((m_LimitMapY + differenceY), -1);
		m_LimitMapX += differenceX;
		m_LimitMapY += differenceY;
	}
	m_map[((unsigned int)(mousePosition.x / 32)) - 1][((unsigned int)(mousePosition.y / 32)) - 1] = idSelector;
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
			PlaceTile(idSelector, window);
	}
	draw(window, tileTexture);
}
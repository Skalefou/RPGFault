#include "map.hpp"

Map::Map() : scrollingX(0), scrollingY(0), m_LimitMapX(0), m_LimitMapY(0), m_selection(false), m_selectionRect(sf::Vector2f(10.f, 10.f))
{
	m_selectionRect.setFillColor(sf::Color(0, 0, 0, 0));
	m_selectionRect.setOutlineThickness(3.f);
	m_selectionRect.setOutlineColor(sf::Color(255, 255, 255));
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

void Map::selectionTile(sf::RenderWindow& window)
{
	static bool unclick = false;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		if (!(unclick))
		{
			sf::Vector2i firstSelection = sf::Mouse::getPosition(window);
			m_firstSelection = window.mapPixelToCoords(firstSelection);
		}
		unclick = true;
	}
	else if (unclick)
	{
		sf::Vector2i secondlySelection = sf::Mouse::getPosition(window);
		m_secondlySelection = window.mapPixelToCoords(secondlySelection);
		if (((signed int)(m_firstSelection.x / 32) != (signed int)(m_secondlySelection.x / 32)) || ((signed int)(m_firstSelection.y / 32) != (signed int)(m_secondlySelection.y / 32)))
		{
			
			if (m_secondlySelection.x < m_firstSelection.x || m_secondlySelection.y < m_firstSelection.y)
			{
				m_secondlySelection.x -= 32;
				m_firstSelection.x += 32;
				m_secondlySelection.y -= 32;
				m_firstSelection.y += 32;
			}
			signed int fx = (signed int)(m_firstSelection.x / 32);
			signed int fy = (signed int)(m_firstSelection.y / 32);
			signed int sx = (signed int)((m_secondlySelection.x / 32) + 1);
			signed int sy = (signed int)((m_secondlySelection.y / 32) + 1);
			m_selectionRect.setSize(sf::Vector2f((float)((sx - fx) * 32 - 3), (float)((sy - fy) * 32 - 3)));
			m_selectionRect.setPosition(sf::Vector2f((float)(fx * 32 + 3), (float)(fy * 32 + 3)));

			m_selection = true;
		}
		else
			m_selection = false;
		unclick = false;
	}
}

void Map::drawTile(sf::RenderWindow& window, Texture& tileTexture) const
{
	for (unsigned int x = 0; x < m_LimitMapX; x++)
		for (unsigned int y = 0; y < m_LimitMapY; y++)
			if (m_map[x][y] >= 0)
				tileTexture.draw(m_map[x][y], (float)((x * 32) - (scrollingX * 32)), (float)((y * 32) - (scrollingY * 32)), window);
}



void Map::drawSelection(sf::RenderWindow& window)
{
	static sf::Clock clock;
	static bool color = true;
	if (clock.getElapsedTime() >= sf::milliseconds(750))
	{
		if (color)
			m_selectionRect.setOutlineColor(sf::Color(0, 0, 0));
		else
			m_selectionRect.setOutlineColor(sf::Color(255, 255, 255));
		color = !color;
		clock.restart();
	}
	window.draw(m_selectionRect);
}

void Map::mainMap(const signed int idSelector, const bool inventoryOn, sf::RenderWindow& window, Texture& tileTexture)
{
	if (!(inventoryOn))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && idSelector >= 0)
			placeTile(idSelector, window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			deleteTile(window);

			selectionTile(window);
	}
	if(m_LimitMapX > 0 && m_LimitMapY > 0)
		drawTile(window, tileTexture);
	if(m_selection && !(inventoryOn))
		drawSelection(window);
}



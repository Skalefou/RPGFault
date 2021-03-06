#ifndef MAP_HPP
#define MAP_HPP
#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "texture.hpp"

struct TILEPRESENT
{
	unsigned int id, numberOfTile;
};

class Map
{
public:
	Map();
	sf::Vector2f mousePositionWithScrolling(const sf::Vector2i localPosition, sf::RenderWindow& window) const;
	void placeTile(const signed int idSelector, sf::RenderWindow &window);
	void deleteTile(sf::RenderWindow &window);
	void selectionTile(sf::RenderWindow& window);
	void drawTile(sf::RenderWindow& window, Texture& tileTexture) const;
	void drawSelection(sf::RenderWindow &window);
	void mainMap(const signed int idSelector, const bool inventoryOn, sf::RenderWindow &window, Texture& tileTexture);
private:
	std::vector<TILEPRESENT> m_tilePresent;
	unsigned int m_LimitMapX, m_LimitMapY, scrollingX, scrollingY;
	std::vector<std::vector<signed int>> m_map;
	sf::Vector2f m_firstSelection, m_secondlySelection;
	bool m_selection;
	sf::RectangleShape m_selectionRect;
};

#endif
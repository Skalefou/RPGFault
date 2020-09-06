#ifndef TILE_HPP
#define TILE_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Tile {
protected:
	std::vector<sf::Texture> m_texture;
	std::vector<sf::Sprite> m_sprite;
};

class TileRPG : public Tile {
public:
	TileRPG();
	void draw(int id, float x, float y, sf::RenderWindow& window);
};

#endif
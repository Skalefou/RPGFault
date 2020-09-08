#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include "tile.hpp"

void TileRPG::draw(int id, float x, float y, sf::RenderWindow& window) {
	m_sprite[id].setPosition(sf::Vector2f(x, y));
	window.draw(m_sprite[id]);
}


TileRPG::TileRPG() {
	std::ifstream file { "data/tileRPGList.rf" };
	std::string line{ "" }, access { "" };
	sf::Texture texture;
	sf::Sprite sprite;
	unsigned int i = 0;

	while (std::getline(file, line)) {
		m_texture.push_back(texture);
		m_sprite.push_back(sprite);
		access = "data/" + line;
		m_texture[i].loadFromFile(access);
		i++;
	}
	for(int y = 0; y < i; y++)
		m_sprite[y].setTexture(m_texture[y]);
}
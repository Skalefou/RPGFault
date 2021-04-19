#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>

class Texture
{
public:
	Texture(const std::string fileAccess);
	std::string nameInit(std::string line, const char firstCharacter, const char lastCharacter) const;
	std::string ascendName(const unsigned int id) const;
	void draw(const unsigned int id, const float x, const float y, sf::RenderWindow& window);
	unsigned int ascendNumberOfTexture() const;
	sf::FloatRect ascendSize(const unsigned int id) const;
protected:
	std::vector<sf::Texture> m_texture;
	std::vector<sf::Sprite> m_sprite;
	std::vector<std::string> m_name;
	unsigned int m_numberOfTexture;
};

#endif
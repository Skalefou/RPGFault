#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <string>

enum {GRASS, WATER}; //id tile

class Texture
{
public:
	unsigned int init(std::string fileAccess);
	std::string nameInit(std::string line, const char firstCharacter, const char lastCharacter) const;
	void draw(unsigned int id, float x, float y, sf::RenderWindow& window);
protected:
	std::vector<sf::Texture> m_texture;
	std::vector<sf::Sprite> m_sprite;
	std::vector<std::string> m_name;
	unsigned int m_numberOfTexture;
};

class TextureAll
{
public:
	TextureAll(std::string tileFile);
	Texture tile;
};

#endif
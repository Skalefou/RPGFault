#include "texture.hpp"

Texture::Texture(std::string fileAccess)
{
	std::ifstream file{ fileAccess };
	std::string line{ "" }, access{ "" };
	sf::Texture texture;
	sf::Sprite sprite;

	while (std::getline(file, line))
	{
		m_texture.push_back(texture);
		m_sprite.push_back(sprite);
		m_name.push_back("");
		access = "data/" + line;
		m_texture[m_numberOfTexture].loadFromFile(access);
		m_name[m_numberOfTexture] = nameInit(line, '/', '.');
		m_numberOfTexture++;
	}
	for (unsigned int y = 0; y < m_numberOfTexture; y++)
		m_sprite[y].setTexture(m_texture[y]);
}

std::string Texture::nameInit(std::string line, const char firstCharacter, const char lastCharacter) const
{
	unsigned int i = 0;
	bool t = true;
	while (t) 
	{
		if (line[i] != firstCharacter)
			i++;
		else {
			line.erase(0, (i + 1));
			t = false;
		}
	}
	i = 0;
	t = true;
	while (t) 
	{
		if (line[i] != lastCharacter)
			i++;
		else {
			line.erase(i);
			t = false;
		}
	}
	return line;
}

void Texture::draw(unsigned int id, float x, float y, sf::RenderWindow& window)
{
	m_sprite[id].setPosition(sf::Vector2f(x, y));
	window.draw(m_sprite[id]);
}

unsigned int Texture::ascendNumberOfTexture() const
{
	return m_numberOfTexture;
}

sf::FloatRect Texture::ascendSize(unsigned int id) const
{
	return m_sprite[id].getGlobalBounds();
}

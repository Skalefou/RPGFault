#include "inventory.hpp"
#include <sstream>
#include <iostream>


Inventory::Inventory(std::string fontFile) : m_inventory(false), m_page(0), m_selector(-1)
{
	m_font.loadFromFile(fontFile);
	m_textNameTexture.setFont(m_font);
	m_textPage.setFont(m_font);
	m_textNameTexture.setCharacterSize(16);
	m_textPage.setCharacterSize(48);
	m_textPage.setString("Page : 0");
	m_textPage.setPosition(sf::Vector2f(((1920/2) - (m_textPage.getGlobalBounds().width/2)), (1080 - m_textPage.getGlobalBounds().height)));
}

void Inventory::changeInventory(Screen &screen)
{
	static bool ePress = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !ePress) {
		m_inventory = !m_inventory;
		ePress = true;
		if(m_inventory == true) 
		{
			sf::Color color(128, 128, 128, 128);
			screen.changeColorBackground(color);
		}
		else
		{
			sf::Color color(0, 0, 0, 255);
			screen.changeColorBackground(color);
		}
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::E) && ePress)
		ePress = false;
}

void Inventory::changeTextPage()
{
	std::string text = "Page : ";
	std::ostringstream oss;
	oss << text << m_page;
	m_textPage.setString(oss.str());
}

void Inventory::changePage(Texture& tileTexture)
{
	static unsigned int i = 5;
	if (i >= 10)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && tileTexture.ascendNumberOfTexture() > ((m_page + 1) * 28 * 12))
		{
			m_page++;
			changeTextPage();
			i = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && m_page > 0)
		{
			m_page--;
			changeTextPage();
			i = 0;
		}
	}
	i++;
}

signed int Inventory::collisionMouseTexture(Texture& tileTexture, sf::RenderWindow& window) const
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosition = window.mapPixelToCoords(localPosition);
	for (signed int y = 0; y < 12; y++)
		for (signed int x = 0; x < 28; x++)
			if ((mousePosition.x >= ((x * 64) + 64))
				&& (mousePosition.x <= ((x * 64) + 64 + 32))
				&& (mousePosition.y >= ((y * 64) + 64))
				&& (mousePosition.y <= ((y * 64) + 64 + 32))
				&& (tileTexture.ascendNumberOfTexture() > (m_page * 28 * 12) + x + (y * 28)))
					return ((m_page * 28 * 12) + x + (y * 28));
	return -1;
}

unsigned int Inventory::limitTileDraw(Texture &tileTexture) const
{
	unsigned int r = ((m_page+1) * 28 * 12);
	if (tileTexture.ascendNumberOfTexture() < r)
		r = tileTexture.ascendNumberOfTexture();
	return r;
}

void Inventory::drawTile(sf::RenderWindow& window, Texture& tileTexture) const
{
	float x = 32, y = 64;
	for (unsigned int numberOfTexture = (m_page*28*12); numberOfTexture < limitTileDraw(tileTexture); numberOfTexture++)
	{
		if ((x + 32 + tileTexture.ascendSize(numberOfTexture).width) >= (1920 - 64))
		{
			x = 64;
			y += 64;
		}
		else
			x += 32;

		tileTexture.draw(numberOfTexture, x, y, window);
		x += 32;
	}
}

void Inventory::inventoryMain(Screen& screen, sf::RenderWindow& window, Texture& tileTexture)
{
	changeInventory(screen);
	if (m_inventory)
	{
		changePage(tileTexture);
		drawTile(window, tileTexture);
		window.draw(m_textPage);
		std::cout << collisionMouseTexture(tileTexture, window) << std::endl;
	}
}
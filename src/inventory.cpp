#include "inventory.hpp"
#include <sstream>
#include <iostream>


Inventory::Inventory(const std::string fontFile) : m_inventory(false), m_page(0), m_selector(-1), m_releaseMouse(false), m_selectorMouse(-1)
{
	m_font.loadFromFile(fontFile);
	m_textNameTexture.setFont(m_font);
	m_textPage.setFont(m_font);
	m_textNameTexture.setCharacterSize(16);
	m_textPage.setCharacterSize(48);
	m_textPage.setString("Page : 0");
	m_textPage.setPosition(sf::Vector2f(((1920/2) - (m_textPage.getGlobalBounds().width/2)), (1080 - m_textPage.getGlobalBounds().height)));
	m_textSelector.setFont(m_font);
	m_textPage.setCharacterSize(48);
	m_textCursor.setFont(m_font);
}

void Inventory::changeInventory()
{
	static bool ePress = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !ePress) {
		m_inventory = !m_inventory;
		ePress = true;
		if(m_inventory == true) 
		{
			m_page = 0;
			changeTextPage();
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

void Inventory::changePage(const Texture& tileTexture)
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

signed int Inventory::collisionMouseTexture(const Texture& tileTexture, sf::RenderWindow& window) const
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

void Inventory::clickMouse(const Texture &tileTexture, sf::RenderWindow& window)
{
	m_selectorMouse = collisionMouseTexture(tileTexture, window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		m_releaseMouse = true;
	if (m_releaseMouse == true && !(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
	{
		if (m_selectorMouse >= 0)
		{
			m_selector = m_selectorMouse;
			changeTextSelector(tileTexture);
		}
		m_releaseMouse = false;
	}
}

unsigned int Inventory::limitTileDraw(const Texture &tileTexture) const
{
	unsigned int r = ((m_page+1) * 28 * 12);
	if (tileTexture.ascendNumberOfTexture() < r)
		r = tileTexture.ascendNumberOfTexture();
	return r;
}

signed int Inventory::ascendSelector() const
{
	return m_selector;
}

bool Inventory::ascendInventoryOn() const
{
	return m_inventory;
}

void Inventory::changeTextSelector(const Texture& tileTexture)
{
	m_textSelector.setString(tileTexture.ascendName(m_selector));
	m_textSelector.setPosition(sf::Vector2f((30 + 10 + tileTexture.ascendSize(m_selector).width) ,((1080 - 30) - m_textSelector.getGlobalBounds().height)));
}

void Inventory::drawTile( Texture& tileTexture, sf::RenderWindow& window) const
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

void Inventory::drawCursor(const Texture& tileTexture, sf::RenderWindow& window)
{
	m_textCursor.setString(tileTexture.ascendName(m_selectorMouse));
	m_textCursor.setPosition(sf::Vector2f((1920 - 20 - m_textCursor.getGlobalBounds().width), (1080 - m_textCursor.getGlobalBounds().height - 30)));
	window.draw(m_textCursor);
}

void Inventory::displaySelector(sf::RenderWindow& window, Texture &tileTexture)
{
	tileTexture.draw(m_selector, 30.f, (1080 - tileTexture.ascendSize(m_selector).height - 30), window);
	window.draw(m_textSelector);
}

void Inventory::inventoryMain(Screen& screen, sf::RenderWindow& window, Texture& tileTexture)
{
	changeInventory();
	if (m_inventory)
	{
		screen.displayBackground(window);
		changePage(tileTexture);
		drawTile(tileTexture, window);
		clickMouse(tileTexture, window);

		if (m_selector >= 0)
			displaySelector(window, tileTexture);
		if (m_selectorMouse >= 0)
			drawCursor(tileTexture, window);
		window.draw(m_textPage);
	}
}
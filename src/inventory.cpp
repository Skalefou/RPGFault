#include "inventory.hpp"

Inventory::Inventory() : m_inventory(false), m_page(0)
{

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
		drawTile(window, tileTexture);

	}
}

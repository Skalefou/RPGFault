#include "inventory.hpp"

Inventory::Inventory() : m_inventory(false)
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

void Inventory::inventoryMain(Screen &screen)
{
	changeInventory(screen);
	if (m_inventory)
	{

	}
}

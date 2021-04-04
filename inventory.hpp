#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "texture.hpp"

class Inventory 
{
public:
	Inventory();
	void changeInventory(Screen &screen);
	unsigned int limitTileDraw(Texture& tileTexture) const;
	void drawTile(sf::RenderWindow &window, Texture &tileTexture) const;
	void inventoryMain(Screen &screen, sf::RenderWindow& window, Texture &tileTexture);
	
private:
	bool m_inventory;
	unsigned int m_page;
};

#endif

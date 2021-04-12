#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "texture.hpp"

class Inventory 
{
public:
	Inventory(std::string fontFile);
	void changeInventory(Screen &screen);
	void changePage(Texture &tileTexture);
	unsigned int limitTileDraw(Texture& tileTexture) const;
	void changeTextSelector(Texture &tileTexture);
	void drawTile(Texture& tileTexture, sf::RenderWindow& window) const;
	void drawCursor(Texture& tileTexture, sf::RenderWindow& window);
	void displaySelector(sf::RenderWindow& window, Texture& tileTexture);
	void changeTextPage();
	void clickMouse(Texture& tileTexture, sf::RenderWindow& window);
	signed int collisionMouseTexture(Texture& tileTexture, sf::RenderWindow& window) const;
	void inventoryMain(Screen& screen, sf::RenderWindow& window, Texture& tileTexture);
private:
	bool m_inventory, m_releaseMouse;
	unsigned int m_page;
	signed int m_selector, m_selectorMouse;
	sf::Font m_font;
	sf::Text m_textPage, m_textNameTexture, m_textSelector, m_textCursor;
};

#endif
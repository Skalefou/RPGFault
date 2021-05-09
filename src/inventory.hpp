#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include "screen.hpp"
#include "texture.hpp"

class Inventory 
{
public:
	Inventory(const std::string fontFile);
	void changeInventory();
	void changePage(const Texture &tileTexture);
	unsigned int limitTileDraw(const Texture& tileTexture) const;
	signed int ascendSelector() const;
	bool ascendInventoryOn() const;
	void changeTextSelector(const Texture &tileTexture);
	void drawTile(Texture& tileTexture, sf::RenderWindow& window) const;
	void drawCursor(const Texture& tileTexture, sf::RenderWindow& window);
	void displaySelector(sf::RenderWindow& window, Texture& tileTexture);
	void changeTextPage();
	void clickMouse(const Texture& tileTexture, sf::RenderWindow& window);
	signed int collisionMouseTexture(const Texture& tileTexture, sf::RenderWindow& window) const;
	void inventoryMain(Screen& screen, sf::RenderWindow& window, Texture& tileTexture);
private:
	bool m_inventory, m_releaseMouse;
	unsigned int m_page;
	signed int m_selector, m_selectorMouse;
	sf::Font m_font;
	sf::Text m_textPage, m_textNameTexture, m_textSelector, m_textCursor;
};

#endif
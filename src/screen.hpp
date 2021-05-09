#ifndef SCREEN_HPP
#define SCREEN_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "const.hpp"

class Screen
{
public:
	Screen(sf::RenderWindow &window, const std::string nameFileFont, sf::View &view);
	bool isFullscreen() const; //Returns true, if the user's window is full screen
	void changeFullScreen(sf::RenderWindow& window); // activate/deactivate fullscreen
	sf::Color colorBackground() const;
	void changeColorBackground(const sf::Color color);
	void displayBackground(sf::RenderWindow& window) const;
private:
	bool m_fullscreen;
	sf::Color m_colorBackground;
	sf::RectangleShape m_background;
};

#endif
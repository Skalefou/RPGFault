#ifndef SCREEN_HPP
#define SCREEN_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include "const.hpp"

class Screen
{
public:
	Screen();
	bool isFullscreen() const; //Returns true, if the user's window is full screen
	void changeFullScreen(sf::RenderWindow& window); // activate/deactivate fullscreen
	sf::Color colorBackground() const;
	void changeColorBackground(sf::Color color);
private:
	bool m_fullscreen;
	sf::Color m_colorBackground;
};

#endif

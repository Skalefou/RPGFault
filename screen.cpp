#include <iostream>
#include "screen.hpp"

Screen::Screen() : m_fullscreen(false), m_colorBackground(0, 0, 0, 255)
{

}

bool Screen::isFullscreen() const
{
	return m_fullscreen;
}

void Screen::changeFullScreen(sf::RenderWindow& window)
{
	static bool f11Press = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && !f11Press)
	{
		m_fullscreen = !m_fullscreen;
		f11Press = true;
		if(m_fullscreen)
			window.create(sf::VideoMode(1280, 720), WINDOW_NAME, sf::Style::Close);
		else
			window.create(sf::VideoMode::getDesktopMode(), WINDOW_NAME, sf::Style::Fullscreen);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F11) && f11Press)
		f11Press = false;
}

sf::Color Screen::colorBackground() const
{
	return m_colorBackground;
}

void Screen::changeColorBackground(sf::Color color)
{
	m_colorBackground = color;
}

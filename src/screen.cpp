#include "screen.hpp"

Screen::Screen(sf::RenderWindow& window, std::string nameFileFont, sf::View& view) : m_fullscreen(false), m_colorBackground(0, 0, 0, 255)
{
	sf::Font font;
	sf::Text text;
	window.setView(view);
	font.loadFromFile(nameFileFont);
	text.setFont(font);
	text.setString("Loading...");
	text.setCharacterSize(32);
	text.setPosition(sf::Vector2f(((1920 / 2) - (text.getGlobalBounds().width / 2)), ((1080 / 2) - (text.getGlobalBounds().height / 2))));
	window.clear(sf::Color::Black);
	window.draw(text);
	window.display();

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

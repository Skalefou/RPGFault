#include <SFML/Window.hpp>
#include "screen.hpp"
#include "const.hpp"

sf::VideoMode rf::Screen::getScreenSize() {
	sf::VideoMode screenDesktop { sf::VideoMode::getDesktopMode() };

	switch (screenDesktop.width) {
		case 4096:
			divideResolution(screenDesktop, 1.6);
			break;
		case 2560:
			divideResolution(screenDesktop, 1.3333);
			break;
		case 1920:
			divideResolution(screenDesktop, 1.5);
			break;
		case 1280:
			divideResolution(screenDesktop, 2);
			break;
		default:
			divideResolution(screenDesktop, 1.5);
			break;
	}
	return screenDesktop;
}

void rf::Screen::setFullscreen(sf::RenderWindow& window) {
	static bool fullscreen = false;
	if (fullscreen)
		window.create(rf::Screen::getScreenSize(), WINDOW_NAME, sf::Style::Close);
	else 
		window.create(sf::VideoMode::getDesktopMode(), WINDOW_NAME, sf::Style::Fullscreen);
	fullscreen = !fullscreen;
}

void rf::Screen::divideResolution(sf::VideoMode& screenDesktop, const double divide) {
	double width = screenDesktop.width / divide, height = screenDesktop.height / divide;
	screenDesktop.width = (unsigned int)width;
	screenDesktop.height = (unsigned int)height;
}
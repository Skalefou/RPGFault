#include "screensize.hpp"

sf::VideoMode rf::ScreenSize::getScreenSize() {
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

void rf::ScreenSize::divideResolution(sf::VideoMode& screenDesktop, const double divide) {
	double width = screenDesktop.width / divide, height = screenDesktop.height / divide;
	screenDesktop.width = (unsigned int)width;
	screenDesktop.height = (unsigned int)height;
}
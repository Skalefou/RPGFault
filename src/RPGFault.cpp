#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "screen.hpp"
#include "tile.hpp"
#include "const.hpp"

int main(void) {
	sf::RenderWindow window(rf::Screen::getScreenSize(), WINDOW_NAME, sf::Style::Close);
	bool fullscreenWait = true;
	TileRPG tileRPG;

	window.clear(sf::Color::Black);
	tileRPG.draw(WATER, 10.f, 15.f, window);
	window.display();

	window.setVerticalSyncEnabled(true);
	while (window.isOpen()) {
		sf::sleep(sf::microseconds(16'666));
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyReleased:
				fullscreenWait = true;
				break;
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt))
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)
		&& fullscreenWait) {
			rf::Screen::setFullscreen(window);
			fullscreenWait = false;
		}

	}
	return 0;
}
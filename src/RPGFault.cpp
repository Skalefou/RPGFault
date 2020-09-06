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
	tileRPG.draw(GRASS, 10.f, 15.f, window);
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

/*window.clear(sf::Color::Black);
vectorTexture.push_back(texture);
vectorTexture[0].loadFromFile("data/tileRPG/grass.png");
vectorTexture.push_back(texture);
vectorTexture[1].loadFromFile("data/tileRPG/water.png");
vectorSprite.push_back(sprite);
vectorSprite[0].setTexture(vectorTexture[0]);
vectorSprite[0].setPosition(sf::Vector2f(100.f, 50.f));
window.draw(vectorSprite[0]);
vectorSprite.push_back(sprite);
vectorSprite[1].setTexture(vectorTexture[1]);
vectorSprite[1].setPosition(sf::Vector2f(10.f, 50.f));
window.draw(vectorSprite[1]);
window.display();*/
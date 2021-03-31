#include "screen.hpp"
#include <iostream>

int main(void) 
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), WINDOW_NAME, sf::Style::Close);
	Screen screen;
	sf::View view(sf::FloatRect(0, 0, 1920, 1080));


	sf::Texture texture;
	texture.loadFromFile("data/tileRPG/grass.png");
	sf::Sprite sprite;
	sprite.setTexture(texture);

	

	window.setVerticalSyncEnabled(true);
	while (window.isOpen()) 
	{
		sf::sleep(sf::microseconds(16'666));
		window.clear(sf::Color::Black);
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		
		screen.changeFullScreen(window);

		

		sprite.setPosition((float)(view.getSize().x / 2 - 16), (float)(view.getSize().y / 2 - 16));
		window.draw(sprite);

		window.setView(view);
		window.display();
	}

	return 0;
}

#include "screen.hpp"
#include "inventory.hpp"
#include "texture.hpp"
#include <iostream>

int main(void) 
{

	sf::RenderWindow window(sf::VideoMode(1280, 720), WINDOW_NAME, sf::Style::Close);
	sf::View view(sf::FloatRect(0, 0, 1920, 1080));
	Screen screen(window, "data/Pixeled.ttf", view);
	Inventory inventory("data/Pixeled.ttf");
	Texture tileTexture("data/tileRPGList.rf");

	window.setVerticalSyncEnabled(true);
	while (window.isOpen()) 
	{
		sf::sleep(sf::microseconds(16'666));
		window.clear(screen.colorBackground());
		sf::Event event;
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();
		
		screen.changeFullScreen(window);
		inventory.inventoryMain(screen, window, tileTexture);

		window.setView(view);
		window.display();
	}

	return 0;
}

//TODO: Start the file backup system
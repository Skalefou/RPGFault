#include "screen.hpp"
#include "inventory.hpp"
#include "texture.hpp"
#include "map.hpp"


int main(void) 
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), WINDOW_NAME, sf::Style::Close);
	sf::View view(sf::FloatRect(0, 0, 1920, 1080));
	Screen screen(window, "data/Pixeled.ttf", view);
	Texture tileTexture("data/tileRPGList.rf");
	Inventory inventory("data/Pixeled.ttf");
	Map map;

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
		map.mainMap(inventory.ascendSelector(), inventory.ascendInventoryOn(), window, tileTexture);
		inventory.inventoryMain(screen, window, tileTexture);

		window.setView(view);
		window.display();
	}

	return 0;
}

//TODO: 1-Create the "Fill" a selection with tile tool 
//TODO: 2-Create a scrolling for the map 
//TODO: 3-Create a background editing tool 
//TODO: 4-Start the file backup system
//TODO: ---END---
//TODO: 1-Using Threads
//TODO: 2-Check for bugs
//TODO: 3-Optimize the program  
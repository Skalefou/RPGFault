#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::Texture grass;
	sf::Texture player;
	if (!grass.loadFromFile("data/tileRPG/grass.png"))
	{
		window.close();
	}
	if (!grass.loadFromFile("data/player/player.png"))
	{
		window.close();
	}

	window.setFramerateLimit(60);

    window.setActive(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			switch (event.type)
			{
			case sf::Event::Closed:
                window.close();
				break;
			
			case sf::Event::KeyPressed:
				shape.setFillColor(sf::Color::Black);
           		break;

			case sf::Event::Resized:
				shape.setFillColor(sf::Color::Red);
                glViewport(0, 0, event.size.width, event.size.height);
           		break;


			default:
				break;
			}
			// sf::Mouse::setPosition(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2), window); // window is a sf::Window
        }

        
        window.clear();
        
        window.display();
    }

    return 0;
}
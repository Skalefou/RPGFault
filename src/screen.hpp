#ifndef SCREENSIZE_HPP
#define SCREENSIZE_HPP
#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace rf {
	class Screen {
	public:
		static sf::VideoMode getScreenSize();
		static void setFullscreen(sf::RenderWindow& window);
	private:
		static void divideResolution(sf::VideoMode& screenDesktop, const double divide);
	};
}

#endif
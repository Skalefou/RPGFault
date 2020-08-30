#ifndef SCREENSIZE_HPP
#define SCREENSIZE_HPP
#pragma once

#include <SFML/Window/VideoMode.hpp>

namespace rf {
	class ScreenSize {
	public:
		static sf::VideoMode getScreenSize();
	private:
		static void divideResolution(sf::VideoMode& screenDesktop, const double divide);
		double m_ratio;
	};
}

#endif
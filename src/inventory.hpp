#ifndef INVENTORY_HPP
#define INVENTORY_HPP
#pragma once

#include <SFML/Graphics.hpp>
#include "screen.hpp"

class Inventory 
{
public:
	Inventory();
	void changeInventory(Screen &screen);
	void inventoryMain(Screen &screen);
	
private:
	bool m_inventory;
};

#endif

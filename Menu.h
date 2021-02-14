#pragma once
#include "Warehouse.h"
#include "Package.h"

class Menu
{
private:
	enum Options { AUSLAGERN = 97, AUSGABE, EINLAGERN = 101, EXIT = 120 };
	
	Warehouse w;


public:
	Menu();
	void showOptions();
};


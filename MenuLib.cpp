#include "MenuLib.h"
#include "SimulationLib.h"

namespace MenuLib {

	Menu::Menu(SimulationLib::Simulation* _simulationPointer)
	{
		simulationPointer = _simulationPointer;
	}

	void Menu::handleMenu()
	{
		// Print out environment
		printEnvironment();

		// Print out menu UI
		//writeToConsole("hello\n", 0, 20, 15);

		// Pointer to vector of menuItems
		// Bit of indirection because we might instantiate a vector of menuItems depending on the currentMenuType
		std::vector<MenuItem>* menuItemsPointer;

		// Before getting menu, check if its one of the derived menus (availableDevices, availabeRovers)

		if (currentMenuType == menuType::availableDevices)
		{
			currentMenuItems = getAvailableDevicesMenu();
		}
		else if (currentMenuType == menuType::availableRovers)
		{
			currentMenuItems = getAvailableRoversMenu();
		}
		else
		{
			// Set menuItems to point to the pre-defined vector of menu items using the value of menu.currentMenuType
			currentMenuItems = menuItemsArray[(int)currentMenuType];
		}

		// Print current menu items
		printMenuItems(*currentMenuItems);

		// Take user input
		int input;
		std::cin >> input;
		input--; // make an index

		// Call callback function inside selected menuItem
		// - Check if input is within valid range
		if (input >= 0 && input <= (*currentMenuItems).size())
		{
			// Call the callback function pointer inside the menu item, passing a pointer to menu as an argument
			(*currentMenuItems)[input].callbackFunctionPointer(this, input);
		}
		else
		{
			throw "Input outside valid range";
		}

	}

	std::vector<MenuItem>* Menu::getAvailableDevicesMenu()
	{
		// Create a vector of MenuItems
		std::vector<MenuItem> * menuItems = new std::vector<MenuItem>;
		int index = 1;

		// Instantiate a menu item for each unassigned device and check a pointer to it in menuItems
		for (SimulationLib::Device* d : (*simulationPointer).devices)
		{
			if (d->attachedRover == nullptr)
			{
				menuItems->push_back(MenuItem{ std::to_string(index) + " " + d->name, &selectDevice });
				index++;
			}
		}

		// Set menuItemsPointer to point to menuItems
		return menuItems;
	};

	std::vector<MenuItem>* Menu::getAvailableRoversMenu()
	{
		// Create a vector of MenuItems
		std::vector<MenuItem>* menuItems = new std::vector<MenuItem>;
		int index = 1;

		for (SimulationLib::Rover* r : (*simulationPointer).rovers)
		{
			menuItems->push_back(MenuItem{ std::to_string(index) + ". Rover id: " + std::to_string(r->id), &selectRover });
			index++;
		}

		return menuItems;
	}

	void Menu::printMenuItems(std::vector<MenuItem> &menuItems)
	{
		for (int i = 0; i < menuItems.size(); i++)
		{
			std::cout << menuItems[i].text << std::endl;
		}
	}

	void Menu::printEnvironment()
	{
		// Print out the environment to the console
		HANDLE hConsole;
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsole, COORD{ (short)0, (short)0 });

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				int val = simulationPointer->environment.matrix[i][j];
				std::string text = std::to_string(val) + (val > 9 ? " " : std::string(2, ' '));
				writeToConsole(hConsole, text, 1);
			}
			writeToConsole(hConsole, "\n", 1);
		}


	}

	void Menu::writeToConsole(HANDLE hConsole, std::string text, int color)
	{
		const char* msgBuff = text.c_str();
		SetConsoleTextAttribute(hConsole, color);
		WriteConsoleA(hConsole, msgBuff, (DWORD)strlen(msgBuff), NULL, NULL);
		SetConsoleTextAttribute(hConsole, 7);
	}

	MenuItem::MenuItem(std::string _text, void (*_callbackFunctionPointer)(Menu* menuPointer, int index))
	{
		text = _text;
		callbackFunctionPointer = _callbackFunctionPointer;
	}

	std::vector<MenuItem> mainMenuItems = {
		MenuItem("1. Select Rover", &getAvailableRovers),
		MenuItem("2. Quit", &exitMenu)
	};

	std::vector<MenuItem> roverOperationItems = {
		MenuItem("1. Operate Motor", &selectRover),
		MenuItem("2. Operate Radar", &selectRover),
		MenuItem("3. Operate Solar Panel", &selectRover),
		MenuItem("4. Operate Drill", &selectRover),
		MenuItem("5. Exit", &goToRoverSelectMenu)
	};

	std::vector<MenuItem>* menuItemsArray[] = {
		&mainMenuItems,
		&roverOperationItems
	};

	// Called when selecting an available device to attach to Rover
	void MenuLib::selectDevice(Menu* menuPointer, int index)
	{
		// Send the index to rover.attachDevice. Rover.attachDevice will get a list of unassigned devices and
		// .. try to attach the one at index.
		menuPointer->simulationPointer->rovers[menuPointer->selectedRoverIndex]->attachDeviceByIndex(menuPointer->simulationPointer, index);

		// Go back to available devices menu
		menuPointer->currentMenuType = MenuLib::menuType::availableDevices;
	}

	void MenuLib::getAvailableRovers(Menu* menuPointer, int index)
	{
		menuPointer->currentMenuType = menuType::availableRovers;
	}

	void MenuLib::selectRover(Menu* menuPointer, int index)
	{
		menuPointer->selectedRoverIndex = index;
		menuPointer->currentMenuType = menuType::operateRover;
	}

	void MenuLib::exitMenu(Menu* menuPointer, int index)
	{
		menuPointer->currentMenuType = menuType::exit;
	}

	void MenuLib::goToRoverSelectMenu(Menu* menuPointer, int index)
	{
		menuPointer->currentMenuType = menuType::start;
	}
}
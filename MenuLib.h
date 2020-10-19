#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "SimulationLib.h"
#include <windows.h>

namespace MenuLib
{
	enum class menuType {
		exit = -3,
		availableDevices = -2,
		availableRovers = -1,
		start = 0,
		operateRover
	};

	class Menu;

	// A class for each individual item (option) in a menu
	class MenuItem {
	public:
		std::string text;
		void (*callbackFunctionPointer)(Menu* menuPointer, int index);
		// Constructor
		MenuItem(std::string _text, void (*_callbackFunctionPointer)(Menu* menuPointer, int index));
	};

	class Menu {
	public:
		int selectedRoverIndex = -1;
		SimulationLib::deviceType currentDeviceType = SimulationLib::deviceType::none;
		SimulationLib::Simulation* simulationPointer;
		
		// Current menu items
		std::vector<MenuItem>* currentMenuItems;

		// For selecting devices
		int selectedDeviceIndex = -1;

		// Current type of menu to show
		menuType currentMenuType = menuType::start;
		
		// Pointer to simulation
		Menu(SimulationLib::Simulation* simulation);
		
		void handleMenu();

		// UI methods
		void printMenuItems(std::vector<MenuItem> &menuItems);
		void printEnvironment();
		void writeToConsole(HANDLE hConsole, std::string text, int color);

		std::vector<MenuItem>* getAvailableDevicesMenu();
		std::vector<MenuItem>* getAvailableRoversMenu();
	};

	// Vector to hold relative menu items together
	extern std::vector<MenuItem> mainMenuItems;
	extern std::vector<MenuItem> roverOperationItems;

	// Array to hold pointers to vectors of menu items
	extern std::vector<MenuItem>* menuItemsArray[];

	// Callback functions for menuItems
	extern void selectDevice(Menu* menuPointer, int index);
	extern void selectRover(Menu* menuPointer, int index);
	extern void exitMenu(Menu* menuPointer, int index);
	extern void getAvailableRovers(Menu* menuPointer, int index);
	extern void goToRoverSelectMenu(Menu* menuPointer, int index);
}
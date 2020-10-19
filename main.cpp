#include <iostream>
#include <vector>
#include "MenuLib.h"
#include "SimulationLib.h"

using namespace std;

int main()
{

	// Create simulation to hold parts of simulation
	SimulationLib::Simulation simulation;

	// Generate an environment inside the simulation
	simulation.environment.generateEnvironment();
	
	// Create some rovers (with ids)
	SimulationLib::Rover rover1{ 1 }, rover2{ 2 };
	simulation.rovers.push_back(&rover1); simulation.rovers.push_back(&rover2);

	// Create some batteries
	SimulationLib::Battery battery1{ 20, 20 }, battery2{ 20, 20 }, battery3{ 20, 20 }, battery4{ 20, 20 };
	simulation.batteries.push_back(&battery1); simulation.batteries.push_back(&battery2);
	simulation.batteries.push_back(&battery3); simulation.batteries.push_back(&battery4);

	// Create some parts
	SimulationLib::Motor motor1, motor2;
	SimulationLib::SolarPanel solarPanel1, solarPanel2;
	SimulationLib::Radar radar1, radar2;
	SimulationLib::Drill drill1, drill2;
	simulation.devices.push_back(&(SimulationLib::Device)motor1); 
	simulation.devices.push_back(&(SimulationLib::Device)motor2);
	simulation.devices.push_back(&(SimulationLib::Device)solarPanel1);
	simulation.devices.push_back(&(SimulationLib::Device)solarPanel2);
	simulation.devices.push_back(&(SimulationLib::Device)radar1);
	simulation.devices.push_back(&(SimulationLib::Device)radar2);
	simulation.devices.push_back(&(SimulationLib::Device)drill1);
	simulation.devices.push_back(&(SimulationLib::Device)drill2);

	// Menu object to handle menu
	MenuLib::Menu menu(&simulation);

	while (menu.currentMenuType != MenuLib::menuType::exit)
	{
		menu.handleMenu();
	}

	std::cout << "Exited";
}

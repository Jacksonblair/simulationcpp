#include "SimulationLib.h"
#include <time.h>

namespace SimulationLib
{
	SimulationLib::Rover::Rover(int _id)
	{
		id = _id;
	};

	void SimulationLib::Rover::attachDeviceByIndex(Simulation* simulationPointer, int index)
	{

	};

	void SimulationLib::Rover::attachDevice(SimulationLib::Device * deviceToAttach)
	{
		// Check if there is already a device of this type attached.
		for (auto i = 0; i < devices.size(); i++)
		{
			if (devices[i]->deviceType == deviceToAttach->deviceType)
			{
				throw "There is already a device of this type attached.";
			}
		};

		// Attach device
		deviceToAttach->attachedRover = this; // Store pointer to rover in device.attachedRover
		devices.push_back(deviceToAttach); // Store pointer to device in rover.devices

		// Try to attach device to battery w. highest charge
		int highestChargeBatteryIndex = -1;
		int highestCharge = 1;

		// Get battery with highest charge
		for (auto i = 0; i < batteries.size(); i++)
		{
			if (batteries[i]->charge > highestCharge)
			{
				highestChargeBatteryIndex = i;
				highestCharge = batteries[i]->charge;
			}
		}

		// If we have a battery
		if (highestChargeBatteryIndex >= 0)
		{
			attachDeviceToRoverBattery(deviceToAttach, batteries[highestChargeBatteryIndex]);
		}
		else
		{
			throw "Could not attach to battery. Rover has no batteries";
		}
	};

	void SimulationLib::Rover::attachDeviceToRoverBattery(SimulationLib::Device* deviceToAttach, SimulationLib::Battery* roverBattery)
	{
		deviceToAttach->attachedBattery = roverBattery;
	};

	SimulationLib::Battery::Battery(int _charge, int _maxCharge)
	{
		charge = _charge;
		maxCharge = _maxCharge;
	};

	SimulationLib::Device::Device(SimulationLib::deviceType _deviceType)
	{
		name = "defaultname";
		deviceType = _deviceType;
	};

	SimulationLib::Motor::Motor() : Device(SimulationLib::deviceType::motor)
	{

	};

	SimulationLib::SolarPanel::SolarPanel() : Device(SimulationLib::deviceType::solarPanel)
	{

	};

	SimulationLib::Radar::Radar() : Device(SimulationLib::deviceType::radar)
	{

	};

	SimulationLib::Drill::Drill() : Device(SimulationLib::deviceType::drill)
	{

	};

	SimulationLib::Specimen::Specimen(std::string _name, int _size)
	{
		name = _name;
		size = _size;
	};

	SimulationLib::Environment::Environment()
	{

	};

	void SimulationLib::Environment::generateEnvironment()
	{
		srand(time(NULL));

		// Make 10 specimens and store pointers to them in environment.
		// Give 'random' size between 1 and 3
		for (auto i = 0; i < 10; i++)
		{
			SimulationLib::Specimen * specimen = new SimulationLib::Specimen("Specimen " + std::to_string(i), (rand() % 3 + 1));
			specimenArray[i] = specimen;
		}
		
		// Generate 10 random integers between 0 - 19 and store in array (these are our Y indices)
		int randIntArr[10];
		for (int i = 0; i < 10; i++)
		{
			randIntArr[i] = rand() % 19;
		}

		// For each x index
		for (int i = 1; i <= sizeof(randIntArr) / sizeof(randIntArr[0]); i++)
		{
			// Generate a y index
			int randY = rand() % 19;

			// Check if specimen index already present at xy index
			if (matrix[i][randY] != 0)
			{
				// If adding 1 to that index is still in range, add 1
				if ((randY + 1) <= 19)
				{
					randY++;
					matrix[i][randY] = i; // Set that xy to current index
				}
				// Else just decrement it and add that instead
				else
				{
					randY--;
					matrix[i][randY] = i;
				}
			}
			// If nothing present at xy location, store the index
			else
			{
				matrix[i][randY] = i;
			}
		}


	};

}
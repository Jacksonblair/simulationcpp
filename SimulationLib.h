#pragma once
#include <string>
#include <vector>

namespace SimulationLib
{
	class Battery;
	class Rover;
	class Simulation;
	class Specimen;

	// Simulation environment for the rover to explore
	class Environment
	{
	public:
		Environment();
		int matrix[20][20];
		Specimen * specimenArray[10];
		// Places indices of pointers to specimens at 'random' locations in the matrix
		void generateEnvironment();
	};

	enum class deviceType {
		none = -1,
		motor,
		radar,
		solarPanel,
		drill
	};

	class Device
	{
	public:
		deviceType deviceType;
		Battery* attachedBattery = nullptr;
		Rover* attachedRover = nullptr;
		std::string name;
		Device(SimulationLib::deviceType _deviceType);
	};

	class Battery
	{
	public:
		Rover* attachedRover = nullptr;
		int charge;
		int maxCharge;
		Battery(int _charge, int _maxCharge);
	};

	class Rover
	{
	public:
		int id;
		Rover(int _id);
		std::vector<Battery*> batteries;
		std::vector<Device*> devices;
		void attachDevice(Device * deviceToAttach);
		// Takes an index that is a Device from a vector of unassigned device
		void attachDeviceByIndex(Simulation* simulationPointer, int index);
		void attachDeviceToRoverBattery(Device* device, Battery* battery);
	};

	class Simulation
	{
	public:
		std::vector<Rover*> rovers;
		std::vector<Battery*> batteries;
		std::vector<Device*> devices;
		Environment environment;
	};

	// Drives rover
	class Motor: public Device
	{
	public:
		Motor();
	};

	// Detects specimens
	class Radar : public Device
	{
	public:
		Radar();
	};

	// Generates energy
	class SolarPanel : public Device
	{
	public:
		SolarPanel();
	};

	// Drills area
	class Drill : public Device
	{
	public:
		Drill();
	};

	class Specimen {
		int size;
		std::string name;
	public:
		Specimen(std::string _name, int _size);
	};

}
#include "LevelFileSystem.h"

#include <iostream>
#include <fstream>  
#include <string>  

#include "TempMap.h"

void ReadWallData(std::ifstream* file, int levelWidth, int levelHeight);
void ReadFloorData(std::ifstream* file, FloorData floorData);
void ReadObjectData(std::ifstream* file, int levelWidth, int levelHeight);

#define DEFAULT_MAP_WIDTH 24
#define DEFAULT_MAP_HEIGHT 24

std::vector<std::vector<int>>worldMap;
FloorData floorData;
FloorData ceilingData;

void LevelFileSystem::CreateFile(std::string fileName)
{
	std::ofstream outfile("Levels/" + fileName + g_fileType);

	// Create default data maps.
	outfile << DEFAULT_MAP_WIDTH << " " << DEFAULT_MAP_HEIGHT << std::endl;
	outfile << "Walls:" << std::endl << std::endl;
	outfile << "Objects:" << std::endl << std::endl;
	outfile << "Floor:" << std::endl << std::endl;
	outfile << "Ceiling:" << std::endl << std::endl;

	outfile.close();
}

void LevelFileSystem::ReadFile(std::string fileName)
{
    std::ifstream file("Levels/" + fileName + g_fileType);

    if (!file)
    {
        std::cout << "Failed to open file at " << "Levels/" + fileName + g_fileType << std::endl;
        return;
    }

    std::string line;
    int levelWidth = 0;
    int levelHeight = 0;

    file >> levelWidth >> levelHeight;
    worldMap.resize(levelWidth, std::vector<int>(levelHeight));

    while (std::getline(file, line))
    {
        if (line == "Walls:")
        {
            ReadWallData(&file, levelWidth, levelHeight);
        }

        else if (line == "Floor:")
        {
            ReadFloorData(&file, floorData);
        }
        else if (line == "Ceiling:")
        {
            ReadFloorData(&file, ceilingData);
        }

        else if (line == "Objects:")
        {
            ReadObjectData(&file, levelWidth, levelHeight);
        }
    }

    file.close();
}

void ReadWallData(std::ifstream* file, int levelWidth, int levelHeight)
{
    for (int y = 0; y < levelHeight; ++y)
    {
        std::string wallLine;
        if (!std::getline(*file, wallLine)) {
            std::cerr << "Failed to read wall line at row " << y << "\n";
            return;
        }

        if (wallLine.length() < levelWidth) {
            std::cerr << "Wall line " << y << " is too short: " << wallLine << "\n";
            return;
        }

        for (int x = 0; x < levelWidth; ++x)
        {
            if (!isdigit(wallLine[x])) {
                std::cerr << "Invalid wall data at (" << x << ", " << y << "): " << wallLine[x] << "\n";
                return;
            }

            int wallData = wallLine[x] - '0'; // convert char to int
            worldMap[x][y] = wallData;
            std::cout << x << "x" << y << " " << wallData << std::endl;
        }
    }
}

void ReadFloorData(std::ifstream* file, FloorData floorData)
{
    std::string line;

    std::getline(*file, line);

    if (line == "FloorCheckered:")
    {
        std::getline(*file, line);
        floorData.isCheckered = std::stoi(line);

        // If the floor is checkered it will always have multiplier values.
        std::getline(*file, line);
        if (line == "tex1Multiplier:")
        {
            std::getline(*file, line);
            floorData.multiplier1 = std::stoi(line);
        }

        std::getline(*file, line);
        if (line == "tex2Multiplier:")
        {
            std::getline(*file, line);
            floorData.multiplier2 = std::stoi(line);
        }
    }
}

void ReadObjectData(std::ifstream* file, int levelWidth, int levelHeight)
{

}
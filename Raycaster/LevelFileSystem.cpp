#include "LevelFileSystem.h"

#include <iostream>
#include <fstream>  
#include <string>  

#include "TempMap.h"

#define DEFAULT_MAP_WIDTH 24
#define DEFAULT_MAP_HEIGHT 24

std::vector<std::vector<int>>worldMap;

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
    std::ifstream file("Levels/" + fileName + g_fileType);  // Consider renaming the file if not JSON

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
            for (int y = 0; y < levelHeight; ++y)
            {
                std::string wallLine;
                if (!std::getline(file, wallLine)) {
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

        else if (line == "Floor:")
        {

        }

        else if (line == "Ceiling:")
        {

        }

        else if (line == "Objects:")
        {

        }
    }

    file.close();
}
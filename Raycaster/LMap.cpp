#include "LMap.h"

#include <iostream>
#include <fstream>   

std::string LMap::g_fileType = ".hlvl";

LMap::LMap() 
    : m_width(0),
      m_height(0)
{}

LMap::LMap(LMap& other) 
    : m_lvlArray(other.m_lvlArray)
{}

LMap::~LMap() {}

// Helper funcs.
void ReadWallData(std::ifstream* file, LevelArray& lArray, int levelWidth, int levelHeight);
void ReadFloorData(std::ifstream* file, FloorData& floorData);
void ReadObjectData(std::ifstream* file, int levelWidth, int levelHeight);

void LMap::CreateFile(std::string fileName)
{
    std::ofstream outfile("Levels/" + fileName + g_fileType);

    // Create default data maps.
    outfile << DEFAULT_MAP_WIDTH << " " << DEFAULT_MAP_HEIGHT << std::endl;
    outfile << "Walls:" << std::endl << std::endl;
    outfile << "Objects:" << std::endl << std::endl;
    outfile << "Floor:" << std::endl << std::endl;
    outfile << "Ceiling:" << std::endl << std::endl;

    outfile.close();

    if (!outfile.good()) { std::cout << "[LevelFileSystem] Failed to write to file: " << fileName; }
}

void LMap::ReadFile(LMap& map, std::string path)
{
    std::ifstream file(path);

    if (!file)
    {
        std::cout << "[LMap] Failed to open file at " << path << std::endl;
        return;
    }

    std::string line;

    map.m_width = 0;
    map.m_height = 0;

    file >> map.m_width >> map.m_height;
    map.m_lvlArray.resize(map.m_width, std::vector<int>(map.m_height));

    while (std::getline(file, line))
    {
        if (line == "Walls:")
        {
            ReadWallData(&file, map.m_lvlArray, map.m_width, map.m_height);
        }

        else if (line == "Floor:")
        {
            ReadFloorData(&file, map.m_floorData);
        }
        else if (line == "Ceiling:")
        {
            ReadFloorData(&file, map.m_ceilingData);
        }

        else if (line == "Objects:")
        {
            ReadObjectData(&file, map.m_width, map.m_height);
        }
    }

    file.close();
}

void ReadWallData(std::ifstream* file, LevelArray& lArray,  int levelWidth, int levelHeight)
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
            lArray[x][y] = wallData;
        }
    }
}

void ReadFloorData(std::ifstream* file, FloorData& floorData)
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

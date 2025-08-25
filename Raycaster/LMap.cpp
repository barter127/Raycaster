#include "LMap.h"

#include <iostream>
#include <fstream>   

std::string LMap::m_fileType = ".hlvl";

std::string LMap::m_defaultLevelArray = 
R"(111111111111111111111111
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
100000000000000000000001
111111111111111111111111)";

LMap::LMap() 
    : m_width(0),
      m_height(0)
{}

LMap::~LMap() {}

// Helper funcs.
void ReadWallData(std::ifstream* file, LevelArray& lArray, int levelWidth, int levelHeight);
void ReadFloorData(std::ifstream* file, FloorData& floorData);
void ReadObjectData(std::ifstream* file, int levelWidth, int levelHeight);
void ReadTexturePaths(std::ifstream* file, std::vector<std::string>& pathsVector);

std::string LMap::CreateFile(std::string fileName)
{
    std::ofstream outfile("Assets/Levels/" + fileName + m_fileType);

    if (!outfile)
    {
        std::cout << "[LMap] Failed to write to file: " << fileName << std::endl;
        outfile.close();
        return "Failed";
    }

    outfile << DEFAULT_MAP_WIDTH << " " << DEFAULT_MAP_HEIGHT << std::endl;

    outfile << "Textures:" << std::endl;
    outfile << 5 << std::endl;
    outfile << "Assets/Brick_Wall_64x64.png" << std::endl;;
    outfile << "Assets/Green_Wall_Rocks_64x64.png" << std::endl;;
    outfile << "Assets/Dirty_Mossy_Tiles_64x64.png" << std::endl;;
    outfile << "Assets/Dehydrated_Earth_64x64.png" << std::endl;;
    outfile << "Assets/Water_64x64.png" << std::endl;
    outfile << std::endl;

    // Create default data maps.
    outfile << "Walls:" << std::endl;
    outfile << m_defaultLevelArray;
    outfile << std::endl << std::endl;

    outfile << "Objects:" << std::endl << std::endl;

    outfile << "Floor:" << std::endl;
    outfile << "FloorCheckered:" << std::endl << 0 << std::endl;
    outfile << "tex1Multiplier:" << std::endl << 2 << std::endl;
    outfile << "tex2Multiplier:" << std::endl << 1 << std::endl;
    outfile << std::endl;

    outfile << "Ceiling:" << std::endl;
    outfile << "FloorCheckered:" << std::endl << 0 << std::endl;
    outfile << "tex1Multiplier:" << std::endl << 2 << std::endl;
    outfile << "tex2Multiplier:" << std::endl << 1 << std::endl;
    outfile << std::endl;

    outfile.close();

    return "Levels/" + fileName + m_fileType;
}

bool LMap::ReadFile(LMap& map, std::string path)
{
    std::ifstream file(path);

    if (!file)
    {
        std::cout << "[LMap] Failed to open file for reading: " << path << std::endl;
        file.close();
        return false;
    }

    std::string line;

    map.m_width = 0;
    map.m_height = 0;

    file >> map.m_width >> map.m_height;
    map.m_lvlArray.resize(map.m_width, std::vector<int>(map.m_height));

    while (std::getline(file, line))
    {
        if (line == "Textures:")
        {
            ReadTexturePaths(&file, map.m_texturePaths);
        }

        else if (line == "Walls:")
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
    return true;
}

bool LMap::SaveFile(const LMap& map, std::string path)
{
    std::ofstream outfile(path);

    if (outfile)
    {
        outfile << map.m_width << " " << map.m_height << std::endl;

        outfile << "Walls:"  << std::endl;
            for (int y = 0; y < map.m_height; y++)
            {
                for (int x = 0; x < map.m_width; x++)
                {
                    outfile << map.m_lvlArray[x][y];
                }

                outfile << std::endl;
            }

        outfile << "Objects:" << std::endl << std::endl;

        outfile << "Floor:" << std::endl;
            outfile << "FloorCheckered:" << std::endl << map.m_floorData.isCheckered << std::endl;
            outfile << "tex1Multiplier:" << std::endl << map.m_floorData.multiplier1 << std::endl;
            outfile << "tex2Multiplier:" << std::endl << map.m_floorData.multiplier2 << std::endl;
        outfile << std::endl;

        outfile << "Ceiling:" << std::endl;
            outfile << "FloorCheckered:" << std::endl << map.m_ceilingData.isCheckered << std::endl;
            outfile << "tex1Multiplier:" << std::endl << map.m_ceilingData.multiplier1 << std::endl;
            outfile << "tex2Multiplier:" << std::endl << map.m_ceilingData.multiplier2 << std::endl;
        outfile << std::endl;
    }
    else
    {
        std::cerr << "[LMap] Failed to open file during saving: path" << std::endl;
        outfile.close();
        return false;
    }

    outfile.close();
    return true;
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

void ReadTexturePaths(std::ifstream* file, std::vector<std::string>& pathsVector)
{
    std::string line;

    std::getline(*file, line);

    // This assumes the value is an int and is DANGEROUS!
    int textureAmount = stoi(line);
    pathsVector.reserve(textureAmount);

    for (int i = 0; i < textureAmount; i++)
    {
        std::getline(*file, line);
        pathsVector.push_back(line);
    }
}

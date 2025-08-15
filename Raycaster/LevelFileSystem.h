#pragma once

#ifndef _FILE_MAPPING_H
#define _FILE_MAPPING_H

#include <string>
#include <vector>

// Just in case I want to store 
static std::string g_fileType = ".hlvl";

extern std::vector<std::vector<int>>worldMap;


namespace LevelFileSystem
{
	void CreateFile(std::string fileName);

	void ReadFile(std::string fileName);
};

#endif // !_FILE_MAPPING_H
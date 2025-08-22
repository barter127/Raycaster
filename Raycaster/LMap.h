#pragma once

#ifndef _LMAP_H
#define _LMAP_H

#include <vector>
#include <string>

struct FloorData {
bool isCheckered = 0;
int multiplier1 = 1;
int multiplier2 = 1;
};

#define DEFAULT_MAP_WIDTH 24
#define DEFAULT_MAP_HEIGHT 24

typedef std::vector<std::vector<int>> LevelArray;

class LMap
{
public:
	LMap();
	LMap(LMap& other);
	~LMap();

	LMap& operator=(const LMap& other) {
		if (this != &other) {
			m_lvlArray = other.m_lvlArray;
		}
		return *this;
	}

	inline LevelArray GetLevelArray() { return m_lvlArray; }
	void UpdateLevelArray(LevelArray inputLvlArray) { m_lvlArray = inputLvlArray; }

	inline FloorData GetFloorData() { return m_floorData; }
	void UpdateFloorData(FloorData inputFloorData) { m_floorData = inputFloorData; }

	inline FloorData GetCeilingData() { return m_ceilingData; }
	void UpdateCeilingData(FloorData inputCeilingData) { m_ceilingData = inputCeilingData; }

	inline int GetWidth() { return m_width; }
	inline int GetHeight() { return m_height; }

	static std::string CreateFile(std::string fileName);

	static bool ReadFile(LMap& map, std::string fileName);

	static bool SaveFile(const LMap& map, std::string fileName);


private: // Read Only (Except From FileSystem).
	static std::string g_fileType;

	LevelArray m_lvlArray;
	FloorData m_floorData;
	FloorData m_ceilingData;

	int m_width;
	int m_height;
};

#endif // !_LMAP_H
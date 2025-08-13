#pragma once

#ifndef _PLAYER_H
#define _PLAYER_H

#include "GameObject.h"

class Player : public GameObject
{ 
private:
	float m_movementSpeed = 5;

public:
	Player(SDL_Renderer* renderer, Vector2D startPosition);
	~Player();

	void Update(float deltaTime, SDL_Event event);
	void Render();
};

#endif


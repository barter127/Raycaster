#pragma once

#ifndef _PLAYER_H
#define _PLAYER_H

#include "SDL.h"

#include "GameObject.h"
#include "Collisions.h"

class Player : public GameObject
{ 
private:
	float m_movementSpeed = 5;
	float m_rotationSpeed = 0.5f;

	void Input(float deltaTime, SDL_Event event);

public:
	Player(SDL_Renderer* renderer, Vector2D startPosition);
	~Player();

	void Update(float deltaTime, SDL_Event event);
	void Render();

	Vector2D m_direction = Vector2D(-1, 0);
	Vector2D m_plane = Vector2D(0, 0.66f); // The 2d raycaster version of camera plane.

	BoxCollider m_collider = { true, this, m_position.x, m_position.y, 1, 1 };
};

#endif


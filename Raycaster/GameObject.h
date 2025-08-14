#pragma once

#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H
#include<string>

#include "SDL.h"

#include "Vector2D.h"

class GameObject
{
protected:
	SDL_Renderer* m_renderer = nullptr;

public:
	GameObject(SDL_Renderer* renderer, Vector2D startPosition);
	~GameObject();

	// Display textures on the screen.
	virtual void Render() = 0;
	virtual void Update(float deltaTime, SDL_Event e) = 0;

	Vector2D m_position = Vector2D(0.0f, 0.0f);
};
#endif // _GAMEOBJECT_H


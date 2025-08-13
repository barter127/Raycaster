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

	// Transform

	// === Collision ===
	bool m_hasCollision = false;

	float m_collisionBoxWidth = 0.0f;
	float m_collisionBoxHeight = 0.0f;

public:
	GameObject(SDL_Renderer* renderer, Vector2D startPosition);
	~GameObject();

	// Display textures on the screen.
	virtual void Render() = 0;
	virtual void Update(float deltaTime, SDL_Event e) = 0;

	// Sets the game objects collision radius for AABB collision.
	inline void SetCollisionBox(float width, float height) { m_collisionBoxWidth = width; m_collisionBoxHeight = height; };

	// Performs checks to see if it should return texture width & height or return m_collisionBoxWidth & m_collisionBoxHeight.
	SDL_Rect GetCollisionBox();

	Vector2D m_position = Vector2D(0.0f, 0.0f);
};
#endif // _GAMEOBJECT_H

